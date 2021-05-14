#include <stdio.h>
#include <Fnt.h>
#include <stdint.h>
#include "SDL.h"

int main(int argc, char** argv)
{
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

	Fnt fnt = { 0 };
	Fnt_LoadFromFileW(L"Han3.fnt", &fnt, "", renderer);

	bool quit = false;
	while (!quit)
	{
		SDL_RenderClear(renderer);
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
				quit = true;
		}

		SDL_FPoint cursor = { .x = 10.0f, .y = 10.0f };

		Fnt_RenderTextUTF16(renderer, L"안녕하세요", &fnt, NULL, &cursor);
		SDL_RenderPresent(renderer);

	}
	return 2;

}