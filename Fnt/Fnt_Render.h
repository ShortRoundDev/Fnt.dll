#pragma once
#include <stdbool.h>

#include "SDL.h"

#include "framework.h"
#include "Fnt_Types.h"
#include "Fnt_Encoding.h"
#include "Fnt_RenderOptions.h"

/** Render text using a null-terminated ASCII string in its */
DLLEXPORT SDL_FPoint Fnt_RenderText(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor, Fnt_Encoding encoding);
DLLEXPORT SDL_FPoint Fnt_RenderTextUTF8(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor);
DLLEXPORT SDL_FPoint Fnt_RenderTextUTF16(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor);
DLLEXPORT SDL_FPoint Fnt_RenderTextUTF32(SDL_Renderer* renderer, const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor);
DLLEXPORT SDL_FPoint Fnt_RenderTextOEM(const char* text, Fnt* fnt, Fnt_RenderOptions* renderOptions, SDL_FPoint* cursor);
bool _Fnt_FindCharCodeLocation(Fnt* fnt, uint32_t charCode, Fnt_Char** fntChar);
bool _Fnt_BinarySearchCharCodeLocation(Fnt_Char* start, Fnt_Char* end, uint32_t charCode, Fnt_Char** fntChar);