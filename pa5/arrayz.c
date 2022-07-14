//
//  pa5
// csc 352
/*a library of functions for operating on arrays. the first part, utils,
 is copy past of a seprate libbrary of widely used functions, so very few are actually used
 in arrayz, but are inlcdued here for conveneice.
*/

#include "arrayz.h"

/* * * * * * * * * UTILS FUNCTIONS * * * * * * * * * * */
//get the length of an int array
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

//get the length of an long array
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
//get the length of an double array
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

//get the length of an char array
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
/* * * * * * * * * * * * *END UTILS FUNCTIONS * * * * * * * * * * * * * * */

//sum the values in an array
long sum(long values[]){
    //Return the sum of every element in values
    int sum = 0;
    int len = (int)values[0];
    for (int i = 1; i <= len; i++){
        sum+= values[i];
    }
    return sum;
}

//Return the index of the minimum value in values
int minil(long values[]){
    long min= values[1];
    int min_idx = 1;
    int len = (int)values[0];
    for (int i = 1; i <= len; i++){
        if (values[i] < min){
            min_idx = i;
            min = values[i];
        }
    }
    return min_idx;
}

int minid(double values[]){
    int len = values[0];
    double min = values[1];
    int min_idx = 1;
    for (int i = 1; i <= len; i++){
        if (values[i] < min){
            min_idx = i;
            min = values[i];
        }
    }
    return min_idx;
}//Return the index of the minimum value in values

int maxil(long values[]){
    int len = (int)values[0];
    long max = values[1];
    int max_idx = 1;
    for (int i = 2; i <= len; i++){
        if (values[i] > max){
            max_idx = i;
            max = values[i];
        }
    }
    return max_idx;
}//Return the index of the maximum value in values

int maxid(double values[]){
    int len = values[0];
    double max = values[1];
    int max_idx = 1;
    for (int i = 2; i <= len; i++){
        if (values[i] > max){
            max = values[i];
            max_idx = i;
        }
    }
    return max_idx;
}//Return the index of the maximum value in values

void printal(long values[]){//Print the elements in values Formatted as: length ARRAY_LENGTH array: EL1, EL2, ..., ELN
    int len = (int)values[0];
printf("length %d array: ",len );
    for (int i = 1; i <= len; i++)
    {
        if (i == len )
        {
            printf("%ld\n", values[i]);
            return;
        }
        else
        {
            printf("%ld, ", values[i]);
        }
    }
}


void printad(double values[]){//Print the elements in values. Formatted as: length ARRAY_LENGTH array: EL1, EL2, ..., ELN
    int len = values[0];
    printf("length %d array: ",len );
    for (int i = 1; i <= len; i++)
    {
        if (i == len )
        {
            printf("%f\n", values[i]);
            return;
        }
        else
        {
            printf("%f, ", values[i]);
        }
    }
}



//Return the mean(average) of the elements in values
double mean(long values[]){
    int len = (int)values[0];
    double sum = 0;
    for (int i = 1; i <= len; ++i) {
        sum += values[i];
    }
    return sum/len;
}

double sdev(long values[]){
    int len = (int)values[0];
    double ave, dev = 0.0;
    ave = mean(values);
    for (int i = 1; i <= len; ++i) {
        dev += pow(values[i] - ave, 2);
    }
    return sqrt(dev / len);
}//Return the standard deviation of the elements in values
