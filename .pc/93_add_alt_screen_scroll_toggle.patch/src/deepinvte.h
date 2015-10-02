/*
 * Copyright (C) 2001,2002,2003,2009,2010 Red Hat, Inc.
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
 */

#ifndef deepinvte_deepinvte_h_included
#define deepinvte_deepinvte_h_included

#include <glib.h>
#include <gio/gio.h>
#include <pango/pango.h>
#include <gtk/gtk.h>

#define __DEEPINVTE_DEEPINVTE_H_INSIDE__ 1

#include "deepinvtepty.h"
#include "deepinvtetypebuiltins.h"
#include "deepinvteversion.h"

#undef __DEEPINVTE_DEEPINVTE_H_INSIDE__

G_BEGIN_DECLS

#ifdef DEEPINVTE_SEAL_ENABLE
#define _DEEPINVTE_SEAL(name) _deepinvte_sealed__ ## name
#else
#define _DEEPINVTE_SEAL(name) name
#endif

#ifdef DEEPINVTE_DISABLE_DEPRECATED
#define _DEEPINVTE_DEPRECATED(name) _deepinvte_deprecated__ ## name
#else
#define _DEEPINVTE_DEPRECATED(name) name
#endif

#define DEEPINVTE_TYPE_TERMINAL            (deepinvte_terminal_get_type())
#define DEEPINVTE_TERMINAL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), DEEPINVTE_TYPE_TERMINAL, DeepinvteTerminal))
#define DEEPINVTE_TERMINAL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  DEEPINVTE_TYPE_TERMINAL, DeepinvteTerminalClass))
#define DEEPINVTE_IS_TERMINAL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DEEPINVTE_TYPE_TERMINAL))
#define DEEPINVTE_IS_TERMINAL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  DEEPINVTE_TYPE_TERMINAL))
#define DEEPINVTE_TERMINAL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  DEEPINVTE_TYPE_TERMINAL, DeepinvteTerminalClass))

typedef struct _DeepinvteTerminal             DeepinvteTerminal;
typedef struct _DeepinvteTerminalPrivate      DeepinvteTerminalPrivate;
typedef struct _DeepinvteTerminalClass        DeepinvteTerminalClass;
typedef struct _DeepinvteTerminalClassPrivate DeepinvteTerminalClassPrivate;

/**
 * DeepinvteTerminal:
 *
 * All of these fields should be considered read-only and deprecated.
 */
struct _DeepinvteTerminal {
	GtkWidget widget;
        /*< private >*/
	GtkAdjustment *_DEEPINVTE_SEAL(adjustment);	/* Scrolling adjustment. */

	/* Metric and sizing data. */
	glong _DEEPINVTE_SEAL(char_width), _DEEPINVTE_SEAL(char_height);	/* dimensions of character cells */
	glong _DEEPINVTE_SEAL(char_ascent), _DEEPINVTE_SEAL(char_descent); /* important font metrics */
	glong _DEEPINVTE_SEAL(row_count), _DEEPINVTE_SEAL(column_count);	/* dimensions of the window */

	/* Titles. */
	char *_DEEPINVTE_SEAL(window_title);
	char *_DEEPINVTE_SEAL(icon_title);

	/*< private >*/
	DeepinvteTerminalPrivate *pvt;
};

/**
 * DeepinvteTerminalClass:
 *
 * All of these fields should be considered read-only, except for derived classes.
 */
struct _DeepinvteTerminalClass {
	/*< public > */
	/* Inherited parent class. */
	GtkWidgetClass parent_class;

	/*< protected > */
	/* Default signal handlers. */
	void (*eof)(DeepinvteTerminal* terminal);
	void (*child_exited)(DeepinvteTerminal* terminal);
	void (*emulation_changed)(DeepinvteTerminal* terminal);
	void (*encoding_changed)(DeepinvteTerminal* terminal);
	void (*char_size_changed)(DeepinvteTerminal* terminal, guint char_width, guint char_height);
	void (*window_title_changed)(DeepinvteTerminal* terminal);
	void (*icon_title_changed)(DeepinvteTerminal* terminal);
	void (*selection_changed)(DeepinvteTerminal* terminal);
	void (*contents_changed)(DeepinvteTerminal* terminal);
	void (*cursor_moved)(DeepinvteTerminal* terminal);
	void (*status_line_changed)(DeepinvteTerminal* terminal);
	void (*commit)(DeepinvteTerminal* terminal, const gchar *text, guint size);

