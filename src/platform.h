#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#define PLATFORM_PRINTF(fmt, ...) Serial.printf(fmt, ##__VA_ARGS__)
#else
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#define PLATFORM_PRINTF(fmt, ...) printf(fmt, ##__VA_ARGS__)
#endif
