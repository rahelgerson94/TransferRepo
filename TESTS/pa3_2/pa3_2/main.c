//
//  main.c
//  pa3
//
//  Created by Rahel Gerson on 6/20/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end);
int len(int arr[]);
int assign_line(char* out, char* in, int out_start, int in_start, int in_end );
void reset_arr(char* arr, int start, int end );
void scut_line(char* output, char* input, int* col_list, int* delim_locs);
int len_int(int* arr);
int len_char(char* arr);
void parse_cmd_args(char* input, int* output);
void find_locs(char* input, int* delim_locs, char delim);
void print_int_arr(int* arr);
//void get_separation_locs(char input[], char delim,int startLoc, int endLoc,int Output[]);
void get_separation_locs(char input[], char delim, int start_loc, int end_loc, int output[]);
void scut_letters(char input[], int cols2keep[], char output[] );

//void get_separation_locs(char input[],char delim,int startLoc, int endLoc,int output[], char delim_type);
void de_escape(char* arr);
char decide(char in);
char output[102];

int main(int argc, const char * argv[]) {
    
    
    char* delim_type = argv[1];
    //char delim = delim_type[1];
    //TODO: make case statements for different delim types
    
    char delim = decide(delim_type[1]);
    char* col_list = (char*) argv[2];
    
    //declarations
    int cols2keep[100] = {0};
    int delim_locs[100] = {0};
    int new_line_locs[100] = {0};
    char curr_line[102]; //null charachter and newline
    //char input[102]; //null charachter and newline
    
    //assignments
    int in_start;
    int in_end = 0;
    
    //begin
    //parse command args
    parse_cmd_args(col_list, cols2keep); //take the string list and turn it into an int list
    print_int_arr(cols2keep);
    memset(curr_line,'\0',100);
    //get input text
    //fgets(input, 100, stdin);
    //char* input = "the big lazy fox will\ngo to sit in the cave\nover by the small mountain";
    char* input = "alice,30,532,AZ,S\nbob,25,3411,CA,Z\njonas,40,8192,AZ,T\ngreg,50,400,UT,C";
//    for (int i = 0; i < 100; i++){
//        printf("%d. %c\n", i, input[i]);
//    }
    de_escape(input);
//    for (int i = 0; i < 100; i++){
//        printf("%d. %c\n", i, input[i]);
//    }
    get_separation_locs(input, '\n', 0, -1, new_line_locs);
    
    int num_lines = len_int(new_line_locs);// + 1;
    
    for (int line = 0; line < num_lines; line++){
        memset(curr_line,'\0',100);
        in_start = in_end;
        in_end = new_line_locs[line];
        strcpy_(curr_line, input, 0, in_start, in_end);
        if (delim == 'l'){ scut_letters(curr_line, cols2keep, output);}
        
        else{
            get_separation_locs(curr_line, delim, 0, -1, delim_locs);
            scut_line(output, curr_line, cols2keep, delim_locs);
        }
        
        in_start = new_line_locs[line] + 1;
        //reset_arr(delim_locs, 0, 100);
        memset(delim_locs, -1, 100 );
        in_end++;
    }
  
    return 0;
}

void scut_line(char* output, char* input, int* col_list, int* delim_locs){
    memset(output, '\0', 100);
    int ii = 0;
    int start = ii;
    int col = 0;
    char word[100] = {'\0'};
    while(delim_locs[ii] > 0){
        col++;
        memcpy( word, &input[start], delim_locs[ii] - start);
        int cc = 0;
        while(col_list[cc] > 0){
            if(col_list[cc] == col){
                //printf("The Correct Word >> %s\n",word);
                printf("%s ",word);
                break;
            }
            cc++;
        }
        start = delim_locs[ii] + 1;
        ii++;
        memset(word,'\0',100);
    }
    printf("\n");
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

//void get_separation_locs(char Input[],char delim,int startLoc, int endLoc,int Output[]){
//    if(endLoc == -1){
//        endLoc = 100;
//    }
//    int ll=0;
//    for(int ii = startLoc;ii < endLoc;ii++){
//        if(Input[ii] == delim || Input[ii] == '\n'){
//            Output[ll++] = ii;
//        }else if(Input[ii] == '\0') {
//            Output[ll++] = ii;
//            break;
//        }
//    }
//}
void get_separation_locs(char input[], char delim,int startLoc, int endLoc,int output[]){
    if(endLoc == -1){
        endLoc = 100;
    }
    int ll=0;
    for(int ii = startLoc;ii < endLoc;ii++){
        if(input[ii] == delim || input[ii] == '\n'){
            output[ll++] = ii;
        }else if(input[ii] == '\0') {
            output[ll++] = ii;
            break;
        }
    }
}
void scut_letters(char input[], int cols2keep[], char output[] ){
    int output_idx = 0;
    for (int i = 0; i < sizeof(cols2keep)/sizeof(int); i++){
        int col = cols2keep[i];
        output[output_idx] = input[col];
        output[output_idx+1] = ' ';
        output_idx = output_idx+2;
    }
    printf("%s \n", output);
}

char decide(char in){
    if (in == 'c') return ',';
    else if (in == 'w') return ' ';
    else return 'l';
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
            printf("%d ,", output[out_idx]);
        }
    }
    output[out_idx] = -1;
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

void de_escape(char* arr){
    int curr = 0;
    int next = 1;
    while (arr[next] != '\0'){
        if (arr[curr] == '\\' && arr[next] == 'n'){
            arr[curr] = '\n';
            int temp = next;
            while (arr[temp] !=  '\0'){
                arr[temp] = arr[temp+1];
                temp++;
            }
        }
            curr++;
            next++;
    }
}


