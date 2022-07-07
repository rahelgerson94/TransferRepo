
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#define debug
/*utils*/
int len_int(int arr[]);
int len_char(char arr[]);
void reset_char_arr(char arr[], int start, int end);
void reset_int_arr( int arr[], int start, int end, int val);
void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end);
bool is_char(char c);
bool is_digit(char c);
bool contains_pattern(char string[100], char pattern[100]);

/*pa4 specific functions*/
void sgrep(bool e, bool i, bool o, char pattern[200], char line[200]);
bool match_char(char act, char ref, bool i);
int check_pattern(char pat[200]);
bool o, e, i_;
char line[200], pattern[200];

int main(int argc, const char * argv[]) {
    reset_char_arr(line, 0, 200); reset_char_arr(pattern, 0, 200);
    
 
    if (argc < 1 || argc > 5){
        fprintf(stderr, "Requires more command arguments\n");
        return 1;
    }
    else{
        for (int i = 1; i < argc; i++){
            if (argv[i][0] != '-')
                strcpy_(pattern, (char*)argv[i], 0, 0, (int)strlen(argv[i]));
                
            else{
                switch (argv[i][1]){
                    case 'o':
                        o = true;
                        break;
                    
                    case 'e':
                        e = true;
                        break;

                    case 'i':
                        i_ = true;
                        break;
                    }
                
                }//else
        }//for
    }//end else
    //if (e){
        int res = check_pattern(pattern);
        if (res == 2){
            fprintf(stderr, "Invalid search term.\n");
            return 2;
        }
            
    //}
    
    
    while(fgets(line, 200, stdin) != NULL){
        sgrep(e,i_,o, pattern, line);
    }

    return 0;
}


void sgrep(bool e, bool i, bool o, char pattern[200], char line[200]){
    char buff[200]; reset_char_arr(buff, 0, 200);
    bool match;
#ifdef debug
    printf("p l b\n");
#endif
    /*if the -e option NOT enabled, take this control path*/
    if (!e){
        
        int p = 0; int b = 0;
        int len_line = len_char(line);
        for (int l = 0; l <= len_line; l++){
            
            if (pattern[p] == '\0'){
                if (o) {
                    printf("%s\n", buff);
                    reset_char_arr(buff, 0, 200);
                    b = 0;
                    p = 0;
                }
                else{
                    printf("%s", line);
                    return;
                }
            }//end if pattern[p] == '\0'
            
            
            else{ /*we're still in the process of matching */
                match = match_char(line[l], pattern[p], i);
                if (match){
                    buff[b] = line[l];
                    b++;
                    p++;
                    //match = false;
#ifdef debug
                printf ("%c %c %c\n", pattern[p-1], line[l], buff[b-1]);
#endif
                }//if match
                else{
                    reset_char_arr(buff, 0, 200);
                    b = 0;
                    p = 0;
                }
            }//end else for matching
        }//end outer for
    }//end case !e
    
    /*if the -e is enabled, take this control path*/
    else{ // e
        int p = 0; int b = 0;
        int len_line = len_char(line);
        bool hash = false;
        
        for (int l = 0; l <= len_line; l++){
            if (!hash){
                if (pattern[p] == '#'){
                    hash = true;
                    buff[b] = line[l];
#ifdef debug
                    printf ("%c %c %c\n", pattern[p], line[l], buff[b]);
#endif
                    b++;
                    p++;
                }
                else if (pattern[p] == '.'){
                    buff[b] = line[l];
                    b++;
                    p++;
#ifdef debug
                    printf ("%c %c %c\n", pattern[p-1], line[l], buff[b-1]);
#endif
                }
                else{ /*we're still in the process of matching */
                    match = match_char(line[l], pattern[p], i);
                    if (match){
                        buff[b] = line[l];
                        b++;
                        p++;
#ifdef debug
                        printf ("%c %c %c\n", pattern[p-1], line[l], buff[b-1]);
#endif
                        
                    }//if not match
                    else{
                        reset_char_arr(buff, 0, 200);
                        b = 0;
                        p = 0;
#ifdef debug
                        printf ("%c %c %c\n", pattern[p], line[l], buff[b]);
#endif
                    }
                }   //end case where curr char is a normal char
                if (pattern[p] == '\0'){
                    if (o) {
                        printf("%s\n", buff);
                        reset_char_arr(buff, 0, 200);
                        b = 0;
                        p = 0;
                    }
                    else
                    {
                        printf("%s", line);
                        return;
                    }
                }

            }//if !hash
            else{ //hash

                if (match_char(line[l], pattern[p], i)){
                    buff[b] = line[l];
#ifdef debug
                    printf ("%c %c %c\n", pattern[p], line[l], buff[b]);
#endif
                    b++;
                    p++;
                    hash = false;
                }
                else{
                    buff[b] = line[l];
#ifdef debug
                    printf ("%c %c %c\n", pattern[p], line[l], buff[b]);
#endif
                    b++;
                    
                }
                
            }//end hash case
            /*check if we've matched whole pattern*/
            if (pattern[p] == '\0'){
                if (o) {
                    printf("%s\n", buff);
                    reset_char_arr(buff, 0, 200);
                    b = 0;
                    p = 0;
                }
                else{
                    printf("%s", line);
                    return;
                }
            }
            
        }//end for
    }//end case e = true
}//end sgrep


