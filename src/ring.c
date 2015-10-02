/*
 * Copyright (C) 2002,2009,2010 Red Hat, Inc.
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Red Hat Author(s): Nalin Dahyabhai, Behdad Esfahbod
 */

#include <config.h>

#include "debug.h"
#include "ring.h"

#include <string.h>

/*
 * DeepinvteRing: A buffer ring
 */

#ifdef DEEPINVTE_DEBUG
static void
_deepinvte_ring_validate (DeepinvteRing * ring)
{
	g_assert(ring != NULL);
	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING,
			" Delta = %lu, Length = %lu, Max = %lu, Writable = %lu.\n",
			ring->start, ring->end - ring->start,
			ring->max, ring->end - ring->writable);

	g_assert (ring->start <= ring->writable);
	g_assert (ring->writable <= ring->end);

	g_assert (ring->end - ring->start <= ring->max);
	g_assert (ring->end - ring->writable <= ring->mask);
}
#else
#define _deepinvte_ring_validate(ring) G_STMT_START {} G_STMT_END
#endif

static void
_deepinvte_ring_ensure_stream (DeepinvteRing *ring)
{
	if (G_LIKELY(ring->attr_stream))
		return;

	if (ring->max >= G_MAXLONG) {
		/* "Infinite" scroll-back buffer limit, file-backed. */
		ring->attr_stream = _deepinvte_file_stream_new ();
		ring->text_stream = _deepinvte_file_stream_new ();
		ring->row_stream = _deepinvte_file_stream_new ();
	} else {
		/* Predefined scroll-back buffer limit, memory-backed. */
		ring->attr_stream = _deepinvte_mem_stream_new ();
		ring->text_stream = _deepinvte_mem_stream_new ();
		ring->row_stream = _deepinvte_mem_stream_new ();
	}
}


void
_deepinvte_ring_init (DeepinvteRing *ring, gulong max_rows)
{
	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "New ring %p.\n", ring);

	memset (ring, 0, sizeof (*ring));

	ring->max = MAX (max_rows, 3);

	ring->mask = 31;
	ring->array = g_malloc0 (sizeof (ring->array[0]) * (ring->mask + 1));

	ring->last_attr.text_offset = 0;
	ring->last_attr.attr.i = basic_cell.i.attr;
	ring->utf8_buffer = g_string_sized_new (128);

	_deepinvte_row_data_init (&ring->cached_row);
	ring->cached_row_num = (gulong) -1;

	_deepinvte_ring_validate(ring);
}

void
_deepinvte_ring_fini (DeepinvteRing *ring)
{
	gulong i;

	_deepinvte_ring_ensure_stream (ring);

	for (i = 0; i <= ring->mask; i++)
		_deepinvte_row_data_fini (&ring->array[i]);

	g_free (ring->array);

	g_object_unref (ring->attr_stream);
	g_object_unref (ring->text_stream);
	g_object_unref (ring->row_stream);

	g_string_free (ring->utf8_buffer, TRUE);

	_deepinvte_row_data_fini (&ring->cached_row);
}

typedef struct _DeepinvteRowRecord {
	gsize text_offset;
	gsize attr_offset;
} DeepinvteRowRecord;

static gboolean
_deepinvte_ring_read_row_record (DeepinvteRing *ring, DeepinvteRowRecord *record, gulong position)
{
	_deepinvte_ring_ensure_stream (ring);
	return _deepinvte_stream_read (ring->row_stream, position * sizeof (*record), (char *) record, sizeof (*record));
}

static void
_deepinvte_ring_append_row_record (DeepinvteRing *ring, const DeepinvteRowRecord *record, gulong position)
{
	_deepinvte_ring_ensure_stream (ring);
	_deepinvte_stream_append (ring->row_stream, (const char *) record, sizeof (*record));
}

