#include "Fnt_Parse.h"
#include <stdlib.h>

int _Fnt_ParseFromMemoryBlock(uint8_t* memoryBlock, size_t memoryBlockSize, Fnt* fnt) {
	if (memoryBlockSize < 3) {
		// File too small
		return -1;
	}
	// Binary file
	if (
		memoryBlock[0] == 'B' &&
		memoryBlock[1] == 'M' &&
		memoryBlock[2] == 'F') {
		fnt->header = memoryBlock[3];
		return _Fnt_ParseBinary(memoryBlock + 4, memoryBlockSize - 4, fnt);
	}
	return -1;
}

int _Fnt_ParseBinary(uint8_t* memoryBlock, size_t memoryBlockSize, Fnt* fnt) {
	uint8_t* memoryBlockStart = memoryBlock;
	size_t cursor = memoryBlockSize;
	while (cursor > 0) {
		memoryBlock = _Fnt_ParseBinaryBlock(memoryBlock, fnt);
		if (memoryBlock == NULL) {
			return -2;
		}
		cursor = memoryBlockSize - (memoryBlock - memoryBlockStart);
	}
	return 0;
}

uint8_t* _Fnt_ParseBinaryBlock(uint8_t* memoryBlockStart, Fnt* fnt) {
	size_t blockSize = 0;
	switch (memoryBlockStart[0]) {
	// Info
	case 1: {
		_Fnt_SetInfoBlock(&(fnt->info), memoryBlockStart);
		blockSize = fnt->info.blockHeader.blockSize;
		break;
	}
	// Common
	case 2: {
		_Fnt_SetCommonBlock(&(fnt->common), memoryBlockStart);
		blockSize = fnt->common.blockHeader.blockSize;
		break;
	}
	// Pages
	case 3: {
		_Fnt_SetPageBlock(&(fnt->pages), memoryBlockStart);
		blockSize = fnt->pages.blockHeader.blockSize;
		break;
	}
	// Chars
	case 4: {
		_Fnt_SetCharBlock(&(fnt->chars), memoryBlockStart);
		blockSize = fnt->chars.blockHeader.blockSize;
		break;
	}
	// Kerning
	case 5: {
		_Fnt_SetKerningBlock(&(fnt->kerning), memoryBlockStart);
		blockSize = fnt->kerning.blockHeader.blockSize;
		break;
	}
	default: {
		//Error; misaligned
		return NULL;
	}
	}

	return memoryBlockStart + BLOCK_HEADER_SIZE + blockSize; // 5 = size of block header in file
}

void _Fnt_SetBlockHeader(Fnt_Block_Header* header, uint8_t* start) {
	start = _Fnt_Deserialize_8(&header->blockType, start);
	start = _Fnt_Deserialize_32(&header->blockSize, start);
}

void _Fnt_SetInfoBlock(Fnt_Info* info, uint8_t* start) {
	_Fnt_SetBlockHeader(&info->blockHeader, start);
	start += BLOCK_HEADER_SIZE; // size of block header
	start = _Fnt_Deserialize_16(&info->fontSize, start);
	start = _Fnt_Deserialize_u8(&info->bitField, start);
	start = _Fnt_Deserialize_u8(&info->charSet, start);
	start = _Fnt_Deserialize_u16(&info->stretchH, start);
	start = _Fnt_Deserialize_u8(&info->aa, start);
	start = _Fnt_Deserialize_u8(&info->paddingUp, start);
	start = _Fnt_Deserialize_u8(&info->paddingRight, start);
	start = _Fnt_Deserialize_u8(&info->paddingDown, start);
	start = _Fnt_Deserialize_u8(&info->paddingLeft, start);
	start = _Fnt_Deserialize_u8(&info->spacingHoriz, start);
	start = _Fnt_Deserialize_u8(&info->spacingVert, start);
	start = _Fnt_Deserialize_u8(&info->outline, start);

	info->fontname = (char*)start;
}

