#ifndef _UTILS_H_
#define _UTILS_H_

#include "alloc.h"

#define NOT_READ_MODE 229
#define MULTIPILE_MODE_DECLARATION 230
#define WRONG_MODE 228

#define NO_FILE_FOUND 231
#define WRONG_RANGE_OF_WAGES 234
#define WRONG_NUM_OF_COL 233
#define WRONG_NUM_OF_ROWS 232
#define NO_FLAG_FOUND 235

#define WEIGHT 1
#define EDGE 2
#define RANDOM 3 
#define READ 4

#define NO_MODE 0
#define NO_ERRORS 0
#define NO_FLAG 0

void ifReadMode(short int mode, entryR* entryR, entryG* entryG);

void validateFileName(char* optarg, entryR* entryR, entryG* entryG);

void validateRangeEnd(char* optarg, entryR* entryR, entryG* entryG);

void validateRangeStart(char* optarg, entryR* entryR, entryG* entryG);

void validateColumns(char* optarg, entryR* entryR, entryG* entryG);

void validateRows(char* optarg, entryR* entryR, entryG* entryG);

void checkDataGen(entryG* entryG, entryR* entryR);

void checkDataRead(entryR* entryR, entryG* entryG);

void ifModeWasDeclared(short int mode, entryR* entryR, entryG* entryG);

#endif