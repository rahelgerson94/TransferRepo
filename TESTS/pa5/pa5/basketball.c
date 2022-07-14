//  csc 352
//  basketball.c
//  pa5
//  Created by Rahel Gerson on 7/2/22.
#include "utils.h"
#include "basketball.h"
#include "array.h"

#define MAX 1100

void pre_proc(char line[MAX], double stats[7], char name[100] ){
    long temp_stats[100][4];
    for (int i = 0; i < 100; i++){
        reset_long_arr(temp_stats[i], 0, 4, -1);
    }
    //put length in the zeroth elem
    for (int i = 0; i < 100; i++){
        temp_stats[i][0] = 3;
    }
    
    /*determine name*/
    int l = 0;
    int c = 0;
    while (line[c] != '['){
        name[c] = line[c];
        c++;
    }
    c+=1;
    /* now, populate the temp_stats matrix as intermed step to determine
     sdev, mean */
    char stats_single_game[10]; reset_char_arr(stats_single_game, 0, 10);
    int stats_idx = 0;
    int len = len_char(line);
    
    for (int i = c; i < len; i++){
        if (line[i]== '[') continue;
        if (line[i] != ']'){
            stats_single_game[stats_idx] = line[i];
            stats_idx++;
        }
        else if (line[i] == ']'){
            long temp_temp_stats[3];
            str2long_list(stats_single_game, temp_temp_stats);
            longcpy_( temp_stats[l], temp_temp_stats,  1, 0, 3);
            printal(temp_stats[l]);
            stats_idx = 0;
            l++;
            reset_char_arr(stats_single_game, 0, 10);
        }
    } //end population of temp_stats
    
    /* generate P,A,I vectors*/
    int N = l; //number of games
    long P[N+1], A[N+1], R[N+1];
    
    
    P[0] = N; A[0] = N; R[0] = N;
    for (int l = 0; l < N; l++){
        P[l+1] = temp_stats[l][0+1]; //fetch 0th col
        R[l+1] = temp_stats[l][1+1]; //fetch 1st col
        A[l+1] = temp_stats[l][2+1]; //fetch 2nd col
    }
    printf("P: "); printal(P);
    printf("R: "); printal(R);
    printf("A: "); printal(A);
    printf("\n");
    /* populate the desired stats vector */
    stats[1+0] = sdev(P);
    stats[1+1] = sdev(R);
    stats[1+2] = sdev(A);
    stats[1+3] = mean(P);
    stats[1+4] = mean(R);
    stats[1+5] = mean(A);
    //printad(stats);
}

void transpose(long out[7][max], long in[max][7], int num_rows){
    int num_cols = (int)out[0][0];
    
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            if (j==0) out[i][0] = num_rows;
            else{
                out[j][i-1] = in[i][j+1];
            }
        }
        printal(out[i]);
    }
}


void get_stats(double stats[100][7],  char names[100][100], int lines){
//below variable naminng convention: C is for consisitent, M is for mean.
//S,R,A stand for scorrer, rebounder, assister.
            char* CS_min = NULL; //Consistent scorer min
            char* CS_max = NULL; //Consistent scorer max
            char* CR_min = NULL;
            char* CR_max = NULL;
            char* CA_min = NULL;
            char* CA_max = NULL;
            char* MS_min = NULL; //Mean scorer min
            char* MS_max = NULL; //Mean scorer max
            char* MR_min = NULL;
            char* MR_max = NULL;
            char* MA_min = NULL;
            char* MA_max = NULL;

    for (int i = 1; i < 7; i++){
        double temp[lines+1];
        temp[0] = lines;
        
         //printf("%d: ", i);
         
         for (int j = 0; j < lines; j++){ //populate temp
             temp[j+1] = stats[j][i];
             //printf("%lf ", temp[j+1]);
         }
         //*/
       
        
        int min_idx = minid(temp) -1;
        int max_idx = maxid(temp)-1;
        //printf("\ntemp[0] = %.2lf", temp[0]);
        /*
         printf("\nmin: %s\n", names[min_idx]);
         printf("max: %s\n", names[max_idx]);
         printf("min_idx = %d, max_idx = %d", min_idx, max_idx);
         printf("\n\n");
         */
       
        switch(i){
            case 1:
                CS_min = names[max_idx]; //want names[0]
                CS_max = names[min_idx]; //want names[1]
            break;
            case 2:
                CR_min = names[max_idx]; //names[1] James Harden
                CR_max = names[min_idx]; //names[3] Chris Paul
            break;
            case 3:
                CA_min = names[max_idx];
                CA_max = names[min_idx];
            break;
            case 4:
                MS_min = names[min_idx]; // Mean scorer min
                MS_max = names[max_idx]; //Mean scorer max
            break;
            case 5:
                MR_min = names[min_idx];
                MR_max = names[max_idx];
            break;
            case 6:
                MA_min = names[min_idx];
                MA_max = names[max_idx];
            break;
        }
        
        reset_double_arr(temp, 1, lines+1, -1);
    } //end outer for
    
   printf("most consistent scorer: %s\n", CS_max);
   printf("most inconsistent scorer: %s\n", CS_min);
   printf("highest scorer: %s\n", MS_max);
   printf("lowest scorer: %s\n", MS_min);
   printf("most inconsistent rebounder: %s\n", CR_min);
   printf("most consistent rebounder: %s\n", CR_max);
   printf("highest rebounder: %s\n", MR_max);
   printf("lowest rebounder: %s\n", MR_min);
   printf("most inconsistent assister: %s\n", CA_min);
   printf("most consistent assister: %s\n", CA_max);
   printf("lowest assister: %s\n", MA_min);
   printf("highest assister: %s\n", MA_max);

}
        
