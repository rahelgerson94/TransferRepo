//
//  zq.h
//  pa7
//
//  Created by Rahel Gerson on 7/13/22.
//

#ifndef zq_h
#define zq_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* A ZQDecisionTreeNode represents one question or group of answers. */
typedef struct ZQDecisionTreeNode{
    char text[50];
    int num_answers;
    char** answers;
    struct ZQDecisionTreeNode* yes;
    struct ZQDecisionTreeNode* no;
}ZQDecisionTreeNode;
typedef struct ZQDecisionTree{
    ZQDecisionTreeNode* root;
}ZQDecisionTree;

/* functions*/
void ZQ_print_tree(ZQDecisionTree* root);
ZQDecisionTree* ZQ_build_tree(char* file_name);
void ZQ_populate_tree(ZQDecisionTree* tree, char* file_name);
void ZQ_free_tree(ZQDecisionTree* tree);

/* helper functions */
ZQDecisionTreeNode* create_node(){
    ZQDecisionTreeNode* n= malloc(1);
    return n;
}
#endif /* zq_h */