static void
_deepinvte_ring_freeze_row (DeepinvteRing *ring, gulong position, const DeepinvteRowData *row)
{
	DeepinvteRowRecord record;
	DeepinvteCell *cell;
	GString *buffer = ring->utf8_buffer;
	int i;

	_deepinvte_debug_print (DEEPINVTE_DEBUG_RING, "Freezing row %lu.\n", position);
	_deepinvte_ring_ensure_stream (ring);

	record.text_offset = _deepinvte_stream_head (ring->text_stream);
	record.attr_offset = _deepinvte_stream_head (ring->attr_stream);

	g_string_set_size (buffer, 0);
	for (i = 0, cell = row->cells; i < row->len; i++, cell++) {
		DeepinvteIntCellAttr attr;
		int num_chars;

		/* Attr storage:
		 *
		 * 1. We don't store attrs for fragments.  They can be
		 * reconstructed using the columns of their start cell.
		 *
		 * 2. We store one attr per deepinvteunistr character starting
		 * from the second character, with columns=0.
		 *
		 * That's enough to reconstruct the attrs, and to store
		 * the text in real UTF-8.
		 */
		attr.s = cell->attr;
		if (G_LIKELY (!attr.s.fragment)) {

			if (ring->last_attr.attr.i != attr.i) {
				ring->last_attr.text_offset = record.text_offset + buffer->len;
				_deepinvte_stream_append (ring->attr_stream, (const char *) &ring->last_attr, sizeof (ring->last_attr));
				if (!buffer->len)
					/* This row doesn't use last_attr, adjust */
					record.attr_offset += sizeof (ring->last_attr);
				ring->last_attr.attr = attr;
			}

			num_chars = _deepinvte_unistr_strlen (cell->c);
			if (num_chars > 1) {
				attr.s.columns = 0;
				ring->last_attr.text_offset = record.text_offset + buffer->len
							    + g_unichar_to_utf8 (_deepinvte_unistr_get_base (cell->c), NULL);
				_deepinvte_stream_append (ring->attr_stream, (const char *) &ring->last_attr, sizeof (ring->last_attr));
				ring->last_attr.attr = attr;
			}

			_deepinvte_unistr_append_to_string (cell->c, buffer);
		}
	}
	if (!row->attr.soft_wrapped)
		g_string_append_c (buffer, '\n');

	_deepinvte_stream_append (ring->text_stream, buffer->str, buffer->len);
	_deepinvte_ring_append_row_record (ring, &record, position);
}

static void
_deepinvte_ring_thaw_row (DeepinvteRing *ring, gulong position, DeepinvteRowData *row, gboolean do_truncate)
{
	DeepinvteRowRecord records[2], record;
	DeepinvteIntCellAttr attr;
	DeepinvteCellAttrChange attr_change;
	DeepinvteCell cell;
	const char *p, *q, *end;
	GString *buffer = ring->utf8_buffer;

	_deepinvte_debug_print (DEEPINVTE_DEBUG_RING, "Thawing row %lu.\n", position);
	_deepinvte_ring_ensure_stream (ring);

	_deepinvte_row_data_clear (row);

	attr_change.text_offset = 0;

	if (!_deepinvte_ring_read_row_record (ring, &records[0], position))
		return;
	if ((position + 1) * sizeof (records[0]) < _deepinvte_stream_head (ring->row_stream)) {
		if (!_deepinvte_ring_read_row_record (ring, &records[1], position + 1))
			return;
	} else
		records[1].text_offset = _deepinvte_stream_head (ring->text_stream);

	g_string_set_size (buffer, records[1].text_offset - records[0].text_offset);
	if (!_deepinvte_stream_read (ring->text_stream, records[0].text_offset, buffer->str, buffer->len))
		return;

	record = records[0];

	if (G_LIKELY (buffer->len && buffer->str[buffer->len - 1] == '\n'))
		buffer->len--;
	else
		row->attr.soft_wrapped = TRUE;

	p = buffer->str;
	end = p + buffer->len;
	while (p < end) {

		if (record.text_offset >= ring->last_attr.text_offset) {
			attr = ring->last_attr.attr;
		} else {
			if (record.text_offset >= attr_change.text_offset) {
				if (!_deepinvte_stream_read (ring->attr_stream, record.attr_offset, (char *) &attr_change, sizeof (attr_change)))
					return;
				record.attr_offset += sizeof (attr_change);
			}
			attr = attr_change.attr;
		}

		cell.attr = attr.s;
		cell.c = g_utf8_get_char (p);

		q = g_utf8_next_char (p);
		record.text_offset += q - p;
		p = q;

		if (G_UNLIKELY (cell.attr.columns == 0)) {
			if (G_LIKELY (row->len)) {
				/* Combine it */
				row->cells[row->len - 1].c = _deepinvte_unistr_append_unichar (row->cells[row->len - 1].c, cell.c);
			} else {
				cell.attr.columns = 1;
				_deepinvte_row_data_append (row, &cell);
			}
		} else {
			_deepinvte_row_data_append (row, &cell);
			if (cell.attr.columns > 1) {
				/* Add the fragments */
				int i, columns = cell.attr.columns;
				cell.attr.fragment = 1;
				cell.attr.columns = 1;
				for (i = 1; i < columns; i++)
					_deepinvte_row_data_append (row, &cell);
			}
		}
	}

	if (do_truncate) {
		if (records[0].text_offset < ring->last_attr.text_offset)
			if (!_deepinvte_stream_read (ring->attr_stream, records[0].attr_offset, (char *) &ring->last_attr, sizeof (ring->last_attr))) {
				ring->last_attr.text_offset = 0;
				ring->last_attr.attr.i = basic_cell.i.attr;
			}
		_deepinvte_stream_truncate (ring->row_stream, position * sizeof (record));
		_deepinvte_stream_truncate (ring->attr_stream, records[0].attr_offset);
		_deepinvte_stream_truncate (ring->text_stream, records[0].text_offset);
	}
}

