#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

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
char** out = malloc(sizeof(char*)* num_lines);
    for (int i = 0; i < num_lines+1; i++)
        out[i] = NULL;
    FILE* in = fopen(path, "r");
    char curr_data[buff_size];
    int l = 0;
    int num_buffs = 1;
    
    while(fgets(curr_data, buff_size, in) != NULL){
        if (out[l] == NULL){
            out[l] = calloc(sizeof(char), buff_size);
            strcpy(out[l], curr_data);
        }
        else{
            int len = (buff_size)*(num_buffs);
            char temp[len];
            reset_char_arr(temp, 0, len);
            strcpy(temp, out[l]); //temp = out[l]
            out[l] = realloc(out[l], len);
            reset_char_arr(out[l], 0, len);
            strcpy(out[l], temp); //temp = out[l]
            
            if (count_char(curr_data, '\n') > 0){
                //printf("curr_data:>%s<\n", curr_data);
                int new_line_loc =  checkCharLoc(curr_data, '\n');
                curr_data[new_line_loc] = '\0';
                
                strncat(out[l], curr_data, buff_size*(num_buffs));
                printf("%d. %s\n", l, out[l]);
                //printf("%s\n", out[l]);
                num_buffs = 1;
                l++;
            }
            else{
                strncat(out[l], curr_data, buff_size);
                printf("%d. %s\n", l, out[l]);
                num_buffs = num_buffs+1;
            }
        }
        
    }
    fclose(in);
    return out;
}


void free_string_arr(char** ll ){ //take a reference to a list of strings
    int i = 0;
    while (ll[i]!=NULL){
        free(ll[i]);
    }
    free(ll);
}

int main(int argc, const char * argv[]) {
    char path[300] ;
    strcpy(path, argv[1]);
    int num_lines = count_num_lines(path, 3);
    char** data = read_(path, 3);
    free(data);
    return 0;
}
