#include "Fnt_Render.h"

SDL_FPoint Fnt_RenderText(const char* text, Fnt* fnt)
{
	SDL_FPoint p = { 0 };
	return p;
}


bool _Fnt_FindCharCodeLocation(Fnt* fnt, wchar_t charCode, SDL_Point* location) {
	if (fnt == NULL || fnt->chars.chars == NULL) {
		return false;
	}
	return _Fnt_BinarySearchCharCodeLocation(fnt->chars.chars, fnt->chars.chars + fnt->chars.numberOfFntChars, charCode, location);
}

bool _Fnt_BinarySearchCharCodeLocation(Fnt_Char* start, Fnt_Char* end, wchar_t charCode, SDL_Point* location) {
	ptrdiff_t width = (end - start);
	Fnt_Char* mid = start + width / 2;
	if (mid->id == charCode) {
		location->x = (int)mid->x;
		location->y = (int)mid->y;
		return true;
	}
	if (width == 0)
		return false;
	if (mid->id > charCode) {
		return _Fnt_BinarySearchCharCodeLocation(
			start,
			mid,
			charCode,
			location);
		// go left
	}
	else {
		return _Fnt_BinarySearchCharCodeLocation(
			mid,
			end,
			charCode,
			location);
		// go right
	}
	return false;
}