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

enum{white, black};

//bit macros

#define get_bit(bb, square) (bb & (1ULL << square))
#define set_bit(bb, square) (bb |= (1ULL << square))
#define pop_bit(bb, square) get_bit(bb, square) ? bb ^= (1ULL << square) : 0
//print bitboard
void print_bitboard(U64 bb)
{
    printf("\n");
    for (int rank = 0; rank < 8 ; rank++){
        for (int file = 0; file < 8 ; file++){
            int square = 8*rank + file;
            if(!file){
                printf(" %d ", 8 - rank);
            }
            //estado del bit 'square' 1 ó 0
            printf(" %d", get_bit(bb,square) ?  1 : 0);
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n\n");

    printf("Bitboard: %llud \n", bb);
}
//tabla de ataques -> [side][attacks]
U64 pawn_attacks[2][64];

/* not A file
0 1 1 1 1 1 1 1
0 1 1 1 1 1 1 1
0 1 1 1 1 1 1 1
0 1 1 1 1 1 1 1
0 1 1 1 1 1 1 1
0 1 1 1 1 1 1 1
0 1 1 1 1 1 1 1
0 1 1 1 1 1 1 1
*/  
const U64 not_a_file = 18374403900871474942ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_hg_file = 4557430888798830399ULL;

//generate pawn attacks
U64 mask_pawn_attacks(int side, int square){
    U64 localbb = 0ULL;
    U64 attacks = 0ULL;

    //set piece on board
    set_bit(localbb, square);
    if(!side){ //white
        if((localbb>>7) & not_a_file) attacks |= (localbb >> 7);
        if((localbb>>9) & not_h_file) attacks |= (localbb >> 9);
    }
    else { //black
        if((localbb<<7) & not_h_file) attacks |= (localbb << 7);
        if((localbb<<9) & not_a_file) attacks |= (localbb << 9);
    }
    return attacks;
}

//init leaper_peaces attacks
void init_leaper_attacks(){
    for (int square = 0; square < 64 ; square ++){
        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);
    }
}

int main(){

    U64 bb = 0ULL;
    init_leaper_attacks();
    // for (int square = 0; square < 64 ; square ++){
    //     print_bitboard(pawn_attacks[white][square]);
    // }
    for (int square = 0; square < 64 ; square ++){
        print_bitboard(pawn_attacks[black][square]);
    }
    
}