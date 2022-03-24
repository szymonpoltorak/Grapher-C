#ifndef _UTILS_H_
#define _UTILS_H_

#define NO_FILE_FOUND 231

#define EDGE 2
#define WEIGHT 1
#define RANDOM 3 
#define READ 4

void ifReadMode(const char* usage, short unsigned int mode);

void validateFileName(char* optarg, const char* usage);

#endif