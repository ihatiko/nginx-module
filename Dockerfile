ARG NGINX_VERSION=1.22.0

FROM nginx:stable-alpine AS builder

RUN apk update && \
    apk upgrade && \
    apk add  \
    --no-cache  \
    --virtual .build-deps  \
    git  \
    gcc  \
    libc-dev  \
    make  \
    openssl-dev  \
    pcre-dev zlib-dev  \
    linux-headers  \
    curl  \
    gnupg  \
    libxslt-dev  \
    gd-dev  \
    geoip-dev  \
    curl

COPY src /modules

RUN nginx -v
RUN curl "https://nginx.org/download/nginx-$NGINX_VERSION.tar.gz" -o nginx-$NGINX_VERSION.tar.gz
RUN tar -xvf nginx-$NGINX_VERSION.tar.gz
WORKDIR nginx-$NGINX_VERSION/
RUN ./configure --with-compat --add-dynamic-module=../modules
RUN make modules

FROM nginx:stable-alpine
COPY --from=builder nginx-$NGINX_VERSION/objs/ngx_http_hello_world_module.so /etc/nginx/modules/ngx_http_hello_world_module.so
COPY nginx.conf /etc/nginx/nginx.conf
COPY default.conf /etc/nginx/conf.d/default.conf