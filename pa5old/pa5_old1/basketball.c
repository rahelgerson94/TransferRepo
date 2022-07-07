//  csc 352
//  basketball.c
//  pa5
//  Created by Rahel Gerson on 7/2/22.
#include "arrayz.h"
#define max 1100


void pre_proc(char line[max], double stats[6], char name[100] );
void get_stats(double arr[100][7], char names[100][100], int lines);


char curr_line[max];
char names[100][100];
double stats[100][7];
int main(int argc, const char * argv[]) {
    if (!(argc == 2)){
        fprintf(stderr, "expects 1 command line argument\n");
        return 1;
    }
    /*set up the data*/
    for (int l = 0; l < 100; l++){
        stats[l][0] = 6;
    }
    char* path = calloc(strlen(argv[1]), sizeof(char));
    strcpy(path, argv[1]);
           
    FILE* data = fopen(path, "r");
    int l = 0;
    while(fgets(curr_line, max, data) != NULL){
        //printf("%s", curr_line);
        pre_proc(curr_line, stats[l], names[l]);
       
        //printad(stats[l]);
        
        l++;
    }
    
    /*
     for (int i = 0; i < 5; i++){
         printf("%s\n", names[i]);
     }
     */
    
    get_stats(stats,  names, l);
    /*CLEANUP*/
    fclose(data);
    /*freeing data*/
    free(path);
    return 0;
}


void pre_proc(char line[max], double stats[7], char name[100] ){
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
            //printal(temp_stats[l]);
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
//    printf("P: "); printal(P);
//    printf("R: "); printal(R);
//    printf("A: "); printal(A);
//    printf("\n");
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

void print_stats(double arr[100][7], char names[100][100], int lines){
    for (int i = 1; i < 7; i++){
        double temp[lines+1];
        temp[0] = lines;
        printf("%d: ", i);
        /*
         for (int j = 0; j < lines; j++){
             temp[j+1] = arr[j][i];
             printf("%lf ", temp[j+1]);
         }
         printf("\n\n");
         */
       
        int min_idx = minid(temp);
        int max_idx = maxid(temp);
        char* name_min = names[min_idx];
        char* name_max = names[max_idx];
        switch(i){
            case 1:
                printf("most consistent scorer: %s\n", name_min);
                printf("most inconsistent scorer: %s\n", name_max);
            break;
            case 2:
                printf("highest scorer: %s\n", name_max);
                printf("lowest scorer: %s\n", name_min);
            break;
            case 3:
                printf("most inconsistent rebounder: %s\n", name_max);
                printf("most consistent rebounder: %s\n", name_min);
            break;
            case 4:
                printf("highest rebounder: %s\n", name_max);
                printf("lowest rebounder: %s\n", name_min);
            break;
            case 5:
                printf("most inconsistent assister: %s\n", name_max);
                printf("most consistent assister: %s\n", name_min);
            break;
            case 6:
                printf("lowest assister: %s\n", name_max);
                printf("highest assister: %s\n", name_min);
            break;
        }
        reset_double_arr(temp, 1, lines+1, -1);
    } //end outer for
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
        /*
         printf("%d: ", i);
         for (int j = 0; j < lines; j++){ //populate temp
             temp[j+1] = stats[j][i];
             printf("%lf ", temp[j+1]);
         }
         */
       
        
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
        
