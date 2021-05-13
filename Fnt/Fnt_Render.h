#pragma once
#include <stdbool.h>
#include "framework.h"
#include "Fnt_Types.h"
#include "SDL.h"

/** Render text using a null-terminated ASCII string in its */
SDL_FPoint DLLEXPORT Fnt_RenderText(const char* text, Fnt* fnt);
bool DLLEXPORT _Fnt_FindCharCodeLocation(Fnt* fnt, wchar_t charCode, SDL_Point* location);
bool _Fnt_BinarySearchCharCodeLocation(Fnt_Char* start, Fnt_Char* end, wchar_t charCode, SDL_Point* location);