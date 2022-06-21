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
int repeat_string(char key[], char repeated_key[], char input_key[], int key_idx);
int beaufort_cipher(char key[], char input_str[], char output_str[]);
int beaufort_cipher_small_input(char key[], char input_str[], char output_str[]);
int count_num_spaces(char str[]);
//void beaufort_cipher(char key[], char input_str[], char output_str[]);
void reset_array(char some_array[], int array_len);
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
     TEST INPUTS
     FORTIFICATION
     DEFENDTHEEASTWALLOFTHECASTLE
     WALLS MUST BE DEFENDED
     DEFEND THE EAST WALL OF THE CASTLE
     
     QUACK
     WALL WERROR
     CAT PANDA DOG
     WRAPS
     SO MUCH JU
     BLA
     LOST IN TRANS LAT
     
     QUACK
     A
     ALPHA BETA GAMMA
     BANANA
     
    */
    char* EOF_true;
    //int  num_spaces = 0;
    fgets(key, 128, stdin);
   
    EOF_true = fgets(input_str, 128, stdin) ;
    int input_str_len = count_valuable_chars(input_str);
    reset_array(repeated_key, input_str_len);

    while(EOF_true != NULL && strcmp(input_str, "\n") != 0){
        key_offset = repeat_string(key, repeated_key, input_str, key_offset);
        beaufort_cipher(repeated_key, input_str, encryped_str);
        /*
         printf("key_offset = %d\n", key_offset);
         printf("repeated_key = %s\n", repeated_key);
         printf("input_str    = %s\n", input_str);
         printf("encrypted_str  = %s\n", encryped_str);
         */
        
        printf("%s", encryped_str);
        reset_array(repeated_key, input_str_len);
        reset_array(encryped_str, input_str_len);
        EOF_true = fgets(input_str, 128, stdin) ;
        printf("\n");
       
    }
     
   
    
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

int repeat_string(char key[], char repeated_key[], char input_string[], int key_idx){
    int key_len = count_valuable_chars(key);
    //for (int i = 0; i < input_str_len - 1; i ++){
    //char db_input_char, db_key_char;
    int input_str_len = count_valuable_chars(input_string);
    for (int i = 0; i < input_str_len; i++){ // No new lines
        //if (key[key_idx] == '\n')
        if (key_idx % (key_len ) == 0 && i != 0){ //gets you to a '\n'
            key_idx = 0;
        }
        if (input_string[i] == ' '){
            repeated_key[i] = ' ';
            //repeated_key[i+1] = ' ';
            
        }
        else{
            repeated_key[i] = key[key_idx];
            key_idx++;
        }
        //printf("%c   %c\n", repeated_key[i], input_str[i]);
    }
    return key_idx % key_len;
}

void reset_array(char some_array[128], int array_len){
    int i;
    for (i = 0; i < array_len; ++i)
        some_array[i] = '\0';
    //some_array[i] = '\0';
}


int beaufort_cipher(char key[], char input_str[], char output_str[]){
    //printf("%s\n", input_str);
    int num_spaces = 0; //add up number of spaces, subtract this number from  key_offset
    char c;
    int input_str_len = count_valuable_chars(input_str);
    int key_idx = 0;
  
    for (int output_idx = 0; output_idx < input_str_len; output_idx++ ){
        //char db_input_char = input_str[output_idx];
        //char db_key_char = key[key_idx];
        int res = strncmp(&input_str[output_idx], " ", 1);
        if ( res == 0){
            c = ' ';
            strncat(&output_str[output_idx], &c, 1 );
            
        }
            else {
               c = find_beau_char(input_str[output_idx], key[key_idx]);
               strncat(&output_str[output_idx], &c, 1 );
                
           }
        key_idx++;
        //printf("%c   %c\n", db_input_char, db_key_char);
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
