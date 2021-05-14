#include <stdio.h>
#include <Fnt.h>
#include <stdint.h>

int main(int argc, char** argv)
{
	uint8_t utf8[17] = {
		0xf0, 0x90, 0x8d, 0x88, // 4 byte character
		0xed, 0x95, 0x9c,		// 3 byte character
		0xe2, 0x82, 0xac,		// 3 byte character
		0xe0, 0xa4, 0xb9,		// 3 byte character
		0xc2, 0xa2,				// 2 byte character
		0x24,					// 1 byte character
		0x00					// null terminator
	};

	uint8_t* ptr = utf8;
	while (ptr != NULL)
	{
		uint32_t out;
		ptr = _Fnt_GetNextCharPoint_UTF8(ptr, &out);
		printf("0x%06X\n", out);
	}

	printf("-----\n");

	LPWSTR str = L"𤭢𐐷€$\0";
	ptr = (uint8_t*)str;
	while (ptr != NULL)
	{
		uint32_t out;
		ptr = _Fnt_GetNextCharPoint_UTF16(ptr, &out);
		printf("0x%06X\n", out);
	}
}