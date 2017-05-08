/*
	This c file contains the set_minver() function used to
  set the values of the matrix to that of an invertible matrix.
	
	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License
	
 */

#include "minver_init.h"

void set_minver(mat_type minver_a[DIM][DIM]) {


  #if(DIM == 3)

  minver_a[0][0] = 1;
  minver_a[0][1] = 3;
  minver_a[0][2] = 2;
  minver_a[1][0] = 3;
  minver_a[1][1] = 3;
  minver_a[1][2] = 2;
  minver_a[2][0] = 1;
  minver_a[2][1] = 3;
  minver_a[2][2] = 1;

  #elif(DIM == 4)

  minver_a[0][0] = 1;
  minver_a[0][1] = 2;
  minver_a[0][2] = 3;
  minver_a[0][3] = 2;
  minver_a[1][0] = 1;
  minver_a[1][1] = 3;
  minver_a[1][2] = 1;
  minver_a[1][3] = 3;
  minver_a[2][0] = 3;
  minver_a[2][1] = 3;
  minver_a[2][2] = 2;
  minver_a[2][3] = 1;
  minver_a[3][0] = 3;
  minver_a[3][1] = 1;
  minver_a[3][2] = 4;
  minver_a[3][3] = 3;

  #elif(DIM == 16)

  minver_a[0][0] = 6;
  minver_a[0][1] = 16;
  minver_a[0][2] = 13;
  minver_a[0][3] = 1;
  minver_a[0][4] = 4;
  minver_a[0][5] = 10;
  minver_a[0][6] = 11;
  minver_a[0][7] = 7;
  minver_a[0][8] = 1;
  minver_a[0][9] = 9;
  minver_a[0][10] = 5;
  minver_a[0][11] = 7;
  minver_a[0][12] = 10;
  minver_a[0][13] = 2;
  minver_a[0][14] = 16;
  minver_a[0][15] = 2;
  minver_a[1][0] = 6;
  minver_a[1][1] = 1;
  minver_a[1][2] = 13;
  minver_a[1][3] = 13;
  minver_a[1][4] = 6;
  minver_a[1][5] = 5;
  minver_a[1][6] = 3;
  minver_a[1][7] = 15;
  minver_a[1][8] = 13;
  minver_a[1][9] = 11;
  minver_a[1][10] = 12;
  minver_a[1][11] = 5;
  minver_a[1][12] = 7;
  minver_a[1][13] = 14;
  minver_a[1][14] = 10;
  minver_a[1][15] = 7;
  minver_a[2][0] = 3;
  minver_a[2][1] = 1;
  minver_a[2][2] = 12;
  minver_a[2][3] = 14;
  minver_a[2][4] = 3;
  minver_a[2][5] = 10;
  minver_a[2][6] = 7;
  minver_a[2][7] = 10;
  minver_a[2][8] = 7;
  minver_a[2][9] = 1;
  minver_a[2][10] = 11;
  minver_a[2][11] = 8;
  minver_a[2][12] = 3;
  minver_a[2][13] = 7;
  minver_a[2][14] = 10;
  minver_a[2][15] = 15;
  minver_a[3][0] = 11;
  minver_a[3][1] = 5;
  minver_a[3][2] = 14;
  minver_a[3][3] = 9;
  minver_a[3][4] = 11;
  minver_a[3][5] = 5;
  minver_a[3][6] = 8;
  minver_a[3][7] = 13;
  minver_a[3][8] = 9;
  minver_a[3][9] = 10;
  minver_a[3][10] = 6;
  minver_a[3][11] = 16;
  minver_a[3][12] = 14;
  minver_a[3][13] = 6;
  minver_a[3][14] = 12;
  minver_a[3][15] = 12;
  minver_a[4][0] = 9;
  minver_a[4][1] = 2;
  minver_a[4][2] = 1;
  minver_a[4][3] = 12;
  minver_a[4][4] = 16;
  minver_a[4][5] = 14;
  minver_a[4][6] = 4;
  minver_a[4][7] = 5;
  minver_a[4][8] = 2;
  minver_a[4][9] = 15;
  minver_a[4][10] = 7;
  minver_a[4][11] = 14;
  minver_a[4][12] = 15;
  minver_a[4][13] = 15;
  minver_a[4][14] = 3;
  minver_a[4][15] = 15;
  minver_a[5][0] = 12;
  minver_a[5][1] = 3;
  minver_a[5][2] = 16;
  minver_a[5][3] = 9;
  minver_a[5][4] = 12;
  minver_a[5][5] = 14;
  minver_a[5][6] = 7;
  minver_a[5][7] = 10;
  minver_a[5][8] = 3;
  minver_a[5][9] = 8;
  minver_a[5][10] = 14;
  minver_a[5][11] = 10;
  minver_a[5][12] = 9;
  minver_a[5][13] = 6;
  minver_a[5][14] = 9;
  minver_a[5][15] = 11;
  minver_a[6][0] = 15;
  minver_a[6][1] = 9;
  minver_a[6][2] = 3;
  minver_a[6][3] = 6;
  minver_a[6][4] = 9;
  minver_a[6][5] = 16;
  minver_a[6][6] = 1;
  minver_a[6][7] = 11;
  minver_a[6][8] = 14;
  minver_a[6][9] = 9;
  minver_a[6][10] = 15;
  minver_a[6][11] = 14;
  minver_a[6][12] = 11;
  minver_a[6][13] = 5;
  minver_a[6][14] = 3;
  minver_a[6][15] = 6;
  minver_a[7][0] = 14;
  minver_a[7][1] = 6;
  minver_a[7][2] = 2;
  minver_a[7][3] = 2;
  minver_a[7][4] = 6;
  minver_a[7][5] = 10;
  minver_a[7][6] = 14;
  minver_a[7][7] = 10;
  minver_a[7][8] = 1;
  minver_a[7][9] = 3;
  minver_a[7][10] = 2;
  minver_a[7][11] = 1;
  minver_a[7][12] = 4;
  minver_a[7][13] = 8;
  minver_a[7][14] = 11;
  minver_a[7][15] = 3;
  minver_a[8][0] = 6;
  minver_a[8][1] = 4;
  minver_a[8][2] = 14;
  minver_a[8][3] = 16;
  minver_a[8][4] = 8;
  minver_a[8][5] = 16;
  minver_a[8][6] = 10;
  minver_a[8][7] = 1;
  minver_a[8][8] = 11;
  minver_a[8][9] = 9;
  minver_a[8][10] = 1;
  minver_a[8][11] = 14;
  minver_a[8][12] = 12;
  minver_a[8][13] = 4;
  minver_a[8][14] = 14;
  minver_a[8][15] = 4;
  minver_a[9][0] = 13;
  minver_a[9][1] = 14;
  minver_a[9][2] = 13;
  minver_a[9][3] = 3;
  minver_a[9][4] = 6;
  minver_a[9][5] = 2;
  minver_a[9][6] = 15;
  minver_a[9][7] = 9;
  minver_a[9][8] = 11;
  minver_a[9][9] = 2;
  minver_a[9][10] = 9;
  minver_a[9][11] = 11;
  minver_a[9][12] = 7;
  minver_a[9][13] = 13;
  minver_a[9][14] = 6;
  minver_a[9][15] = 7;
  minver_a[10][0] = 5;
  minver_a[10][1] = 5;
  minver_a[10][2] = 15;
  minver_a[10][3] = 11;
  minver_a[10][4] = 14;
  minver_a[10][5] = 1;
  minver_a[10][6] = 15;
  minver_a[10][7] = 3;
  minver_a[10][8] = 12;
  minver_a[10][9] = 15;
  minver_a[10][10] = 11;
  minver_a[10][11] = 15;
  minver_a[10][12] = 2;
  minver_a[10][13] = 10;
  minver_a[10][14] = 1;
  minver_a[10][15] = 15;
  minver_a[11][0] = 13;
  minver_a[11][1] = 12;
  minver_a[11][2] = 11;
  minver_a[11][3] = 13;
  minver_a[11][4] = 13;
  minver_a[11][5] = 7;
  minver_a[11][6] = 15;
  minver_a[11][7] = 8;
  minver_a[11][8] = 5;
  minver_a[11][9] = 1;
  minver_a[11][10] = 6;
  minver_a[11][11] = 5;
  minver_a[11][12] = 3;
  minver_a[11][13] = 4;
  minver_a[11][14] = 3;
  minver_a[11][15] = 6;
  minver_a[12][0] = 3;
  minver_a[12][1] = 8;
  minver_a[12][2] = 2;
  minver_a[12][3] = 6;
  minver_a[12][4] = 7;
  minver_a[12][5] = 11;
  minver_a[12][6] = 15;
  minver_a[12][7] = 7;
  minver_a[12][8] = 9;
  minver_a[12][9] = 13;
  minver_a[12][10] = 12;
  minver_a[12][11] = 1;
  minver_a[12][12] = 11;
  minver_a[12][13] = 10;
  minver_a[12][14] = 3;
  minver_a[12][15] = 6;
  minver_a[13][0] = 10;
  minver_a[13][1] = 4;
  minver_a[13][2] = 7;
  minver_a[13][3] = 11;
  minver_a[13][4] = 1;
  minver_a[13][5] = 11;
  minver_a[13][6] = 12;
  minver_a[13][7] = 11;
  minver_a[13][8] = 13;
  minver_a[13][9] = 14;
  minver_a[13][10] = 8;
  minver_a[13][11] = 1;
  minver_a[13][12] = 2;
  minver_a[13][13] = 1;
  minver_a[13][14] = 4;
  minver_a[13][15] = 2;
  minver_a[14][0] = 10;
  minver_a[14][1] = 13;
  minver_a[14][2] = 3;
  minver_a[14][3] = 8;
  minver_a[14][4] = 8;
  minver_a[14][5] = 11;
  minver_a[14][6] = 8;
  minver_a[14][7] = 10;
  minver_a[14][8] = 2;
  minver_a[14][9] = 5;
  minver_a[14][10] = 5;
  minver_a[14][11] = 11;
  minver_a[14][12] = 8;
  minver_a[14][13] = 7;
  minver_a[14][14] = 9;
  minver_a[14][15] = 5;
  minver_a[15][0] = 2;
  minver_a[15][1] = 11;
  minver_a[15][2] = 6;
  minver_a[15][3] = 2;
  minver_a[15][4] = 12;
  minver_a[15][5] = 2;
  minver_a[15][6] = 5;
  minver_a[15][7] = 5;
  minver_a[15][8] = 5;
  minver_a[15][9] = 1;
  minver_a[15][10] = 12;
  minver_a[15][11] = 9;
  minver_a[15][12] = 5;
  minver_a[15][13] = 1;
  minver_a[15][14] = 15;
  minver_a[15][15] = 9;


  #elif(DIM == 32)

  minver_a[0][0] = 21;
  minver_a[0][1] = 27;
  minver_a[0][2] = 1;
  minver_a[0][3] = 16;
  minver_a[0][4] = 24;
  minver_a[0][5] = 7;
  minver_a[0][6] = 30;
  minver_a[0][7] = 30;
  minver_a[0][8] = 17;
  minver_a[0][9] = 15;
  minver_a[0][10] = 26;
  minver_a[0][11] = 10;
  minver_a[0][12] = 26;
  minver_a[0][13] = 15;
  minver_a[0][14] = 12;
  minver_a[0][15] = 4;
  minver_a[0][16] = 18;
  minver_a[0][17] = 14;
  minver_a[0][18] = 8;
  minver_a[0][19] = 7;
  minver_a[0][20] = 17;
  minver_a[0][21] = 13;
  minver_a[0][22] = 16;
  minver_a[0][23] = 30;
  minver_a[0][24] = 19;
  minver_a[0][25] = 29;
  minver_a[0][26] = 7;
  minver_a[0][27] = 4;
  minver_a[0][28] = 31;
  minver_a[0][29] = 3;
  minver_a[0][30] = 29;
  minver_a[0][31] = 10;
  minver_a[1][0] = 3;
  minver_a[1][1] = 6;
  minver_a[1][2] = 16;
  minver_a[1][3] = 10;
  minver_a[1][4] = 14;
  minver_a[1][5] = 12;
  minver_a[1][6] = 31;
  minver_a[1][7] = 16;
  minver_a[1][8] = 30;
  minver_a[1][9] = 31;
  minver_a[1][10] = 6;
  minver_a[1][11] = 11;
  minver_a[1][12] = 27;
  minver_a[1][13] = 13;
  minver_a[1][14] = 19;
  minver_a[1][15] = 13;
  minver_a[1][16] = 28;
  minver_a[1][17] = 30;
  minver_a[1][18] = 20;
  minver_a[1][19] = 32;
  minver_a[1][20] = 17;
  minver_a[1][21] = 29;
  minver_a[1][22] = 22;
  minver_a[1][23] = 22;
  minver_a[1][24] = 8;
  minver_a[1][25] = 22;
  minver_a[1][26] = 25;
  minver_a[1][27] = 11;
  minver_a[1][28] = 26;
  minver_a[1][29] = 27;
  minver_a[1][30] = 8;
  minver_a[1][31] = 12;
  minver_a[2][0] = 23;
  minver_a[2][1] = 12;
  minver_a[2][2] = 13;
  minver_a[2][3] = 28;
  minver_a[2][4] = 19;
  minver_a[2][5] = 29;
  minver_a[2][6] = 19;
  minver_a[2][7] = 3;
  minver_a[2][8] = 11;
  minver_a[2][9] = 30;
  minver_a[2][10] = 30;
  minver_a[2][11] = 31;
  minver_a[2][12] = 2;
  minver_a[2][13] = 7;
  minver_a[2][14] = 3;
  minver_a[2][15] = 8;
  minver_a[2][16] = 32;
  minver_a[2][17] = 26;
  minver_a[2][18] = 9;
  minver_a[2][19] = 4;
  minver_a[2][20] = 8;
  minver_a[2][21] = 28;
  minver_a[2][22] = 12;
  minver_a[2][23] = 31;
  minver_a[2][24] = 18;
  minver_a[2][25] = 22;
  minver_a[2][26] = 18;
  minver_a[2][27] = 22;
  minver_a[2][28] = 30;
  minver_a[2][29] = 17;
  minver_a[2][30] = 27;
  minver_a[2][31] = 15;
  minver_a[3][0] = 17;
  minver_a[3][1] = 16;
  minver_a[3][2] = 32;
  minver_a[3][3] = 6;
  minver_a[3][4] = 32;
  minver_a[3][5] = 22;
  minver_a[3][6] = 13;
  minver_a[3][7] = 13;
  minver_a[3][8] = 3;
  minver_a[3][9] = 22;
  minver_a[3][10] = 3;
  minver_a[3][11] = 2;
  minver_a[3][12] = 13;
  minver_a[3][13] = 30;
  minver_a[3][14] = 24;
  minver_a[3][15] = 26;
  minver_a[3][16] = 16;
  minver_a[3][17] = 23;
  minver_a[3][18] = 22;
  minver_a[3][19] = 15;
  minver_a[3][20] = 18;
  minver_a[3][21] = 25;
  minver_a[3][22] = 10;
  minver_a[3][23] = 20;
  minver_a[3][24] = 10;
  minver_a[3][25] = 21;
  minver_a[3][26] = 29;
  minver_a[3][27] = 29;
  minver_a[3][28] = 3;
  minver_a[3][29] = 20;
  minver_a[3][30] = 27;
  minver_a[3][31] = 18;
  minver_a[4][0] = 17;
  minver_a[4][1] = 6;
  minver_a[4][2] = 9;
  minver_a[4][3] = 5;
  minver_a[4][4] = 12;
  minver_a[4][5] = 31;
  minver_a[4][6] = 13;
  minver_a[4][7] = 20;
  minver_a[4][8] = 26;
  minver_a[4][9] = 26;
  minver_a[4][10] = 20;
  minver_a[4][11] = 5;
  minver_a[4][12] = 5;
  minver_a[4][13] = 20;
  minver_a[4][14] = 20;
  minver_a[4][15] = 32;
  minver_a[4][16] = 23;
  minver_a[4][17] = 15;
  minver_a[4][18] = 31;
  minver_a[4][19] = 21;
  minver_a[4][20] = 20;
  minver_a[4][21] = 28;
  minver_a[4][22] = 4;
  minver_a[4][23] = 9;
  minver_a[4][24] = 17;
  minver_a[4][25] = 8;
  minver_a[4][26] = 25;
  minver_a[4][27] = 2;
  minver_a[4][28] = 15;
  minver_a[4][29] = 17;
  minver_a[4][30] = 10;
  minver_a[4][31] = 6;
  minver_a[5][0] = 15;
  minver_a[5][1] = 6;
  minver_a[5][2] = 5;
  minver_a[5][3] = 30;
  minver_a[5][4] = 14;
  minver_a[5][5] = 17;
  minver_a[5][6] = 11;
  minver_a[5][7] = 25;
  minver_a[5][8] = 29;
  minver_a[5][9] = 25;
  minver_a[5][10] = 31;
  minver_a[5][11] = 30;
  minver_a[5][12] = 27;
  minver_a[5][13] = 6;
  minver_a[5][14] = 17;
  minver_a[5][15] = 18;
  minver_a[5][16] = 1;
  minver_a[5][17] = 31;
  minver_a[5][18] = 9;
  minver_a[5][19] = 5;
  minver_a[5][20] = 18;
  minver_a[5][21] = 13;
  minver_a[5][22] = 18;
  minver_a[5][23] = 5;
  minver_a[5][24] = 1;
  minver_a[5][25] = 31;
  minver_a[5][26] = 17;
  minver_a[5][27] = 7;
  minver_a[5][28] = 27;
  minver_a[5][29] = 2;
  minver_a[5][30] = 5;
  minver_a[5][31] = 29;
  minver_a[6][0] = 21;
  minver_a[6][1] = 9;
  minver_a[6][2] = 27;
  minver_a[6][3] = 27;
  minver_a[6][4] = 16;
  minver_a[6][5] = 14;
  minver_a[6][6] = 19;
  minver_a[6][7] = 10;
  minver_a[6][8] = 32;
  minver_a[6][9] = 8;
  minver_a[6][10] = 5;
  minver_a[6][11] = 24;
  minver_a[6][12] = 25;
  minver_a[6][13] = 9;
  minver_a[6][14] = 25;
  minver_a[6][15] = 11;
  minver_a[6][16] = 31;
  minver_a[6][17] = 12;
  minver_a[6][18] = 26;
  minver_a[6][19] = 25;
  minver_a[6][20] = 32;
  minver_a[6][21] = 5;
  minver_a[6][22] = 4;
  minver_a[6][23] = 19;
  minver_a[6][24] = 6;
  minver_a[6][25] = 15;
  minver_a[6][26] = 24;
  minver_a[6][27] = 15;
  minver_a[6][28] = 13;
  minver_a[6][29] = 21;
  minver_a[6][30] = 17;
  minver_a[6][31] = 21;
  minver_a[7][0] = 14;
  minver_a[7][1] = 10;
  minver_a[7][2] = 5;
  minver_a[7][3] = 4;
  minver_a[7][4] = 22;
  minver_a[7][5] = 3;
  minver_a[7][6] = 5;
  minver_a[7][7] = 4;
  minver_a[7][8] = 10;
  minver_a[7][9] = 16;
  minver_a[7][10] = 7;
  minver_a[7][11] = 22;
  minver_a[7][12] = 10;
  minver_a[7][13] = 24;
  minver_a[7][14] = 23;
  minver_a[7][15] = 18;
  minver_a[7][16] = 29;
  minver_a[7][17] = 30;
  minver_a[7][18] = 31;
  minver_a[7][19] = 19;
  minver_a[7][20] = 10;
  minver_a[7][21] = 6;
  minver_a[7][22] = 8;
  minver_a[7][23] = 4;
  minver_a[7][24] = 22;
  minver_a[7][25] = 3;
  minver_a[7][26] = 7;
  minver_a[7][27] = 10;
  minver_a[7][28] = 26;
  minver_a[7][29] = 5;
  minver_a[7][30] = 5;
  minver_a[7][31] = 20;
  minver_a[8][0] = 11;
  minver_a[8][1] = 28;
  minver_a[8][2] = 12;
  minver_a[8][3] = 15;
  minver_a[8][4] = 13;
  minver_a[8][5] = 11;
  minver_a[8][6] = 1;
  minver_a[8][7] = 18;
  minver_a[8][8] = 18;
  minver_a[8][9] = 32;
  minver_a[8][10] = 18;
  minver_a[8][11] = 25;
  minver_a[8][12] = 29;
  minver_a[8][13] = 21;
  minver_a[8][14] = 11;
  minver_a[8][15] = 22;
  minver_a[8][16] = 32;
  minver_a[8][17] = 30;
  minver_a[8][18] = 9;
  minver_a[8][19] = 12;
  minver_a[8][20] = 8;
  minver_a[8][21] = 15;
  minver_a[8][22] = 11;
  minver_a[8][23] = 5;
  minver_a[8][24] = 16;
  minver_a[8][25] = 5;
  minver_a[8][26] = 20;
  minver_a[8][27] = 17;
  minver_a[8][28] = 19;
  minver_a[8][29] = 4;
  minver_a[8][30] = 6;
  minver_a[8][31] = 9;
  minver_a[9][0] = 20;
  minver_a[9][1] = 18;
  minver_a[9][2] = 9;
  minver_a[9][3] = 3;
  minver_a[9][4] = 8;
  minver_a[9][5] = 16;
  minver_a[9][6] = 18;
  minver_a[9][7] = 25;
  minver_a[9][8] = 27;
  minver_a[9][9] = 12;
  minver_a[9][10] = 24;
  minver_a[9][11] = 2;
  minver_a[9][12] = 28;
  minver_a[9][13] = 31;
  minver_a[9][14] = 18;
  minver_a[9][15] = 14;
  minver_a[9][16] = 23;
  minver_a[9][17] = 9;
  minver_a[9][18] = 1;
  minver_a[9][19] = 25;
  minver_a[9][20] = 12;
  minver_a[9][21] = 11;
  minver_a[9][22] = 24;
  minver_a[9][23] = 12;
  minver_a[9][24] = 20;
  minver_a[9][25] = 9;
  minver_a[9][26] = 17;
  minver_a[9][27] = 3;
  minver_a[9][28] = 4;
  minver_a[9][29] = 12;
  minver_a[9][30] = 13;
  minver_a[9][31] = 4;
  minver_a[10][0] = 10;
  minver_a[10][1] = 18;
  minver_a[10][2] = 23;
  minver_a[10][3] = 18;
  minver_a[10][4] = 27;
  minver_a[10][5] = 19;
  minver_a[10][6] = 12;
  minver_a[10][7] = 31;
  minver_a[10][8] = 27;
  minver_a[10][9] = 5;
  minver_a[10][10] = 7;
  minver_a[10][11] = 15;
  minver_a[10][12] = 24;
  minver_a[10][13] = 12;
  minver_a[10][14] = 2;
  minver_a[10][15] = 25;
  minver_a[10][16] = 4;
  minver_a[10][17] = 32;
  minver_a[10][18] = 11;
  minver_a[10][19] = 28;
  minver_a[10][20] = 8;
  minver_a[10][21] = 7;
  minver_a[10][22] = 11;
  minver_a[10][23] = 16;
  minver_a[10][24] = 20;
  minver_a[10][25] = 25;
  minver_a[10][26] = 6;
  minver_a[10][27] = 32;
  minver_a[10][28] = 21;
  minver_a[10][29] = 3;
  minver_a[10][30] = 24;
  minver_a[10][31] = 24;
  minver_a[11][0] = 20;
  minver_a[11][1] = 19;
  minver_a[11][2] = 2;
  minver_a[11][3] = 12;
  minver_a[11][4] = 23;
  minver_a[11][5] = 8;
  minver_a[11][6] = 9;
  minver_a[11][7] = 15;
  minver_a[11][8] = 4;
  minver_a[11][9] = 3;
  minver_a[11][10] = 10;
  minver_a[11][11] = 1;
  minver_a[11][12] = 11;
  minver_a[11][13] = 13;
  minver_a[11][14] = 13;
  minver_a[11][15] = 27;
  minver_a[11][16] = 13;
  minver_a[11][17] = 1;
  minver_a[11][18] = 31;
  minver_a[11][19] = 15;
  minver_a[11][20] = 5;
  minver_a[11][21] = 10;
  minver_a[11][22] = 25;
  minver_a[11][23] = 25;
  minver_a[11][24] = 19;
  minver_a[11][25] = 18;
  minver_a[11][26] = 25;
  minver_a[11][27] = 7;
  minver_a[11][28] = 10;
  minver_a[11][29] = 27;
  minver_a[11][30] = 7;
  minver_a[11][31] = 9;
  minver_a[12][0] = 31;
  minver_a[12][1] = 24;
  minver_a[12][2] = 27;
  minver_a[12][3] = 15;
  minver_a[12][4] = 18;
  minver_a[12][5] = 28;
  minver_a[12][6] = 26;
  minver_a[12][7] = 18;
  minver_a[12][8] = 18;
  minver_a[12][9] = 14;
  minver_a[12][10] = 20;
  minver_a[12][11] = 13;
  minver_a[12][12] = 3;
  minver_a[12][13] = 12;
  minver_a[12][14] = 27;
  minver_a[12][15] = 5;
  minver_a[12][16] = 17;
  minver_a[12][17] = 7;
  minver_a[12][18] = 15;
  minver_a[12][19] = 28;
  minver_a[12][20] = 14;
  minver_a[12][21] = 3;
  minver_a[12][22] = 25;
  minver_a[12][23] = 27;
  minver_a[12][24] = 27;
  minver_a[12][25] = 32;
  minver_a[12][26] = 30;
  minver_a[12][27] = 28;
  minver_a[12][28] = 4;
  minver_a[12][29] = 18;
  minver_a[12][30] = 1;
  minver_a[12][31] = 13;
  minver_a[13][0] = 31;
  minver_a[13][1] = 10;
  minver_a[13][2] = 20;
  minver_a[13][3] = 12;
  minver_a[13][4] = 14;
  minver_a[13][5] = 12;
  minver_a[13][6] = 30;
  minver_a[13][7] = 17;
  minver_a[13][8] = 23;
  minver_a[13][9] = 22;
  minver_a[13][10] = 17;
  minver_a[13][11] = 21;
  minver_a[13][12] = 25;
  minver_a[13][13] = 2;
  minver_a[13][14] = 23;
  minver_a[13][15] = 4;
  minver_a[13][16] = 5;
  minver_a[13][17] = 26;
  minver_a[13][18] = 26;
  minver_a[13][19] = 20;
  minver_a[13][20] = 22;
  minver_a[13][21] = 2;
  minver_a[13][22] = 10;
  minver_a[13][23] = 3;
  minver_a[13][24] = 22;
  minver_a[13][25] = 6;
  minver_a[13][26] = 22;
  minver_a[13][27] = 2;
  minver_a[13][28] = 24;
  minver_a[13][29] = 11;
  minver_a[13][30] = 23;
  minver_a[13][31] = 4;
  minver_a[14][0] = 9;
  minver_a[14][1] = 26;
  minver_a[14][2] = 16;
  minver_a[14][3] = 9;
  minver_a[14][4] = 8;
  minver_a[14][5] = 31;
  minver_a[14][6] = 18;
  minver_a[14][7] = 32;
  minver_a[14][8] = 29;
  minver_a[14][9] = 17;
  minver_a[14][10] = 29;
  minver_a[14][11] = 19;
  minver_a[14][12] = 3;
  minver_a[14][13] = 23;
  minver_a[14][14] = 30;
  minver_a[14][15] = 27;
  minver_a[14][16] = 25;
  minver_a[14][17] = 7;
  minver_a[14][18] = 8;
  minver_a[14][19] = 29;
  minver_a[14][20] = 25;
  minver_a[14][21] = 11;
  minver_a[14][22] = 20;
  minver_a[14][23] = 24;
  minver_a[14][24] = 27;
  minver_a[14][25] = 6;
  minver_a[14][26] = 27;
  minver_a[14][27] = 13;
  minver_a[14][28] = 22;
  minver_a[14][29] = 25;
  minver_a[14][30] = 14;
  minver_a[14][31] = 31;
  minver_a[15][0] = 23;
  minver_a[15][1] = 8;
  minver_a[15][2] = 8;
  minver_a[15][3] = 9;
  minver_a[15][4] = 18;
  minver_a[15][5] = 10;
  minver_a[15][6] = 25;
  minver_a[15][7] = 13;
  minver_a[15][8] = 15;
  minver_a[15][9] = 2;
  minver_a[15][10] = 29;
  minver_a[15][11] = 12;
  minver_a[15][12] = 8;
  minver_a[15][13] = 17;
  minver_a[15][14] = 3;
  minver_a[15][15] = 7;
  minver_a[15][16] = 10;
  minver_a[15][17] = 6;
  minver_a[15][18] = 6;
  minver_a[15][19] = 9;
  minver_a[15][20] = 12;
  minver_a[15][21] = 10;
  minver_a[15][22] = 12;
  minver_a[15][23] = 30;
  minver_a[15][24] = 14;
  minver_a[15][25] = 11;
  minver_a[15][26] = 30;
  minver_a[15][27] = 14;
  minver_a[15][28] = 14;
  minver_a[15][29] = 20;
  minver_a[15][30] = 17;
  minver_a[15][31] = 5;
  minver_a[16][0] = 9;
  minver_a[16][1] = 1;
  minver_a[16][2] = 21;
  minver_a[16][3] = 23;
  minver_a[16][4] = 10;
  minver_a[16][5] = 32;
  minver_a[16][6] = 8;
  minver_a[16][7] = 26;
  minver_a[16][8] = 29;
  minver_a[16][9] = 9;
  minver_a[16][10] = 29;
  minver_a[16][11] = 20;
  minver_a[16][12] = 25;
  minver_a[16][13] = 32;
  minver_a[16][14] = 21;
  minver_a[16][15] = 11;
  minver_a[16][16] = 12;
  minver_a[16][17] = 28;
  minver_a[16][18] = 22;
  minver_a[16][19] = 25;
  minver_a[16][20] = 26;
  minver_a[16][21] = 1;
  minver_a[16][22] = 16;
  minver_a[16][23] = 2;
  minver_a[16][24] = 28;
  minver_a[16][25] = 31;
  minver_a[16][26] = 30;
  minver_a[16][27] = 23;
  minver_a[16][28] = 13;
  minver_a[16][29] = 30;
  minver_a[16][30] = 28;
  minver_a[16][31] = 5;
  minver_a[17][0] = 3;
  minver_a[17][1] = 16;
  minver_a[17][2] = 23;
  minver_a[17][3] = 31;
  minver_a[17][4] = 20;
  minver_a[17][5] = 15;
  minver_a[17][6] = 21;
  minver_a[17][7] = 14;
  minver_a[17][8] = 4;
  minver_a[17][9] = 16;
  minver_a[17][10] = 22;
  minver_a[17][11] = 29;
  minver_a[17][12] = 22;
  minver_a[17][13] = 12;
  minver_a[17][14] = 1;
  minver_a[17][15] = 23;
  minver_a[17][16] = 13;
  minver_a[17][17] = 31;
  minver_a[17][18] = 16;
  minver_a[17][19] = 15;
  minver_a[17][20] = 27;
  minver_a[17][21] = 24;
  minver_a[17][22] = 21;
  minver_a[17][23] = 32;
  minver_a[17][24] = 25;
  minver_a[17][25] = 20;
  minver_a[17][26] = 3;
  minver_a[17][27] = 3;
  minver_a[17][28] = 4;
  minver_a[17][29] = 3;
  minver_a[17][30] = 27;
  minver_a[17][31] = 29;
  minver_a[18][0] = 10;
  minver_a[18][1] = 3;
  minver_a[18][2] = 18;
  minver_a[18][3] = 3;
  minver_a[18][4] = 20;
  minver_a[18][5] = 18;
  minver_a[18][6] = 29;
  minver_a[18][7] = 10;
  minver_a[18][8] = 10;
  minver_a[18][9] = 9;
  minver_a[18][10] = 6;
  minver_a[18][11] = 30;
  minver_a[18][12] = 25;
  minver_a[18][13] = 22;
  minver_a[18][14] = 8;
  minver_a[18][15] = 28;
  minver_a[18][16] = 24;
  minver_a[18][17] = 5;
  minver_a[18][18] = 27;
  minver_a[18][19] = 21;
  minver_a[18][20] = 14;
  minver_a[18][21] = 17;
  minver_a[18][22] = 28;
  minver_a[18][23] = 10;
  minver_a[18][24] = 21;
  minver_a[18][25] = 26;
  minver_a[18][26] = 24;
  minver_a[18][27] = 32;
  minver_a[18][28] = 8;
  minver_a[18][29] = 1;
  minver_a[18][30] = 20;
  minver_a[18][31] = 16;
  minver_a[19][0] = 31;
  minver_a[19][1] = 17;
  minver_a[19][2] = 18;
  minver_a[19][3] = 16;
  minver_a[19][4] = 15;
  minver_a[19][5] = 15;
  minver_a[19][6] = 29;
  minver_a[19][7] = 7;
  minver_a[19][8] = 8;
  minver_a[19][9] = 17;
  minver_a[19][10] = 2;
  minver_a[19][11] = 4;
  minver_a[19][12] = 12;
  minver_a[19][13] = 3;
  minver_a[19][14] = 15;
  minver_a[19][15] = 24;
  minver_a[19][16] = 15;
  minver_a[19][17] = 27;
  minver_a[19][18] = 4;
  minver_a[19][19] = 16;
  minver_a[19][20] = 1;
  minver_a[19][21] = 27;
  minver_a[19][22] = 7;
  minver_a[19][23] = 11;
  minver_a[19][24] = 25;
  minver_a[19][25] = 11;
  minver_a[19][26] = 14;
  minver_a[19][27] = 12;
  minver_a[19][28] = 15;
  minver_a[19][29] = 29;
  minver_a[19][30] = 30;
  minver_a[19][31] = 19;
  minver_a[20][0] = 21;
  minver_a[20][1] = 31;
  minver_a[20][2] = 15;
  minver_a[20][3] = 26;
  minver_a[20][4] = 8;
  minver_a[20][5] = 2;
  minver_a[20][6] = 4;
  minver_a[20][7] = 13;
  minver_a[20][8] = 6;
  minver_a[20][9] = 23;
  minver_a[20][10] = 19;
  minver_a[20][11] = 20;
  minver_a[20][12] = 29;
  minver_a[20][13] = 17;
  minver_a[20][14] = 4;
  minver_a[20][15] = 13;
  minver_a[20][16] = 5;
  minver_a[20][17] = 21;
  minver_a[20][18] = 18;
  minver_a[20][19] = 28;
  minver_a[20][20] = 26;
  minver_a[20][21] = 22;
  minver_a[20][22] = 29;
  minver_a[20][23] = 7;
  minver_a[20][24] = 9;
  minver_a[20][25] = 4;
  minver_a[20][26] = 21;
  minver_a[20][27] = 14;
  minver_a[20][28] = 22;
  minver_a[20][29] = 19;
  minver_a[20][30] = 29;
  minver_a[20][31] = 13;
  minver_a[21][0] = 23;
  minver_a[21][1] = 10;
  minver_a[21][2] = 14;
  minver_a[21][3] = 25;
  minver_a[21][4] = 3;
  minver_a[21][5] = 5;
  minver_a[21][6] = 29;
  minver_a[21][7] = 15;
  minver_a[21][8] = 8;
  minver_a[21][9] = 10;
  minver_a[21][10] = 6;
  minver_a[21][11] = 28;
  minver_a[21][12] = 10;
  minver_a[21][13] = 13;
  minver_a[21][14] = 13;
  minver_a[21][15] = 9;
  minver_a[21][16] = 6;
  minver_a[21][17] = 20;
  minver_a[21][18] = 20;
  minver_a[21][19] = 15;
  minver_a[21][20] = 21;
  minver_a[21][21] = 30;
  minver_a[21][22] = 2;
  minver_a[21][23] = 32;
  minver_a[21][24] = 27;
  minver_a[21][25] = 27;
  minver_a[21][26] = 19;
  minver_a[21][27] = 28;
  minver_a[21][28] = 18;
  minver_a[21][29] = 27;
  minver_a[21][30] = 11;
  minver_a[21][31] = 3;
  minver_a[22][0] = 22;
  minver_a[22][1] = 19;
  minver_a[22][2] = 5;
  minver_a[22][3] = 14;
  minver_a[22][4] = 3;
  minver_a[22][5] = 17;
  minver_a[22][6] = 13;
  minver_a[22][7] = 20;
  minver_a[22][8] = 30;
  minver_a[22][9] = 6;
  minver_a[22][10] = 4;
  minver_a[22][11] = 7;
  minver_a[22][12] = 27;
  minver_a[22][13] = 12;
  minver_a[22][14] = 3;
  minver_a[22][15] = 24;
  minver_a[22][16] = 11;
  minver_a[22][17] = 7;
  minver_a[22][18] = 2;
  minver_a[22][19] = 7;
  minver_a[22][20] = 7;
  minver_a[22][21] = 21;
  minver_a[22][22] = 24;
  minver_a[22][23] = 18;
  minver_a[22][24] = 24;
  minver_a[22][25] = 30;
  minver_a[22][26] = 4;
  minver_a[22][27] = 1;
  minver_a[22][28] = 31;
  minver_a[22][29] = 15;
  minver_a[22][30] = 30;
  minver_a[22][31] = 18;
  minver_a[23][0] = 26;
  minver_a[23][1] = 24;
  minver_a[23][2] = 17;
  minver_a[23][3] = 8;
  minver_a[23][4] = 20;
  minver_a[23][5] = 14;
  minver_a[23][6] = 25;
  minver_a[23][7] = 32;
  minver_a[23][8] = 23;
  minver_a[23][9] = 26;
  minver_a[23][10] = 22;
  minver_a[23][11] = 19;
  minver_a[23][12] = 6;
  minver_a[23][13] = 23;
  minver_a[23][14] = 10;
  minver_a[23][15] = 4;
  minver_a[23][16] = 4;
  minver_a[23][17] = 25;
  minver_a[23][18] = 12;
  minver_a[23][19] = 16;
  minver_a[23][20] = 1;
  minver_a[23][21] = 6;
  minver_a[23][22] = 25;
  minver_a[23][23] = 22;
  minver_a[23][24] = 24;
  minver_a[23][25] = 21;
  minver_a[23][26] = 21;
  minver_a[23][27] = 7;
  minver_a[23][28] = 9;
  minver_a[23][29] = 6;
  minver_a[23][30] = 26;
  minver_a[23][31] = 31;
  minver_a[24][0] = 20;
  minver_a[24][1] = 24;
  minver_a[24][2] = 26;
  minver_a[24][3] = 4;
  minver_a[24][4] = 23;
  minver_a[24][5] = 29;
  minver_a[24][6] = 21;
  minver_a[24][7] = 22;
  minver_a[24][8] = 13;
  minver_a[24][9] = 4;
  minver_a[24][10] = 12;
  minver_a[24][11] = 5;
  minver_a[24][12] = 13;
  minver_a[24][13] = 5;
  minver_a[24][14] = 24;
  minver_a[24][15] = 3;
  minver_a[24][16] = 31;
  minver_a[24][17] = 11;
  minver_a[24][18] = 4;
  minver_a[24][19] = 27;
  minver_a[24][20] = 23;
  minver_a[24][21] = 27;
  minver_a[24][22] = 32;
  minver_a[24][23] = 13;
  minver_a[24][24] = 20;
  minver_a[24][25] = 24;
  minver_a[24][26] = 27;
  minver_a[24][27] = 28;
  minver_a[24][28] = 11;
  minver_a[24][29] = 8;
  minver_a[24][30] = 2;
  minver_a[24][31] = 6;
  minver_a[25][0] = 12;
  minver_a[25][1] = 1;
  minver_a[25][2] = 6;
  minver_a[25][3] = 28;
  minver_a[25][4] = 27;
  minver_a[25][5] = 27;
  minver_a[25][6] = 12;
  minver_a[25][7] = 27;
  minver_a[25][8] = 19;
  minver_a[25][9] = 26;
  minver_a[25][10] = 29;
  minver_a[25][11] = 16;
  minver_a[25][12] = 7;
  minver_a[25][13] = 16;
  minver_a[25][14] = 17;
  minver_a[25][15] = 9;
  minver_a[25][16] = 22;
  minver_a[25][17] = 2;
  minver_a[25][18] = 4;
  minver_a[25][19] = 23;
  minver_a[25][20] = 10;
  minver_a[25][21] = 4;
  minver_a[25][22] = 18;
  minver_a[25][23] = 23;
  minver_a[25][24] = 29;
  minver_a[25][25] = 19;
  minver_a[25][26] = 31;
  minver_a[25][27] = 25;
  minver_a[25][28] = 25;
  minver_a[25][29] = 10;
  minver_a[25][30] = 25;
  minver_a[25][31] = 6;
  minver_a[26][0] = 15;
  minver_a[26][1] = 6;
  minver_a[26][2] = 31;
  minver_a[26][3] = 14;
  minver_a[26][4] = 25;
  minver_a[26][5] = 32;
  minver_a[26][6] = 32;
  minver_a[26][7] = 24;
  minver_a[26][8] = 28;
  minver_a[26][9] = 25;
  minver_a[26][10] = 29;
  minver_a[26][11] = 27;
  minver_a[26][12] = 11;
  minver_a[26][13] = 8;
  minver_a[26][14] = 31;
  minver_a[26][15] = 5;
  minver_a[26][16] = 16;
  minver_a[26][17] = 14;
  minver_a[26][18] = 27;
  minver_a[26][19] = 26;
  minver_a[26][20] = 14;
  minver_a[26][21] = 12;
  minver_a[26][22] = 22;
  minver_a[26][23] = 32;
  minver_a[26][24] = 2;
  minver_a[26][25] = 12;
  minver_a[26][26] = 2;
  minver_a[26][27] = 12;
  minver_a[26][28] = 9;
  minver_a[26][29] = 26;
  minver_a[26][30] = 5;
  minver_a[26][31] = 21;
  minver_a[27][0] = 12;
  minver_a[27][1] = 16;
  minver_a[27][2] = 9;
  minver_a[27][3] = 4;
  minver_a[27][4] = 30;
  minver_a[27][5] = 25;
  minver_a[27][6] = 14;
  minver_a[27][7] = 2;
  minver_a[27][8] = 10;
  minver_a[27][9] = 19;
  minver_a[27][10] = 8;
  minver_a[27][11] = 10;
  minver_a[27][12] = 32;
  minver_a[27][13] = 2;
  minver_a[27][14] = 32;
  minver_a[27][15] = 16;
  minver_a[27][16] = 24;
  minver_a[27][17] = 28;
  minver_a[27][18] = 13;
  minver_a[27][19] = 12;
  minver_a[27][20] = 7;
  minver_a[27][21] = 25;
  minver_a[27][22] = 1;
  minver_a[27][23] = 28;
  minver_a[27][24] = 19;
  minver_a[27][25] = 16;
  minver_a[27][26] = 21;
  minver_a[27][27] = 21;
  minver_a[27][28] = 9;
  minver_a[27][29] = 14;
  minver_a[27][30] = 13;
  minver_a[27][31] = 5;
  minver_a[28][0] = 26;
  minver_a[28][1] = 23;
  minver_a[28][2] = 22;
  minver_a[28][3] = 9;
  minver_a[28][4] = 6;
  minver_a[28][5] = 8;
  minver_a[28][6] = 29;
  minver_a[28][7] = 24;
  minver_a[28][8] = 14;
  minver_a[28][9] = 8;
  minver_a[28][10] = 11;
  minver_a[28][11] = 10;
  minver_a[28][12] = 17;
  minver_a[28][13] = 12;
  minver_a[28][14] = 24;
  minver_a[28][15] = 19;
  minver_a[28][16] = 4;
  minver_a[28][17] = 13;
  minver_a[28][18] = 23;
  minver_a[28][19] = 28;
  minver_a[28][20] = 26;
  minver_a[28][21] = 9;
  minver_a[28][22] = 13;
  minver_a[28][23] = 22;
  minver_a[28][24] = 25;
  minver_a[28][25] = 22;
  minver_a[28][26] = 5;
  minver_a[28][27] = 8;
  minver_a[28][28] = 6;
  minver_a[28][29] = 14;
  minver_a[28][30] = 25;
  minver_a[28][31] = 18;
  minver_a[29][0] = 8;
  minver_a[29][1] = 12;
  minver_a[29][2] = 13;
  minver_a[29][3] = 15;
  minver_a[29][4] = 23;
  minver_a[29][5] = 23;
  minver_a[29][6] = 8;
  minver_a[29][7] = 21;
  minver_a[29][8] = 14;
  minver_a[29][9] = 5;
  minver_a[29][10] = 30;
  minver_a[29][11] = 2;
  minver_a[29][12] = 14;
  minver_a[29][13] = 23;
  minver_a[29][14] = 9;
  minver_a[29][15] = 19;
  minver_a[29][16] = 21;
  minver_a[29][17] = 9;
  minver_a[29][18] = 17;
  minver_a[29][19] = 23;
  minver_a[29][20] = 7;
  minver_a[29][21] = 8;
  minver_a[29][22] = 32;
  minver_a[29][23] = 3;
  minver_a[29][24] = 16;
  minver_a[29][25] = 14;
  minver_a[29][26] = 29;
  minver_a[29][27] = 20;
  minver_a[29][28] = 31;
  minver_a[29][29] = 4;
  minver_a[29][30] = 31;
  minver_a[29][31] = 17;
  minver_a[30][0] = 31;
  minver_a[30][1] = 12;
  minver_a[30][2] = 2;
  minver_a[30][3] = 4;
  minver_a[30][4] = 8;
  minver_a[30][5] = 17;
  minver_a[30][6] = 5;
  minver_a[30][7] = 32;
  minver_a[30][8] = 1;
  minver_a[30][9] = 15;
  minver_a[30][10] = 15;
  minver_a[30][11] = 30;
  minver_a[30][12] = 9;
  minver_a[30][13] = 28;
  minver_a[30][14] = 9;
  minver_a[30][15] = 19;
  minver_a[30][16] = 15;
  minver_a[30][17] = 21;
  minver_a[30][18] = 11;
  minver_a[30][19] = 5;
  minver_a[30][20] = 6;
  minver_a[30][21] = 4;
  minver_a[30][22] = 24;
  minver_a[30][23] = 8;
  minver_a[30][24] = 32;
  minver_a[30][25] = 32;
  minver_a[30][26] = 1;
  minver_a[30][27] = 3;
  minver_a[30][28] = 4;
  minver_a[30][29] = 19;
  minver_a[30][30] = 4;
  minver_a[30][31] = 30;
  minver_a[31][0] = 24;
  minver_a[31][1] = 17;
  minver_a[31][2] = 31;
  minver_a[31][3] = 16;
  minver_a[31][4] = 23;
  minver_a[31][5] = 13;
  minver_a[31][6] = 17;
  minver_a[31][7] = 28;
  minver_a[31][8] = 13;
  minver_a[31][9] = 27;
  minver_a[31][10] = 12;
  minver_a[31][11] = 16;
  minver_a[31][12] = 12;
  minver_a[31][13] = 29;
  minver_a[31][14] = 21;
  minver_a[31][15] = 18;
  minver_a[31][16] = 11;
  minver_a[31][17] = 14;
  minver_a[31][18] = 22;
  minver_a[31][19] = 6;
  minver_a[31][20] = 13;
  minver_a[31][21] = 28;
  minver_a[31][22] = 12;
  minver_a[31][23] = 17;
  minver_a[31][24] = 10;
  minver_a[31][25] = 16;
  minver_a[31][26] = 19;
  minver_a[31][27] = 32;
  minver_a[31][28] = 28;
  minver_a[31][29] = 28;
  minver_a[31][30] = 18;
  minver_a[31][31] = 15;

#endif

}