static void
_deepinvte_ring_reset_streams (DeepinvteRing *ring, gulong position)
{
	_deepinvte_debug_print (DEEPINVTE_DEBUG_RING, "Reseting streams to %lu.\n", position);
	_deepinvte_ring_ensure_stream (ring);

	_deepinvte_stream_reset (ring->row_stream, position * sizeof (DeepinvteRowRecord));
	_deepinvte_stream_reset (ring->text_stream, 0);
	_deepinvte_stream_reset (ring->attr_stream, 0);

	ring->last_attr.text_offset = 0;
	ring->last_attr.attr.i = basic_cell.i.attr;

	ring->last_page = position;
}

static void
_deepinvte_ring_new_page (DeepinvteRing *ring)
{
	_deepinvte_debug_print (DEEPINVTE_DEBUG_RING, "Starting new stream page at %lu.\n", ring->writable);
	_deepinvte_ring_ensure_stream (ring);

	_deepinvte_stream_new_page (ring->attr_stream);
	_deepinvte_stream_new_page (ring->text_stream);
	_deepinvte_stream_new_page (ring->row_stream);

	ring->last_page = ring->writable;
}



static inline DeepinvteRowData *
_deepinvte_ring_writable_index (DeepinvteRing *ring, gulong position)
{
	return &ring->array[position & ring->mask];
}

const DeepinvteRowData *
_deepinvte_ring_index (DeepinvteRing *ring, gulong position)
{
	if (G_LIKELY (position >= ring->writable))
		return _deepinvte_ring_writable_index (ring, position);

	if (ring->cached_row_num != position) {
		_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "Caching row %lu.\n", position);
		_deepinvte_ring_thaw_row (ring, position, &ring->cached_row, FALSE);
		ring->cached_row_num = position;
	}

	return &ring->cached_row;
}

static void _deepinvte_ring_ensure_writable (DeepinvteRing *ring, gulong position);
static void _deepinvte_ring_ensure_writable_room (DeepinvteRing *ring);

DeepinvteRowData *
_deepinvte_ring_index_writable (DeepinvteRing *ring, gulong position)
{
	_deepinvte_ring_ensure_writable (ring, position);
	return _deepinvte_ring_writable_index (ring, position);
}

static void
_deepinvte_ring_freeze_one_row (DeepinvteRing *ring)
{
	DeepinvteRowData *row;

	if (G_UNLIKELY (ring->writable == ring->start))
		_deepinvte_ring_reset_streams (ring, ring->writable);

	row = _deepinvte_ring_writable_index (ring, ring->writable);
	_deepinvte_ring_freeze_row (ring, ring->writable, row);

	ring->writable++;

	if (G_UNLIKELY (ring->writable == ring->last_page || ring->writable - ring->last_page >= ring->max))
		_deepinvte_ring_new_page (ring);
}

static void
_deepinvte_ring_thaw_one_row (DeepinvteRing *ring)
{
	DeepinvteRowData *row;

	g_assert (ring->start < ring->writable);

	_deepinvte_ring_ensure_writable_room (ring);

	ring->writable--;

	if (ring->writable == ring->cached_row_num)
		ring->cached_row_num = (gulong) -1; /* Invalidate cached row */

	row = _deepinvte_ring_writable_index (ring, ring->writable);

	_deepinvte_ring_thaw_row (ring, ring->writable, row, TRUE);
}

