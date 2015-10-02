
/* Generated data (by glib-mkenums) */

#include "deepinvte.h"

/* enumerations from "deepinvte.h" */
GType
deepinvte_terminal_erase_binding_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { DEEPINVTE_ERASE_AUTO, "DEEPINVTE_ERASE_AUTO", "auto" },
      { DEEPINVTE_ERASE_ASCII_BACKSPACE, "DEEPINVTE_ERASE_ASCII_BACKSPACE", "ascii-backspace" },
      { DEEPINVTE_ERASE_ASCII_DELETE, "DEEPINVTE_ERASE_ASCII_DELETE", "ascii-delete" },
      { DEEPINVTE_ERASE_DELETE_SEQUENCE, "DEEPINVTE_ERASE_DELETE_SEQUENCE", "delete-sequence" },
      { DEEPINVTE_ERASE_TTY, "DEEPINVTE_ERASE_TTY", "tty" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = \
       g_enum_register_static (g_intern_static_string ("DeepinvteTerminalEraseBinding"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
deepinvte_terminal_cursor_blink_mode_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { DEEPINVTE_CURSOR_BLINK_SYSTEM, "DEEPINVTE_CURSOR_BLINK_SYSTEM", "system" },
      { DEEPINVTE_CURSOR_BLINK_ON, "DEEPINVTE_CURSOR_BLINK_ON", "on" },
      { DEEPINVTE_CURSOR_BLINK_OFF, "DEEPINVTE_CURSOR_BLINK_OFF", "off" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = \
       g_enum_register_static (g_intern_static_string ("DeepinvteTerminalCursorBlinkMode"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
deepinvte_terminal_cursor_shape_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { DEEPINVTE_CURSOR_SHAPE_BLOCK, "DEEPINVTE_CURSOR_SHAPE_BLOCK", "block" },
      { DEEPINVTE_CURSOR_SHAPE_IBEAM, "DEEPINVTE_CURSOR_SHAPE_IBEAM", "ibeam" },
      { DEEPINVTE_CURSOR_SHAPE_UNDERLINE, "DEEPINVTE_CURSOR_SHAPE_UNDERLINE", "underline" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = \
       g_enum_register_static (g_intern_static_string ("DeepinvteTerminalCursorShape"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
deepinvte_terminal_write_flags_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { DEEPINVTE_TERMINAL_WRITE_DEFAULT, "DEEPINVTE_TERMINAL_WRITE_DEFAULT", "default" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = \
       g_enum_register_static (g_intern_static_string ("DeepinvteTerminalWriteFlags"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

/* enumerations from "deepinvtepty.h" */
GType
deepinvte_pty_flags_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GFlagsValue values[] = {
      { DEEPINVTE_PTY_NO_LASTLOG, "DEEPINVTE_PTY_NO_LASTLOG", "no-lastlog" },
      { DEEPINVTE_PTY_NO_UTMP, "DEEPINVTE_PTY_NO_UTMP", "no-utmp" },
      { DEEPINVTE_PTY_NO_WTMP, "DEEPINVTE_PTY_NO_WTMP", "no-wtmp" },
      { DEEPINVTE_PTY_NO_HELPER, "DEEPINVTE_PTY_NO_HELPER", "no-helper" },
      { DEEPINVTE_PTY_NO_FALLBACK, "DEEPINVTE_PTY_NO_FALLBACK", "no-fallback" },
      { DEEPINVTE_PTY_DEFAULT, "DEEPINVTE_PTY_DEFAULT", "default" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = \
       g_flags_register_static (g_intern_static_string ("DeepinvtePtyFlags"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

GType
deepinvte_pty_error_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { DEEPINVTE_PTY_ERROR_PTY_HELPER_FAILED, "DEEPINVTE_PTY_ERROR_PTY_HELPER_FAILED", "pty-helper-failed" },
      { DEEPINVTE_PTY_ERROR_PTY98_FAILED, "DEEPINVTE_PTY_ERROR_PTY98_FAILED", "pty98-failed" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = \
       g_enum_register_static (g_intern_static_string ("DeepinvtePtyError"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}

/* enumerations from "deepinvtedeprecated.h" */
GType
deepinvte_terminal_anti_alias_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
 
  if (g_once_init_enter (&g_define_type_id__volatile)) {
    static const GEnumValue values[] = {
      { DEEPINVTE_ANTI_ALIAS_USE_DEFAULT, "DEEPINVTE_ANTI_ALIAS_USE_DEFAULT", "use-default" },
      { DEEPINVTE_ANTI_ALIAS_FORCE_ENABLE, "DEEPINVTE_ANTI_ALIAS_FORCE_ENABLE", "force-enable" },
      { DEEPINVTE_ANTI_ALIAS_FORCE_DISABLE, "DEEPINVTE_ANTI_ALIAS_FORCE_DISABLE", "force-disable" },
      { 0, NULL, NULL }
    };
    GType g_define_type_id = \
       g_enum_register_static (g_intern_static_string ("DeepinvteTerminalAntiAlias"), values);
      
    g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
  }
    
  return g_define_type_id__volatile;
}



/* Generated data ends here */

