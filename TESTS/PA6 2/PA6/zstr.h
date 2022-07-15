//
//  zstr.h
//  PA6
//
//  Created by Rahel Gerson on 7/7/22.
//

#ifndef zstr_h
#define zstr_h
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define ZSTR_OK 0
#define ZSTR_ERROR 100
#define ZSTR_GREATER 1
#define ZSTR_LESS -1
#define ZSTR_EQUAL 0
typedef char* zstr;
typedef int zstr_code;
extern zstr_code zstr_status;

zstr zstr_create(char* initial_data);
void zstr_destroy(zstr to_destroy);
void zstr_append(zstr * base, zstr to_append);
int zstr_index(zstr base, zstr to_search);
int zstr_count(zstr base, zstr to_search);
int zstr_compare(zstr x, zstr y);
zstr zstr_substring(zstr base, int begin, int end);
void zstr_print_detailed(zstr data);
int get_total_bytes(char* data);
void set_status(zstr z, char* data, zstr_code* zstr_status, bool init, bool substring, bool append);
void get_info(zstr z, int* data_len, int* total_bytes, char** data);
void set_info(zstr* z, int data_len, int total_bytes, char* data, int start);

#endif /* zstr_h */
