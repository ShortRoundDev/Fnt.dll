#pragma once
#include "SDL.h"

/** Options passed to draw calls to modify the render at draw-time */
typedef struct _Fnt_RenderOptions
{

	/** The size of the font */
	int16_t fontSize;
	/** The distance between lines of characters after a line break */
	int16_t lineHeight;
	/** The width point at which characters should wrap to the next line */
	uint16_t wrapWidth;
	/** The padding between each character */
	int8_t charSpacing;
	/** The scale quality (sampling level) of the texture.
	 *  0 = nearest neighbor (pixelated)
	 *  1 = linear (OpenGL and D3D)
	 *  2 = anisotropic (D3D)
	 * @details https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY */
	uint8_t renderScaleQuality;
	/** A pointer to an array of offsets for each character. This is used for
	 *  drawing real-time text effects such as moving text */
	const SDL_FPoint* offsets;
	/** The number of offsets in the offset array. If this is 0 and `offsets`
	 *  is not NULL, then SDL_Fnt will assume that the length of the string
	 *  is the length of offsets. */
	size_t offsetLength;
	/** The color of the text */
	SDL_Color color;
	/** Whether or not the font is italic */
	bool italic;
	/** Whether or not the font is bold */
	bool bold;
} Fnt_RenderOptions;