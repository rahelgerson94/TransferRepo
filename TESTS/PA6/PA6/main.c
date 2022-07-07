//
//  main.c
//  PA6
//
//  Created by Rahel Gerson on 7/5/22.
// 0-3, 4-7, 8-11

#include <stdio.h>
#include "zstr.h"
int main(int argc, const char * argv[]) {
    char* initial_data = "giraffe";
    int total_bytes = get_total_bytes(initial_data);
    zstr z = calloc(total_bytes, sizeof(char));
   
    int* l = (int*)z;//l points to the same mem address as z. modifying the contents of one modifies the contents of the other.
    *(l) = 2000; //store 2000 in 1st 4 bytes of z and l
    *(l+1) = 2048;
    *(z+8) = 'x';
    printf("address of (z+8) = %p, contents: %c\n", z+8, *(z+8));
    printf("address of (l+2) = %p, contents: %c\n", l+2, *(l+2));
    
   
    //l
    int i = 0;
    for (int i = 0; i < 2; i++){
        printf("%d\n", *(l+i));
    }
    i=8;
    while (i < total_bytes){
        if (*(z+i) == '\0') printf("%d. NULL\n", i);
        else printf("%d. %c\n", i, *(z+i));
        i++;
        }
    
    free(z);
    
    
    printf("%d\n",sizeof(char));
    printf("%d\n",sizeof(int));
    return 0;
}
