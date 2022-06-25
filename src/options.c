#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "options.h"
#include "enters.h"

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

        if ((flag = getopt_long_only(argc, argv, "", flags, NULL)) == -1){
            break;
        }

        switch(flag){
            case 'w':
                mode = enterWageMode(entryR, entryG, mode);
                break;
            case 'm':
                mode = enterRandomMode(entryR, entryG, mode);
                break;
            case 'e':
                mode = enterEdgeMode(entryR, entryG, mode);
                break;
            case 'r':
                mode = enterReadMode(entryR, entryG, mode);
                break;
            case 'x':
                enterExtendedPrintFlag(entryR, entryG, mode);
                break;
            case 's':
                enterStandardPrintFlag(entryR, entryG, mode);
                break;
            case 'f':
                enterFile(entryR, entryG, mode, optarg);
                break;
            case 'c':
                enterColumns(entryR, entryG, mode, optarg);
                break;
            case 'o':
                enterRows(entryR, entryG, mode, optarg);
                break;
            case 'p':
                enterPoints(entryR, entryG, mode, optarg);
                break;
            case 'n':
                enterRangeEnd(entryR, entryG, mode, optarg);
                break;
            case 't':
                enterRangeStart(entryR, entryG, mode, optarg);
                break;
            default:
                fprintf(stderr, "INVALID DATA. USAGE:\n%s\n", usage);
                freeEntries(entryR, entryG);
                exit(INVALID_DATA);
        }
    }

    if (entryG -> rangeStart >= entryG -> rangeEnd && mode != READ){
        fprintf(stderr, "WRONG RANGE OF WEIGHTS!! USAGE:\n%s\n", usage);
        freeEntries(entryR, entryG);
        exit(WRONG_RANGE_OF_WAGES);
    }

    return mode;
}

void chooseProperMode(entryG* entryG, entryR* entryR, short int mode){
    if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
        checkDataGen(entryG, entryR);
        freeEntryRead(entryR);
        generateMode(entryG);
    } else if (mode == READ){
        checkDataRead(entryR, entryG);
        free(entryG);
        readMode(entryR);
    } else {
        fprintf(stderr, "UNKNOWN MODE !!\n");
        exit(NO_MODE_FOUND);
    }
}
