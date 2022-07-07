//
//  basketball.h
//  pa5
//
//  Created by Rahel Gerson on 7/2/22.
//
#define max 100
#ifndef basketball_h
#define basketball_h


void pre_proc(char line[100], double stats[6], char name[100] );
void get_separation_locs(char input[], char delim_type, int startLoc, int endLoc, int output[]);
void parse_cmd_args2(char input[], int output[]);
void str2long_list(char input[], long output[]);
void str2int_list(char input[], int output[]);
void print_stats(double arr[100][7], char names[100][100], int lines);
void get_stats(double arr[100][7], char names[100][100], int lines);

int expandList(char input[], int output[]);
int expandListLong(char input[], long output[]);
int char2num(char Input);
int checkCharLoc(char input[],char b);
int combineElements(char arr[], int cc);
void transpose(long out[7][max], long in[max][7], int num_rows);
#endif /* basketball_h */