/*
 this function takes in
 1) a ref char and compares it to 2) another char.
 it also takes in a boolean i. if i is true, it will match insensitive
 it returns true upon a match, and false else.
 */
bool match_char(char act, char ref, bool i){
    //act: curr line char
    //ref: curr pattern char
    bool match = false;
    if (i){
        if ((int)act >= 97  && act <= 122 ){ //if lower case char
            if ((int)act == (int)ref || (int)act-32 == (int)ref )
                match = true;
        }
        else if (((int)act >= 65  && (int)act <= 90)){ //if upper case char
            if ((int)act == (int)ref || (int)act+32 == (int)ref)
                match = true;
        }
        else{ //not a letter
            if ((int)act == (int)ref )match = true;
        }
    }//end case sensitive
    
    else {
        if ((int)act == (int)ref )
            match = true;
        else match = false;
    }
    return match;
}

/*this function ensures that the input pattern is valid */

int check_pattern(char pat[200]){
    // search term should contain only upper and lower case letters, digits, periods, and hash-tags.
    //Also, a hashtag must have a letter immediately before and after it
    int len = len_char(pat);
    bool char_true = false, digit_true = false;
    //printf("\tcheck_pattern\n");
    //printf("\t pattern: %s\n", pat);
    if (len == 0) return 2;
    if (pat[0] == '#' || pat[len-1] == '#') return 2;
    else{
        for (int i = 0; i < len; i++){
            //bool valid_sub_pat = false;
            if (pat[i] == '#') {
                if  (!( is_char(pat[i-1] ) &&  is_char(pat[i+1]))) return 2;
            }
            else{
                char_true = is_char(pat[i]);
                digit_true = is_digit(pat[i]);
            }
            
            if (!( char_true || digit_true || pat[i] == '.')) return 2;
        }
        return 0;
    }
}

int len_int(int arr[]){
    int i = 0;
    int len = 0;
    while (arr[i] >= 0){ //!= -1){
        //printf("%d ",arr[i] ) ;
        len++;
        i++;
    }
    return len;
}

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
void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end){
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++)
    {
        if (src[in_i]== '\n') break;
        dst[out_i] = src[in_i];
        in_i++;
    }
}

bool is_char(char c){
    bool is_char = false;
    bool upper = false;  bool lower = false;
    
    if ((int)c >= 97 && (int)c <= 122) lower = true;
    if ((int)c >= 65 && (int)c <= 90) upper = true;
    if (upper || lower ) is_char = true;
    return is_char;
}
bool is_digit(char c){
    //[48-57]
    if ((int)c >= 48 && (int)c <= 57) return true;
    else return false;
}


