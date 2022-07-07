//
//  zstr.c
//  PA6
//
//  Created by Rahel Gerson on 7/7/22.
//

#include "zstr.h"
zstr_code zstr_status;
zstr zstr_create(char* initial_data){
    /*
     hold the char array initial_data using the malloc function, store the string length
     and allocated size, and then return a zstr
     */
    int total_bytes = get_total_bytes(initial_data);
    int len_str = len_char(initial_data);
    zstr z = calloc(total_bytes, sizeof(char));
    /*
     l and z now point to the same mem addr. modifying the contents of one modifies the contents of the other.
     difference: l is an int pointer rather than a char pointer.
     writing to a single elem in l writes to 4 bytes of data, whereas writing to a single elem
     in z writes to 1 byte of data
     */
    int* l = (int*)z;
    *l = len_str; // bytes 0-3 of l and z contain data
    *(l+1) = total_bytes; // bytes 4-7 of l and z contain data
    
    int in_i=0; //input iterator
    for (int i = 8; i < 8+len_str; i++){
        *(z+i) = *(initial_data + in_i);
        in_i++;
    }
    *(z+8+len_str) = '\0';
    return z;
}

void zstr_destroy(zstr to_destroy){}
void zstr_append(zstr * base, zstr to_append){}
int zstr_index(zstr base, zstr to_search){
    /*
     search for the first occurrence of to_search within base.
     It should return the index if found, or -1 if not found.
     It should return the index based on the beginning of the actual char array.
     */
    return 0;
}
int zstr_count(zstr base, zstr to_search){
    /*
    count how many times to_search appears within base.
    return 0 if no match is found.
     */
    return 0;
}

int zstr_compare(zstr x, zstr y){
    /*
    return ZSTR_GREATER if x > y, ZSTR_EQUAL if x == y, and ZSTR_LESS if x < y.
    compares based on ascii character values, in the same way that strcmp does.
     */
    return 0;
}


//zstr zstr_substring(zstr base, int begin, int end){
//    /*
//     create a new zstr with the contents that are contained within the substring of base
//     between begin (inclusive) and end (exclusive). The function should ensure that the new zstr
//     created uses the smallest zstr size in order to fit the substring.
//     */
//
//}


void zstr_print_detailed(zstr z){
    /*
    STRLENGTH: 20
    DATASIZE: 32
    STRING: >data<*/
    int* l = (int*)z;
    printf("STRLENGTH: %d\n", *(l));
    printf("DATASIZE: %d\n", *(l+1));
    printf("STRING: >");
    for (int i = 8; i < 8+ *(l) ; i++){
        printf("%c",*(z+i));
    }
    printf("<\n");
}

// 16, 32, 256, 1024, or 2048
int get_total_bytes(char* data){
    /*determine the total mallocated size based off strlen*/
    int len = len_char(data);
    int min = len+9; //bytes
    if (min <= 16 ) return 16;
    else if (min <= 32) return 32; // 17 < min < 32
    else if (min <= 256) return 256; // 33 < min < 256
    else if (min <= 1024) return 1024; // 257 < min < 1024
    else return 2048;
}
