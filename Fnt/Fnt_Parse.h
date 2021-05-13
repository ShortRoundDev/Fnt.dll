#pragma once
#include "Fnt_Types.h"

/** Parses a fnt file from the given memory block, of the given memory block size, into the provided Fnt*
* @return 0 on success, or an error code on failure
* @param memoryBlock The block of memory where the fnt file has been loaded into; text, binary, or xml.
* @param memoryBlockSize The size of the block of memory
* @param fnt A pointer to the Fnt struct that will occupy the information. Allocations
*			 on members are done within this call. */
int _Fnt_ParseFromMemoryBlock(uint8_t* memoryBlock, size_t memoryBlockSize, Fnt* fnt);

/** Parses a fnt file from the given binary-formatted memory block, of the given memory block size, into the provided Fnt*
* @return 0 on success, or an error code on failure
* @param memoryBlock The block of memory where the fnt file has been loaded into; binary format.
* @param memoryBlockSize The size of the block of memory
* @param fnt A pointer to the Fnt struct that will occupy the information. Allocations
*			 on members are done within this call. */
int _Fnt_ParseBinary(uint8_t* memoryBlock, size_t memoryBlockSize, Fnt* fnt);

/** Parses the block beginning at the memoryBlockStart pointer into the fnt struct at its appropriate location*
* @return the address of the next block on succes, or NULL on error
* @param memoryBlock The block of memory where the fnt file has been loaded into; binary format.
* @param memoryBlockSize The size of the block of memory
* @param fnt A pointer to the Fnt struct that will occupy the information. Allocations
*			 on members are done within this call. */
uint8_t* _Fnt_ParseBinaryBlock(uint8_t* memoryBlockStart, Fnt* fnt);

void _Fnt_SetBlockHeader(Fnt_Block_Header* header, uint8_t* start);

void _Fnt_SetInfoBlock(Fnt_Info* info, uint8_t* start);

void _Fnt_SetCommonBlock(Fnt_Common* info, uint8_t* start);

void _Fnt_SetPageBlock(Fnt_Pages* info, uint8_t* start);

void _Fnt_SetCharBlock(Fnt_Char_Block* charBlock, uint8_t* start);

void _Fnt_SetKerningBlock(Fnt_Kerning_Block* kerningBlock, uint8_t* start);

uint8_t* _Fnt_Deserialize_32(int32_t* value, uint8_t* memory);
uint8_t* _Fnt_Deserialize_16(int16_t* value, uint8_t* memory);
uint8_t* _Fnt_Deserialize_8(int8_t* value, uint8_t* memory);

uint8_t* _Fnt_Deserialize_u32(uint32_t* value, uint8_t* memory);
uint8_t* _Fnt_Deserialize_u16(uint16_t* value, uint8_t* memory);
uint8_t* _Fnt_Deserialize_u8(uint8_t* value, uint8_t* memory);
