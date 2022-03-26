#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include "readGraph.h"
#include "genGraph.h"
#include "utils.h"

int main(int argc, char** argv){
    const char* usage = {
        "For the Generate Modes:\n\
        ./grapher [mode] [file] [rows] [columns] [start] [end]\n\
        For the Read Mode:\n\
        ./grapher [mode] [file] [flag] [points]\n\
        For more detailed info check documentation\n"
    };
    short int mode = NO_MODE;

    srand(time(NULL));

    entryG* entryG = allocEntryGen();
    entryR* entryR = allocEntryRead();

    if (argc == 1){
        fprintf(stderr, "%s : NO MODE FOUND. USAGE:\n%s\n", argv[0], usage);
        freeAll(entryR, entryG);
        exit(NO_MODE_FOUND);
    }

    while(true){
        int flag = 0;
        opterr = 0; //wyłącza error dla getopt

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
                ifModeWasDeclared(usage, mode, entryR, entryG);
                entryG -> mode = mode = WEIGHT;
                break;
            case 'm':
                ifModeWasDeclared(usage, mode, entryR, entryG);
                entryG -> mode = mode = RANDOM;
                break;
            case 'e':
                ifModeWasDeclared(usage, mode, entryR, entryG);
                entryG -> mode = mode = EDGE;
                break;                
            case 'r':
                ifModeWasDeclared(usage, mode, entryR, entryG);
                mode = READ;
                break;               
            case 'x':
                ifReadMode(usage, mode, entryR, entryG);
                entryR -> printFlag = EXTENDED;
                break;
            case 's':
                ifReadMode(usage, mode, entryR, entryG);
                entryR -> printFlag = STANDARD;
                break;
            case 'f':
                validateFileName(optarg, usage, entryR, entryG);
                if (mode == READ){
                    entryR -> fileName = optarg;
                }
                else {
                    entryG -> fileName = optarg;
                }
                break;
            case 'c':
                if (mode != READ){
                    validateColumns(optarg, usage, entryR, entryG);
                    entryG -> columns = atoi(optarg);
                }
                else {
                    fprintf(stderr, "COLUMNS ARE NOT BEING DECLARED IN READ MODE. USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'o':
                if (mode != READ){
                    validateRows(optarg, usage, entryR, entryG);
                    entryG -> rows = atoi(optarg);
                }
                else {
                    fprintf(stderr, "ROWS ARE NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(EXIT_FAILURE);
                }            
                break;
            case 'p':
                ifReadMode(usage, mode, entryR, entryG);
                allocPoints(optarg, entryR, entryG);
                break;
            case 'n':
                if (mode != READ){
                    validateRangeEnd(optarg, usage, entryR, entryG);
                    entryG -> rangeEnd = atof(optarg);
                }
                else {
                    fprintf(stderr, "RANGE END IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(EXIT_FAILURE);
                }
                break;
            case 't':
                if (mode != READ){
                    validateRangeStart(optarg, usage, entryR, entryG);
                    entryG -> rangeStart = atof(optarg);
                }
                else {
                    fprintf(stderr, "RANGE START IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    freeAll(entryR, entryG);
                    exit(EXIT_FAILURE);                    
                }
                break;
            default:
                fprintf(stderr, "NO MODE FOUND. USAGE:\n%s\n", usage);
                freeAll(entryR, entryG);
                exit(NO_MODE_FOUND);
        }
    }

    if (entryG -> rangeStart >= entryG -> rangeEnd && mode != READ){
        fprintf(stderr, "WRONG RANGE OF WEIGHTS!! ERROR CODE: 505\n");
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