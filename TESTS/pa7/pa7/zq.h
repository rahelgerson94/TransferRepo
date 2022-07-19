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
void process(char** data, char delim, int num_lines, char* col1[], char* col2[]);
void read_(FILE* data , int indices[], char*** file_data, int* num_lines);
char* read_line(char* curr_buff, char** next_buff, char* temp, int* num_buffs );
void parse_line(char* line, char delim, char** out1, char** out2);



void ZQ_print_tree(ZQDecisionTree* root);
void ZQ_print_tree_helper(ZQDecisionTreeNode* curr, int level);
ZQDecisionTree* ZQ_build_tree(char* file_name);
void ZQ_populate_tree(ZQDecisionTree* tree, char* file_name);
void ZQ_free_tree(ZQDecisionTree* tree);
ZQDecisionTreeNode* ZQ_build_tree_helper(char** field, int num_levels, int curr_level);

//void ZQ_populate_tree_helper(ZQDecisionTreeNode* tree, ZQDecisionTreeNode node, char* field, int* map, int num_levels, int curr_level);

//void ZQ_populate_tree_helper(ZQDecisionTreeNode* node, char* field, int* map, int num_levels, int curr_level);
void ZQ_populate_tree_helper(ZQDecisionTreeNode* node, char* field, int* map, int curr_lvl, int num_lvls);

void ZQ_print_node_info(ZQDecisionTreeNode* node);
void ZQ_db_print_tree_helper(ZQDecisionTreeNode* cur, int level);
void ZQ_db_print_tree(ZQDecisionTree* tree);

#endif /* zq_h */
