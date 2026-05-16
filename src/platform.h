#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#define PLATFORM_PRINTF(fmt, ...) Serial.printf(fmt, ##__VA_ARGS__)
#define PLATFORM_STRING String
#define PLATFORM_STRING_AT(str, index) str.charAt(index)
#define PLATFORM_STRING_POP_FRONT(str) str.substring(0)
#define PLATFORM_STRING_PUSH_BACK(str, c) str.concat(c)
#define PLATFORM_STRING_POP_BACK(str) str.remove(str.length() - 1)
#else
using namespace std;
#include <cstdlib>
#include <string>
#include <cstdint>
#include <cstdio>
#include <cstring>
#define PLATFORM_PRINTF(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define PLATFORM_STRING string
#define PLATFORM_STRING_AT(str, index) str.at(index)
#define PLATFORM_STRING_POP_FRONT(str) str.substr(1)
#define PLATFORM_STRING_PUSH_BACK(str, c) str.push_back(c)
#define PLATFORM_STRING_POP_BACK(str) str.pop_back()
#endif
