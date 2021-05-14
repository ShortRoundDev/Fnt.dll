#include "Fnt_Render.h"
#include "Fnt_Encoding.h"

SDL_FPoint Fnt_RenderText(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* options, SDL_FPoint* cursor, Fnt_Encoding encoding)
{
	switch (encoding)
	{
	case UTF8:
		return Fnt_RenderTextUTF8(renderer, text, fnt, options, cursor);
	case UTF16:
		return Fnt_RenderTextUTF16(renderer, text, fnt, options, cursor);
	case UTF32:
		return Fnt_RenderTextUTF32(renderer, text, fnt, options, cursor);
	case OEM:
		return Fnt_RenderTextOEM(renderer, text, fnt, options, cursor);
	default:
		break;
	}
}

SDL_FPoint Fnt_RenderTextUTF8(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor)
{
	uint8_t* ptr = (uint8_t*) text;
	while (ptr != NULL)
	{
		uint32_t charCode = 0;
		ptr = _Fnt_GetNextCharPoint_UTF8(ptr, &charCode);
		SDL_Point src = { 0 };
		if (!_Fnt_FindCharCodeLocation(fnt, charCode, &src))
		{
			// TODO: iterate by 1, handle some error, etc
			continue;
		}

		//render point
	}
}

SDL_FPoint Fnt_RenderTextUTF16(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor)
{
	uint8_t* ptr = (uint8_t*)text;
	while (ptr != NULL)
	{
		uint32_t charCode = 0;
		ptr = _Fnt_GetNextCharPoint_UTF16(ptr, &charCode);
		Fnt_Char* fntChar = NULL;
		if (!_Fnt_FindCharCodeLocation(fnt, charCode, &fntChar))
		{
			// TODO: iterate by 1, handle some error, etc
			continue;
		}
		SDL_FRect dst = {
			.x = cursor->x,
			.y = cursor->y,
			.w = (float)fntChar->width,
			.h = (float)fntChar->height
		};

		SDL_Rect src = {
			.x = fntChar->x,
			.y = fntChar->y,
			.w = fntChar->width,
			.h = fntChar->height
		};

		SDL_RenderCopyF(
			renderer,
			fnt->pages.pageTextures[fntChar->page],
			&src,
			&dst
		);

		cursor->x += src.w;
	}
	return;
}

SDL_FPoint Fnt_RenderTextUTF32(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor)
{

}

SDL_FPoint Fnt_RenderTextOEM(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor)
{

}


bool _Fnt_FindCharCodeLocation(Fnt* fnt, uint32_t charCode, Fnt_Char** fntChar) {
	if (fnt == NULL || fnt->chars.chars == NULL) {
		return false;
	}
	return _Fnt_BinarySearchCharCodeLocation(fnt->chars.chars, fnt->chars.chars + fnt->chars.numberOfFntChars, charCode, fntChar);
}

bool _Fnt_BinarySearchCharCodeLocation(Fnt_Char* start, Fnt_Char* end, uint32_t charCode, Fnt_Char** fntChar) {
	ptrdiff_t width = (end - start);
	Fnt_Char* mid = start + width / 2;
	if (mid->id == charCode) {
		*fntChar = mid;
		return true;
	}
	if (width == 0)
		return false;
	if (mid->id > charCode) {
		return _Fnt_BinarySearchCharCodeLocation(
			start,
			mid,
			charCode,
			fntChar);
		// go left
	}
	else {
		return _Fnt_BinarySearchCharCodeLocation(
			mid,
			end,
			charCode,
			fntChar);
		// go right
	}
	return false;
}