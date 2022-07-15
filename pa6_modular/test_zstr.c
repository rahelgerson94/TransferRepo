//
//  main.c
//  PA6
//
//  Created by Rahel Gerson on 7/5/22.
// 0-3, 4-7, 8-11

#include <stdio.h>
#include "zstr.h"
//zstr_code zstr_zstr_status;
//zstr_code zstr_status;
void test_substring();
void test_append();
void test_append2();
void test_count();
void test_create();
void print_zstr_status();

void test_compare();
/*
 void test_substring( );
 void test_append( );
 void test_count( );
 void test_create( );
 
 void print_zstr_status(zstr_code zstr_status);

 */
int main(int argc, const char * argv[]) {
    test_create();
    test_substring();
    //test_append();
    //test_append2();
    //test_count();
    test_compare();
    
    return 0;
}

void test_create(){
    int bad_len = 2048;
    char bad_data[2048];
    for (int i = 0; i < bad_len; i++){
        bad_data[i] = 'a';
    }
    bad_data[2048] = '\0';
    zstr z = zstr_create(bad_data);
    print_zstr_status();
    free(z);
}
void print_zstr_status(){
    switch(zstr_status){
        case 100: printf("zstr_status = ERROR\n"); break;
        case 0: printf("zstr_status = OK\n"); break;
    }
}
void test_substring(){
    printf("test_substring()\n");
    //zstr dna = zstr_create("my humps my lovely lady lumps");
    int bad_len = 2048;
    char bad_data[2048];
    for (int i = 0; i < bad_len; i++){
        bad_data[i] = 'a';
    }
    bad_data[bad_len] = '\0';
    zstr b = zstr_create(bad_data);
    zstr n = zstr_substring(b, 2, 20);
    
    zstr_print_detailed(n);
    zstr_destroy(b);
    zstr_destroy(n);
    print_zstr_status();
    printf("\n");
}

void test_append(){
    printf("test_append()\n");
    zstr b = zstr_create("craps and ham");
    zstr s = zstr_create("craps");
    zstr_append(&b, s);
    int dl, tl; char* d;
    get_info(b, &dl, &tl , &d);
    printf("data length: %d, total length: %d, data: %s\n", dl, tl, d);
    zstr_destroy(s);
    zstr_destroy(b);
    print_zstr_status();
    printf("\n");
}

void test_append2(){ //test with a bad length
    //create 1st string
    int bad_len = 2048-9;
    //char bad_data[bad_len+1];
    char bad_data[bad_len];
    for (int i = 0; i < bad_len; i++){
        bad_data[i] = 'a';
    }
    bad_data[bad_len]='\0';
    zstr base = zstr_create(bad_data);
    
    //create second string
    int len2 = 9;
    char bad_data2[len2];
    for (int i = 0; i < len2; i++){
        bad_data2[i] = 'b';
    }
    bad_data2[len2]='\0';
    zstr z2 = zstr_create(bad_data2);
    
    //append
    zstr_append(&base,z2);
    print_zstr_status();
    
    //get data
    int dl, tl; char* d;
    get_info(base, &dl, &tl , &d);
    printf("data length: %d, total length: %d, data: %s\n", dl, tl, d);
    
    //clean
    zstr_destroy(z2);
    zstr_destroy(base);
    
}

void test_count( ){
    printf("test_count()\n");
    zstr b = zstr_create("    yote    yote    yote    yote   ");
    zstr s = zstr_create("yote");
    int i = zstr_index(b, s);
    printf("i: %d\n", i);
    int count = zstr_count(b, s);
    printf("count: %d\n", count);
    int c = zstr_compare(b, s);
    printf("zstr_compare res: %d\n", c);
    zstr_destroy(s);
    zstr_destroy(b);
    print_zstr_status();
    printf("\n");
}


void test_compare(){
    printf("test_compare()\n");
    zstr x = NULL;
    zstr y = zstr_create("yote");
    int ans = zstr_compare(x, y);
    printf("zstr_comp: %d\n", ans);
    print_zstr_status();
    
}
