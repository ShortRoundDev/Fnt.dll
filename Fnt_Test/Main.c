#include <stdio.h>
#include <Fnt.h>

int main(int argc, char** argv)
{
	printf("Hello world!");
	Fnt fnt;

	wchar_t buffer[1024];
	GetCurrentDirectoryW(1024, buffer);
	wprintf(L"%ls", buffer);

	Fnt_LoadFromFileW(L".\\Test3.fnt", &fnt);

	SDL_Point p;
	for (wchar_t i = L'A'; i < L'Z'; i++)
	{
		if (!_Fnt_FindCharCodeLocation(&fnt, i, &p))
		{
			wprintf(L"ERROR on %lc\n", i);
		}
		else
		{
			wprintf(L"%c => x: %d\ty: %d\n", i, p.x, p.y);
		}
	}
}