//
//  pa4.h
//  pa4
//
//  Created by Rahel Gerson on 6/26/22.
//

#ifndef pa4_h
#define pa4_h
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"


void sgrep(bool e, bool i, bool o, char pattern[200], char line[200]);
bool match_char(char act, char ref, bool i);
int check_pattern(char pat[200]);

#endif /* pa4_h */
