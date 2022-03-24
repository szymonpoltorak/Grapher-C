#ifndef _UTILS_H_
#define _UTILS_H_

#define NO_FILE_FOUND 231
#define WRONG_RANGE_OF_WAGES 234
#define WRONG_NUM_OF_COL 233

#define WEIGHT 1
#define EDGE 2
#define RANDOM 3 
#define READ 4

void ifReadMode(const char* usage, short int mode);

void validateFileName(char* optarg, const char* usage);

void validateRangeEnd(char* optarg, const char* usage);

void validateRangeStart(char* optarg, const char* usage);

void validateColumns(char* optarg, const char* usage);

#endif