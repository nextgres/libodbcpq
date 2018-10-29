/* ========================================================================= **
**                       ____                                    __          **
**            ____  ____/ / /_  _________ ___  __  ___________ _/ /          **
**           / __ \/ __  / __ \/ ___/ __ `__ \/ / / / ___/ __ `/ /           **
**          / /_/ / /_/ / /_/ / /__/ / / / / / /_/ (__  ) /_/ / /            **
**          \____/\__,_/_.___/\___/_/ /_/ /_/\__, /____/\__, /_/             **
**                                          /____/        /_/                **
**                                                                           **
** ========================================================================= **
**                   MYSQL CLIENT LIBRARY DRIVER FOR ODBC                    **
** ========================================================================= **
**                                                                           **
** Copyright (c) 2008-2018 Jonah H. Harris.                                  **
**                                                                           **
** This library is free software; you can redistribute it and/or modify it   **
** under the terms of the GNU Lesser General Public License as published by  **
** the Free Software Foundation; either version 3 of the License, or (at     **
** your option) any later version.                                           **
**                                                                           **
** This library is distributed in the hope it will be useful, but WITHOUT    **
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     **
** FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public       **
** License for more details.                                                 **
**                                                                           **
** You should have received a copy of the GNU Lesser General Public License  **
** along with this library; if not, write to the Free Software Foundation,   **
** Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                             **
** ========================================================================= */

/* ========================================================================= */
/* -- INCLUSIONS ----------------------------------------------------------- */
/* ========================================================================= */

/* Library Header */
#include "libodbcpq.h"

/* INIH Headers */
#include "ini.h"

/* ========================================================================= */
/* -- DEFINITIONS ---------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- MACROS --------------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- PRIVATE TYPES -------------------------------------------------------- */
/* ========================================================================= */

typedef struct {
  #define CFG(s, n, default) char *s##_##n;
  #include "libodbcpq_config.def"
  #undef CFG
} libodbcpq_config_t;

/* ========================================================================= */
/* -- PRIVATE METHOD PROTOTYPES -------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- PRIVATE DATA --------------------------------------------------------- */
/* ========================================================================= */

static bool _libodbcpq_is_initialized = false;
static void * _libodbcpq_dlhandle = NULL;
static libodbcpq_config_t _libodbcpq_configuration = {
  #define CFG(s, n, default) default,
  #include "libodbcpq_config.def"
  #undef CFG
};

/* ========================================================================= */
/* -- PUBLIC DATA ---------------------------------------------------------- */
/* ========================================================================= */

#define DEFINE_MYSQL_FPTR(name)                                         \
  libodbcpq_##name##_fptr_t libodbcpq_dlsym_##name = NULL;
