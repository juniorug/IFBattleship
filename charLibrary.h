#ifndef charLibrary_h
#define charLibrary_h

#include "Arduino.h"

 //Space (Char 0x20)
const byte char_space[7] {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
//!
const byte char_exc[7] {B10000000,B10000000,B10000000,B10000000,B00000000,B00000000,B10000000};
//"
const byte char_aspasd[7] {B10100000,B10100000,B10100000,B00000000,B00000000,B00000000,B00000000};
//#
const byte char_tralha[7] {B01010000,B01010000,B11111000,B01010000,B11111000,B01010000,B01010000};
 //$
const byte char_dollar[7] {B00100000,B01111000,B10100000,B01110000,B00101000,B11110000,B00100000};
//%
const byte char_percent[7] {B11000000,B11001000,B00010000,B00100000,B01000000,B10011000,B00011000};
//&
const byte char_ecom[7] {B01100000,B10010000,B10100000,B01000000,B10101000,B10010000,B01101000};
//'
const byte char_apost[7] {B11000000,B01000000,B10000000,B00000000,B00000000,B00000000,B00000000};
//(
const byte char_abrep[7] {B00100000,B01000000,B10000000,B10000000,B10000000,B01000000,B00100000};
//)
const byte char_fechap[7] {B10000000,B01000000,B00100000,B00100000,B00100000,B01000000,B10000000};
//*
const byte char_asterisco[7] {B00000000,B00100000,B10101000,B01110000,B10101000,B00100000,B00000000};
 //+
const byte char_mais[7] {B00000000,B00100000,B00100000,B11111000,B00100000,B00100000,B00000000};
//,
const byte char_virgula[7] {B00000000,B00000000,B00000000,B00000000,B11000000,B01000000,B10000000};
//-
const byte char_dash[7] {B00000000,B00000000,B11111000,B00000000,B00000000,B00000000,B00000000};
//.
const byte char_ponto[7] {B00000000,B00000000,B00000000,B00000000,B00000000,B11000000,B11000000};
///
const byte char_barra[7] {B00000000,B00001000,B00010000,B00100000,B01000000,B10000000,B00000000};
//0
const byte char_zero[7] {B01110000,B10001000,B10011000,B10101000,B11001000,B10001000,B01110000};
//1
const byte char_1[7] {B01000000,B11000000,B01000000,B01000000,B01000000,B01000000,B11100000};
//2
const byte char_2[7] {B01110000,B10001000,B00001000,B00010000,B00100000,B01000000,B11111000};
//3
const byte char_3[7] {B11111000,B00010000,B00100000,B00010000,B00001000,B10001000,B01110000};
//4
const byte char_4[7] {B00010000,B00110000,B01010000,B10010000,B11111000,B00010000,B00010000};
 //5
const byte char_5[7] {B11111000,B10000000,B11110000,B00001000,B00001000,B10001000,B01110000};
//6
const byte char_6[7] {B00110000,B01000000,B10000000,B11110000,B10001000,B10001000,B01110000};
//7
const byte char_7[7] {B11111000,B10001000,B00001000,B00010000,B00100000,B00100000,B00100000};
//8
const byte char_8[7] {B01110000,B10001000,B10001000,B01110000,B10001000,B10001000,B01110000};
//9
const byte char_9[7] {B01110000,B10001000,B10001000,B01111000,B00001000,B00010000,B01100000};
//:
const byte char_doisp[7] {B00000000,B11000000,B11000000,B00000000,B11000000,B11000000,B00000000};
//;
const byte char_pontovirg[7] {B00000000,B11000000,B11000000,B00000000,B11000000,B01000000,B10000000};
//<
const byte char_menor[7] {B00010000,B00100000,B01000000,B10000000,B01000000,B00100000,B00010000};
//=
const byte char_igual[7] {B00000000,B00000000,B11111000,B00000000,B11111000,B00000000,B00000000};
//>
const byte char_maior[7] {B10000000,B01000000,B00100000,B00010000,B00100000,B01000000,B10000000};
//?
const byte char_inter[7] {B01110000,B10001000,B00001000,B00010000,B00100000,B00000000,B00100000};
//@
const byte char_arroba[7] {B01110000,B10001000,B00001000,B01101000,B10101000,B10101000,B01110000};
//A
const byte char_A[7] {B01110000,B10001000,B10001000,B10001000,B11111000,B10001000,B10001000};
//B
const byte char_B[7] {B11110000,B10001000,B10001000,B11110000,B10001000,B10001000,B11110000};
//C
const byte char_C[7] {B01110000,B10001000,B10000000,B10000000,B10000000,B10001000,B01110000};
//D
const byte char_D[7] {B11100000,B10010000,B10001000,B10001000,B10001000,B10010000,B11100000};
//E
const byte char_E[7] {B11111000,B10000000,B10000000,B11110000,B10000000,B10000000,B11111000};
//F
const byte char_F[7] {B11111000,B10000000,B10000000,B11110000,B10000000,B10000000,B10000000};
//G
const byte char_G[7] {B01110000,B10001000,B10000000,B10111000,B10001000,B10001000,B01111000};
//H
const byte char_H[7] {B10001000,B10001000,B10001000,B11111000,B10001000,B10001000,B10001000};
//I
const byte char_I[7] {B11100000,B01000000,B01000000,B01000000,B01000000,B01000000,B11100000};
//J
const byte char_J[7] {B00111000,B00010000,B00010000,B00010000,B00010000,B10010000,B01100000};
//K
const byte char_K[7] {B10001000,B10010000,B10100000,B11000000,B10100000,B10010000,B10001000};
 //L
const byte char_L[7] {B10000000,B10000000,B10000000,B10000000,B10000000,B10000000,B11111000};
//M
const byte char_M[7] {B10001000,B11011000,B10101000,B10101000,B10001000,B10001000,B10001000};
//N
const byte char_N[7] {B10001000,B10001000,B11001000,B10101000,B10011000,B10001000,B10001000};
 //O
const byte char_O[7] {B01110000,B10001000,B10001000,B10001000,B10001000,B10001000,B01110000};
//P
const byte char_P[7] {B11110000,B10001000,B10001000,B11110000,B10000000,B10000000,B10000000};
 //Q
const byte char_Q[7] {B01110000,B10001000,B10001000,B10001000,B10101000,B10010000,B01101000};
 //R
const byte char_R[7] {B11110000,B10001000,B10001000,B11110000,B10100000,B10010000,B10001000};
//S
const byte char_S[7] {B01111000,B10000000,B10000000,B01110000,B00001000,B00001000,B11110000};
//T
const byte char_T[7] {B11111000,B00100000,B00100000,B00100000,B00100000,B00100000,B00100000};
//U
const byte char_U[7] {B10001000,B10001000,B10001000,B10001000,B10001000,B10001000,B01110000};
//V
const byte char_V[7] {B10001000,B10001000,B10001000,B10001000,B10001000,B01010000,B00100000};
//W
const byte char_W[7] {B10001000,B10001000,B10001000,B10101000,B10101000,B10101000,B01010000};
//X
const byte char_X[7] {B10001000,B10001000,B01010000,B00100000,B01010000,B10001000,B10001000};
//Y
const byte char_Y[7] {B10001000,B10001000,B10001000,B01010000,B00100000,B00100000,B00100000};
//Z
const byte char_Z[7] {B11111000,B00001000,B00010000,B00100000,B01000000,B10000000,B11111000};
//[
const byte char_abrecolc[7] {B11100000,B10000000,B10000000,B10000000,B10000000,B10000000,B11100000};
//(Backward Slash)
const byte char_backslash[7] {B00000000,B10000000,B01000000,B00100000,B00010000,B00001000,B00000000};
//]
const byte char_fechacolc[7] {B11100000,B00100000,B00100000,B00100000,B00100000,B00100000,B11100000};
 //^
const byte char_chapeu[7] {B00100000,B01010000,B10001000,B00000000,B00000000,B00000000,B00000000};
//_
const byte char_underline[7] {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111000};
//`
const byte char_crase[7] {B10000000,B01000000,B00100000,B00000000,B00000000,B00000000,B00000000};
//a
const byte char_a[7] {B00000000,B00000000,B01110000,B00001000,B01111000,B10001000,B01111000};
//b
const byte char_b[7] {B10000000,B10000000,B10110000,B11001000,B10001000,B10001000,B11110000};
//c
const byte char_c[7] {B00000000,B00000000,B01110000,B10001000,B10000000,B10001000,B01110000};
//d
const byte char_d[7] {B00001000,B00001000,B01101000,B10011000,B10001000,B10001000,B01111000};
//e
const byte char_e[7] {B00000000,B00000000,B01110000,B10001000,B11111000,B10000000,B01110000};
//f
const byte char_f[7] {B00110000,B01001000,B01000000,B11100000,B01000000,B01000000,B01000000};
//g
const byte char_g[7] {B00000000,B01111000,B10001000,B10001000,B01111000,B00001000,B01110000};
//h
const byte char_h[7] {B10000000,B10000000,B10110000,B11001000,B10001000,B10001000,B10001000};
//i
const byte char_i[7] {B01000000,B00000000,B11000000,B01000000,B01000000,B01000000,B11100000};
//j
const byte char_j[7] {B00010000,B00000000,B00110000,B00010000,B00010000,B10010000,B01100000};
//k
const byte char_k[7] {B10000000,B10000000,B10010000,B10100000,B11000000,B10100000,B10010000};
//l
const byte char_l[7] {B11000000,B01000000,B01000000,B01000000,B01000000,B01000000,B11100000};
//m
const byte char_m[7] {B00000000,B00000000,B11010000,B10101000,B10101000,B10001000,B10001000};
//n
const byte char_n[7] {B00000000,B00000000,B10110000,B11001000,B10001000,B10001000,B10001000};
//o
const byte char_o[7] {B00000000,B00000000,B01110000,B10001000,B10001000,B10001000,B01110000};
//p
const byte char_p[7] {B00000000,B00000000,B11110000,B10001000,B11110000,B10000000,B10000000};
//q
const byte char_q[7] {B00000000,B00000000,B01101000,B10011000,B01111000,B00001000,B00001000};
//r
const byte char_r[7] {B00000000,B00000000,B10110000,B11001000,B10000000,B10000000,B10000000};
//s
const byte char_s[7] {B00000000,B00000000,B01110000,B10000000,B01110000,B00001000,B11110000};
//t
const byte char_t[7] {B01000000,B01000000,B11100000,B01000000,B01000000,B01001000,B00110000};
//u
const byte char_u[7] {B00000000,B00000000,B10001000,B10001000,B10001000,B10011000,B01101000};
 //v 
const byte char_v[7] {B00000000,B00000000,B10001000,B10001000,B10001000,B01010000,B00100000};
 //w
const byte char_w[7] {B00000000,B00000000,B10001000,B10101000,B10101000,B10101000,B01010000};
//x
const byte char_x[7] {B00000000,B00000000,B10001000,B01010000,B00100000,B01010000,B10001000};
//y
const byte char_y[7] {B00000000,B00000000,B10001000,B10001000,B01111000,B00001000,B01110000};
//z
const byte char_z[7] {B00000000,B00000000,B11111000,B00010000,B00100000,B01000000,B11111000};
//{
const byte char_abrechave[7] {B00100000,B01000000,B01000000,B10000000,B01000000,B01000000,B00100000};
//|
const byte char_pipe[7] {B10000000,B10000000,B10000000,B10000000,B10000000,B10000000,B10000000};
//}
const byte char_fechachave[7] {B10000000,B01000000,B01000000,B00100000,B01000000,B01000000,B10000000};
//~
const byte char_til[7] {B00000000,B00000000,B00000000,B01101000,B10010000,B00000000,B00000000};


const byte numbers[10][7] =  { {B01110000,B10001000,B10011000,B10101000,B11001000,B10001000,B01110000},
                            {B01000000,B11000000,B01000000,B01000000,B01000000,B01000000,B11100000},
                            {B01110000,B10001000,B00001000,B00010000,B00100000,B01000000,B11111000},
                            {B11111000,B00010000,B00100000,B00010000,B00001000,B10001000,B01110000},
                            {B00010000,B00110000,B01010000,B10010000,B11111000,B00010000,B00010000},
                            {B11111000,B10000000,B11110000,B00001000,B00001000,B10001000,B01110000},
                            {B00110000,B01000000,B10000000,B11110000,B10001000,B10001000,B01110000},
                            {B11111000,B10001000,B00001000,B00010000,B00100000,B00100000,B00100000},
                            {B01110000,B10001000,B10001000,B01110000,B10001000,B10001000,B01110000},
                            {B01110000,B10001000,B10001000,B01111000,B00001000,B00010000,B01100000}
                        };

#endif