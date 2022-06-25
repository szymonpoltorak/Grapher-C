#ifndef _ENTERS_H_
#define _ENTERS_H_

#include "alloc.h"

void enterStandardPrintFlag(entryR* entryR, entryG* entryG, int mode);

void enterExtendedPrintFlag(entryR* entryR, entryG* entryG, int mode);

void enterFile(entryR* entryR, entryG* entryG, int mode, char* optarg);

void enterRows(entryR* entryR, entryG* entryG, int mode, char* optarg);

void enterColumns(entryR* entryR, entryG* entryG, int mode, char* optarg);

void enterRangeStart(entryR* entryR, entryG* entryG, int mode, char* optarg);

void enterRangeEnd(entryR* entryR, entryG* entryG, int mode, char* optarg);

void enterPoints(entryR* entryR, entryG* entryG, int mode, char* optarg);

short int enterWageMode(entryR* entryR, entryG* entryG, int mode);

short int enterReadMode(entryR* entryR, entryG* entryG, int mode);

short int enterEdgeMode(entryR* entryR, entryG* entryG, int mode);

short int enterRandomMode(entryR* entryR, entryG* entryG, int mode);

#endif