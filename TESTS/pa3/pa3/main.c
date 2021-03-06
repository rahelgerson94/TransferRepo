//
//  main.c
//  pa3
//
//  Created by Rahel Gerson on 6/20/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end);
int len(int arr[]);
int assign_line(char* out, char* in, int out_start, int in_start, int in_end );
void reset_arr(char* arr, int start, int end );
void scut_line(char* output, char* input, int* col_list, int* delim_locs);
//void scut_line(char* output, char* input, int delim_locs,int cols2keep[]);
int len_int(int* arr);
int len_char(char* arr);
    void parse_cmd_args(char* input, int* output);
void find_locs(char* input, int* delim_locs, char delim);

void print_int_arr(int* arr);
void get_separation_locations(char Input[],char delim,int startLoc, int endLoc,int Output[]);

char output[102];
int main(int argc, const char * argv[]) {
    char* EOF_true;
    char* input = "the big lazy fox will\ngo to sit in the cave\nover by the small mountain";
    char* out_ptr;
    
    //char* delim = (char*)argv[1];
    //char* col_list = (char*) argv[2];

    int cols_locs[100] = {0};
    int cols2keep[100] = {0};
    int delim_locs[100] = {0};
    int new_line_locs[100] = {0};
    char curr_line[102]; //null charachter and newline
    parse_cmd_args("2,4,5", cols2keep); //take the string list and turn it into an int list
    //find_locs(input, delim_locs, ' ');
    get_separation_locations(input, '\n', 0, -1,new_line_locs);
    //find_locs(input, new_line_locs, '\n');
    int num_lines = len_int(new_line_locs);// + 1;
    int in_end = 0;
    int in_start;
    for (int line = 0; line < num_lines; line++){

        memset(curr_line,'\0',100);
        in_start = in_end;
        in_end = new_line_locs[line];
        strcpy_(curr_line, input, 0, in_start, in_end  );
        //reset_arr(curr_line, new_line_locs[line], 102); //set all chars after last char to null
        printf("curr_line = %s\n", curr_line);
        get_separation_locations(curr_line, ' ', 0, -1,delim_locs);
        //find_locs(curr_line, delim_locs, ' ');
        printf("delim_locs = "); print_int_arr(delim_locs);
        scut_line(output, curr_line, cols2keep,delim_locs);
        //scut_line(output, curr_line, cols_locs, delim_locs);
        //printf("output = %s\n", output);
        in_start = new_line_locs[line] + 1;
        reset_arr(delim_locs, 0, 100);
        in_end++;
    }
    
    
    
   
    //scut_line(output, input, cols_locs, delim_locs);
   

    
    return 0;
}
void scut_line(char* output, char* input, int* col_list, int* delim_locs){
    memset(output, '\0', 100);
    int ii = 0;
    int Start = ii;
    int end = delim_locs[0];
    int col = 0;
    char word[100] = {'\0'};
    while(delim_locs[ii] > 0){
        col++;
        memcpy( word, &input[Start], delim_locs[ii] - Start);
        int cc = 0;
        while(col_list[cc] > 0){
            if(col_list[cc] == col){
                printf("The Correct Word >> %s\n",word);
                break;
            }
            cc++;
        }
        Start = delim_locs[ii] + 1;
        ii++;
        memset(word,'\0',100);
    }
}
//void scut_line(char* output, char* input, int* col_list, int* delim_locs){
//    int out_idx = 0;
//    int in_start, in_end;
//    memset(output, '\0', 100);
//    int num_cols = len_int(col_list);
//    printf("\t[scut_line]\n");
//    for (int delim = 0; delim < num_cols ; delim++){
//        int i = col_list[delim]; //1
//        in_start = delim_locs[i-1] + 1; //8
//        in_end = delim_locs[i];
//
//        out_idx = assign_line(output, input, out_idx, in_start, in_end); //out_idx for the (i+1)th col.
//        printf("\t\tin_start, in_end = (%d, %d)\n", in_start, in_end);
//        //printf("%s\n", output);
//    }
//        reset_arr(output, out_idx-1, 100);  //out_idx-1 bc output string will have a delim after the last letter
//}

int assign_line(char* out, char* in, int out_start_curr, int in_start, int in_end ){
    int out_start_next;
    int len =  in_end-in_start;
    for ( out_start_next = out_start_curr; out_start_next < out_start_curr + len; out_start_next++){
        out[out_start_next] = in[in_start];
        in_start++;
    }
    return out_start_next+1; //take into account the space after the word
}

void reset_arr(char* arr, int start, int end ){
    for ( int i = start; i < end ; i++){
        arr[i] = '\0';
    }
}

void get_separation_locations(char Input[],char delim,int startLoc, int endLoc,int Output[]){
    if(endLoc == -1){
        endLoc = 100;
    }
    int ll=0;
    for(int ii = startLoc;ii < endLoc;ii++){
        if(Input[ii] == delim || Input[ii] == '\n'){
            Output[ll++] = ii;
        }else if(Input[ii] == '\0') {
            Output[ll++] = ii;
            break;
        }
    }
}

void find_locs(char* input, int* delim_locs, char delim){
    int in_idx = 0;
    int out_idx=0;
    
    while (input[in_idx] != '\0'){
        if (input[in_idx] == delim) {
            delim_locs[out_idx] = in_idx;
            out_idx++;
            
        }
        in_idx++;
    }
    delim_locs[out_idx] = -1;
}

//find the length of an int array
int len_int(int* arr){
    int i = 0;
    int len = 0;
    while(arr[i] > 0){//!= -1){
        len++;
        i++;
    }
    return len;
}

int len_char(char* arr){
    int i = 0;
    int len = 0;
    while(arr[i] != '\0'){
        if (arr[i] == '\n')continue;
        else {len++;}
        i++;
    }
    return len;
}

void parse_cmd_args(char* input, int* output){
    int out_idx=0;
    for (int i = 0; input[i] != '\0'; i++){
        if (input[i] == ',') continue;
        else if (input[i] == ' ') continue;
        else{
            output[out_idx] = atoi(&input[i]);// -1; //make 0 indexed
            out_idx++;
        }
    }
    output[out_idx] = -1;
}

void scut(int* input){
    int i = 0;
    while (input[i] != NULL){
        if (input[i]  == '\n'){
            
        }
        else{
            
        }
    }
}

void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end){
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++){
        dst[out_i] = src[in_i];
        in_i++;
    }
}

void print_int_arr(int* arr){
    printf("{ ");
    int length = len_int(arr);
    
    for (int i = 0; i < length; i++){
        if (i == length -1 ){
            printf("%d }\n", arr[i]);
            return;
        }
        else{
            printf("%d, ", arr[i]);
        }
    }
}



