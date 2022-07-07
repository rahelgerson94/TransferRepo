//
//  pa4.c
//  pa4
//
//  Created by Rahel Gerson on 6/26/22.
//
//#define debug

#include "pa4.h"
void sgrep(bool e, bool i, bool o, char pattern[200], char line[200]){
    char buff[200]; reset_char_arr(buff, 0, 200);
    bool match;
#ifdef debug
    printf("p l b\n");
#endif
    
    if (!e){
        //int p_len = len_char(pattern);
        int p = 0; int b = 0;
        int len_line = len_char(line);
        for (int l = 0; l <= len_line; l++){
            //if (line[l] == '\0' ) break;
            
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
                        
                    }//if match
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
    if (pat[0] == '#' || pat[len-1] == '#') return 2;
    else{
        for (int i = 0; i < len; i++){
            bool valid_sub_pat = false;
            if (pat[i] == '#') {
                if  ( is_char(pat[i-1] ) &&  is_char(pat[i+1]))
                    valid_sub_pat = true;
                else return 2;
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

