/*
 Rahel Gerson
 CSC352
 this program calculates the number of locations a piece could be in given a number  of moves
 */
#include <stdio.h>
int brigade_locations(int m);
int king_locations(int m);

int main(int argc, const char * argv[]) {
    char piece_type;
    int m; //number of moves
    int locs;

    printf("Enter piece type (k, b, p):\n");
    scanf("%c", &piece_type );
    printf("Enter number of moves:\n");
    scanf("%d", &m );
    
    switch(piece_type){
        case 'k': locs = king_locations(m); break;
        case 'p': locs = m+1; break;
        case 'b': locs = brigade_locations(m); break;
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


