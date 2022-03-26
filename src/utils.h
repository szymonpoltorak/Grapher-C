#ifndef _UTILS_H_
#define _UTILS_H_

#include "alloc.h"

#define NO_FILE_FOUND 231
#define WRONG_RANGE_OF_WAGES 234
#define WRONG_NUM_OF_COL 233
#define WRONG_NUM_OF_ROWS 232

#define WEIGHT 1
#define EDGE 2
#define RANDOM 3 
#define READ 4
#define NO_MODE 0

void ifReadMode(const char* usage, short int mode, entryR* entryR, entryG* entryG);

void validateFileName(char* optarg, const char* usage, entryR* entryR, entryG* entryG);

void validateRangeEnd(char* optarg, const char* usage, entryR* entryR, entryG* entryG);

void validateRangeStart(char* optarg, const char* usage, entryR* entryR, entryG* entryG);

void validateColumns(char* optarg, const char* usage, entryR* entryR, entryG* entryG);

void validateRows(char* optarg, const char* usage, entryR* entryR, entryG* entryG);

void checkDataGen(entryG* entryG, entryR* entryR);

void checkDataRead(entryR* entryR, entryG* entryG);

void ifModeWasDeclared(const char* usage, short int mode, entryR* entryR, entryG* entryG);

#endif