void _Fnt_SetCommonBlock(Fnt_Common* common, uint8_t* start) {
	_Fnt_SetBlockHeader(&common->blockHeader, start);
	start += BLOCK_HEADER_SIZE;

	start = _Fnt_Deserialize_u16(&common->lineHeight, start);
	start = _Fnt_Deserialize_u16(&common->base, start);
	start = _Fnt_Deserialize_u16(&common->scaleW, start);
	start = _Fnt_Deserialize_u16(&common->scaleH, start);
	start = _Fnt_Deserialize_u16(&common->pages, start);
	start = _Fnt_Deserialize_u8(&common->bitfield, start);
	start = _Fnt_Deserialize_u8(&common->alphaChnl, start);
	start = _Fnt_Deserialize_u8(&common->redChnl, start);
	start = _Fnt_Deserialize_u8(&common->greenChnl, start);
	start = _Fnt_Deserialize_u8(&common->blueChnl, start);
}

void _Fnt_SetPageBlock(Fnt_Pages* pages, uint8_t* start) {
	_Fnt_SetBlockHeader(&pages->blockHeader, start);
	start += BLOCK_HEADER_SIZE;
	pages->pageNames = start;
}

void _Fnt_SetCharBlock(Fnt_Char_Block* charBlock, uint8_t* start) {
	_Fnt_SetBlockHeader(&charBlock->blockHeader, start);
	start += BLOCK_HEADER_SIZE;

	charBlock->numberOfFntChars = charBlock->blockHeader.blockSize / FNT_CHAR_SIZE;
	charBlock->chars = malloc(sizeof(Fnt_Char) * charBlock->numberOfFntChars);
	if (charBlock->chars == NULL) {
		// Error
		return;
	}

	for (int i = 0; i < charBlock->numberOfFntChars; i++) {
		Fnt_Char* fntChar = &charBlock->chars[i];
		start = _Fnt_Deserialize_u32(&fntChar->id, start);
		start = _Fnt_Deserialize_u16(&fntChar->x, start);
		start = _Fnt_Deserialize_u16(&fntChar->y, start);
		start = _Fnt_Deserialize_u16(&fntChar->width, start);
		start = _Fnt_Deserialize_u16(&fntChar->height, start);
		start = _Fnt_Deserialize_16(&fntChar->xoffset, start);
		start = _Fnt_Deserialize_16(&fntChar->yoffset, start);
		start = _Fnt_Deserialize_16(&fntChar->xadvance, start);
		start = _Fnt_Deserialize_u8(&fntChar->page, start);
		start = _Fnt_Deserialize_u8(&fntChar->chnl, start);
	}
}

void _Fnt_SetKerningBlock(Fnt_Kerning_Block* kerningBlock, uint8_t* start) {
	_Fnt_SetBlockHeader(&kerningBlock->blockHeader, start);
	start += BLOCK_HEADER_SIZE;

	kerningBlock->numberOfFntKernings = kerningBlock->blockHeader.blockSize / FNT_KERNING_SIZE;
	kerningBlock->kerning = malloc(sizeof(Fnt_Char) * kerningBlock->numberOfFntKernings);
	if (kerningBlock->kerning == NULL) {
		// Error
		return;
	}

	for (int i = 0; i < kerningBlock->numberOfFntKernings; i++) {
		Fnt_Kerning* kerning = &kerningBlock->kerning[i];
		start = _Fnt_Deserialize_u32(&kerning->first, start);
		start = _Fnt_Deserialize_u32(&kerning->second, start);
		start = _Fnt_Deserialize_16(&kerning->amount, start);
	}
}

uint8_t* _Fnt_Deserialize_32(int32_t* value, uint8_t* memory) {
	*value = (*(int32_t*)(memory));
	return memory + sizeof(int32_t);
}

uint8_t* _Fnt_Deserialize_16(int16_t* value, uint8_t* memory) {
	*value = (*(int16_t*)(memory));
	return memory + sizeof(int16_t);
}

uint8_t* _Fnt_Deserialize_8(int8_t* value, uint8_t* memory) {
	*value = (*(int8_t*)(memory));
	return memory + sizeof(int8_t);
}

uint8_t* _Fnt_Deserialize_u32(uint32_t* value, uint8_t* memory) {
	*value = *((uint32_t*)(memory));
	return memory + sizeof(uint32_t);
}

uint8_t* _Fnt_Deserialize_u16(uint16_t* value, uint8_t* memory) {
	*value = (*(uint16_t*)(memory));
	return memory + sizeof(uint16_t);
}

uint8_t* _Fnt_Deserialize_u8(uint8_t* value, uint8_t* memory) {
	*value = *memory;
	return memory + sizeof(uint8_t);
}
