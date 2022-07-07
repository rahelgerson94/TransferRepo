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

#define ZTR_OK 0
#define ZTR_ERROR 100
#define ZTR_GREATER 1
#define ZTR_LESS -1
#define ZTR_EQUAL 0
typedef char* zstr;
typedef int zstr_code;

zstr zstr_create(char* initial_data);
void zstr_destroy(zstr to_destroy);
void zstr_append(zstr * base, zstr to_append);
int zstr_index(zstr base, zstr to_search);
int zstr_count(zstr base, zstr to_search);
int zstr_compare(zstr x, zstr y);
zstr zstr_substring(zstr base, int begin, int end);
void zstr_print_detailed(zstr data);
int get_total_bytes(char* data);
#endif /* zstr_h */
