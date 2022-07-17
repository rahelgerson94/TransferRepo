
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "zq.h"







int main(int argc, const char * argv[]) {
    //questions = calloc(BUFFSIZE+1, sizeof(char));
    char* path = calloc(strlen(argv[1])+1, sizeof(char));
    //char* path = (char*)argv[1];
    strcpy(path, argv[1]);
    
    char* line = "apple,cat,dog,baby";
    char* list[4];
    delimit(line, ',', list);

    for (int i = 0; i < 3+1; i++){
        printf("%s\n", *(list+i));
    }
    ZQDecisionTree* tree = ZQ_build_tree(path);
    
   
    return 0;
}


