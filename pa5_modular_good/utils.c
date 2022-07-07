#include "utils.h"
int len_int(int arr[]){
    int i = 0;
    int len = 0;
    while (arr[i] >= 0){ //!= -1){
        //printf("%d ",arr[i] ) ;
        len++;
        i++;
    }
    return len;
}
int len_long(long arr[]){
    int i = 0;
    int len = 0;
    while (arr[i] >= 0){ //!= -1){
        //printf("%d ",arr[i] ) ;
        len++;
        i++;
    }
    return len;
}
int len_double(double arr[]){
    int i = 0;
    int len = 0;
    while (arr[i] >= 0){ //!= -1){
        //printf("%d ",arr[i] ) ;
        len++;
        i++;
    }
    return len;
}

int len_char(char arr[]){
    int i = 0;
    int len = 0;
    while (arr[i] != '\0'){
        if (arr[i] == '\n')
            break;
        else{
            len++;
        }
        i++;
    }
    return len;
}


void reset_char_arr(char arr[], int start, int end){
    for (int i = start; i < end; i++)
    {
        arr[i] = '\0';
    }
}
void reset_int_arr(int arr[], int start, int end, int val)
{
    for (int i = start; i < end; i++)
    {
        arr[i] = val;
    }
}
void reset_long_arr(long arr[], int start, int end, int val)
{
    for (int i = start; i < end; i++)
    {
        arr[i] = val;
    }
}

void reset_float_arr(float arr[], int start, int end, int val)
{
    for (int i = start; i < end; i++)
    {
        arr[i] = val;
    }
}
void reset_double_arr(double arr[], int start, int end, int val)
{
    for (int i = start; i < end; i++)
    {
        arr[i] = val;
    }
}
void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end){
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++)
    {
        if (src[in_i]== '\n') break;
        dst[out_i] = src[in_i];
        in_i++;
    }
}

bool is_char(char c){
    bool is_char = false;
    bool upper = false;  bool lower = false;
    
    if ((int)c >= 97 && (int)c <= 122) lower = true;
    if ((int)c >= 65 && (int)c <= 90) upper = true;
    if (upper || lower ) is_char = true;
    return is_char;
}
bool is_digit(char c){
    //[48-57]
    if ((int)c >= 48 && (int)c <= 57) return true;
    else return false;
}


void print_int_arr(int arr[])
{
    printf("{ ");
    int length = len_int(arr);

    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            printf("%d }\n", arr[i]);
            return;
        }
        else
        {
            printf("%d, ", arr[i]);
        }
    }
}


void intcpy_(int dst[], int src[], int out_start, int in_start, int in_end)
{
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++)
    {
        dst[out_i] = src[in_i];
        in_i++;
    }
}

void floatcpy_(float dst[], float src[], int out_start, int in_start, int in_end)
{
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++)
    {
        dst[out_i] = src[in_i];
        in_i++;
    }
}
void doublecpy_(double dst[], double src[], int out_start, int in_start, int in_end)
{
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++)
    {
        dst[out_i] = src[in_i];
        in_i++;
    }
}
void longcpy_(long dst[], long src[], int out_start, int in_start, int in_end)
{
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++)
    {
        dst[out_i] = src[in_i];
        in_i++;
    }
}

