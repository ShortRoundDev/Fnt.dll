#pragma once
#include <stdint.h>
#include "framework.h"

#define UTF8_MASK4 0xf0
#define UTF8_MASK3 0xe0
#define UTF8_MASK2 0xc0
#define UTF8_MASK1 0x80

#define UTF16_MASK_HIGH 0xd800
#define UTF16_MASK_LOW 0xdc00

typedef enum _Fnt_Encoding
{
	OEM, // ASCII, etc.
	UTF8,
	UTF16,
	UTF32,
} Fnt_Encoding;

//uint8_t* _Fnt_GetNextCharPoint_OEM(uint8_t* oemString, uint32_t* out);
DLLEXPORT uint8_t* _Fnt_GetNextCharPoint_UTF8(uint8_t* utf8String, uint32_t* out);
DLLEXPORT uint8_t* _Fnt_GetNextCharPoint_UTF16(uint8_t* utf16String, uint32_t* out);