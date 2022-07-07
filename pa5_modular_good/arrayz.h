

#ifndef array_h
#define array_h

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

long sum(long values[]);//Return the sum of every element in values
int minil(long values[]);//Return the index of the minimum value in values
int minid(double values[]);//Return the index of the minimum value in values
int maxil(long values[]);//Return the index of the maximum value in values
int maxid(double values[]);//Return the index of the maximum value in values
void printal(long values[]);//Print the elements in values Formatted as: length ARRAY_LENGTH array: EL1, EL2, ..., ELN
void printad(double values[]);//Print the elements in values. Formatted as: length ARRAY_LENGTH array: EL1, EL2, ..., ELN
double mean(long values[]);//Return the mean(average) of the elements in values
double sdev(long values[]);//Return the standard deviation of the elements in values
int len_int(int arr[]);
int len_long(long arr[]);
int len_double(double arr[]);
//utils 
int len_char(char arr[]);
void reset_char_arr(char arr[], int start, int end);
void reset_int_arr( int arr[], int start, int end, int val);
void reset_long_arr(long arr[], int start, int end, int val);
void reset_float_arr(float arr[], int start, int end, int val);
void reset_double_arr(double arr[], int start, int end, int val);

void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end);
bool is_char(char c);
bool is_digit(char c);
//void print_int_arr(int arr[]);
void intcpy_(int dst[], int src[], int out_start, int in_start, int in_end);
void floatcpy_(float dst[], float src[], int out_start, int in_start, int in_end);
void doublecpy_(double dst[], double src[], int out_start, int in_start, int in_end);
void longcpy_(long dst[], long src[], int out_start, int in_start, int in_end);


#endif /* array_h */
