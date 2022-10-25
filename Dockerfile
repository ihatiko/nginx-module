FROM nginx

COPY default.conf /etc/nginx/conf.d/
COPY ngx_http_sandbox_module.c /etc/nginx/modules/
