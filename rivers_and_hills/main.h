#ifndef MAIN_H


#include <windows.h>
#include <stdint.h>
#include <dwmapi.h>
#include <assert.h>

#pragma  comment(lib, "dwmapi.lib")

#define global_variable static
#define function static
#define local_persist static

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int64_t s64;
typedef int32_t b32;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

#define array_count(Array)(sizeof(Array)/sizeof((Array)[0]))

#include "helper_functions.h"
#include "rivers_opengl.h"

#define  STB_IMAGE_IMPLEMENTATION 1
#include "stb_image.h"


#define MAIN_H
#endif