	void (*deiconify_window)(DeepinvteTerminal* terminal);
	void (*iconify_window)(DeepinvteTerminal* terminal);
	void (*raise_window)(DeepinvteTerminal* terminal);
	void (*lower_window)(DeepinvteTerminal* terminal);
	void (*refresh_window)(DeepinvteTerminal* terminal);
	void (*restore_window)(DeepinvteTerminal* terminal);
	void (*maximize_window)(DeepinvteTerminal* terminal);
	void (*resize_window)(DeepinvteTerminal* terminal, guint width, guint height);
	void (*move_window)(DeepinvteTerminal* terminal, guint x, guint y);

	void (*increase_font_size)(DeepinvteTerminal* terminal);
	void (*decrease_font_size)(DeepinvteTerminal* terminal);

	void (*text_modified)(DeepinvteTerminal* terminal);
	void (*text_inserted)(DeepinvteTerminal* terminal);
	void (*text_deleted)(DeepinvteTerminal* terminal);
	void (*text_scrolled)(DeepinvteTerminal* terminal, gint delta);
	void (*copy_clipboard)(DeepinvteTerminal* terminal);
	void (*paste_clipboard)(DeepinvteTerminal* terminal);

#if !GTK_CHECK_VERSION (2, 91, 2)
	void (* set_scroll_adjustments) (GtkWidget *widget,
					 GtkAdjustment *hadjustment,
					 GtkAdjustment *vadjustment);
#endif

 	void (*beep)(DeepinvteTerminal* terminal);

#if GTK_CHECK_VERSION (2, 99, 0)
        /* Padding for future expansion. */
        gpointer padding[16];
#else
	/* Padding for future expansion. */
	void (*deepinvte_reserved3)(void);
	void (*deepinvte_reserved4)(void);

	/*< private > */
	/* Signals we might emit. */
        guint _DEEPINVTE_DEPRECATED(eof_signal);
        guint _DEEPINVTE_DEPRECATED(child_exited_signal);
        guint _DEEPINVTE_DEPRECATED(emulation_changed_signal);
        guint _DEEPINVTE_DEPRECATED(encoding_changed_signal);
        guint _DEEPINVTE_DEPRECATED(char_size_changed_signal);
        guint _DEEPINVTE_DEPRECATED(window_title_changed_signal);
        guint _DEEPINVTE_DEPRECATED(icon_title_changed_signal);
        guint _DEEPINVTE_DEPRECATED(selection_changed_signal);
        guint _DEEPINVTE_DEPRECATED(contents_changed_signal);
        guint _DEEPINVTE_DEPRECATED(cursor_moved_signal);
        guint _DEEPINVTE_DEPRECATED(status_line_changed_signal);
        guint _DEEPINVTE_DEPRECATED(commit_signal);
        guint _DEEPINVTE_DEPRECATED(deiconify_window_signal);
        guint _DEEPINVTE_DEPRECATED(iconify_window_signal);
        guint _DEEPINVTE_DEPRECATED(raise_window_signal);
        guint _DEEPINVTE_DEPRECATED(lower_window_signal);
        guint _DEEPINVTE_DEPRECATED(refresh_window_signal);
        guint _DEEPINVTE_DEPRECATED(restore_window_signal);
        guint _DEEPINVTE_DEPRECATED(maximize_window_signal);
        guint _DEEPINVTE_DEPRECATED(resize_window_signal);
        guint _DEEPINVTE_DEPRECATED(move_window_signal);
        guint _DEEPINVTE_DEPRECATED(increase_font_size_signal);
        guint _DEEPINVTE_DEPRECATED(decrease_font_size_signal);
        guint _DEEPINVTE_DEPRECATED(text_modified_signal);
        guint _DEEPINVTE_DEPRECATED(text_inserted_signal);
        guint _DEEPINVTE_DEPRECATED(text_deleted_signal);
        guint _DEEPINVTE_DEPRECATED(text_scrolled_signal);
        guint _DEEPINVTE_DEPRECATED(reserved1);
        guint _DEEPINVTE_DEPRECATED(reserved2);
        guint _DEEPINVTE_DEPRECATED(reserved3);
        guint _DEEPINVTE_DEPRECATED(reserved4);
        guint _DEEPINVTE_DEPRECATED(reserved5);
        guint _DEEPINVTE_DEPRECATED(reserved6);
#endif

#if GTK_CHECK_VERSION (2, 99, 0)
        DeepinvteTerminalClassPrivate *priv;
#endif
};

