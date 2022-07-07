// Rahel Gerson
// csc 352

#include "pa4.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool o, e, i_;
char line[200], pattern[200];

int main(int argc, const char * argv[]) {
    reset_char_arr(line, 0, 200); reset_char_arr(pattern, 0, 200);
    /*turn on flags by checking command args*/
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
    if (e){
        int res = check_pattern(pattern);
        if (res == 2){
            fprintf(stderr, "Invalid search term.\n");
            return 2;
        }
            
    }
    
    char temp[200]; reset_char_arr(temp, 0, 200);
    while(fgets(temp, 200, stdin) != NULL){
        strcpy_(line, temp, 0, 0, len_char(temp));
        sgrep(e,i_,o, pattern, line);
    }

    return 0;
}

