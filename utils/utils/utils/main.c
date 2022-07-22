//
//  main.c
//  utils
//
//  Created by Rahel Gerson on 7/22/22.
//

#include <stdio.h>
#include "utils.h"
int main(int argc, const char * argv[]) {
    //char path[200] = "/Users/rahelmizrahi/Library/Mobile_Documents/com~apple~CloudDocs/csc352/cs352_pas/pa5/data.txt";
    char path[300] = "/Users/rahelmizrahi/Library/Mobile_Documents/com~apple~CloudDocs/csc352/utils/utils/utils/stock_data.txt";
    int num_lines = count_num_lines(path, 3);
    char** data = read_(path, 3);
    printf("num_lines = %d\n", num_lines);
    return 0;
}