static void
_deepinvte_ring_discard_one_row (DeepinvteRing *ring)
{
	ring->start++;
	if (G_UNLIKELY (ring->start == ring->writable)) {
		_deepinvte_ring_reset_streams (ring, 0);
	}
	if (ring->start > ring->writable)
		ring->writable = ring->start;
}

static void
_deepinvte_ring_maybe_freeze_one_row (DeepinvteRing *ring)
{
	if (G_LIKELY (ring->writable + ring->mask == ring->end))
		_deepinvte_ring_freeze_one_row (ring);
}

static void
_deepinvte_ring_maybe_discard_one_row (DeepinvteRing *ring)
{
	if ((gulong) _deepinvte_ring_length (ring) == ring->max)
		_deepinvte_ring_discard_one_row (ring);
}

static void
_deepinvte_ring_ensure_writable_room (DeepinvteRing *ring)
{
	gulong new_mask, old_mask, i, end;
	DeepinvteRowData *old_array, *new_array;;

	if (G_LIKELY (ring->writable + ring->mask > ring->end))
		return;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "Enlarging writable array.\n");

	old_mask = ring->mask;
	old_array = ring->array;

	ring->mask = (ring->mask << 1) + 1;
	ring->array = g_malloc0 (sizeof (ring->array[0]) * (ring->mask + 1));

	new_mask = ring->mask;
	new_array = ring->array;

	end = ring->writable + old_mask + 1;
	for (i = ring->writable; i < end; i++)
		new_array[i & new_mask] = old_array[i & old_mask];

	g_free (old_array);
}

static void
_deepinvte_ring_ensure_writable (DeepinvteRing *ring, gulong position)
{
	if (G_LIKELY (position >= ring->writable))
		return;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "Ensure writable %lu.\n", position);

	while (position < ring->writable)
		_deepinvte_ring_thaw_one_row (ring);
}

/**
 * _deepinvte_ring_resize:
 * @ring: a #DeepinvteRing
 * @max_rows: new maximum numbers of rows in the ring
 *
 * Changes the number of lines the ring can contain.
 */
void
_deepinvte_ring_resize (DeepinvteRing *ring, gulong max_rows)
{
	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "Resizing to %lu.\n", max_rows);
	_deepinvte_ring_validate(ring);

	/* Adjust the start of tail chunk now */
	if ((gulong) _deepinvte_ring_length (ring) > max_rows) {
		ring->start = ring->end - max_rows;
		if (ring->start >= ring->writable) {
			_deepinvte_ring_reset_streams (ring, 0);
			ring->writable = ring->start;
		}
	}

	ring->max = max_rows;
}

void
_deepinvte_ring_shrink (DeepinvteRing *ring, gulong max_len)
{
	if ((gulong) _deepinvte_ring_length (ring) <= max_len)
		return;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "Shrinking to %lu.\n", max_len);
	_deepinvte_ring_validate(ring);

	if (ring->writable - ring->start <= max_len)
		ring->end = ring->start + max_len;
	else {
		while (ring->writable - ring->start > max_len) {
			_deepinvte_ring_ensure_writable (ring, ring->writable - 1);
			ring->end = ring->writable;
		}
	}

	/* TODO May want to shrink down ring->array */

	_deepinvte_ring_validate(ring);
}

/**
 * _deepinvte_ring_insert_internal:
 * @ring: a #DeepinvteRing
 * @position: an index
 *
 * Inserts a new, empty, row into @ring at the @position'th offset.
 * The item at that position and any items after that are shifted down.
 *
 * Return: the newly added row.
 */
DeepinvteRowData *
_deepinvte_ring_insert (DeepinvteRing *ring, gulong position)
{
	gulong i;
	DeepinvteRowData *row, tmp;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "Inserting at position %lu.\n", position);
	_deepinvte_ring_validate(ring);

	_deepinvte_ring_maybe_discard_one_row (ring);

	_deepinvte_ring_ensure_writable (ring, position);
	_deepinvte_ring_ensure_writable_room (ring);

	g_assert (position >= ring->writable && position <= ring->end);

	tmp = *_deepinvte_ring_writable_index (ring, ring->end);
	for (i = ring->end; i > position; i--)
		*_deepinvte_ring_writable_index (ring, i) = *_deepinvte_ring_writable_index (ring, i - 1);
	*_deepinvte_ring_writable_index (ring, position) = tmp;

	row = _deepinvte_ring_writable_index (ring, position);
	_deepinvte_row_data_clear (row);
	ring->end++;

	_deepinvte_ring_maybe_freeze_one_row (ring);

	_deepinvte_ring_validate(ring);
	return row;
}

