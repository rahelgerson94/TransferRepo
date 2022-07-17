
#define debug
#define BUFFSIZE 10
#include "zq.h"
#include "utils.h"

void ZQ_print_tree(ZQDecisionTree* root){
    /* print out a text representation of a decision tree. */
}


ZQDecisionTree* ZQ_build_tree(char* file_name){
    FILE* data = fopen(file_name, "r");
    int indices[1]  = {0};
    char** file_data;
    int num_lines;
    read_(data, indices, &file_data, &num_lines);
#ifdef  debug
    printf("ZQ_build_tree()\n");
    for (int i = 0; i < num_lines+1; i++){
        printf("%s\n", *(file_data+i));
    }
#endif
    char* questions = *(file_data+0);
    int num_levels = count_char(questions, '?');
    
    char* qs_list[num_lines];
    delimit(questions, '?', qs_list);
    
    ZQDecisionTree* root = ZQ_build_tree_helper(questions, num_levels, 1);
 /* ***************************  CLEANUP ******************************************* */
  
    
    for (int i = 0; i < num_lines+1; i++)
        free(*(file_data+ i));
    free(file_data);
    
    for (int i = 0; i < num_lines; i++)
        free(*(qs_list+ i));
    
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

ZQDecisionTree* ZQ_build_tree_helper(char** questions, int num_levels, int curr_lvl ){
    ZQDecisionTree* root;
    if (curr_lvl == num_levels){
        return root;
    }
    else{
        ZQDecisionTreeNode* root = calloc(sizeof(ZQDecisionTree), 1);
        strcpy(root->text,  *(questions+curr_lvl));
        (*root)->yes = ZQ_build_tree_helper(questions, num_levels, curr_lvl++);
        root->no = ZQ_build_tree_helper(questions, num_levels, curr_lvl++);
    }
    return root;
}


void ZQ_populate_tree(ZQDecisionTree* tree, char* file_name){
    FILE* data = fopen(file_name, "r");
    int indices[1]  = {0};
    char** file_data;
    int num_lines;
    read_(data, indices, &file_data, &num_lines);
#ifdef  debug
    printf("ZQ_build_tree()\n");
    for (int i = 0; i < num_lines+1; i++){
        printf("%s\n", *(file_data+i));
    }
#endif
    char* questions = *(file_data+0);
    ZQDecisionTree* root = ZQ_build_tree_helper(questions, 0,0);
    
    char* col1[num_lines]; char* col2[num_lines];
    process(file_data, ',', num_lines, col1, col2);
#ifdef  debug
    printf("ZQ_build_tree()\n");
    for (int i = 0; i < num_lines; i++){
        printf("%d. %s\t", i, col1[i]);
        printf("%s\n", col2[i]);
    }
    printf("\n");
#endif
    
 /* ***************************  CLEANUP ******************************************* */
    for (int i = 0; i < num_lines; i++)
        free(*(col1+ i));
    for (int i = 0; i < num_lines; i++)
        free(*(col2+ i));
    for (int i = 0; i < num_lines+1; i++)
        free(*(file_data+ i));
    free(file_data);
/*
 This takes a previously-built tree and a char* with the name of the data file.
 The function populates the tree with the answers within the correct leaf nodes based on the data
 from the file, following the correct yes/no paths through the tree.
 */
}
void ZQ_free_tree(ZQDecisionTree* tree){
    /* free all memory associated with tree.*/
}
/* helper functions */

/* this function splits the data contained in data and places it into col1 and col2, based on a delimter.
 the data before the first occurence of delim will be in col1, and all data after that first delim
 will be in col2.
 col1 and col2 are outparams */
void process(char** data, char delim, int num_lines, char* col1[], char* col2[]){
    //int num_qs = count(*data, "?");
    int num_qs = count_char(*data, '?');
    int col2_elems = (num_qs*2) - 1; //col2 elems are always 1 digit, and look like 0,1,... and we know how many 0's and 1s there are (there are num_qs of them)
    
    /* allocate  space for col2*/
    for (int l = 0; l < num_lines; l ++){
        col2[l] = calloc(col2_elems, sizeof(char)); // allocate space for each row in col2//*col2[l] this did not work
    }
    
#ifdef  debug
    printf("process()\n");
    for (int i = 1; i < num_lines+1; i++){
        printf("%s\n", *(data+i));
    }
    printf("\n");
#endif
    //populate col1, col2
    for (int l = 0; l < num_lines; l++){
        int col1_elems = len_char(*(data+l+1))-col2_elems;
        col1[l] = calloc(col1_elems, sizeof(char));
        parse_line(*(data+l+1), ',', &(col1[l]), &(col2[l]));
#ifdef  debug
        printf("%d. %s\t", l, col1[l]);
        printf("%s\n", col2[l]);
    }
#endif
}


void parse_line(char* line, char delim, char** out1, char** out2){
    int c = 0;
    while (line[c] != delim){
        *(*out1+c) = line[c];
        c++;
    }
    *(*out1+c) = '\0';
    int out2_i = 0;
    c = c+1;
    while (line[c] != '\0'){
        *(*out2+out2_i) = line[c];
        c++;
        out2_i++;
    }
    *(*out2+out2_i) = '\0';
}

char* read_line(char* curr_buff, char** prev_buff, char* line, int* num_buffs){
    free(line);
    line =  calloc(BUFFSIZE*(*num_buffs)+1, sizeof(char));
    //strcpy_(line, *prev_buff, 0, 0, BUFFSIZE*(*num_buffs));
    strcpy(line, *prev_buff);
    strcat(line, curr_buff);
    free(*prev_buff);
    *prev_buff = calloc(BUFFSIZE*(*num_buffs), sizeof(char));
    strcpy(*prev_buff, line);
    (*num_buffs)++;
    return line;
}


/* this function stores the info contained in a file in a variable, file_data
 the first line must contain the number of lines in the file
 file_data,then   stores all lines except the first */
void read_(FILE* data , int indices[], char*** file_data, int* num_lines){
    /*
     indices: the lines that are to be treated as special
     */
    char* curr_data = calloc(BUFFSIZE+1, sizeof(char));
    char* prev_data = calloc(BUFFSIZE+1, sizeof(char));
    char* line = calloc(BUFFSIZE+1, sizeof(char));
    int l = 0;
    int data_i=0;
    int num_buffs=1;
    while(fgets(curr_data, BUFFSIZE, data) != NULL){
        data_i = l-1;
        if (l == indices[0]){ //number of qs
            *num_lines = atoi(curr_data);
            *file_data = calloc(1 + *num_lines, sizeof(char*));
            l++;
            num_buffs = 1; //rst  num_buffs for next code block;
            continue;
        }
        else{  //the questions
            if ( data_i < *num_lines ){
                //if (count(curr_data, "\n" ) <= 0 ){ //if curr_data does not contain a newline char
                if (count_char(curr_data, '\n' ) <= 0 ){ //if curr_data does not contain a newline char
                    line = read_line(curr_data, &prev_data, line, &num_buffs);
                    //questions = read_line(curr_data, &prev_data, questions, &num_buffs);
                    //read_line(curr_data, &prev_data, &temp, &num_buffs);
                }
                else { //the possible objects and their clues
                    char temp_[BUFFSIZE*num_buffs]; memset(temp_, '\0', BUFFSIZE*num_buffs);
                    strcpy_(temp_, curr_data, 0, 0, BUFFSIZE*num_buffs);
                    line = read_line(temp_, &prev_data, line, &num_buffs);
                    *(*file_data+ data_i) = calloc(1+len_char(line), sizeof(char));
                    strcpy_(*(*file_data+ data_i), line, 0, 0, len_char(line));
//    #ifdef debug
//                    printf("file_data[%d]:", data_i);
//                    printf("%s\n", *(*file_data+ data_i));
//    #endif
                    free(line);
                    free(prev_data);
                    line = calloc(1+BUFFSIZE, sizeof(char));
                    prev_data = calloc(1+BUFFSIZE, sizeof(char));
                    num_buffs = 1;
                    l++;
                    continue;
                }
            }//end l < num_lines - 1
            else{
                line = read_line(curr_data, &prev_data, line, &num_buffs);
                *(*file_data+ data_i) = calloc(1+ len_char(line), sizeof(char));
                strcpy_(*(*file_data+ data_i), line, 0, 0, len_char(line));
#ifdef debug
                printf("%s\n", *(*file_data+ data_i));
#endif
                }//end NOT(data_i == num_lines -1)
            }//end l ≠ 0
        }//end while
    /*CLEANUP*/
    fclose(data);
    /*freeing data*/
    free(curr_data);
    free(prev_data);
    free(line);
}