void get_separation_locs(char input[], char delim_type, int startLoc, int endLoc, int output[]){
    char delim;
    if (delim_type == 'c'){
        delim = ',';
    }
    else if (delim_type == '\n'){
        delim = '\n';
    }
    if (endLoc == -1)
    {
        endLoc = 100;
    }
    int ll = 0;
    for (int ii = startLoc; ii < endLoc; ii++)
    {
        if (input[ii] == delim || input[ii] == '\n')
        {
            output[ll++] = ii;
        }
        else if (input[ii] == '\0')
        {
            output[ll++] = ii;
            break;
        }
    }
}


void str2int_list(char input[], int output[]){
    int Start = 0;
    // int End = 0;
    int ii = 0;
    int extra = 0;
    int commas[100] = {0};
    // int num;
    get_separation_locs(input, 'c', 0, -1, commas);
    while (commas[ii] > 0)
    {
        char dst[100] = {'\0'};
        reset_char_arr(dst, 0,100);
        strcpy_(dst, input, 0, Start, commas[ii]);
        if (checkCharLoc(dst, '-') >= 0){
            int expandedList[100] = {-1};
            reset_int_arr(expandedList, 0,100, -1);
            int len = expandList(dst, expandedList);
            intcpy_(output, expandedList, ii + extra, 0, len);
            extra += (len -1);
            Start = commas[ii] + 1;
            ii++;
        }else{
        int num = combineElements(dst, commas[ii] - Start);
        output[ii] = num;
        Start = commas[ii] + 1;
        ii++;
        }
    }
}
void str2long_list(char input[], long output[]){
    int Start = 0;
    // int End = 0;
    int ii = 0;
    int extra = 0;
    int commas[100] = {0};
    // int num;
    get_separation_locs(input, 'c', 0, -1, commas);
    while (commas[ii] > 0)
    {
        char dst[100] = {'\0'};
        reset_char_arr(dst, 0,100);
        strcpy_(dst, input, 0, Start, commas[ii]);
        if (checkCharLoc(dst, '-') >= 0){
            long expandedList[100] = {-1};
            reset_long_arr(expandedList, 0,100, -1);
            int len = expandListLong(dst, expandedList);
            longcpy_(output, expandedList, ii + extra, 0, len);
            extra += (len -1);
            Start = commas[ii] + 1;
            ii++;
        }else{
        int num = combineElements(dst, commas[ii] - Start);
        output[ii] = num;
        Start = commas[ii] + 1;
        ii++;
        }
    }
}

int expandList(char input[], int output[]){
    int check = checkCharLoc(input,'-');
    if(check < 0) return -1;
    output[0] = combineElements(input, check);
    int ll = 1;
    while (input[ll] >=0){
        int jj = ll;
        char dst[100] = {'\0'};
        int Size = len_char(input);
        strcpy_(dst, input, 0, check + 1, Size);
        int num2go2 = combineElements(dst, Size - check - 1);
        int Add = 1;
        while (output[jj - 1] != num2go2)
        {
            output[jj++] = output[ll - 1] + Add++;
        }
        return jj;
        ll = jj + 1;
    }
    ll++;
    return ll;
}
int expandListLong(char input[], long output[]){
    int check = checkCharLoc(input,'-');
    if(check < 0) return -1;
    output[0] = combineElements(input, check);
    int ll = 1;
    while (input[ll] >=0){
        int jj = ll;
        char dst[100] = {'\0'};
        int Size = len_char(input);
        strcpy_(dst, input, 0, check + 1, Size);
        int num2go2 = combineElements(dst, Size - check - 1);
        int Add = 1;
        while (output[jj - 1] != num2go2)
        {
            output[jj++] = output[ll - 1] + Add++;
        }
        return jj;
        ll = jj + 1;
    }
    ll++;
    return ll;
}

int char2num(char Input)
{
    int out = Input - '0';
    if (out > 9 || out < 0)
    {
        return -1;
    }
    return out;
}



int combineElements(char arr[], int cc){
    int nums[100] = {-1};

    for (int ll = 0; ll < cc; ll++)
    {

        int temp = char2num(arr[ll]);
        // TODO : fix the zero problem
        if (temp >= 0)
            nums[ll] = temp;
        else
        {
            char dst[100] = {'\0'};
            int expandedList[100] = {-1};
            reset_int_arr(expandedList, 0,100, -1);
            int Size = len_char(arr);
            strcpy_(dst, arr, 0, ll + 1, Size);
            expandList(dst, expandedList);
//            int num2go2 = combineElements(dst, Size - ll - 1);
//            int Add = 1;
//            while (nums[jj - 1] != num2go2)
//            {
//                nums[jj++] = nums[ll - 1] + Add++;
//            }
//            ll = jj + 1;
        }
    }
    int out = 0;
    int mult = 1;
    for (int ii = cc - 1; ii >= 0; ii--)
    {
        out += nums[ii] * mult;
        mult = mult * 10;
    }
    return out;
}

int checkCharLoc(char input[],char b){
    int ii = 0;
    while(input[ii] != '\0'){
        if (input[ii] == b) return ii;
        ii++;
    }
    return -1;
}

