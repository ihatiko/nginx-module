#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

typedef struct {
    ngx_uint_t  enable;
} ngx_http_sandbox_conf_t;

static char *ngx_http_sandbox(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_int_t ngx_http_sandbox_handler(ngx_http_request_t *r);

static ngx_command_t ngx_http_sandbox_commands[] = {

        { ngx_string("sandbox"),
          NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
          ngx_http_sandbox,
          0,
          0,
          NULL},

        ngx_null_command
};

static ngx_http_module_t ngx_http_sandbox_module_ctx = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
};

ngx_module_t ngx_http_sandbox_module = {
        NGX_MODULE_V1,
        &ngx_http_sandbox_module_ctx,
        ngx_http_sandbox_commands,
        NGX_HTTP_MODULE,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NGX_MODULE_V1_PADDING
};

static ngx_int_t ngx_http_sandbox_handler(ngx_http_request_t *r) {
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "Sandbox hello world: %s\n", r->uri.data);
}

static char *ngx_http_sandbox(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_sandbox_handler;

    return NGX_CONF_OK;
}