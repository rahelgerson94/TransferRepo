
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define debug
#define BUFFSIZE 10
#define EOL '\n'
int my_main();
void test_append();
char** game_data;
char* questions;
char* line;
int num_qs;
//void read_line(char* curr_buff, char** next_buff, char** line, int* num_buffs);
char* read_line(char* curr_buff, char** next_buff, char* temp, int* num_buffs);
int main(int argc, const char * argv[]) {
    questions = calloc(BUFFSIZE, sizeof(char));
    char* curr_data = calloc(1+BUFFSIZE, sizeof(char));
    char* prev_data = calloc(1+BUFFSIZE, sizeof(char));
    char* temp = calloc(1+BUFFSIZE, sizeof(char));
    char* prev_data1 = calloc(1+BUFFSIZE, sizeof(char));
    char* line1 = calloc(1+BUFFSIZE, sizeof(char));
    char* path = calloc(1+strlen(argv[1])+1, sizeof(char));
    strcpy(path, argv[1]);
    FILE* data = fopen(path, "r");
    int l = 0;
    int num_buffs;
    while(fgets(curr_data, BUFFSIZE, data) != NULL){
        if (l == 0){ //number of qs
            num_qs = atoi(curr_data);
            game_data = calloc(1+num_qs, sizeof(char*));
            //char* game_data[num_qs];
            l++;
            num_buffs = 1; //rst  num_buffs for next code block;
            continue;
        }
        if (l==1){ //the questions
            if (count(curr_data, "\n" ) <= 0 ){ //if curr_data does not contain a newline char
                questions = read_line(curr_data, &prev_data, questions, &num_buffs);
                //questions = read_line(curr_data, &prev_data, questions, &num_buffs);
                //read_line(curr_data, &prev_data, &temp, &num_buffs);
            }
            else { //the possible objects and their clues
                char temp[BUFFSIZE*num_buffs]; memset(temp, '\0', BUFFSIZE*num_buffs); //strip newline char
                strcpy_(temp, curr_data, 0, 0, BUFFSIZE*num_buffs);
                questions = read_line(temp, &prev_data, questions, &num_buffs);
                l++;
#ifdef debug
                printf("questions:");
                printf("%s\n", questions);
#endif
                num_buffs = 1; // reset for next if block
                l++;
                continue;
            }
        }//end l==1
        int data_i = l-3; //data_i is the index of our data array. each elem in data looks like: obj,0,1,0,...0
        if (l>=2 ){
            if ( data_i < num_qs -1){ //the rest is possible objects and answers to questions
                if (count(curr_data, "\n" ) <= 0 ){ //if curr_data doesn't contain a newline char
                    line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
                    //read_line(curr_data, &prev_data, &temp, &num_buffs);
                }
                else { //buff contains newline
                    //line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
                    char temp[BUFFSIZE*num_buffs]; memset(temp, '\0', BUFFSIZE*num_buffs);
                    strcpy_(temp, curr_data, 0, 0, BUFFSIZE*num_buffs);
                    line1 = read_line(temp, &prev_data1, line1, &num_buffs);
                    *(game_data+ data_i) = calloc(1+len_char(line1), sizeof(char));
                    strcpy_(*(game_data+ data_i), line1, 0, 0, len_char(line1));
    #ifdef debug
                printf("game_data[%d]:",data_i );
                printf("%s\n", *(game_data+data_i));
    #endif
                    free(line1);
                    free(prev_data1);
                    line1 = calloc(1+BUFFSIZE, sizeof(char));
                    prev_data1 = calloc(1+BUFFSIZE, sizeof(char));
                    num_buffs = 1;
                    l++;
                    continue;
                }
            }//data_i < num_qs -1
            else{// we are on the last line
                    line1 = read_line(curr_data, &prev_data1, line1, &num_buffs);
                    *(game_data+ data_i) = calloc(1+len_char(line1), sizeof(char));
                    strcpy_(*(game_data+ data_i), line1, 0, 0, len_char(line1));
                }//end NOT(data_i == num_qs -1)
            }//end l>=2
    }//end while
    
#ifdef  debug
        for (int i = 0; i < num_qs; i++)
            printf("%s\n", *(game_data+i));
#endif
/*CLEANUP*/
    fclose(data);
    /*freeing data*/
    free(path);
    free(curr_data);
    free(prev_data);
    free(prev_data1);
    free(line1);
    free(temp);
    for (int i = 0; i < num_qs; i++)
        free(*(game_data+ i));
    free(game_data);
    return 0;
}



/*
 void read_line(char* curr_buff, char** prev_buff, char** line, int* num_buffs){
     free(*line);
     *line =  calloc(1+BUFFSIZE*(*num_buffs), sizeof(char));
     strcpy(*line, *prev_buff);
     strcat(*line, curr_buff);
     free(*prev_buff);
     *prev_buff = calloc(1+BUFFSIZE*(*num_buffs), sizeof(char));
     strcpy(*prev_buff, *line);
     (*num_buffs)++;
    
 }
 */

char* read_line(char* curr_buff, char** prev_buff, char* line, int* num_buffs){
    
    free(line);
    line =  calloc(1+BUFFSIZE*(*num_buffs), sizeof(char));
    //strcpy_(line, *prev_buff, 0, 0, BUFFSIZE*(*num_buffs));
    strcpy(line, *prev_buff);
    strcat(line, curr_buff);
    free(*prev_buff);
    *prev_buff = calloc(1+BUFFSIZE*(*num_buffs), sizeof(char));
    strcpy(*prev_buff, line);
    (*num_buffs)++;
    return line;
}

void test_append(){
    printf("test_append()\n");
    char* s1= calloc(1+10,sizeof(char));
    char* s2 = calloc(1+10,sizeof(char));
    strcpy(s1, "hello!!");
    strcpy(s2, "hi!");
    
    str_append(&s1, s2);
    printf("%s\n", s1);
    free(s1);
    free(s2);
    printf("\n");
}
