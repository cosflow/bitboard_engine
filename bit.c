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
U64 knight_attacks[64];
U64 king_attacks[64];

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

U64 mask_knight_attacks(int square){
    U64 localbb = 0ULL;
    U64 attacks = 0ULL;

    //set piece on board
    set_bit(localbb, square);
    if((localbb>>17) & not_h_file) attacks |= (localbb >> 17);
    if((localbb>>15) & not_a_file) attacks |= (localbb >> 15);
    if((localbb>>10) & not_hg_file) attacks |= (localbb >> 10);
    if((localbb>>6) & not_ab_file) attacks |= (localbb >> 6);
    if((localbb<<17) & not_a_file) attacks |= (localbb << 17);
    if((localbb<<15) & not_h_file) attacks |= (localbb << 15);
    if((localbb<<10) & not_ab_file)attacks |= (localbb << 10);
    if((localbb<<6) & not_hg_file) attacks |= (localbb << 6);
    
    return attacks;
}

U64 mask_king_attacks(int square){
    U64 localbb = 0ULL;
    U64 attacks = 0ULL;
    //set piece on board
    set_bit(localbb, square);
    if((localbb>>7) & not_a_file) attacks |= (localbb >> 7);
    if((localbb>>1) & not_h_file) attacks |= (localbb >> 1);
    if((localbb<<7) & not_h_file) attacks |= (localbb << 7);
    if((localbb>>9) & not_h_file) attacks |= (localbb >> 9);
    if((localbb<<1) & not_a_file) attacks |= (localbb << 1);
    if((localbb<<9) & not_a_file) attacks |= (localbb << 9);
    if(localbb>>8) attacks |= (localbb >> 8);
    if(localbb<<8) attacks |= (localbb << 8);

    return attacks;
}

U64 mask_bishop_attacks(int square){
    U64 attacks = 0ULL;

    int r,f;
    int tr = square / 8;
    int tf = square % 8;

    //mask relevant bishop squares
    for (r = tr + 1, f = tf + 1 ; r <= 6 && f <= 6 ; r++, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf + 1 ; r >= 1 && f <= 6 ; r--, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf - 1 ; r >= 1 && f >= 1 ; r--, f--) attacks |= (1ULL << (r * 8 + f));
    for (r = tr + 1, f = tf - 1 ; r <= 6 && f >= 1 ; r++, f--) attacks |= (1ULL << (r * 8 + f));


    return attacks;
}

U64 bishop_attacks_on_the_fly(int square, U64 block){
    U64 attacks = 0ULL;

    int r,f;
    int tr = square / 8;
    int tf = square % 8;

    //mask relevant bishop squares
    for (r = tr + 1, f = tf + 1 ; r <= 7 && f <= 7 ; r++, f++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << r * 8 + f) & block)break;
    }
    for (r = tr - 1, f = tf + 1 ; r >= 0 && f <= 7 ; r--, f++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << r * 8 + f) & block)break;
    }
    for (r = tr - 1, f = tf - 1 ; r >= 0 && f >= 0 ; r--, f--) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << r * 8 + f) & block)break;
    }
    for (r = tr + 1, f = tf - 1 ; r <= 7 && f >= 0 ; r++, f--) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << r * 8 + f) & block)break;
    }
    return attacks;
}

U64 mask_rook_attacks(int square){
    U64 attacks = 0ULL;

    int r,f;
    int tr = square / 8;
    int tf = square % 8;

    //mask relevant rook squares
    for (r = tr + 1 ; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
    for (f = tf + 1 ; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
    for (r = tr - 1 ; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
    for (f = tf - 1 ; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));


    return attacks;
}

U64 rook_attacks_on_the_fly(int square, U64 block){
    U64 attacks = 0ULL;

    int r,f;
    int tr = square / 8;
    int tf = square % 8;

    //mask relevant rook squares
    for (r = tr + 1 ; r <= 7; r++) {
        attacks |= (1ULL << (r * 8 + tf));
        if((1ULL << (r * 8 + tf)) & block) break;
    }
    for (f = tf + 1 ; f <= 7; f++) {
        attacks |= (1ULL << (tr * 8 + f));
        if((1ULL << (tr * 8 + f)) & block) break;

    }
    for (r = tr - 1 ; r >= 0; r--) {
        attacks |= (1ULL << (r * 8 + tf));
        if((1ULL << (r * 8 + tf)) & block) break;
    }
    for (f = tf - 1 ; f >= 0; f--) {
        attacks |= (1ULL << (tr * 8 + f));
        if((1ULL << (tr * 8 + f)) & block) break;
    }

    return attacks;
}
//init leaper_peaces attacks
void init_leaper_attacks(){
    for (int square = 0; square < 64 ; square ++){
        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);
        knight_attacks[square] = mask_knight_attacks(square);
        king_attacks[square] = mask_king_attacks(square);
    }
}

int main(){

    U64 bb = 0ULL;

    init_leaper_attacks();
    // for (int square = 0; square < 64 ; square ++){
    //     print_bitboard(mask_rook_attacks(square));
    // }

    U64 block = 0ULL;
    set_bit(block, b4);
    set_bit(block, d7);
    set_bit(block, d2);
    set_bit(block, f4);
    print_bitboard(rook_attacks_on_the_fly(d4, block));

}