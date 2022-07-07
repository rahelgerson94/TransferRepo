

#ifndef array_h
#define array_h

#include <stdio.h>
#include <math.h>

long sum(long values[]);//Return the sum of every element in values
int minil(long values[]);//Return the index of the minimum value in values
int minid(double values[]);//Return the index of the minimum value in values
int maxil(long values[]);//Return the index of the maximum value in values
int maxid(double values[]);//Return the index of the maximum value in values
void printal(long values[]);//Print the elements in values Formatted as: length ARRAY_LENGTH array: EL1, EL2, ..., ELN
void printad(double values[]);//Print the elements in values. Formatted as: length ARRAY_LENGTH array: EL1, EL2, ..., ELN
double mean(long values[]);//Return the mean(average) of the elements in values
double sdev(long values[]);//Return the standard deviation of the elements in values
#endif /* array_h */
