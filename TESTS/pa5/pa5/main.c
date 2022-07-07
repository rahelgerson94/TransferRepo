//
//  main.c
//  pa5
//
//  Created by Rahel Gerson on 7/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "basketball.h"

#include "utils.h"
#define max 1100
char curr_line[max];
char names[100][100];
double stats[100][7];

int main(int argc, const char * argv[]) {
    if (!(argc == 2)){
        fprintf(stderr, "expects 1 command line argument\n");
        return 1;
    }
    /*set up the data*/
    for (int l = 0; l < 100; l++){
        stats[l][0] = 6;
    }
    char* path = calloc(strlen(argv[1]), sizeof(char));
    strcpy(path, argv[1]);


    
  
    FILE* data = fopen(path, "r");
    int l = 0;
    while(fgets(curr_line, max, data) != NULL){
        //printf("%s", curr_line);
        pre_proc(curr_line, stats[l], names[l]);
       
        //printad(stats[l]);
        
        l++;
    }
    /*
     for (int i = 0; i < 5; i++){
         printf("%s\n", names[i]);
     }
     */
   
    get_stats(stats,  names, l);
    /*CLEANUP*/
    fclose(data);
    /*freeing data*/
    free(path);
    return 0;
}
