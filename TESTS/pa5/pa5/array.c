//
//  array.c
//  pa5
//
//  Created by Rahel Gerson on 7/2/22.
//

#include "array.h"
#include "utils.h"

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
            printf("%.2f\n", values[i]);
            return;
        }
        else
        {
            printf("%.2f, ", values[i]);
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
