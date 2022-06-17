/*
 * name: Rahel Gerson
 * CSC 352
 * this program computes the hypotenuse of a triangle, given two sides.
 *
 */

#include <stdio.h>
#include<math.h>
int check_input(int num);

int main()
{
double A, B, C;
printf("Enter side A length:\n");
scanf("%lf", &A);
while (A < .01){
    printf("number must be greater than .01 for hypotenuse calculation to be accurate\n");
    printf("Enter side A length:\n");
scanf("%lf", &A);
}
while (A > 2.2250738585072014 *pow(10,308)){
    printf("number must be smaller than 2.2250E308 for calculation to be accurate\n");
    printf("Enter side A length:\n");
scanf("%lf", &A);
}
    
printf("Enter side B length:\n");
scanf("%lf", &B);
while (B < .01){
    printf("number must be greater than .01 for hypotenuse calculation to be accurate\n");
    printf("Enter side B length:\n");
    scanf("%lf", &B);
}
while (B  > 2.2250738585072014 *pow(10,308)){
    printf("number must be smaller than 2.2250E308 for calculation to be accurate\n");
    printf("Enter side A length:\n");
scanf("%lf", &B);
}
//calculate C
C = sqrt(pow(A,2)+pow(B,2));
printf("Length of side C: %.2lf\n", C);
}

