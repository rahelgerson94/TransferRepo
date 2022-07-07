/*
 Rahel Gerson
 CSC352
 this program calculates the number of locations a piece could be in given a number  of moves
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
int brigade_locations(int m);
int king_locations(int m);
void checkInputsNUMS(int input);
void checkInputsLETTERS(char arg);
int main(int argc, const char * argv[]) {
    
    char piece_type;
    int m; //number of moves
    int locs;

    printf("Enter piece type (k, b, p):\n");
    scanf("%c", &piece_type );
    checkInputsLETTERS(piece_type);
    
    printf("Enter number of moves:\n");
    scanf("%d", &m );
    checkInputsNUMS(m);
    switch(piece_type){
        case 'k': locs = king_locations(m); break;
        case 'K': locs = king_locations(m); break;
        case 'p': locs = m+1; break;
        case 'P': locs = m+1; break;
        case 'b': locs = brigade_locations(m); break;
        case 'B': locs = brigade_locations(m); break;
    }
    printf("possible locations: %d\n", locs);
    return 0;
}

int brigade_locations(int m){
    if (m == 0){ return 1;}
    else{ return brigade_locations(m - 1) + 4*m; }
}
int king_locations(int m){
    if (m == 0){ return 1;}
    else{ return king_locations(m - 1) + 8*m; }
}
void checkInputsNUMS(int input){
    if(input < 0){
        printf("ERROR : Illegal Alphabet Value passed\n\t");
        exit(EXIT_FAILURE);
    }
    
}
void checkInputsLETTERS(char arg){

    switch (arg){
        case 'k':
            break;
        case 'b':
            break;
        case 'p':
            break;
        case 'K':
            break;
        case 'B':
            break;
        case 'P':
            break;
        default:
            printf("ERROR : Illegal Alphabet Value passed\n\t");
            exit(EXIT_FAILURE);
    }

    
}
