#include "Fnt_IO.h"
#include "Fnt_Parse.h"
#include "stdlib.h"

int Fnt_LoadFromFileW(LPCWSTR path, Fnt* fnt) {
	FILE* fp = NULL;
	errno_t status = _wfopen_s(&fp, path, L"rb");
	if (status != 0) {
		return status;
	}
	return Fnt_LoadReadFile(fp, fnt);
}

int Fnt_LoadFromFile(const char* path, Fnt* fnt) {
	FILE* fp = NULL;
	errno_t status = fopen_s(&fp, path, "rb");
	if (status != 0) {
		return status;
	}
	return Fnt_LoadReadFile(fp, fnt);
}

int Fnt_LoadReadFile(FILE* fp, Fnt* fnt) {
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	uint8_t* fileMemoryBuffer = malloc(size);
	fread_s(
		fileMemoryBuffer,
		size,
		sizeof(uint8_t),
		size,
		fp);
	return _Fnt_ParseFromMemoryBlock(fileMemoryBuffer, size, fnt);
}