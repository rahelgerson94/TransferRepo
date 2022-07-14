

#include "zq.h"

void ZQ_print_tree(ZQDecisionTree* root){
    /* print out a text representation of a decision tree. */
}


ZQDecisionTree* ZQ_build_tree(char* file_name){
/*
 inputs: a char* which represents the name of the file to load the data from.
 returns: a ZQDecisionTree that has been populated with all of the questions.
 this function opens up the file, iterate through the data within, creating an
 intermediate data structure to store it in) and populate a decision tree.
 During this process, the answers should not be added to the tree, just the question structure and
 leaf nodes with no questions or answers are added to the tree. Every level of this
 totally-full tree should have the same question.*/
    ZQDecisionTree* n = malloc(1);
    return n;
}

void ZQ_populate_tree(ZQDecisionTree* tree, char* file_name){
/*
 This takes a previously-built tree and a char* with the name of the data file.
 The function populates the tree with the answers within the correct leaf nodes based on the data
 from the file, following the correct yes/no paths through the tree.
 */
}
void ZQ_free_tree(ZQDecisionTree* tree){
    /* free all memory associated with tree.*/
}
