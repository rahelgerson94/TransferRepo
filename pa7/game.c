//
//  game.c
//  pa7
//
//  Created by Rahel Gerson on 7/22/22.
//
#include "zq.h"
#include <stdio.h>
int main(int argc, const char * argv[]) {
    //questions = calloc(BUFFSIZE+1, sizeof(char));
    char* path = calloc(strlen(argv[1])+1, sizeof(char));
    //char* path = (char*)argv[1];
    strcpy(path, argv[1]);
    ZQDecisionTree* tree = ZQ_build_tree(path);
   
    ZQ_populate_tree(tree, path);
    ZQ_print_tree(tree);
    ZQ_free_tree(tree);
    free(path);
    return 0;
}

 
