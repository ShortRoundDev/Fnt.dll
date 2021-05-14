#include "Fnt_Encoding.h"

uint8_t* _Fnt_GetNextCharPoint_OEM(uint8_t* oemString, uint32_t* out)
{
	*out = (uint32_t)(*oemString);
	if(out == '\0')
		return NULL;
	return oemString + 1;
}

uint8_t* _Fnt_GetNextCharPoint_UTF8(uint8_t* utf8String, uint32_t* out)
{
	uint8_t pageMask = *utf8String & UTF8_MASK4;
	uint32_t value = 0;
	if (pageMask == UTF8_MASK4)
	{
		*out =  ((((uint32_t)*(utf8String))     & 0x7)  << 18)  |
				((((uint32_t)*(utf8String + 1)) & 0x3F) << 12)  |
				((((uint32_t)*(utf8String + 2)) & 0x3F) << 6)   |
				((((uint32_t)*(utf8String + 3)) & 0x3F));
		return utf8String + 4;
	}
	else if ((pageMask & UTF8_MASK3) == UTF8_MASK3)
	{
		*out =  ((((uint32_t)*(utf8String))     & 0x1F) << 12)  |
			    ((((uint32_t)*(utf8String + 1)) & 0x3F) << 6)   |
			    ((((uint32_t)*(utf8String + 2)) & 0x3F));
		return utf8String + 3;
	}
	else if ((pageMask & UTF8_MASK2) == UTF8_MASK2)
	{
		*out =  ((((uint32_t)*(utf8String))     & 0x1F) << 6)   |
				((((uint32_t)*(utf8String + 1)) & 0x3F));
		return utf8String + 2;
	}
	else if ((pageMask & UTF8_MASK1) == 0)
	{
		*out = (uint32_t)*utf8String;
		if(*out == 0)
			return NULL;
		return utf8String + 1;
	}
	*out = 0;
	return NULL;
}

uint8_t* _Fnt_GetNextCharPoint_UTF16(uint8_t* utf16String, uint32_t* out)
{
	uint16_t code = *((uint16_t*)utf16String);
	if (code & UTF16_MASK_HIGH)
	{
		uint16_t low = *(((uint16_t*)utf16String) + 1);
		*out = ((((uint32_t)(code - UTF16_MASK_HIGH)) * 0x0400) | (low - UTF16_MASK_LOW)) + 0x10000;
		return utf16String + 4;
	}
	if (code == 0 && (*((uint16_t*)utf16String + 1)) == 0)
	{
		*out = 0;
		return NULL;
	}
	*out = (uint32_t)code;
	return utf16String + 2;
}