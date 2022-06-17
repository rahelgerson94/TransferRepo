/*
 Rahel Gerson
 csc352
 this program implements a beaufort cipher
 */

#include <stdio.h>
#include <string.h>
#define WIDTH 26

//#define RESETNEWLINE
char find_beau_char(char plaintext_char, char key_char);
int repeat_string(char key[], char repeated_key[], int input_str_len, int key_idx);
int beaufort_cipher(char key[], char input_str[], char output_str[]);
int beaufort_cipher_small_input(char key[], char input_str[], char output_str[]);
int count_num_spaces(char str[]);
//void beaufort_cipher(char key[], char input_str[], char output_str[]);
void reset_array(char some_array[128]);
void kill_new_line(char word[]);
int count_valuable_chars(char Input[]); // This counts the valuable chars
char table[676] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A',
    'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B',
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C',
    'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D',
    'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E','F',
    'H','I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'};
#define WIDTH 26


char key[128];
char input_str[128];
char encryped_str[128];
char repeated_key[128];
int key_offset = 0; int new_key_offset;
int main(int argc, const char * argv[]) {
    /*
     
     FORTIFICATION
     DEFENDTHEEASTWALLOFTHECASTLE
     WALLS MUST BE DEFENDED
     DEFEND THE EAST WALL OF THE CASTLE
     
     QUACK
     WALL WERROR
     CAT PANDA DOG
     WRAPS
     LOST IN TRANS LATINO
     
     QUACK
     A
     ALPHA BETA GAMMA
     BANANA
     
     
    */
    char* EOF_true;
    int  num_spaces;
    num_spaces = 0;
    //strcpy(key, "EITAN\n");
    fgets(key, 128, stdin);
    //int key_len = count_valuable_chars(key);
    //kill_new_line(key);
    int key_len = count_valuable_chars(key);
    EOF_true = fgets(input_str, 128, stdin) ;
    while(EOF_true != NULL && strcmp(input_str, "\n") != 0){
        int input_str_len = count_valuable_chars(input_str);
        num_spaces = count_num_spaces( input_str);
        key_offset = repeat_string(key, repeated_key, input_str_len, key_offset);
        key_offset -=num_spaces;
        if (key_offset < 0){
            key_offset = count_valuable_chars(key) + key_offset + 1;
        }
        if (key_offset > key_len-1){
            key_offset = (key_offset % key_len) +  1;
        }
        beaufort_cipher(repeated_key, input_str, encryped_str);
        
        printf("key_offset = %d\n", key_offset);
        printf("repeated_key = %s\n", repeated_key);
        printf("input_str    = %s\n", input_str);
        printf("encrypted_str  = %s\n", encryped_str);
        //printf("%s\n", encryped_str);
        reset_array(repeated_key);
        reset_array(encryped_str);
        //key_offset = 0;
        EOF_true = fgets(input_str, 128, stdin) ;
    }
    /*
     do {
         //printf("enter an input str: ");
         
         EOF_true = fgets(input_str, 128, stdin) ;
         if (EOF_true == NULL || strcmp(input_str, "\n") == 0){
             return 0;
         }
         int input_str_len = count_valuable_chars(input_str);
         key_offset = repeat_string(key, repeated_key, input_str_len, key_offset);
         num_spaces = beaufort_cipher(repeated_key, input_str, encryped_str);
         key_offset -=num_spaces;
         
 //        printf("key_offset = %d\n", key_offset);
 //        printf("repeated_key = %s\n", repeated_key);
 //        printf("input_str    = %s\n", input_str);
 //        printf("encrypted_str  = %s\n", encryped_str);
         printf("%s\n", encryped_str);

         reset_array(repeated_key);
         reset_array(encryped_str);
         
     } while( EOF_true != NULL || strcmp(input_str, "\n") != 0); //blank line would be read as '\n'


     */
    
    return 0;
}

char find_beau_char(char char2encrypt, char key_char){
    int col = 0;
    while (table[col] != char2encrypt){
        col++;
    }
    const char COL = col;
    int row = 0;
    int location = row*WIDTH + col;
    while(table[location] != key_char){
        row++;
        location = row*WIDTH + COL;
    }
    location -= COL;
    //printf("location = %d*WIDTH + %d\n", row, col);
    return table[location];
}

int repeat_string(char key[], char repeated_key[], char input_key, int key_idx){
    int key_len = count_valuable_chars(key);
    //for (int i = 0; i < input_str_len - 1; i ++){
    
    #ifdef RESETNEWLINE
    key_idx = 0;
    #endif
    
    for (int i = 0; i < input_str_len; i++){ // No new lines
        //if (key[key_idx] == '\n')
        if (key_idx % key_len == 0 && i != 0){ //gets you to a '\n'
            key_idx = 0;
        }
        
        repeated_key[i] = key[key_idx];
        key_idx++;
    }
    
    if (key_len >= input_str_len){
        return input_str_len ; //0-idx
        
    }
    return key_idx;
}

void reset_array(char some_array[128]){
    for (int i = 0; i < 128; ++i)
        some_array[i] = '\0';
}


int beaufort_cipher(char key[], char input_str[], char output_str[]){
    
    int num_spaces = 0; //add up number of spaces, subtract this number from  key_offset
    char c;
    int input_str_len = count_valuable_chars(input_str);
    int key_idx = 0;
  
  //for (int output_idx = 0; output_idx < strlen(input_str) -1; output_idx++ ){
    for (int output_idx = 0; output_idx < input_str_len; output_idx++ ){
        //if (output_idx==strlen(input_str)-1){printf("stop\n");}
        char db_input_char = input_str[output_idx];
        char db_key_char = key[key_idx];
        if (input_str[output_idx] == ' '){
            c = ' ';
            strcpy(&output_str[output_idx], &c );
            num_spaces ++;
        }
            else {
               c = find_beau_char(input_str[output_idx], key[key_idx]);
               strcpy(&output_str[output_idx], &c );
                key_idx++;
           }
        printf("%c   %c\n", db_input_char, db_key_char);
    }
    
    return num_spaces;
}

void kill_new_line(char str1[]){
    for (int ii = 0; ii < strlen(str1); ii++){
        if (str1[ii] == '\n'){
            str1[ii] = '\0';
            break;
        }
        
    }
}

int count_valuable_chars(char Input[]){
    char check = '\0';
    int cc = 0;
    while(check != '\n'  && cc < 128){
        check = Input[cc];
        if (check == '\n' || check == '\0'){
            Input[cc] = '\0';
            return cc;
        }
        cc++;
    }
    return cc;
}
void genEncryptArr(char Arr[128],char key[]){
    int ii = 0;
    int keyCount = 0;
    int maxCount = count_valuable_chars(key);
    while(ii < 128){
        if(keyCount == maxCount) keyCount = 0;
        Arr[ii] = key[keyCount];
        ii++;
        keyCount++;
    }
    
}

int count_num_spaces(char str[]){
    int i = 0; int num_spaces = 0;
    while (str[i] != '\0'){
        if (str[i] == ' ') {num_spaces++;}
        i++;
    }
    
    return num_spaces;
}
