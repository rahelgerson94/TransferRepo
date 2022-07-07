
#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int len_int(int arr[]);
int len_long(long arr[]);
int len_double(double arr[]);

int len_char(char arr[]);
void reset_char_arr(char arr[], int start, int end);
void reset_int_arr( int arr[], int start, int end, int val);
void reset_long_arr(long arr[], int start, int end, int val);
void reset_float_arr(float arr[], int start, int end, int val);
void reset_double_arr(double arr[], int start, int end, int val);

void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end);
bool is_char(char c);
bool is_digit(char c);
void print_int_arr(int arr[]);
void intcpy_(int dst[], int src[], int out_start, int in_start, int in_end);
void floatcpy_(float dst[], float src[], int out_start, int in_start, int in_end);
void doublecpy_(double dst[], double src[], int out_start, int in_start, int in_end);
void longcpy_(long dst[], long src[], int out_start, int in_start, int in_end);


#endif /* utils_h */
