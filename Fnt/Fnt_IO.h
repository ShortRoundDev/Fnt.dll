#pragma once
#include "framework.h"
#include "Fnt_Types.h"

/** Attempts to load a font file from the given UTF-16 path. Loads binary, text, and XML files
* @return 0 on success, or an error code on failure
* @param path The UTF-16 encoded path to the .fnt file
* @param fnt A pointer to the Fnt struct that will occupy the information. Allocations
*			 on members are done within this call.
*/
int DLLEXPORT Fnt_LoadFromFileW(LPCWSTR path, Fnt* fnt);
/**
* Attempts to load a font file from the given path
* @return 0 on success, or an error code on failure
* for failures. Loads binary, text, and XML files
* @param path The path to the .fnt file
* @param fnt A pointer to the Fnt struct that will occupy the information. Allocations
*			 on members are done within this call.
*/
int DLLEXPORT Fnt_LoadFromFile(const char* path, Fnt* fnt);


/** Loads a font file from the given file pointer
* @return 0 on success, or an error code on failure
* @param fp A pointer to an opened file with the Fnt file information
* @param fnt A pointer to the Fnt struct that will occupy the information. Allocations
*			 on members are done within this call. */
int DLLEXPORT Fnt_LoadReadFile(FILE* fp, Fnt* fnt);