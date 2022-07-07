//
//  test.c
//  pa5
//
//  Created by Rahel Gerson on 7/6/22.
//

#include <stdio.h>
#include "array.h"


int test(){
    long nums[100] = {5,1,2,3,4,5};
    int s = sum(nums);
    printf("sum: %d\n", s);
    
    
    long nums1[100] = {7,1,2,3,100,4,5,6};
    printf("min_idx: %d\n", minil(nums1));
    printf("max_idx: %d\n\n", maxil(nums1));
    
    double nums_d[100] = {7,1,2,3,100,4,5,6};
    printf("min_idx: %d\n", minid(nums_d));
    printf("max_idx: %d\n", maxid(nums_d));
    
    printad(nums_d);
    printal(nums1);
    return 0;
}
