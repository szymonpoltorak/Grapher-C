#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

extern const char* usage;

short int checkOptions(entryG* entryG, entryR* entryR, int argc, char** argv){
    short int mode = NO_MODE;

        while(true){
        int flag = NO_FLAG;
        opterr = NO_ERRORS;

        static const struct option flags[] = {
            {"wm", no_argument, 0, 'w'},
            {"WM", no_argument, 0, 'w'},
            {"rem", no_argument, 0, 'm'},
            {"ReM", no_argument, 0, 'm'}, 
            {"EM", no_argument, 0, 'e'},
            {"em", no_argument, 0, 'e'}, 
            {"rm", no_argument, 0, 'r'},
            {"RM", no_argument, 0, 'r'},
            {"extended", no_argument, 0, 'x'},
            {"standard", no_argument, 0, 's'},
            {"file", required_argument, 0, 'f'},
            {"columns", required_argument, 0, 'c'},
            {"rows", required_argument, 0, 'o'},
            {"start", required_argument, 0, 't'},
            {"end", required_argument, 0, 'n'},
            {"points", required_argument, 0, 'p'},
            {0, 0, 0, 0}
        };

        if ((flag = getopt_long_only(argc, argv, "", flags, NULL)) == -1)
            break;

        switch(flag){
            case 'w':
                ifModeWasMultiplied(mode, entryR, entryG);
                entryG -> mode = mode = WEIGHT;
                break;
            case 'm':
                ifModeWasMultiplied(mode, entryR, entryG);
                entryG -> mode = mode = RANDOM;
                break;
            case 'e':
                ifModeWasMultiplied(mode, entryR, entryG);
                entryG -> mode = mode = EDGE;
                break;                
            case 'r':
                ifModeWasMultiplied(mode, entryR, entryG);
                mode = READ;
                break;               
            case 'x':
                ifModeWasDeclared(mode, entryR, entryG);
                ifReadMode(mode, entryR, entryG);
                entryR -> printFlag = EXTENDED;
                break;
            case 's':
                ifModeWasDeclared(mode, entryR, entryG);
                ifReadMode(mode, entryR, entryG);
                entryR -> printFlag = STANDARD;
                break;
            case 'f':
                ifModeWasDeclared(mode, entryR, entryG);
                validateFileName(optarg, entryR, entryG);
                if (mode == READ)
                    entryR -> fileName = optarg;
                else
                    entryG -> fileName = optarg;
                break;
            case 'c':
                ifModeWasDeclared(mode, entryR, entryG);
                if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
                    validateColumns(optarg, entryR, entryG);
                    entryG -> columns = atoi(optarg);
                }
                else if (mode == READ) {
                    fprintf(stderr, "COLUMNS ARE NOT BEING DECLARED IN READ MODE. USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(WRONG_MODE);
                }
                else {
                    fprintf(stderr, "UNKNOWN MODE !!\n");
                    exit(NO_MODE_FOUND);                    
                }
                break;
            case 'o':
                ifModeWasDeclared(mode, entryR, entryG);
                if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
                    validateRows(optarg, entryR, entryG);
                    entryG -> rows = atoi(optarg);
                }
                else if (mode == READ){
                    fprintf(stderr, "ROWS ARE NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(WRONG_MODE);
                }
                else {
                    fprintf(stderr, "UNKNOWN MODE !!\n");
                    exit(NO_MODE_FOUND);                    
                }                            
                break;
            case 'p':
                ifModeWasDeclared(mode, entryR, entryG);
                ifReadMode(mode, entryR, entryG);
                allocPoints(optarg, entryR, entryG);
                break;
            case 'n':
                ifModeWasDeclared(mode, entryR, entryG);
                if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
                    validateRangeEnd(optarg, entryR, entryG);
                    entryG -> rangeEnd = atof(optarg);
                }
                else if (mode == READ) {
                    fprintf(stderr, "RANGE END IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(WRONG_MODE);
                }
                else {
                    fprintf(stderr, "UNKNOWN MODE !!\n");
                    exit(NO_MODE_FOUND);                    
                }
                break;
            case 't':
                ifModeWasDeclared(mode, entryR, entryG);
                if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
                    validateRangeStart(optarg, entryR, entryG);
                    entryG -> rangeStart = atof(optarg);
                }
                else if (mode == READ) {
                    fprintf(stderr, "RANGE START IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);//
                    freeAll(entryR, entryG);
                    exit(WRONG_MODE);
                }
                else {
                    fprintf(stderr, "UNKNOWN MODE !!\n");
                    exit(NO_MODE_FOUND);                    
                }                
                break;
            default:
                fprintf(stderr, "INVALID DATA. USAGE:\n%s\n", usage);
                freeAll(entryR, entryG);
                exit(INVALID_DATA);
        }
    }

    if (entryG -> rangeStart >= entryG -> rangeEnd && mode != READ){
        fprintf(stderr, "WRONG RANGE OF WEIGHTS!! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_RANGE_OF_WAGES);
    }

    return mode;
}

void chooseProperMode(entryG* entryG, entryR* entryR, short int mode){
    if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
        checkDataGen(entryG, entryR);
        freeEntryRead(entryR);
        generateMode(entryG);
    }
    else if (mode == READ){
        checkDataRead(entryR, entryG);
        free(entryG);
        readMode(entryR);
    }
    else {
        fprintf(stderr, "UNKNOWN MODE !!\n");
        exit(NO_MODE_FOUND);
    }
}
