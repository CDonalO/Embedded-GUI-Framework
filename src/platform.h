#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#define PLATFORM_PRINTF(fmt, ...) Serial.printf(fmt, ##__VA_ARGS__)
#define PLATFORM_STRING String
#else
using namespace std;
#include <cstdlib>
#include <string>
#include <cstdint>
#include <cstdio>
#include <cstring>
#define PLATFORM_PRINTF(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define PLATFORM_STRING string
#endif
