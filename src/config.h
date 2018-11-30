#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <Ethernet.h>

byte      config_mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress config_ip(192, 168, 88, 177);
uint8_t   timerPin = 8;

#endif