#pragma once
#include <stdbool.h>

#include "SDL.h"

#include "framework.h"
#include "Fnt_Types.h"
#include "Fnt_Encoding.h"

/** Render text using a null-terminated ASCII string in its */
DLLEXPORT SDL_FPoint Fnt_RenderText(const char* text, Fnt* fnt, Fnt_Encoding encoding);
DLLEXPORT bool _Fnt_FindCharCodeLocation(Fnt* fnt, uint32_t charCode, SDL_Point* location);
bool _Fnt_BinarySearchCharCodeLocation(Fnt_Char* start, Fnt_Char* end, wchar_t charCode, SDL_Point* location);