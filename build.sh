#!/bin/bash

### ENV VARS

ARDUINO_CLI_VERSION=0.3.6-alpha.preview
export USER=root

### PROCESS

apt update -y && apt install make curl git python python-serial -y
curl -L https://github.com/arduino/arduino-cli/releases/download/0.3.6-alpha.preview/arduino-cli-$ARDUINO_CLI_VERSION-linux64.tar.bz2 | tar xj -C /tmp/
mv /tmp/arduino-cli-$ARDUINO_CLI_VERSION-linux64 /usr/local/bin/arduino-cli && chmod +x /usr/local/bin/arduino-cli
cd /builds/btcven/locha/app/
arduino-cli core update-index
arduino-cli core install Heltec-esp32:esp32
test -e arduino_data/packages/Heltec-esp32/hardware/esp32/0.0.2-rc1/libraries/heltec-oled || git clone https://gitlab.com/btcven/locha/heltec-oled  arduino_data/packages/Heltec-esp32/hardware/esp32/0.0.2-rc1/libraries/heltec-oled
test -e arduino_data/packages/Heltec-esp32/hardware/esp32/0.0.2-rc1/libraries/heltec-lora || git clone https://gitlab.com/btcven/locha/heltec-lora  arduino_data/packages/Heltec-esp32/hardware/esp32/0.0.2-rc1/libraries/heltec-lora
arduino-cli lib install Time
arduino-cli compile --fqbn Heltec-esp32:esp32:wifi_lora_32_V2 Turpial
