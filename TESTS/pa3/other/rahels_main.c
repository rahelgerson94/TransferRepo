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
void scut_line(char* output, char* input, int* col_list, int* delim_locs, int new_line_loc);
int len_int(int* arr);
int len_char(char* arr);
    void parse_cmd_args(char* input, int* output);
void find_locs(char* input, int* delim_locs, char delim);

void print_int_arr(int* arr);

char output[102];
int main(int argc, const char * argv[]) {
    char* EOF_true;
    //char* input = "the big lazy fox will\ngo to sit in the cave\nover by the small mountain";
    char* input = "over by the small mountain\n";
    char* out_ptr;
    
    //char* delim = (char*)argv[1];
    //char* col_list = (char*) argv[2];

    int cols_locs[100];
    int delim_locs[100];
    int new_line_locs[100];
    char curr_line[102]; //null charachter and newline
    memset(output, ' ', 100);
    parse_cmd_args("2,4,5", cols_locs); //take the string list and turn it into an int list
    find_locs(input, delim_locs, ' ');
    find_locs(input, new_line_locs, '\n');
    scut_line(output, input, cols_locs, delim_locs, new_line_locs[0]);
    printf("%s\n", output);
    return 0;
}


void scut_line(char* output, char* input, int* col_list, int* delim_locs, int new_line_loc){
    int out_idx = 0;
    int in_start, in_end;
    memset(output, ' ', 100);
    int num_cols = len_int(col_list);
    printf("\t[scut_line]\n");
    for (int delim = 0; delim < num_cols ; delim++){
           //int i = col_list[delim]; //1
            //in_start = delim_locs[i-1] + 1; //8
            in_start = delim_locs[col_list[delim] - 1] + 1; //start of word
            in_end = delim_locs[col_list[delim]] - 1;
            
        
        out_idx = assign_line(output, input, out_idx, in_start, in_end); //out_idx for the (i+1)th col.
        printf("\t\tin_start, in_end = (%d, %d)\n", in_start, in_end);
        //printf("%s\n", output);
    }
        reset_arr(output, out_idx-1, 100);  //out_idx-1 bc output string will have a delim after the last letter
}

int assign_line(char* out, char* in, int out_start_curr, int in_start, int in_end ){
    int out_start_next;
    int len =  in_end-in_start + 1; //+1 for the space after eow
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


void find_locs(char* input, int* delim_locs, char delim){
    int in_idx = 0;
    int out_idx=0;
    while (input[in_idx] != '\0' ){
        if (input[in_idx] == delim || input[in_idx] == '\n') {
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
    while(arr[i] != -1){
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
            output[out_idx] = atoi(&input[i]) -1; //make 0 indexed
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



