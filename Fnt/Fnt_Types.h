/**
 * @file	Fnt_Types.h
 * @author	Shortround
 * @date	5/12/2021
 * @brief	Contains headers and define macros for Fnt structs
 * @details	Format taken from:
 *			https://www.angelcode.com/products/bmfont/doc/file_format.html
 */

#pragma once
#include <stdint.h>
#include "SDL.h"

#define BLOCK_HEADER_SIZE 5
#define FNT_CHAR_SIZE 20
#define FNT_KERNING_SIZE 10

/** Following the first four bytes is a series of blocks with information.
 *  Each block starts with a one byte block type identifier,
 *  followed by a 4 byte integer that gives the size of the block,
 *  not including the block type identifier and the size value. */
typedef struct _Fnt_Block_Header {
	/** Represents the type of the block.
	 *  1 = info
	 *  2 = common
	 *  3 = pages
	 *  4 = chars
	 *  5 = kerning pairs */
	uint8_t blockType;
	/** The size, in bytes, of the block, not including
	 *  the block type identifier and the size value. */
	uint32_t blockSize;
} Fnt_Block_Header;

/** This tag holds information on how the font was generated. */
typedef struct _Fnt_Info {
	/** The header for the current block */
	Fnt_Block_Header blockHeader;
	/** The size of the font */
	int16_t fontSize;
	/** bit 0: smooth, bit 1: unicode, bit 2: italic, bit 3: bold,
	 *	bit 4: fixed Heigth, bits 5-7: reserved */
	uint8_t bitField;
	/** The name of the OEM charset used (when not unicode). */
	uint8_t charSet;
	/** The font height stretch in percentage. 100% means no stretch */
	uint16_t stretchH;
	/**The supersampling level used. 1 means no supersampling was used.*/
	uint8_t aa;
	/** The up-padding for each character*/
	uint8_t paddingUp;
	/** The right-padding for each character */
	uint8_t paddingRight;
	/** The down-padding for each character */
	uint8_t paddingDown;
	/** The left-padding for each character */
	uint8_t paddingLeft;
	/** The horizontal spacing for each character */
	uint8_t spacingHoriz;
	/** The vertical spacing for each character */
	uint8_t spacingVert;
	/** The outline thickness for the characters */
	uint8_t outline;
	/** The name of the font */
	char* fontname;
} Fnt_Info;

/** This tag holds information common to all characters. */
typedef struct _Fnt_Common {
	/** The header for the current block */
	Fnt_Block_Header blockHeader;
	/** This is the distance in pixels between each line of text. */
	uint16_t lineHeight;
	/** The number of pixels from the absolute top of the line to the base of the characters. */
	uint16_t base;
	/** The width of the texture, normally used to scale the x pos of the character image. */
	uint16_t scaleW;
	/** The height of the texture, normally used to scale the y pos of the character image. */
	uint16_t scaleH;
	/** The number of texture pages included in the font. */
	uint16_t pages;
	/** bits 0-6: reserved, bit 7: packed
	 *  set bit 7 to 1 if the monochrome characters have been packed into each of the
	 *  texture channels. In this case alphaChnl describes what is stored in each channel. */
	uint8_t bitfield;
	/** Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it
	 *  holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one. */
	uint8_t alphaChnl;
	/** Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it
	 *  holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one. */
	uint8_t redChnl;
	/** Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it
	 *  holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one. */
	uint8_t greenChnl;
	/** Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it
	 *  holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one. */
	uint8_t blueChnl;
} Fnt_Common;

/** This block gives the name of each texture file with the image data for the characters.
 *  The string pageNames holds the names separated and terminated by null chars.
 *  Each filename has the same length, so once you know the size of the first name,
 *  you can easily determine the position of each of the names.
 *  The id of each page is the zero-based index of the string name. */
typedef struct _Fnt_Pages {
	/** The header for the current block */
	Fnt_Block_Header blockHeader;
	/** Total page textures */
	int totalPages;
	/** Array of null terminated strings */
	char* pageNames; // Don't trust the angelcode spec on size guarantees; check buffer size from block header
	/** Array of textures loaded with the pages provided */
	SDL_Texture** pageTextures;
} Fnt_Pages;

/** This tag describes one character in the font. There is one for each included character in the font.
 *  The number of characters in the file can be computed by taking the size of the block and dividing
 *  with the size of the charInfo structure, i.e.: `numChars = charsBlock.blockSize/20.` */
typedef struct _Fnt_Char {
	/** The character id */
	uint32_t id;
	/** The left position of the character image in the texture. */
	uint16_t x;
	/** The top position of the character image in the texture. */
	uint16_t y;
	/** The width of the character image in the texture. */
	uint16_t width;
	/** The height of the character image in the texture. */
	uint16_t height;
	/** How much the current position should be offset when copying the image
	 *  from the texture to the screen */
	int16_t xoffset;
	/** How much the current position should be offset when copying the image
	 *  from the texture to the screen. */
	int16_t yoffset;
	/** How much the current position should be advanced after drawing the character. */
	int16_t xadvance;
	/** The texture page where the character image is found. */
	uint8_t page;
	/** The texture channel where the character image is found
	 *  (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels). */
	uint8_t chnl;
} Fnt_Char;

/** The Block wrapping Char information */
typedef struct _Fnt_Char_Block // This block contains the meta for the block, plus the pointer to the characters
{
	Fnt_Block_Header blockHeader;
	uint64_t numberOfFntChars;
	Fnt_Char* chars;
} Fnt_Char_Block;


/** The kerning information is used to adjust the distance between certain characters,
 *  e.g. some characters should be placed closer to each other than others.
 *  This block is only in the file if there are any kerning pairs with amount differing from 0. */
typedef struct _Fnt_Kerning {
	/** The first character id. */
	uint32_t first;
	/** The second character id. */
	uint32_t second;
	/** How much the x position should be adjusted when drawing the second character
	 *  immediately following the first. */
	int16_t amount;
} Fnt_Kerning;

/** The Block wrapping Kerning information */
typedef struct _Fnt_Kerning_Block {
	Fnt_Block_Header blockHeader;
	uint64_t numberOfFntKernings;
	Fnt_Kerning* kerning;
} Fnt_Kerning_Block;

/** The root structure wrapping a Fnt file */
typedef struct _Fnt {
	/** The first three bytes are the file identifier and must always be 66, 77, 70, or "BMF".
	 *  The fourth byte gives the format version, currently it must be 3.
	 *  Mask 0xff to get the version number (i.e: `uint8_t version = myFnt.header & 0xff`)*/
	uint32_t header; // Mask 0xff for version number

	/** This tag holds information on how the font was generated. */
	Fnt_Info info;

	/** This tag holds information common to all characters. */
	Fnt_Common common;

	/** This tag gives the name of a texture file. There is one for each page in the font. */
	Fnt_Pages pages;

	/** This tag describes on character in the font. There is one for each included character in the font. */
	Fnt_Char_Block chars;

	/** The kerning information is used to adjust the distance between certain characters,
	 *  e.g. some characters should be placed closer to each other than others.
	 *  This block is only in the file if there are any kerning pairs with amount differing from 0. */
	Fnt_Kerning_Block kerning;

	/** Pointer to raw block of memory, loaded from a binary file. If the font was not loaded from a
	 *  binary file, this must be NULL */
	void* _raw_fnt_head; // pointer to raw block in memory, if file is binary

	/** Format this Font was loaded from
	 *  0 = binary, 1 = text, 2 = xml, 3 = other
	 *  "Other" means it was probably created in software, perhaps for export */
	uint8_t type;
} Fnt;