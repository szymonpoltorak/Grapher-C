#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include "readGraph.h"
#include "genGraph.h"
#include "utils.h"

const char* usage = {
    "For the Generate Modes:\n\
    ./grapher [mode] [file] [rows] [columns] [start] [end]\n\
    For the Read Mode:\n\
    ./grapher [mode] [file] [flag] [points]\n\
    Every argument needs to be set be the user in program call.\n\
    For more detailed info check documentation.\n"
};

int main(int argc, char** argv){
    if (argc == 1){
        fprintf(stderr, "NO MODE FOUND. USAGE:\n%s\n",usage);
        exit(NO_MODE_FOUND);
    }

    short int mode = NO_MODE;

    srand(time(NULL));

    entryG* entryG = allocEntryGen();
    entryR* entryR = allocEntryRead();

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
                ifModeWasDeclared(mode, entryR, entryG);
                entryG -> mode = mode = WEIGHT;
                break;
            case 'm':
                ifModeWasDeclared(mode, entryR, entryG);
                entryG -> mode = mode = RANDOM;
                break;
            case 'e':
                ifModeWasDeclared(mode, entryR, entryG);
                entryG -> mode = mode = EDGE;
                break;                
            case 'r':
                ifModeWasDeclared(mode, entryR, entryG);
                mode = READ;
                break;               
            case 'x':
                ifReadMode(mode, entryR, entryG);
                entryR -> printFlag = EXTENDED;
                break;
            case 's':
                ifReadMode(mode, entryR, entryG);
                entryR -> printFlag = STANDARD;
                break;
            case 'f':
                validateFileName(optarg, entryR, entryG);
                if (mode == READ){
                    entryR -> fileName = optarg;
                }
                else {
                    entryG -> fileName = optarg;
                }
                break;
            case 'c':
                if (mode != READ){
                    validateColumns(optarg, entryR, entryG);
                    entryG -> columns = atoi(optarg);
                }
                else {
                    fprintf(stderr, "COLUMNS ARE NOT BEING DECLARED IN READ MODE. USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(WRONG_MODE);
                }
                break;
            case 'o':
                if (mode != READ){
                    validateRows(optarg, entryR, entryG);
                    entryG -> rows = atoi(optarg);
                }
                else {
                    fprintf(stderr, "ROWS ARE NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(WRONG_MODE);
                }            
                break;
            case 'p':
                ifReadMode(mode, entryR, entryG);
                allocPoints(optarg, entryR, entryG);
                break;
            case 'n':
                if (mode != READ){
                    validateRangeEnd(optarg, entryR, entryG);
                    entryG -> rangeEnd = atof(optarg);
                }
                else {
                    fprintf(stderr, "RANGE END IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(WRONG_MODE);
                }
                break;
            case 't':
                if (mode != READ){
                    validateRangeStart(optarg, entryR, entryG);
                    entryG -> rangeStart = atof(optarg);
                }
                else {
                    fprintf(stderr, "RANGE START IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);//
                    freeAll(entryR, entryG);
                    exit(WRONG_MODE);
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

    if (mode != READ){
        checkDataGen(entryG, entryR);
        generateMode(entryG);
    }
    else {
        checkDataRead(entryR, entryG);
        readMode(entryR);
    }

    freeAll(entryR, entryG);

    exit(EXIT_SUCCESS);
}
