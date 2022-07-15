
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define debug
#define BUFFSIZE 10
#define EOL '\n'
int my_main();
void test_append();
void read_(FILE* data, char** questions, char*** game_info, int* num_qs, int* num_lines);

char** game_data;
char* questions;
char* line;
int num_lines, num_qs;
//void read_line(char* curr_buff, char** next_buff, char** line, int* num_buffs);
char* read_line(char* curr_buff, char** next_buff, char* temp, int* num_buffs);
int main(int argc, const char * argv[]) {
    questions = calloc(BUFFSIZE+1, sizeof(char));
    
//    char* curr_data = calloc(BUFFSIZE+1, sizeof(char));
//    char* prev_data = calloc(BUFFSIZE+1, sizeof(char));
//    char* temp = calloc(BUFFSIZE+1, sizeof(char));
//    char* prev_data1 = calloc(BUFFSIZE+1, sizeof(char));
//    char* line1 = calloc(BUFFSIZE+1, sizeof(char));
    //char* path = calloc(strlen(argv[1])+1, sizeof(char));
    char* path = (char*)argv[1];
    //strcpy(path, argv[1]);
    FILE* data = fopen(path, "r");
    read_( data, &questions, &game_data, &num_qs, &num_lines);
#ifdef  debug
    for (int i = 0; i < num_lines; i++){
        printf("%s\n", *(game_data+i));
    }
#endif
#ifdef debug
        printf("questions:");
        printf("%s\n", questions);
#endif

    
//    int l = 0;
//    int num_buffs=1;
//    while(fgets(curr_data, BUFFSIZE, data) != NULL){
//        if (l == 0){ //number of qs
//            num_lines = atoi(curr_data);
//            game_data = calloc(1+num_lines, sizeof(char*));
//            //char* game_data[num_lines];
//
//            l++;
//            num_buffs = 1; //rst  num_buffs for next code block;
//            continue;
//        }
//        if (l==1){ //the questions
//            if (count(curr_data, "\n" ) <= 0 ){ //if curr_data does not contain a newline char
//                questions = read_line(curr_data, &prev_data, questions, &num_buffs);
//                //questions = read_line(curr_data, &prev_data, questions, &num_buffs);
//                //read_line(curr_data, &prev_data, &temp, &num_buffs);
//            }
//            else { //the possible objects and their clues
//                char temp[BUFFSIZE*num_buffs]; memset(temp, '\0', BUFFSIZE*num_buffs); //strip newline char
//                strcpy_(temp, curr_data, 0, 0, BUFFSIZE*num_buffs);
//                questions = read_line(temp, &prev_data, questions, &num_buffs);
//                l++;
//#ifdef debug
//                printf("questions:");
//                printf("%s\n", questions);
//#endif
//                num_buffs = 1; // reset for next if block
//                l++;
//                continue;
//            }
//        }//end l==1
//        int data_i = l-3; //data_i is the index of our data array. each elem in data looks like: obj,0,1,0,...0
//        if (l>=2 ){
//            if ( data_i < num_lines -1){ //the rest is possible objects and answers to questions
//                if (count(curr_data, "\n" ) <= 0 ){ //if curr_data doesn't contain a newline char
//                    line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
//                    //read_line(curr_data, &prev_data, &temp, &num_buffs);
//                }
//                else { //buff contains newline
//                    //line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
//                    char temp[BUFFSIZE*num_buffs]; memset(temp, '\0', BUFFSIZE*num_buffs);
//                    strcpy_(temp, curr_data, 0, 0, BUFFSIZE*num_buffs);
//                    line1 = read_line(temp, &prev_data1, line1, &num_buffs);
//                    *(game_data+ data_i) = calloc(1+len_char(line1)+1, sizeof(char));
//                    strcpy_(*(game_data+ data_i), line1, 0, 0, len_char(line1));
//    #ifdef debug
//                printf("game_data[%d]:",data_i );
//                printf("%s\n", *(game_data+data_i));
//    #endif
//                    free(line1);
//                    free(prev_data1);
//                    line1 = calloc(1+BUFFSIZE, sizeof(char));
//                    prev_data1 = calloc(1+BUFFSIZE, sizeof(char));
//                    num_buffs = 1;
//                    l++;
//                    continue;
//                }
//            }//data_i < num_lines -1
//            else{// we are on the last line
//                    line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
//                    *(game_data+ data_i) = calloc(1+ len_char(line1), sizeof(char));
//                    strcpy_(*(game_data+ data_i), line1, 0, 0, len_char(line1));
//                }//end NOT(data_i == num_lines -1)
//            }//end l>=2
//    }//end while
//
//#ifdef  debug
//    for (int i = 0; i < num_lines; i++){
//        printf("%s\n", *(game_data+i));
//    }
//
//#endif
///*CLEANUP*/
//    fclose(data);
//    /*freeing data*/
    free(path);
///* *************************** DONE READING IN THE DATA ******************************************* */
//    char* objects[num_lines];
//    int num_qs = count(questions, "?");
//    int answers[num_lines][num_qs];
//
//
//
//    free(curr_data);
//    free(prev_data);
//    free(prev_data1);
//    free(line1);
//    free(temp);
    for (int i = 0; i < num_lines+1; i++)
        free(*(game_data+ i));
    free(game_data);
    return 0;
}