/**
 * DeepinvteTerminalEraseBinding:
 * @DEEPINVTE_ERASE_AUTO: For backspace, attempt to determine the right value from the terminal's IO settings.  For delete, use the control sequence.
 * @DEEPINVTE_ERASE_ASCII_BACKSPACE: Send an ASCII backspace character (0x08).
 * @DEEPINVTE_ERASE_ASCII_DELETE: Send an ASCII delete character (0x7F).
 * @DEEPINVTE_ERASE_DELETE_SEQUENCE: Send the "@@7" control sequence.
 * @DEEPINVTE_ERASE_TTY: Send terminal's "erase" setting.
 *
 * An enumerated type which can be used to indicate which string the terminal
 * should send to an application when the user presses the Delete or Backspace
 * keys.
 */
typedef enum {
	DEEPINVTE_ERASE_AUTO,
	DEEPINVTE_ERASE_ASCII_BACKSPACE,
	DEEPINVTE_ERASE_ASCII_DELETE,
	DEEPINVTE_ERASE_DELETE_SEQUENCE,
	DEEPINVTE_ERASE_TTY
} DeepinvteTerminalEraseBinding;

/**
 * DeepinvteTerminalCursorBlinkMode:
 * @DEEPINVTE_CURSOR_BLINK_SYSTEM: Follow GTK+ settings for cursor blinking.
 * @DEEPINVTE_CURSOR_BLINK_ON: Cursor blinks.
 * @DEEPINVTE_CURSOR_BLINK_OFF: Cursor does not blink.
 *
 * An enumerated type which can be used to indicate the cursor blink mode
 * for the terminal.
 */
typedef enum {
        DEEPINVTE_CURSOR_BLINK_SYSTEM,
        DEEPINVTE_CURSOR_BLINK_ON,
        DEEPINVTE_CURSOR_BLINK_OFF
} DeepinvteTerminalCursorBlinkMode;

/**
 * DeepinvteTerminalCursorShape:
 * @DEEPINVTE_CURSOR_SHAPE_BLOCK: Draw a block cursor.  This is the default.
 * @DEEPINVTE_CURSOR_SHAPE_IBEAM: Draw a vertical bar on the left side of character.
 * This is similar to the default cursor for other GTK+ widgets.
 * @DEEPINVTE_CURSOR_SHAPE_UNDERLINE: Draw a horizontal bar below the character.
 *
 * An enumerated type which can be used to indicate what should the terminal
 * draw at the cursor position.
 */
typedef enum {
        DEEPINVTE_CURSOR_SHAPE_BLOCK,
        DEEPINVTE_CURSOR_SHAPE_IBEAM,
        DEEPINVTE_CURSOR_SHAPE_UNDERLINE
} DeepinvteTerminalCursorShape;

/* The structure we return as the supplemental attributes for strings. */
struct _DeepinvteCharAttributes {
        /*< private >*/
	long row, column;
	GdkColor fore, back;
	guint underline:1, strikethrough:1;
};
typedef struct _DeepinvteCharAttributes DeepinvteCharAttributes;

/* The name of the same structure in the 0.10 series, for API compatibility. */
struct deepinvte_char_attributes {
        /*< private >*/
	long row, column;
	GdkColor fore, back;
	guint underline:1, strikethrough:1;
};

typedef gboolean (*DeepinvteSelectionFunc)(DeepinvteTerminal *terminal,
                                     glong column,
                                     glong row,
                                     gpointer data);

/* The widget's type. */
GType deepinvte_terminal_get_type(void);

GtkWidget *deepinvte_terminal_new(void);

DeepinvtePty *deepinvte_terminal_pty_new (DeepinvteTerminal *terminal,
                              DeepinvtePtyFlags flags,
                              GError **error);

void deepinvte_terminal_watch_child (DeepinvteTerminal *terminal,
                               GPid child_pid);

gboolean deepinvte_terminal_fork_command_full(DeepinvteTerminal *terminal,
                                        DeepinvtePtyFlags pty_flags,
                                        const char *working_directory,
                                        char **argv,
                                        char **envv,
                                        GSpawnFlags spawn_flags,
                                        GSpawnChildSetupFunc child_setup,
                                        gpointer child_setup_data,
                                        GPid *child_pid /* out */,
                                        GError **error);

/* Send data to the terminal to display, or to the terminal's forked command
 * to handle in some way.  If it's 'cat', they should be the same. */
