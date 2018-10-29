AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@PTHREAD_CPPFLAGS@ \
	@LIBODBCMYSQL_DLL_EXPORT@

lib_LTLIBRARIES = libodbcpq.la

libodbcpq_la_SOURCES = \
	ini.c \
	log.c \
	util.c \
	libodbcpq.c \
	my_init.c \
	mysql_affected_rows.c \
	mysql_autocommit.c \
	mysql_change_user.c \
	mysql_character_set_name.c \
	mysql_client_find_plugin.c \
	mysql_client_register_plugin.c \
	mysql_close.c \
	mysql_commit.c \
	mysql_connect.c \
	mysql_create_db.c \
	mysql_data_seek.c \
	mysql_debug.c \
	mysql_drop_db.c \
	mysql_dump_debug_info.c \
	mysql_embedded.c \
	mysql_eof.c \
	mysql_errno.c \
	mysql_error.c \
	mysql_escape_string.c \
	mysql_fetch_field.c \
	mysql_fetch_field_direct.c \
	mysql_fetch_fields.c \
	mysql_fetch_lengths.c \
	mysql_fetch_row.c \
	mysql_field_count.c \
	mysql_field_seek.c \
	mysql_field_tell.c \
	mysql_free_result.c \
	mysql_get_character_set_info.c \
	mysql_get_charset_by_name.c \
	mysql_get_charset_by_nr.c \
	mysql_get_client_info.c \
	mysql_get_client_version.c \
	mysql_get_host_info.c \
	mysql_get_option.c \
	mysql_get_optionv.c \
	mysql_get_parameters.c \
	mysql_get_proto_info.c \
	mysql_get_server_info.c \
	mysql_get_server_name.c \
	mysql_get_server_version.c \
	mysql_get_socket.c \
	mysql_get_ssl_cipher.c \
	mysql_get_timeout_value.c \
	mysql_get_timeout_value_ms.c \
	mysql_hex_string.c \
	mysql_info.c \
	mysql_init.c \
	mysql_insert_id.c \
	mysql_kill.c \
	mysql_library_end.c \
	mysql_library_init.c \
	mysql_list_dbs.c \
	mysql_list_fields.c \
	mysql_list_processes.c \
	mysql_list_tables.c \
	mysql_load_plugin.c \
	mysql_load_plugin_v.c \
	mysql_more_results.c \
	mysql_net_field_length.c \
	mysql_net_read_packet.c \
	mysql_next_result.c \
	mysql_num_fields.c \
	mysql_num_rows.c \
	mysql_options.c \
	mysql_options4.c \
	mysql_ping.c \
	mysql_query.c \
	mysql_read_query_result.c \
	mysql_real_connect.c \
	mysql_real_escape_string.c \
	mysql_real_escape_string_quote.c \
	mysql_real_query.c \
	mysql_refresh.c \
	mysql_reload.c \
	mysql_reset_connection.c \
	mysql_reset_server_public_key.c \
	mysql_result_metadata.c \
	mysql_rollback.c \
	mysql_row_seek.c \
	mysql_row_tell.c \
	mysql_select_db.c \
	mysql_send_query.c \
	mysql_server_end.c \
	mysql_server_init.c \
	mysql_session_track_get_first.c \
	mysql_session_track_get_next.c \
	mysql_set_character_set.c \
	mysql_set_local_infile_default.c \
	mysql_set_local_infile_handler.c \
	mysql_set_server_option.c \
	mysql_shutdown.c \
	mysql_sqlstate.c \
	mysql_ssl_set.c \
	mysql_stat.c \
	mysql_stmt_affected_rows.c \
	mysql_stmt_attr_get.c \
	mysql_stmt_attr_set.c \
	mysql_stmt_bind_param.c \
	mysql_stmt_bind_result.c \
	mysql_stmt_close.c \
	mysql_stmt_data_seek.c \
	mysql_stmt_errno.c \
	mysql_stmt_error.c \
	mysql_stmt_execute.c \
	mysql_stmt_fetch.c \
	mysql_stmt_fetch_column.c \
	mysql_stmt_field_count.c \
	mysql_stmt_free_result.c \
	mysql_stmt_init.c \
	mysql_stmt_insert_id.c \
	mysql_stmt_more_results.c \
	mysql_stmt_next_result.c \
	mysql_stmt_num_rows.c \
	mysql_stmt_param_count.c \
	mysql_stmt_param_metadata.c \
	mysql_stmt_prepare.c \
	mysql_stmt_reset.c \
	mysql_stmt_result_metadata.c \
	mysql_stmt_row_seek.c \
	mysql_stmt_row_tell.c \
	mysql_stmt_send_long_data.c \
	mysql_stmt_sqlstate.c \
	mysql_stmt_store_result.c \
	mysql_store_result.c \
	mysql_thread_end.c \
	mysql_thread_id.c \
	mysql_thread_init.c \
	mysql_thread_safe.c \
	mysql_use_result.c \
	mysql_warning_count.c

libodbcpq_la_LIBADD = \
	@PTHREAD_LIBADD@

libodbcpq_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libodbcpq_definitions.h.in \
	libodbcpq.rc \
	libodbcpq.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libodbcpq_definitions.h
	/bin/rm -f libodbcpq.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libodbcpq ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libodbcpq_la_SOURCES)

