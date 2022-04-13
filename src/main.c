#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "options.h"

const char* usage = {
    "For the Generate Modes:\n\
    ./grapher [mode] [file] [rows] [columns] [start] [end]\n\
    For the Read Mode:\n\
    ./grapher [mode] [file] [flag] [points]\n\
    Every argument needs to be set by the user in program call.\n\
    For more detailed info check documentation.\n"
};

int main(int argc, char** argv){
    checkArgc(argc);

    srand(time(NULL));

    entryG* entryG = allocEntryGen();
    entryR* entryR = allocEntryRead(entryG);
    short int mode = checkOptions(entryG, entryR, argc, argv);

    chooseProperMode(entryG, entryR, mode);

    exit(EXIT_SUCCESS);
}