void deepinvte_terminal_feed(DeepinvteTerminal *terminal, const char *data, glong length);
void deepinvte_terminal_feed_child(DeepinvteTerminal *terminal, const char *text, glong length);
void deepinvte_terminal_feed_child_binary(DeepinvteTerminal *terminal, const char *data, glong length);

/* Copy currently-selected text to the clipboard, or from the clipboard to
 * the terminal. */
void deepinvte_terminal_copy_clipboard(DeepinvteTerminal *terminal);
void deepinvte_terminal_paste_clipboard(DeepinvteTerminal *terminal);
void deepinvte_terminal_copy_primary(DeepinvteTerminal *terminal);
void deepinvte_terminal_paste_primary(DeepinvteTerminal *terminal);

/* simple manipulation of selection */
void deepinvte_terminal_select_all(DeepinvteTerminal *terminal);
void deepinvte_terminal_select_none(DeepinvteTerminal *terminal);

/* Set the terminal's size. */
void deepinvte_terminal_set_size(DeepinvteTerminal *terminal,
			   glong columns, glong rows);

/* Set various on-off settings. */
void deepinvte_terminal_set_audible_bell(DeepinvteTerminal *terminal, gboolean is_audible);
gboolean deepinvte_terminal_get_audible_bell(DeepinvteTerminal *terminal);
void deepinvte_terminal_set_visible_bell(DeepinvteTerminal *terminal, gboolean is_visible);
gboolean deepinvte_terminal_get_visible_bell(DeepinvteTerminal *terminal);
void deepinvte_terminal_set_scroll_background(DeepinvteTerminal *terminal, gboolean scroll);
void deepinvte_terminal_set_scroll_on_output(DeepinvteTerminal *terminal, gboolean scroll);
void deepinvte_terminal_set_scroll_on_keystroke(DeepinvteTerminal *terminal,
					  gboolean scroll);

/* Set the color scheme. */
void deepinvte_terminal_set_color_dim(DeepinvteTerminal *terminal,
				const GdkColor *dim);
void deepinvte_terminal_set_color_bold(DeepinvteTerminal *terminal,
				 const GdkColor *bold);
void deepinvte_terminal_set_color_foreground(DeepinvteTerminal *terminal,
				       const GdkColor *foreground);
void deepinvte_terminal_set_color_background(DeepinvteTerminal *terminal,
				       const GdkColor *background);
void deepinvte_terminal_set_color_cursor(DeepinvteTerminal *terminal,
				   const GdkColor *cursor_background);
void deepinvte_terminal_set_color_highlight(DeepinvteTerminal *terminal,
				      const GdkColor *highlight_background);
void deepinvte_terminal_set_colors(DeepinvteTerminal *terminal,
			     const GdkColor *foreground,
			     const GdkColor *background,
			     const GdkColor *palette,
			     glong palette_size);

#if GTK_CHECK_VERSION (2, 99, 0)
void deepinvte_terminal_set_color_bold_rgba(DeepinvteTerminal *terminal,
                                      const GdkRGBA *bold);
void deepinvte_terminal_set_color_dim_rgba(DeepinvteTerminal *terminal,
	                             const GdkRGBA *dim);
void deepinvte_terminal_set_color_foreground_rgba(DeepinvteTerminal *terminal,
					    const GdkRGBA *foreground);
void deepinvte_terminal_set_color_background_rgba(DeepinvteTerminal *terminal,
					    const GdkRGBA *background);
void deepinvte_terminal_set_color_cursor_rgba(DeepinvteTerminal *terminal,
					const GdkRGBA *cursor_background);
void deepinvte_terminal_set_color_highlight_rgba(DeepinvteTerminal *terminal,
					   const GdkRGBA *highlight_background);
void deepinvte_terminal_set_colors_rgba(DeepinvteTerminal *terminal,
				  const GdkRGBA *foreground,
				  const GdkRGBA *background,
				  const GdkRGBA *palette,
				  gsize palette_size);
#endif

void deepinvte_terminal_set_default_colors(DeepinvteTerminal *terminal);

/* Background effects. */
void deepinvte_terminal_set_background_image(DeepinvteTerminal *terminal, GdkPixbuf *image);
void deepinvte_terminal_set_background_image_file(DeepinvteTerminal *terminal,
					    const char *path);
void deepinvte_terminal_set_background_tint_color(DeepinvteTerminal *terminal,
					    const GdkColor *color);
void deepinvte_terminal_set_background_saturation(DeepinvteTerminal *terminal,
					    double saturation);
void deepinvte_terminal_set_background_transparent(DeepinvteTerminal *terminal,
					     gboolean transparent);