DEFINE_MYSQL_FPTR(mysql_affected_rows);
DEFINE_MYSQL_FPTR(mysql_autocommit);
DEFINE_MYSQL_FPTR(mysql_change_user);
DEFINE_MYSQL_FPTR(mysql_character_set_name);
DEFINE_MYSQL_FPTR(mysql_close);
DEFINE_MYSQL_FPTR(mysql_commit);
DEFINE_MYSQL_FPTR(mysql_connect);
DEFINE_MYSQL_FPTR(mysql_create_db);
DEFINE_MYSQL_FPTR(mysql_data_seek);
DEFINE_MYSQL_FPTR(mysql_debug);
DEFINE_MYSQL_FPTR(mysql_drop_db);
DEFINE_MYSQL_FPTR(mysql_dump_debug_info);
DEFINE_MYSQL_FPTR(mysql_eof);
DEFINE_MYSQL_FPTR(mysql_errno);
DEFINE_MYSQL_FPTR(mysql_error);
DEFINE_MYSQL_FPTR(mysql_escape_string);
DEFINE_MYSQL_FPTR(mysql_fetch_field);
DEFINE_MYSQL_FPTR(mysql_fetch_field_direct);
DEFINE_MYSQL_FPTR(mysql_fetch_fields);
DEFINE_MYSQL_FPTR(mysql_fetch_lengths);
DEFINE_MYSQL_FPTR(mysql_fetch_row);
DEFINE_MYSQL_FPTR(mysql_field_count);
DEFINE_MYSQL_FPTR(mysql_field_seek);
DEFINE_MYSQL_FPTR(mysql_field_tell);
DEFINE_MYSQL_FPTR(mysql_free_result);
DEFINE_MYSQL_FPTR(mysql_get_character_set_info);
DEFINE_MYSQL_FPTR(mysql_get_client_info);
DEFINE_MYSQL_FPTR(mysql_get_client_version);
DEFINE_MYSQL_FPTR(mysql_get_host_info);
DEFINE_MYSQL_FPTR(mysql_get_option);
DEFINE_MYSQL_FPTR(mysql_get_proto_info);
DEFINE_MYSQL_FPTR(mysql_get_server_info);
DEFINE_MYSQL_FPTR(mysql_get_server_version);
DEFINE_MYSQL_FPTR(mysql_get_ssl_cipher);
DEFINE_MYSQL_FPTR(mysql_hex_string);
DEFINE_MYSQL_FPTR(mysql_info);
DEFINE_MYSQL_FPTR(mysql_init);
DEFINE_MYSQL_FPTR(mysql_insert_id);
DEFINE_MYSQL_FPTR(mysql_kill);
DEFINE_MYSQL_FPTR(mysql_library_end);
DEFINE_MYSQL_FPTR(mysql_library_init);
DEFINE_MYSQL_FPTR(mysql_list_dbs);
DEFINE_MYSQL_FPTR(mysql_list_fields);
DEFINE_MYSQL_FPTR(mysql_list_processes);
DEFINE_MYSQL_FPTR(mysql_list_tables);
DEFINE_MYSQL_FPTR(mysql_more_results);
DEFINE_MYSQL_FPTR(mysql_next_result);
DEFINE_MYSQL_FPTR(mysql_num_fields);
DEFINE_MYSQL_FPTR(mysql_num_rows);
DEFINE_MYSQL_FPTR(mysql_options);
DEFINE_MYSQL_FPTR(mysql_options4);
DEFINE_MYSQL_FPTR(mysql_ping);
DEFINE_MYSQL_FPTR(mysql_query);
DEFINE_MYSQL_FPTR(mysql_real_connect);
DEFINE_MYSQL_FPTR(mysql_real_escape_string);
DEFINE_MYSQL_FPTR(mysql_real_escape_string_quote);
DEFINE_MYSQL_FPTR(mysql_real_query);
DEFINE_MYSQL_FPTR(mysql_refresh);
DEFINE_MYSQL_FPTR(mysql_reload);
DEFINE_MYSQL_FPTR(mysql_reset_connection);
DEFINE_MYSQL_FPTR(mysql_reset_server_public_key);
DEFINE_MYSQL_FPTR(mysql_result_metadata);
DEFINE_MYSQL_FPTR(mysql_rollback);
DEFINE_MYSQL_FPTR(mysql_row_seek);
DEFINE_MYSQL_FPTR(mysql_row_tell);
DEFINE_MYSQL_FPTR(mysql_select_db);
DEFINE_MYSQL_FPTR(mysql_server_end);
DEFINE_MYSQL_FPTR(mysql_server_init);
DEFINE_MYSQL_FPTR(mysql_session_track_get_first);
DEFINE_MYSQL_FPTR(mysql_session_track_get_next);
DEFINE_MYSQL_FPTR(mysql_set_character_set);
DEFINE_MYSQL_FPTR(mysql_set_local_infile_default);
DEFINE_MYSQL_FPTR(mysql_set_local_infile_handler);
DEFINE_MYSQL_FPTR(mysql_set_server_option);
DEFINE_MYSQL_FPTR(mysql_shutdown);
DEFINE_MYSQL_FPTR(mysql_sqlstate);
DEFINE_MYSQL_FPTR(mysql_ssl_set);
DEFINE_MYSQL_FPTR(mysql_stat);
DEFINE_MYSQL_FPTR(mysql_store_result);
DEFINE_MYSQL_FPTR(mysql_thread_id);
DEFINE_MYSQL_FPTR(mysql_use_result);
DEFINE_MYSQL_FPTR(mysql_warning_count);
#undef DEFINE_MYSQL_FPTR

/* ========================================================================= */
/* -- EXTERNAL DATA -------------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- EXTERNAL FUNCTION PROTOTYPES ----------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- STATIC ASSERTIONS ---------------------------------------------------- */
/* ========================================================================= */

/* ========================================================================= */
/* -- PRIVATE METHODS ------------------------------------------------------ */
/* ========================================================================= */

