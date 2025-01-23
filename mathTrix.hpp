#ifndef MATHTRIX_HPP
#define MATHTRIX_HPP

#include <iostream>
#include <cstdint>

/* ------------------------------- macros ------------------------------- */
 
#define mZero               0U
#define mOne                1U
#define mForTwo             2U
#define mMinRowsOrCols      4U
#define mNumsFrom0to9       9U
#define mTens               10U
#define mMaxSize            100U

/* ------------------------------- redefinitions ------------------------------- */

typedef uint8_t uint8;

typedef struct {
    bool playerOnePassed = false;
    bool hasPassed = false;
    char val[mForTwo];
} square;

typedef struct {
    uint8 playerX = 0U;
    uint8 playerY = 0U;
    double score = 0;
    const char *color = nullptr;
} player;


/* ------------------------------- function prototypes -------------------------------*/
void fieldChecker(int &rows,int &cols);
void assignValue(square *field, uint8 rows, uint8 cols);
void matrixAssignValue(square field[][mMaxSize], uint8 u8_rows, uint8 u8_cols,bool &b_hasSpecial0, bool &b_hasSpecial2,bool &b_hasSpecialDiv2,bool &b_hasPositive,bool &b_hasNegative);
void printField(square field[mMaxSize][mMaxSize], player s_player1, player s_player2, uint n, uint m);
void createField(square field[mMaxSize][mMaxSize], uint n, uint m);
bool movePlayer(square field[][mMaxSize],player &s_player, uint8 rows, uint8 cols, const char c_direction[mForTwo], bool &isGameOver,bool b_isFirst);
void clear();
void fieldChecker(uint n, uint m);
bool checkGameOver(square field[mMaxSize][mMaxSize], player s_player, uint n, uint m, bool& isGameOver);

#endif // MATHTRIX_HPP