void deepinvte_terminal_set_opacity(DeepinvteTerminal *terminal, guint16 opacity);

/* Set whether or not the cursor blinks. */
void deepinvte_terminal_set_cursor_blink_mode(DeepinvteTerminal *terminal,
					DeepinvteTerminalCursorBlinkMode mode);
DeepinvteTerminalCursorBlinkMode deepinvte_terminal_get_cursor_blink_mode(DeepinvteTerminal *terminal);

/* Set cursor shape */
void deepinvte_terminal_set_cursor_shape(DeepinvteTerminal *terminal,
				   DeepinvteTerminalCursorShape shape);
DeepinvteTerminalCursorShape deepinvte_terminal_get_cursor_shape(DeepinvteTerminal *terminal);

/* Set the number of scrollback lines, above or at an internal minimum. */
void deepinvte_terminal_set_scrollback_lines(DeepinvteTerminal *terminal, glong lines);

/* Append the input method menu items to a given shell. */
void deepinvte_terminal_im_append_menuitems(DeepinvteTerminal *terminal,
				      GtkMenuShell *menushell);

/* Set or retrieve the current font. */
void deepinvte_terminal_set_font(DeepinvteTerminal *terminal,
			   const PangoFontDescription *font_desc);
void deepinvte_terminal_set_font_from_string(DeepinvteTerminal *terminal, const char *name);
const PangoFontDescription *deepinvte_terminal_get_font(DeepinvteTerminal *terminal);
void deepinvte_terminal_set_allow_bold(DeepinvteTerminal *terminal, gboolean allow_bold);
gboolean deepinvte_terminal_get_allow_bold(DeepinvteTerminal *terminal);

/* Check if the terminal is the current selection owner. */
gboolean deepinvte_terminal_get_has_selection(DeepinvteTerminal *terminal);

/* Set the list of word chars, optionally using hyphens to specify ranges
 * (to get a hyphen, place it first), and check if a character is in the
 * range. */
void deepinvte_terminal_set_word_chars(DeepinvteTerminal *terminal, const char *spec);
gboolean deepinvte_terminal_is_word_char(DeepinvteTerminal *terminal, gunichar c);

/* Set what happens when the user strikes backspace or delete. */
void deepinvte_terminal_set_backspace_binding(DeepinvteTerminal *terminal,
					DeepinvteTerminalEraseBinding binding);
void deepinvte_terminal_set_delete_binding(DeepinvteTerminal *terminal,
				     DeepinvteTerminalEraseBinding binding);

/* Manipulate the autohide setting. */
void deepinvte_terminal_set_mouse_autohide(DeepinvteTerminal *terminal, gboolean setting);
gboolean deepinvte_terminal_get_mouse_autohide(DeepinvteTerminal *terminal);

/* Reset the terminal, optionally clearing the tab stops and line history. */
void deepinvte_terminal_reset(DeepinvteTerminal *terminal,
                        gboolean clear_tabstops,
			gboolean clear_history);

/* Read the contents of the terminal, using a callback function to determine
 * if a particular location on the screen (0-based) is interesting enough to
 * include.  Each byte in the returned string will have a corresponding
 * DeepinvteCharAttributes structure in the passed GArray, if the array was not %NULL.
 * Note that it will have one entry per byte, not per character, so indexes
 * should match up exactly. */
char *deepinvte_terminal_get_text(DeepinvteTerminal *terminal,
			    DeepinvteSelectionFunc is_selected,
			    gpointer user_data,
			    GArray *attributes);
char *deepinvte_terminal_get_text_include_trailing_spaces(DeepinvteTerminal *terminal,
						    DeepinvteSelectionFunc is_selected,
						    gpointer user_data,
						    GArray *attributes);
char *deepinvte_terminal_get_text_range(DeepinvteTerminal *terminal,
				  glong start_row, glong start_col,
				  glong end_row, glong end_col,
				  DeepinvteSelectionFunc is_selected,
				  gpointer user_data,
				  GArray *attributes);
void deepinvte_terminal_get_cursor_position(DeepinvteTerminal *terminal,
				      glong *column, glong *row);
/* Display string matching:  clear all matching expressions. */
void deepinvte_terminal_match_clear_all(DeepinvteTerminal *terminal);

/* Add a matching expression, returning the tag the widget assigns to that
 * expression. */
