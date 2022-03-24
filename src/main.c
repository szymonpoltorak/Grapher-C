#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
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
    short int mode = 0;

    srand(time(NULL));

    entryG* entryG = allocEntryGen();
    entryR* entryR = allocEntryRead();
    
    if (argc == 1){
        fprintf(stderr, "%s : NO MODE FOUND. USAGE:\n%s\n", argv[0], usage);
        exit(NO_MODE_FOUND);
    }

    while(true){
        int flag;
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
        };

        if ((flag = getopt_long_only(argc, argv, "", flags, NULL)) == -1)
            break;

        switch(flag){
            case 'w': //to do
                printf("Using Weight Mode\n");
                mode = WEIGHT;
                break;
            case 'm': //to do
                printf("Using Random Mode\n");
                mode = RANDOM;
                break;
            case 'e': //to do
                printf("Using Edge Mode\n");
                mode = EDGE;
                break;                
            case 'r': //to do
                printf("Using Read Mode\n");
                mode = READ;
                break;               
            case 'x': //done
                ifReadMode(usage, mode);
                entryR -> printFlag = EXTENDED;
                break;
            case 's': //done
                ifReadMode(usage, mode);
                entryR -> printFlag = STANDARD;
                break;
            case 'f': //done
                validateFileName(optarg, usage);
                if (mode == READ){
                    entryR -> fileName = optarg;
                }
                else {
                    entryG -> fileName = optarg;
                }
                break;
            case 'c': //done
                if (mode != READ){
                    validateColumns(optarg, usage);
                    entryG -> columns = atoi(optarg);
                }
                else {
                    fprintf(stderr, "COLUMNS ARE NOT BEING DECLARED IN READ MODE. USAGE:\n%s\n", usage);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'o': //done
                if (mode != READ){
                    validateRows(optarg, usage);
                    entryG -> rows = atof(optarg);
                }
                else {
                    fprintf(stderr, "ROWS ARE NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    exit(EXIT_FAILURE);
                }            
                break;
            case 'p': //done
                ifReadMode(usage, mode);
                allocPoints(optarg, entryR);
                break;
            case 'n': //done
                if (mode != READ){
                    validateRangeEnd(optarg, usage);
                    entryG -> rangeEnd = atof(optarg);
                }
                else {
                    fprintf(stderr, "RANGE END IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    exit(EXIT_FAILURE);
                }
                break;
            case 't': //done
                if (mode != READ){
                    validateRangeStart(optarg, usage);
                    entryG -> rangeStart = atof(optarg);
                }
                else {
                    fprintf(stderr, "RANGE START IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);
                    exit(EXIT_FAILURE);                    
                }
                break;
            default: //to do
                fprintf(stderr, "%s : NO MODE FOUND. USAGE:\n%s\n", argv[0], usage);
                exit(NO_MODE_FOUND);
        }
    }

    if (entryG -> rangeStart > entryG -> rangeEnd){
        fprintf(stderr, "WRONG RANGE OF WEIGHTS!! ERROR CODE: 505\n");
        exit(WRONG_RANGE_OF_WAGES);
    }
    
    free(entryG);
    freeEntryRead(entryR);

    exit(EXIT_SUCCESS);
}
