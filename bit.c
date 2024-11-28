#include <stdio.h>

#define U64 unsigned long long
//squares en el tablero
enum{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};
/*
"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
*/

//bit macros
#define get_bit(bb, casilla) (bb & (1ULL <<casilla))
#define set_bit(bb, casilla) (bb |= (1ULL << casilla))
#define pop_bit(bb, casilla) get_bit(bb, casilla) ? bb ^= (1ULL << casilla) : 0
//print bitboard
void print_bitboard(U64 bb)
{
    printf("\n");
    for (int fila = 0; fila < 8 ; fila++){
        for (int col = 0; col < 8 ; col++){
            int casilla = 8*fila + col;
            if(!col){
                printf(" %d ", 8 - fila);
            }
            //estado del bit 'casilla' 1 ó 0
            printf(" %d", get_bit(bb,casilla) ?  1 : 0);
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n\n");

    printf("Bitboard: %llud \n", bb);
}
//[side][attacks]
U64 pawn_attacks[2][64];

int main(){

    U64 bb = 0ULL;

}