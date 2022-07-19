
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
#ifdef db_preproc
    for (int i = 0; i < 3+1; i++)
        printf("%s\n", *(list+i));
#endif
    ZQDecisionTree* tree = ZQ_build_tree(path);
    //ZQ_db_print_tree(tree);
    //ZQ_populate_tree(tree, path);
    ZQ_db_print_tree(tree);

    //ZQ_populate_tree( tree, path);

    free(tree);
    free(path);
    return 0;
}


