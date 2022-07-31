FROM alpine:3.13
RUN apk update \
    && apk add make avr-libc avrdude git cmake g++ jq curl gtest-dev
RUN cd /tmp \
    && wget http://packs.download.atmel.com/Atmel.ATmega_DFP.1.7.374.atpack \
    && unzip *.atpack \
    && cp -r include/* /usr/avr/include/ \
    && cp -r gcc/dev/*/* /usr/avr/lib \
    && cp /usr/avr/lib/device-specs/* /usr/lib/gcc/avr/*/device-specs/ \
    && cd ~ \
    && rm -rf /tmp/*
RUN git clone --depth=1 -b main -q https://github.com/google/googletest.git /googletest \
    && mkdir -p /googletest/build \
    && cd /googletest/build \
    && cmake .. && make && make install \
    && cd ~ \
    && rm -rf /googletest
RUN apk del git cmake jq curl
ENTRYPOINT ["make"]