/**
 * _deepinvte_ring_remove:
 * @ring: a #DeepinvteRing
 * @position: an index
 *
 * Removes the @position'th item from @ring.
 */
void
_deepinvte_ring_remove (DeepinvteRing * ring, gulong position)
{
	gulong i;
	DeepinvteRowData tmp;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "Removing item at position %lu.\n", position);
	_deepinvte_ring_validate(ring);

	if (G_UNLIKELY (!_deepinvte_ring_contains (ring, position)))
		return;

	_deepinvte_ring_ensure_writable (ring, position);

	tmp = *_deepinvte_ring_writable_index (ring, position);
	for (i = position; i < ring->end - 1; i++)
		*_deepinvte_ring_writable_index (ring, i) = *_deepinvte_ring_writable_index (ring, i + 1);
	*_deepinvte_ring_writable_index (ring, ring->end - 1) = tmp;

	if (ring->end > ring->writable)
		ring->end--;

	_deepinvte_ring_validate(ring);
}


/**
 * _deepinvte_ring_append:
 * @ring: a #DeepinvteRing
 * @data: the new item
 *
 * Appends a new item to the ring.
 *
 * Return: the newly added row.
 */
DeepinvteRowData *
_deepinvte_ring_append (DeepinvteRing * ring)
{
	return _deepinvte_ring_insert (ring, _deepinvte_ring_next (ring));
}


static gboolean
_deepinvte_ring_write_row (DeepinvteRing *ring,
		     GOutputStream *stream,
		     DeepinvteRowData *row,
		     DeepinvteTerminalWriteFlags flags,
		     GCancellable *cancellable,
		     GError **error)
{
	DeepinvteCell *cell;
	GString *buffer = ring->utf8_buffer;
	int i;
	gsize bytes_written;

	/* Simple version of the loop in _deepinvte_ring_freeze_row().
	 * TODO Should unify one day */
	g_string_set_size (buffer, 0);
	for (i = 0, cell = row->cells; i < row->len; i++, cell++) {
		if (G_LIKELY (!cell->attr.fragment))
			_deepinvte_unistr_append_to_string (cell->c, buffer);
	}
	if (!row->attr.soft_wrapped)
		g_string_append_c (buffer, '\n');

	return g_output_stream_write_all (stream, buffer->str, buffer->len, &bytes_written, cancellable, error);
}

/**
 * _deepinvte_ring_write_contents:
 * @ring: a #DeepinvteRing
 * @stream: a #GOutputStream to write to
 * @flags: a set of #DeepinvteTerminalWriteFlags
 * @cancellable: optional #GCancellable object, %NULL to ignore
 * @error: a #GError location to store the error occuring, or %NULL to ignore
 *
 * Write entire ring contents to @stream according to @flags.
 *
 * Return: %TRUE on success, %FALSE if there was an error
 */
gboolean
_deepinvte_ring_write_contents (DeepinvteRing *ring,
			  GOutputStream *stream,
			  DeepinvteTerminalWriteFlags flags,
			  GCancellable *cancellable,
			  GError **error)
{
	gulong i;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_RING, "Writing contents to GOutputStream.\n");
	_deepinvte_ring_ensure_stream (ring);

	if (ring->start < ring->writable) {
		DeepinvteRowRecord record;
		/* XXX what to do in case of error? */
		if (_deepinvte_ring_read_row_record (ring, &record, ring->start)) {
			if (!_deepinvte_stream_write_contents (ring->text_stream, stream,
							 record.text_offset,
							 cancellable, error))
				return FALSE;
		}
	}

	for (i = ring->writable; i < ring->end; i++) {
		if (!_deepinvte_ring_write_row (ring, stream,
					  _deepinvte_ring_writable_index (ring, i),
					  flags, cancellable, error))
			return FALSE;
	}

	return TRUE;
}
