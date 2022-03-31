#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "readGraph.h"
#include "genGraph.h"
#include "utils.h"

short int checkOptions(entryG* entryG, entryR* entryR, int argc, char** argv);

void chooseProperMode(entryG* entryG, entryR* entryR, short int mode);

#endif