/*
 void read_line(char* curr_buff, char** prev_buff, char** line, int* num_buffs){
     free(*line);
     *line =  calloc(BUFFSIZE*(*num_buffs), sizeof(char));
     strcpy(*line, *prev_buff);
     strcat(*line, curr_buff);
     free(*prev_buff);
     *prev_buff = calloc(BUFFSIZE*(*num_buffs), sizeof(char));
     strcpy(*prev_buff, *line);
     (*num_buffs)++;
    
 }
 */

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

void test_append(){
    printf("test_append()\n");
    char* s1= calloc(10,sizeof(char));
    char* s2 = calloc(10,sizeof(char));
    strcpy(s1, "hello!!");
    strcpy(s2, "hi!");
    
    str_append(&s1, s2);
    printf("%s\n", s1);
    free(s1);
    free(s2);
    printf("\n");
}

void parse(){
    
}

void read_(FILE* data, char** questions, char*** game_info, int* num_qs, int* num_lines){
    *questions = calloc(BUFFSIZE+1, sizeof(char));
    char* curr_data = calloc(BUFFSIZE+1, sizeof(char));
    char* prev_data = calloc(BUFFSIZE+1, sizeof(char));
    char* temp = calloc(BUFFSIZE+1, sizeof(char));
    char* prev_data1 = calloc(BUFFSIZE+1, sizeof(char));
    char* line1 = calloc(BUFFSIZE+1, sizeof(char));
    int l = 0;
    int num_buffs=1;
    while(fgets(curr_data, BUFFSIZE, data) != NULL){
        if (l == 0){ //number of qs
            *num_lines = atoi(curr_data);
            *game_info = calloc(1+num_lines, (int)sizeof(char*));
            //char* game_info[num_lines];
            
            l++;
            num_buffs = 1; //rst  num_buffs for next code block;
            continue;
        }
        if (l==1){ //the questions
            if (count(curr_data, "\n" ) <= 0 ){ //if curr_data does not contain a newline char
                *questions = read_line(curr_data, &prev_data, *questions, &num_buffs);
                //questions = read_line(curr_data, &prev_data, questions, &num_buffs);
                //read_line(curr_data, &prev_data, &temp, &num_buffs);
            }
            else { //the possible objects and their clues
                char temp[BUFFSIZE*num_buffs]; memset(temp, '\0', BUFFSIZE*num_buffs); //strip newline char
                strcpy_(temp, curr_data, 0, 0, BUFFSIZE*num_buffs);
                *questions = read_line(temp, &prev_data, *questions, &num_buffs);
                l++;
//#ifdef debug
//                printf("questions:");
//                printf("%s\n", *questions);
//#endif
                num_buffs = 1; // reset for next if block
                l++;
                continue;
            }
        }//end l==1
        int data_i = l-3; //data_i is the index of our data array. each elem in data looks like: obj,0,1,0,...0
        if (l>=2 ){
            if ( data_i < *num_lines -1){ //the rest is possible objects and answers to questions
                if (count(curr_data, "\n" ) <= 0 ){ //if curr_data doesn't contain a newline char
                    line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
                    //read_line(curr_data, &prev_data, &temp, &num_buffs);
                }
                else { //buff contains newline
                    //line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
                    char temp[BUFFSIZE*num_buffs]; memset(temp, '\0', BUFFSIZE*num_buffs);
                    strcpy_(temp, curr_data, 0, 0, BUFFSIZE*num_buffs);
                    line1 = read_line(temp, &prev_data1, line1, &num_buffs);
                    *(*game_info+ data_i) = calloc(1+len_char(line1)+1, sizeof(char));
                    strcpy_(*(*game_info+ data_i), line1, 0, 0, len_char(line1));
//    #ifdef debug
//                printf("game_info[%d]:",data_i );
//                printf("%s\n", *(*game_info+data_i));
//    #endif
                    free(line1);
                    free(prev_data1);
                    line1 = calloc(1+BUFFSIZE, sizeof(char));
                    prev_data1 = calloc(1+BUFFSIZE, sizeof(char));
                    num_buffs = 1;
                    l++;
                    continue;
                }
            }//data_i < num_lines -1
            else{// we are on the last line
                    line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
                    *(*game_info+ data_i) = calloc(1+ len_char(line1), sizeof(char));
                    strcpy_(*(*game_info+ data_i), line1, 0, 0, len_char(line1));
                }//end NOT(data_i == num_lines -1)
            }//end l>=2
    }//end while
    
//#ifdef  debug
//    for (int i = 0; i < num_lines; i++){
//        printf("%s\n", *(*game_info+i));
//    }
//
//#endif
    *num_qs = count(*questions, "?");

/*CLEANUP*/
    fclose(data);
    /*freeing data*/
    free(curr_data);
    free(prev_data);
    free(prev_data1);
    free(line1);
    free(temp);
}

