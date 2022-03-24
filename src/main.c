#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
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
    short unsigned int mode = 0;

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
            case 'x': //to do
                ifReadMode(usage, mode);
                printf("Using Extended display\n");
                break;
            case 's': //to do
                ifReadMode(usage, mode);
                printf("Using Standard display\n");
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
            case 'c': //to do
                if (mode != READ){
                    entryG -> columns = atoi(optarg);
                }
                break;
            case 'o': //to do
                break;
            case 'p': //done
                ifReadMode(usage, mode);
                entryR -> points = allocPoints(optarg, entryR);
                break;
            case 'n': //to do
                break;
            case 't': //to do
                break;
            default:
                fprintf(stderr, "%s : NO MODE FOUND. USAGE:\n%s\n", argv[0], usage);
                exit(NO_MODE_FOUND);
        }
    }
    
    exit(EXIT_SUCCESS);
}
