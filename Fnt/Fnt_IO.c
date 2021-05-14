#include <Shlwapi.h>
#include <stdlib.h>

#include "SDL_image.h"

#include "Fnt_IO.h"
#include "Fnt_Parse.h"

int Fnt_LoadFromFileW(LPCWSTR path, Fnt* fnt, const char* resourcePath, const SDL_Renderer* renderer) {
	FILE* fp = NULL;
	errno_t status = _wfopen_s(&fp, path, L"rb");
	if (status != 0) {
		return status;
	}
	return Fnt_LoadReadFile(fp, fnt, resourcePath, renderer);
}

int Fnt_LoadFromFile(const char* path, Fnt* fnt, const char* resourcePath, const SDL_Renderer* renderer) {
	FILE* fp = NULL;
	errno_t status = fopen_s(&fp, path, "rb");
	if (status != 0) {
		return status;
	}
	return Fnt_LoadReadFile(fp, fnt, resourcePath, renderer);
}

int Fnt_LoadReadFile(FILE* fp, Fnt* fnt, const char* resourcePath, const SDL_Renderer* renderer) {
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	uint8_t* fileMemoryBuffer = malloc(size);
	if (fileMemoryBuffer == NULL)
	{
		return -5;
	}
	fread_s(
		fileMemoryBuffer,
		size,
		sizeof(uint8_t),
		size,
		fp);
	int err = _Fnt_ParseFromMemoryBlock(fileMemoryBuffer, size, fnt);

	if(err)
		return err;

	int pageLength = 0;
	_Fnt_GetTotalPages(&fnt->pages, &fnt->pages.totalPages, &pageLength);
	fnt->pages.pageTextures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * fnt->pages.totalPages);

	char pathBuffer[MAX_PATH] = "";
	char* pageCursor = fnt->pages.pageNames;
	for (int i = 0; i < fnt->pages.totalPages; i++)
	{
		PathCombineA((LPSTR)pathBuffer, resourcePath, pageCursor);
		pageCursor += pageLength;
		fnt->pages.pageTextures[i] = IMG_LoadTexture(renderer, (const char*)pathBuffer);
	}
	return err;
}

void _Fnt_GetTotalPages(Fnt_Pages* pages, int* totalPages, int* pageNameLength)
{
	*pageNameLength = strnlen_s(pages->pageNames, MAX_PATH) + 1; // +1 for null terminator
	*totalPages = pages->blockHeader.blockSize / *pageNameLength;
}