int deepinvte_terminal_match_add_gregex(DeepinvteTerminal *terminal, GRegex *regex, GRegexMatchFlags flags);
/* Set the cursor to be used when the pointer is over a given match. */
void deepinvte_terminal_match_set_cursor(DeepinvteTerminal *terminal, int tag,
				   GdkCursor *cursor);
void deepinvte_terminal_match_set_cursor_type(DeepinvteTerminal *terminal,
					int tag, GdkCursorType cursor_type);
void deepinvte_terminal_match_set_cursor_name(DeepinvteTerminal *terminal,
					int tag, const char *cursor_name);
/* Remove a matching expression by tag. */
void deepinvte_terminal_match_remove(DeepinvteTerminal *terminal, int tag);

/* Check if a given cell on the screen contains part of a matched string.  If
 * it does, return the string, and store the match tag in the optional tag
 * argument. */
char *deepinvte_terminal_match_check(DeepinvteTerminal *terminal,
			       glong column, glong row,
			       int *tag);

void      deepinvte_terminal_search_set_gregex      (DeepinvteTerminal *terminal,
					       GRegex      *regex);
GRegex   *deepinvte_terminal_search_get_gregex      (DeepinvteTerminal *terminal);
void      deepinvte_terminal_search_set_wrap_around (DeepinvteTerminal *terminal,
					       gboolean     wrap_around);
gboolean  deepinvte_terminal_search_get_wrap_around (DeepinvteTerminal *terminal);
gboolean  deepinvte_terminal_search_find_previous   (DeepinvteTerminal *terminal);
gboolean  deepinvte_terminal_search_find_next       (DeepinvteTerminal *terminal);


/* Set the emulation type.  Most of the time you won't need this. */
void deepinvte_terminal_set_emulation(DeepinvteTerminal *terminal, const char *emulation);
const char *deepinvte_terminal_get_emulation(DeepinvteTerminal *terminal);
const char *deepinvte_terminal_get_default_emulation(DeepinvteTerminal *terminal);

/* Set the character encoding.  Most of the time you won't need this. */
void deepinvte_terminal_set_encoding(DeepinvteTerminal *terminal, const char *codeset);
const char *deepinvte_terminal_get_encoding(DeepinvteTerminal *terminal);

/* Get the contents of the status line. */
const char *deepinvte_terminal_get_status_line(DeepinvteTerminal *terminal);

void deepinvte_terminal_set_pty_object(DeepinvteTerminal *terminal, DeepinvtePty *pty);
DeepinvtePty *deepinvte_terminal_get_pty_object(DeepinvteTerminal *terminal);

char *deepinvte_get_user_shell (void);

/* Accessors for bindings. */
#if !GTK_CHECK_VERSION (2, 91, 2)
GtkAdjustment *deepinvte_terminal_get_adjustment(DeepinvteTerminal *terminal);
#endif

glong deepinvte_terminal_get_char_width(DeepinvteTerminal *terminal);
glong deepinvte_terminal_get_char_height(DeepinvteTerminal *terminal);
glong deepinvte_terminal_get_row_count(DeepinvteTerminal *terminal);
glong deepinvte_terminal_get_column_count(DeepinvteTerminal *terminal);
const char *deepinvte_terminal_get_window_title(DeepinvteTerminal *terminal);
const char *deepinvte_terminal_get_icon_title(DeepinvteTerminal *terminal);

int deepinvte_terminal_get_child_exit_status(DeepinvteTerminal *terminal);


/* Writing contents out */

/**
 * DeepinvteTerminalWriteFlags:
 * @DEEPINVTE_TERMINAL_WRITE_DEFAULT: Write contents as UTF-8 text.  This is the default.
 *
 * A flag type to determine how terminal contents should be written
 * to an output stream.
 */
typedef enum {
  DEEPINVTE_TERMINAL_WRITE_DEFAULT = 0
} DeepinvteTerminalWriteFlags;

gboolean deepinvte_terminal_write_contents (DeepinvteTerminal *terminal,
				      GOutputStream *stream,
				      DeepinvteTerminalWriteFlags flags,
				      GCancellable *cancellable,
				      GError **error);

#undef _DEEPINVTE_SEAL
#undef _DEEPINVTE_DEPRECATED

G_END_DECLS

#ifndef DEEPINVTE_DISABLE_DEPRECATED
#define __DEEPINVTE_DEEPINVTE_H_INSIDE__ 1
#include "deepinvtedeprecated.h"
#undef __DEEPINVTE_DEEPINVTE_H_INSIDE__
#endif /* DEEPINVTE_DISABLE_DEPRECATED */

#endif
