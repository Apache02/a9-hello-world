FROM alpine:3.18.4

RUN set -eux; \
    apk update; \
    apk add --no-cache bash make build-base gcc-arm-none-eabi; \
    rm -vrf /var/cache/apk/*; \
    rm -rf /tmp/*; \
    mkdir /app

COPY tools /tools

RUN set -eux; \
    (cd /tools && make); \
    cp /tools/encrypt_crc/encrypt_crc /usr/local/bin/; \
    rm -rf /tools

WORKDIR /app

ENTRYPOINT ["/bin/bash", "-c"]
