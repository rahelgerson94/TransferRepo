#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

int len_char(char arr[]){
    int i = 0;
    int len = 0;
    while (arr[i] != '\0'){
        if (arr[i] == '\n')
            break;
        else{
            len++;
        }
        i++;
    }
    return len;
}

void reset_char_arr(char arr[], int start, int end){
    for (int i = start; i < end; i++)
    {
        arr[i] = '\0';
    }
}
void reset_int_arr(int arr[], int start, int end, int val)
{
    for (int i = start; i < end; i++)
    {
        arr[i] = val;
    }
}
int checkCharLoc(char input[],char b){
    int ii = 0;
    while(input[ii] != '\0'){
        if (input[ii] == b) return ii;
        ii++;
    }
    return -1;
}

/* return the number of times search appears in input*/
int count_char(char input[], char search){
    int ind = 0;
    int count = 0;
    while(input[ind] != '\0'){
        if(input[ind] == search){
            count++;
        }
        ind++;
    }
    return count;
}
/* count the number of lines in a file */
int count_num_lines(char* path, int buff_size){
    FILE* data = fopen(path, "r");
    char curr_data[buff_size];
    int num_lines = 0;
    while(fgets(curr_data, buff_size, data) != NULL){
        num_lines+=count_char(curr_data, '\n');
    }
    fclose(data);
    return num_lines+1;
}



char** read_(char* path, int buff_size){
int num_lines = count_num_lines(path, buff_size);    
char** out = malloc(sizeof(char*)* (num_lines+1));
    for (int i = 0; i < num_lines+1; i++){
        printf("\tout[%d]\n", i);  //db
        out[i] = NULL;
    }
    FILE* in = fopen(path, "r");
    char curr_data[buff_size];
    int l = 0;
    int len_new = buff_size;
    int iter0 = 0; //db
    while(fgets(curr_data, buff_size, in) != NULL){
        if (out[l] == NULL){
            out[l] = calloc(sizeof(char), buff_size);
            strcpy(out[l], curr_data);
        }
        else{
            int len_new = len_new + len_char(curr_data) + 1;
            char temp[len_new];
            reset_char_arr(temp, 0, len_new);
            strcpy(temp, out[l]); //temp = out[l]
            
            printf("\t%d. realloc(), l = %d \n", iter0, l);  //db
            out[l] = realloc(out[l], len_new);
            reset_char_arr(out[l], 0, len_new);
            strcpy(out[l], temp); //temp = out[l]
            
            if (count_char(curr_data, '\n') > 0){
                //printf("curr_data:>%s<\n", curr_data);
                int new_line_loc =  checkCharLoc(curr_data, '\n');
                curr_data[new_line_loc] = '\0';
                printf("before strcat: out[%d] = >%s< \n", l, out[l]);
                
                strncat(out[l], curr_data, len_new+1);
                printf("after strcat: out[%d] = >%s< \n", l, out[l]);
                printf("len: %d", len);
                //printf("%d. %s\n", l, out[l]);
                //printf("%s\n", out[l]);
                num_buffs = 1;
                l++;
            }
            else{
                strncat(out[l], curr_data, len_char(out[l]) + 1);
                //printf("%d. %s\n", l, out[l]);
            }
        }
        iter0++;
    }
    fclose(in);
    return out;
}


int get_max_line_len(char* path){
    /* length excludes newline char */
    FILE* data = fopen(path, "r");
    char curr_data[2];
    int num_lines = 0;
    int max_num_char = 0;
    int curr_num_char = 0;
//    printf("<\n");
    while(fgets(curr_data, 2, data) != NULL){
//        printf(">%s<\n",curr_data);
        if (strcmp(curr_data,"\n") == 0 || strcmp(curr_data,"\0") == 0){
            num_lines++;
            if (curr_num_char > max_num_char) max_num_char = curr_num_char;
            curr_num_char = 0;
        }else{
            curr_num_char++;
        }
    }
    fclose(data);
//    printf(">");
    return max_num_char;
    
}

int main(int argc, const char * argv[]) {
    //char path[200] = "/Users/rahelmizrahi/Library/Mobile_Documents/com~apple~CloudDocs/csc352/cs352_pas/pa5/data.txt";
    char path[300] ;
    int buff_size = 10;
    strcpy(path, argv[1]);
    int num_lines = count_num_lines(path, buff_size);
    char* file_data[num_lines];
    read_( path, buff_size, file_data);
    for (int i = 0; i < num_lines; i++){
        printf("%d. >%s<\n", i, file_data[i]);
    }
    
    for (int i = 0; i < num_lines; i++)
        free(file_data[i]);
    return 0;
}

