FROM debian:9
MAINTAINER Kengo Hamasaki <k.hamasaki@gmail.com>

RUN apt-get update && apt-get install --no-install-recommends -y build-essential \
    gcc \
    unzip \
    wget \
    zip \
    gcc-avr \
    binutils-avr \
    avr-libc \
    dfu-programmer \
    dfu-util \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    libnewlib-arm-none-eabi \
    git \
    software-properties-common \
    avrdude \
    python \
    python-pip \
    python-setuptools \
    && rm -rf /var/lib/apt/lists/*

RUN pip install wheel nrfutil

ENV NRFSDK15_ROOT /tmp/nRF5_SDK_15.0.0_a53641a
ENV keyboard ergo42_ble/master
ENV keymap default

VOLUME /qmk
WORKDIR /qmk
COPY . .

RUN wget https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/nRF5_SDK_15.0.0_a53641a.zip -P /tmp/ && unzip /tmp/nRF5_SDK_15.0.0_a53641a.zip -d /tmp/

CMD make clean; export target=`echo ${keyboard} | sed -e "s/\//_/"`_${keymap} && make ${keyboard}:${keymap}:${target}.zip