static int
_libodbcpq_inih_cb (
  void                 *user,
  const char           *section,
  const char           *name,
  const char           *value
) {
  libodbcpq_config_t *cfg = (libodbcpq_config_t *) user;

  if (0) ;
  #define CFG(s, n, default) else if (strcmp(section, #s)==0 && \
      strcmp(name, #n)==0) cfg->s##_##n = strdup(value);
  #include "libodbcpq_config.def"
  #undef CFG

  return 1;
} /* _libodbcpq_inih_cb() */

/* ------------------------------------------------------------------------- */

void
dump_config (
  libodbcpq_config_t        *cfg
) {
  #define CFG(s, n, default) log_debug("%s_%s = %s", #s, #n, cfg->s##_##n);
  #include "libodbcpq_config.def"
  #undef CFG
}

void
_libodbcpq_load_configuration (
  void
) {
  char *ini_file_path = getenv("LIBODBCMYSQL_INI");

  if (NULL != ini_file_path) {
    if (0 > ini_parse(ini_file_path, _libodbcpq_inih_cb,
      &_libodbcpq_configuration)) {
      log_error("Failed to load configuration file (%s); using defaults",
        ini_file_path);
    }
  } else {
#if 0
    /* JHH FIXME XXX */
    const char *search_path[] = {
#ifndef WIN32
      "~/.libodbcpq.ini",
      "/etc/libodbcpq.ini"
#endif /* UNIX */
    };
    for (int ii = 0; ii < (sizeof(search_path) / sizeof(char *)); ++ii) {
      printf("parsing %s\n", search_path[ii]);
      int rc = ini_parse(search_path[ii], _libodbcpq_inih_cb,
        &_libodbcpq_configuration);
      printf("rc = %d\n", rc);
      if (0 == rc) {
        /* If we found and processed a config file; bounce. */
        break;
      }
    }
#endif
  }

  /* Set log level based on our default */
  int log_level = (int) strtol(_libodbcpq_configuration.default_log_level,
    (char **) NULL, 10);
  switch (log_level) {
    case LOG_TRACE:
    case LOG_DEBUG:
    case LOG_INFO:
    case LOG_WARN:
    case LOG_ERROR:
    case LOG_FATAL:
      log_set_level(log_level);
      break;
    default:
      log_error("Invalid log level (%s)",
        _libodbcpq_configuration.default_log_level);
      log_set_level(LOG_ERROR);
  }

  /* Dump the config we've read */
  dump_config(&_libodbcpq_configuration);

  /* Load dynamic */
  if (NULL != _libodbcpq_configuration.default_dlopen) {
    _libodbcpq_dlhandle = dlopen(_libodbcpq_configuration.default_dlopen,
      (RTLD_LOCAL | RTLD_LAZY));
    if (NULL != _libodbcpq_dlhandle) {
      #define ASSIGN_MYSQL_FPTR(name)                                         \
        do {                                                                  \
          if (NULL != _libodbcpq_configuration.name##_dlsym) {             \
            MYSQL_FPTR(name) = MYSQL_FPTR_TYPE(name)                          \
              dlsym(_libodbcpq_dlhandle, #name);                           \
            if (NULL == MYSQL_FPTR(name)) {                                   \
              log_error("Could not load symbol (%s)", #name);                 \
            }                                                                 \
          }                                                                   \
        } while (0)
      ASSIGN_MYSQL_FPTR(mysql_affected_rows);
      ASSIGN_MYSQL_FPTR(mysql_autocommit);
      ASSIGN_MYSQL_FPTR(mysql_change_user);
      ASSIGN_MYSQL_FPTR(mysql_character_set_name);
      ASSIGN_MYSQL_FPTR(mysql_close);
      ASSIGN_MYSQL_FPTR(mysql_commit);
      ASSIGN_MYSQL_FPTR(mysql_connect);
      ASSIGN_MYSQL_FPTR(mysql_create_db);
      ASSIGN_MYSQL_FPTR(mysql_data_seek);
      ASSIGN_MYSQL_FPTR(mysql_debug);
      ASSIGN_MYSQL_FPTR(mysql_drop_db);
      ASSIGN_MYSQL_FPTR(mysql_dump_debug_info);
      ASSIGN_MYSQL_FPTR(mysql_eof);
      ASSIGN_MYSQL_FPTR(mysql_errno);
      ASSIGN_MYSQL_FPTR(mysql_error);
      ASSIGN_MYSQL_FPTR(mysql_escape_string);
      ASSIGN_MYSQL_FPTR(mysql_fetch_field);
      ASSIGN_MYSQL_FPTR(mysql_fetch_field_direct);
      ASSIGN_MYSQL_FPTR(mysql_fetch_fields);
      ASSIGN_MYSQL_FPTR(mysql_fetch_lengths);
      ASSIGN_MYSQL_FPTR(mysql_fetch_row);
      ASSIGN_MYSQL_FPTR(mysql_field_count);
      ASSIGN_MYSQL_FPTR(mysql_field_seek);
      ASSIGN_MYSQL_FPTR(mysql_field_tell);
      ASSIGN_MYSQL_FPTR(mysql_free_result);
      ASSIGN_MYSQL_FPTR(mysql_get_character_set_info);
      ASSIGN_MYSQL_FPTR(mysql_get_client_info);
      ASSIGN_MYSQL_FPTR(mysql_get_client_version);
      ASSIGN_MYSQL_FPTR(mysql_get_host_info);
      ASSIGN_MYSQL_FPTR(mysql_get_option);
      ASSIGN_MYSQL_FPTR(mysql_get_proto_info);
      ASSIGN_MYSQL_FPTR(mysql_get_server_info);
      ASSIGN_MYSQL_FPTR(mysql_get_server_version);
      ASSIGN_MYSQL_FPTR(mysql_get_ssl_cipher);
      ASSIGN_MYSQL_FPTR(mysql_hex_string);
      ASSIGN_MYSQL_FPTR(mysql_info);
      ASSIGN_MYSQL_FPTR(mysql_init);
      ASSIGN_MYSQL_FPTR(mysql_insert_id);
      ASSIGN_MYSQL_FPTR(mysql_kill);
      ASSIGN_MYSQL_FPTR(mysql_library_end);
      ASSIGN_MYSQL_FPTR(mysql_library_init);
      ASSIGN_MYSQL_FPTR(mysql_list_dbs);
      ASSIGN_MYSQL_FPTR(mysql_list_fields);
      ASSIGN_MYSQL_FPTR(mysql_list_processes);
      ASSIGN_MYSQL_FPTR(mysql_list_tables);
      ASSIGN_MYSQL_FPTR(mysql_more_results);
      ASSIGN_MYSQL_FPTR(mysql_next_result);
      ASSIGN_MYSQL_FPTR(mysql_num_fields);
      ASSIGN_MYSQL_FPTR(mysql_num_rows);
      ASSIGN_MYSQL_FPTR(mysql_options);
      ASSIGN_MYSQL_FPTR(mysql_options4);
      ASSIGN_MYSQL_FPTR(mysql_ping);
      ASSIGN_MYSQL_FPTR(mysql_query);
      ASSIGN_MYSQL_FPTR(mysql_real_connect);
      ASSIGN_MYSQL_FPTR(mysql_real_escape_string);
      ASSIGN_MYSQL_FPTR(mysql_real_escape_string_quote);
      ASSIGN_MYSQL_FPTR(mysql_real_query);
      ASSIGN_MYSQL_FPTR(mysql_refresh);
      ASSIGN_MYSQL_FPTR(mysql_reload);
      ASSIGN_MYSQL_FPTR(mysql_reset_connection);
      ASSIGN_MYSQL_FPTR(mysql_reset_server_public_key);
      ASSIGN_MYSQL_FPTR(mysql_result_metadata);
      ASSIGN_MYSQL_FPTR(mysql_rollback);
      ASSIGN_MYSQL_FPTR(mysql_row_seek);
      ASSIGN_MYSQL_FPTR(mysql_row_tell);
      ASSIGN_MYSQL_FPTR(mysql_select_db);
      ASSIGN_MYSQL_FPTR(mysql_server_end);
      ASSIGN_MYSQL_FPTR(mysql_server_init);
      ASSIGN_MYSQL_FPTR(mysql_session_track_get_first);
      ASSIGN_MYSQL_FPTR(mysql_session_track_get_next);
      ASSIGN_MYSQL_FPTR(mysql_set_character_set);
      ASSIGN_MYSQL_FPTR(mysql_set_local_infile_default);
      ASSIGN_MYSQL_FPTR(mysql_set_local_infile_handler);
      ASSIGN_MYSQL_FPTR(mysql_set_server_option);
      ASSIGN_MYSQL_FPTR(mysql_shutdown);
      ASSIGN_MYSQL_FPTR(mysql_sqlstate);
      ASSIGN_MYSQL_FPTR(mysql_ssl_set);
      ASSIGN_MYSQL_FPTR(mysql_stat);
      ASSIGN_MYSQL_FPTR(mysql_store_result);
      ASSIGN_MYSQL_FPTR(mysql_thread_id);
      ASSIGN_MYSQL_FPTR(mysql_use_result);
      ASSIGN_MYSQL_FPTR(mysql_warning_count);
      #undef ASSIGN_MYSQL_FPTR
    }
  }
}

/* ========================================================================= */
/* -- PUBLIC METHODS ------------------------------------------------------- */
/* ========================================================================= */

void
libodbcpq_init (
  void
) {
  if (true == _libodbcpq_is_initialized) {
    return;
  }

  /* Start with ERROR-level logging */
  log_set_level(LOG_ERROR);

  /* Load our configuration */
  _libodbcpq_load_configuration();

  /* One round only */
  _libodbcpq_is_initialized = true;

} /* libodbcpq_init() */

/* :vi set ts=2 et sw=2: */

