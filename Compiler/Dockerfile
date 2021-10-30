FROM alpine:3.13
RUN apk update \
    && apk add make avr-libc avrdude \
    && cd /tmp \
    && wget http://packs.download.atmel.com/Atmel.ATmega_DFP.1.7.374.atpack \
    && unzip *.atpack \
    && cp -r include/* /usr/avr/include/ \
    && cp -r gcc/dev/*/* /usr/avr/lib \
    && cp /usr/avr/lib/device-specs/* /usr/lib/gcc/avr/*/device-specs/ \
    && rm -rf /tmp/*
ENTRYPOINT ["make"]
