#include <iostream>
#include "mathTrix.hpp"
#include <cstdint>

#include <cstdlib>  // For rand()
#include <ctime>

/* -----------------------------------------------------------------------------------------------------------------------------------------------------------
fieldChecker - Checks if the dimensions of the game field (rows and columns) meet the minimum required criteria.                                            //
This function verifies that both the number of rows and columns are greater than or equal to a predefined size                                              //
If either the number of rows or columns is less than the minimum allowed value, the function prompts the user to input new values until the criteria are met//
                                                                                                                                                            //
Parameters:                                                                                                                                                 //
- int rows: The number of rows required for the field.                                                                                                      //
- int cols: The number of columns required for the field.                                                                                                   //
                                                                                                                                                            //
Return type:                                                                                                                                                //  
- void: The function does not return any value, but it modifies the rows and cols values directly through user input if they don't meet the criteria.       //
------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void fieldChecker(int &rows,int &cols)
{
    while ( ( rows < mMinRowsOrCols || cols < mMinRowsOrCols ) && ( rows >= mMinRowsOrCols || cols >= mMinRowsOrCols ) ) {
        if (rows < mMinRowsOrCols && cols < mMinRowsOrCols) {
            std::cout << "Both n and m are less than 4, the minimum requirement is 4!\n";
            std::cin >> rows >> cols;
            continue;
        }
        if (rows < mMinRowsOrCols) {
            std::cout << "Rows are less than 4\n";
        }
        if (cols < mMinRowsOrCols) {
            std::cout << "Colums are less than 4\n";
        }
        std::cin >> rows >> cols;
    }
}
/* -------------------------------------------------------------------------------------------------------------------------------------------
assignValue - Assigns random values to a specific square on the game field, including special values and arithmetic operations.             //
                                                                                                                                            //
This function selects random squares on the field and assigns them various values such as special numbers and arithmetic operations         //
('+', '-', '*', '/'), as well as numbers for operations based on the random selection.                                                      //
                                                                                                                                            //
Parameters:                                                                                                                                 //
- square *field: Pointer to the square in the field where values will be assigned.                                                          //
- uint8 rows: The number of rows in the field.                                                                                              //
- uint8 cols: The number of columns in the field.                                                                                           //
                                                                                                                                            //
Return type:                                                                                                                                //
- void: The function does not return any value but modifies the given square’s value with randomly selected arithmetic and special values.  //
--------------------------------------------------------------------------------------------------------------------------------------------*/
void assignValue(square *field, uint8 rows, uint8 cols)
{
    uint8 specialNumberIndex;
    uint8 negativeNumberIndex;
    uint8 positiveNumberIndex;
    uint8 multiplicationByTwoIndex;
    uint8 devisionByTwoIndex;
    const uint8 maxOperators = mMinRowsOrCols; // they just happen to be the same amount
    specialNumberIndex = (rand() % ((rows * cols) - mForTwo));

    field[specialNumberIndex / cols].val[mZero] = '*';
    field[specialNumberIndex / cols].val[mOne] = '0';

    negativeNumberIndex = (rand() % ((rows * cols) - mForTwo));
    while (negativeNumberIndex == specialNumberIndex) {
        negativeNumberIndex = (rand() % ((rows * cols) - mForTwo));
    }

    positiveNumberIndex = (rand() % ((rows * cols) - mForTwo));
    while ((positiveNumberIndex == specialNumberIndex) || (positiveNumberIndex == negativeNumberIndex)) {
        positiveNumberIndex = (rand() % ((rows * cols) - mForTwo));
    }

    multiplicationByTwoIndex = (rand() % ((rows * cols) - mForTwo));
    while ((multiplicationByTwoIndex == specialNumberIndex) ||
           (multiplicationByTwoIndex == negativeNumberIndex) ||
           (multiplicationByTwoIndex == positiveNumberIndex)) {
        multiplicationByTwoIndex = (rand() % ((rows * cols) - mForTwo));
    }

    devisionByTwoIndex = (rand() % ((rows * cols) - mForTwo));
    while ((devisionByTwoIndex == specialNumberIndex) ||
           (devisionByTwoIndex == negativeNumberIndex) ||
           (devisionByTwoIndex == positiveNumberIndex) ||
           (devisionByTwoIndex == multiplicationByTwoIndex)) {
        devisionByTwoIndex = (rand() % ((rows * cols) - mForTwo));
    }

    char math_op = "+-*/"[rand() % maxOperators];
    uint8 randomNumber = (math_op == '/') ? (rand() % mNumsFrom0to9 + mOne) : (rand() % mTens);

    switch (randomNumber) {
    case 0:
    case 2:
        field->val[mZero] = math_op;
        field->val[mOne] = randomNumber + '0';
        break;
    default:
        field->val[mZero] = math_op;
        field->val[mOne] = randomNumber + '0';
        break;
    }

    field[specialNumberIndex / cols].val[mZero] = '*';
    field[specialNumberIndex / cols].val[mOne] = '0';

    field[negativeNumberIndex / cols].val[mZero] = '-';
    field[negativeNumberIndex / cols].val[mOne] = (rand() % mTens) + '0';

    field[positiveNumberIndex / cols].val[mZero] = '+';
    field[positiveNumberIndex / cols].val[mOne] = (rand() % mTens) + '0';

    field[multiplicationByTwoIndex / cols].val[mZero] = '*';
    field[multiplicationByTwoIndex / cols].val[mOne] = '2';

    field[devisionByTwoIndex / cols].val[mZero] = '/';
    field[devisionByTwoIndex / cols].val[mOne] = '2';
}

/* -----------------------------------------------------------------------------------------------------------------------------------------------
matrixAssignValue - Assigns values to a matrix of squares on the game field and tracks specific special conditions.                             //
                                                                                                                                                //
This function iterates through the matrix of squares in the game field and assigns random values to each square using the assignValue function. //
It also tracks whether certain special values (such as '*0', '*2', '/2', '+', '-') are present on the field using the provided boolean flags.   //
                                                                                                                                                //
Parameters:                                                                                                                                     //
- square field[][100]: A 2D array representing the game field with squares.                                                                     //
- uint8 u8_rows: The number of rows in the field.                                                                                               //
- uint8 u8_cols: The number of columns in the field.                                                                                            //
- bool &b_hasSpecial0: Flag indicating if the special value '*0' has been assigned.                                                             //
- bool &b_hasSpecial2: Flag indicating if the special value '*2' has been assigned.                                                             //
- bool &b_hasSpecialDiv2: Flag indicating if the special value '/2' has been assigned.                                                          //
- bool &b_hasPositive: Flag indicating if a positive value has been assigned.                                                                   //
- bool &b_hasNegative: Flag indicating if a negative value has been assigned.                                                                   //
                                                                                                                                                //
Return type:                                                                                                                                    //
- void: The function does not return any value, but modifies the field values and flags to track special cases.                                 //
------------------------------------------------------------------------------------------------------------------------------------------------*/

void matrixAssignValue(square field[][mMaxSize], uint8 u8_rows, uint8 u8_cols,bool &b_hasSpecial0, bool &b_hasSpecial2,bool &b_hasSpecialDiv2,bool &b_hasPositive,bool &b_hasNegative)
{
    for (uint8 i = mZero; i < u8_rows; i++) {
        for (uint8 j = mZero; j < u8_cols; j++) {
            if (!(i == mZero && j == mZero) && !(i == u8_rows - mOne && j == u8_cols - mOne)) {
                assignValue(&field[i][j], u8_rows, u8_cols);

                // Check if the assigned value satisfies any of the special cases
                b_hasSpecial0 = b_hasSpecial0 || (field[i][j].val[mZero] == '*' && field[i][j].val[mOne] == '0');
                b_hasSpecial2 = b_hasSpecial2 || (field[i][j].val[mZero] == '*' && field[i][j].val[mOne] == '2');
                b_hasSpecialDiv2 = b_hasSpecialDiv2 || (field[i][j].val[mZero] == '/' && field[i][j].val[mOne] == '2');
                b_hasPositive = b_hasPositive || (field[i][j].val[mZero] == '+');
                b_hasNegative = b_hasNegative || (field[i][j].val[mZero] == '-');
            }
        }
    }
}

/* -----------------------------------------------------------------------------------------------------------------------------//
createField - Creates a field by assigning values to each square while ensuring certain special conditions are met.             //
                                                                                                                                //
This function first assigns random values to all squares in the field using matrixAssignValue and then checks                   //
if all required special conditions are present on the field. If any special values are missing, the function fills in the gaps. //
                                                                                                                                //
Parameters:                                                                                                                     //
- square field[][100]: A 2D array representing the game field.                                                                  //
- uint8 u8_rows: The number of rows in the field.                                                                               //
- uint8 u8_cols: The number of columns in the field.                                                                            //
                                                                                                                                //
Return type:                                                                                                                    //
- void: The function does not return any value, but modifies the field values to meet the required conditions.                  //
--------------------------------------------------------------------------------------------------------------------------------*/

void createField(square field[][mMaxSize], uint8 u8_rows, uint8 u8_cols)
{
    bool b_hasSpecial0 = false, b_hasSpecial2 = false, b_hasSpecialDiv2 = false;
    bool b_hasPositive = false, b_hasNegative = false;

    // Assign values to all cells except the first and last
    matrixAssignValue(field,u8_rows, u8_cols, b_hasSpecial0, b_hasSpecial2, b_hasSpecialDiv2, b_hasPositive,b_hasNegative);
    // Handle missing special cases
    for (uint8 i = mZero; i < u8_rows; i++) {
        for (uint8 j = mZero; j < u8_cols; j++) {
            if (!(i == mZero && j == mZero) && !(i == u8_rows - mOne && j == u8_cols - mOne)) {
                if (!b_hasSpecial0) {
                    if (field[i][j].val[mZero] != '*' || field[i][j].val[mOne] != '0') {
                        field[i][j].val[mZero] = '*';
                        field[i][j].val[mOne] = '0';
                        b_hasSpecial0 = true;
                    }
                }
                if (!b_hasSpecial2) {
                    if (field[i][j].val[mZero] != '*' || field[i][j].val[mOne] != '2') {
                        field[i][j].val[mZero] = '*';
                        field[i][j].val[mOne] = '2';
                        b_hasSpecial2 = true;
                    }
                }
                if (!b_hasSpecialDiv2) {
                    if (field[i][j].val[mZero] != '/' || field[i][j].val[mOne] != '2') {
                        field[i][j].val[mZero] = '/';
                        field[i][j].val[mOne] = '2';
                        b_hasSpecialDiv2 = true;
                    }
                }
                if (!b_hasPositive) {
                    if (field[i][j].val[mZero] != '+') {
                        field[i][j].val[mZero] = '+';
                        field[i][j].val[mOne] = (rand() % mTens) + '0';
                        b_hasPositive = true;
                    }
                }
                if (!b_hasNegative) {
                    if (field[i][j].val[mZero] != '-') {
                        field[i][j].val[mZero] = '-';
                        field[i][j].val[mOne] = (rand() % mTens) + '0';
                        b_hasNegative = true;
                    }
                }
            }
        }
    }

    // Set first and last cells to '0'
    field[mZero][mZero].val[mZero] = '0';
    field[mZero][mZero].val[mOne] = '0';
    field[u8_rows - mOne][u8_cols - mOne].val[mZero] = '0';
    field[u8_rows - mOne][u8_cols - mOne].val[mOne] = '0';
}

/* ---------------------------------------------------------------------------------------------------------------------------------------------------------//
printField - Displays the current state of the game field, showing player scores and values on squares.                                                     //
                                                                                                                                                            //
This function iterates through the game field and prints each square’s value. If a player is on a particular square, the player’s score is shown instead of //
the square's value. It ensures both players' scores are displayed next to their respective positions.                                                       //
                                                                                                                                                            //
Parameters:                                                                                                                                                 //
- square field[][100]: A 2D array representing the game field.                                                                                              //
- player &s_player1: A reference to the first player object containing player 1's position and score.                                                       //
- player &s_player2: A reference to the second player object containing player 2's position and score.                                                      //
- uint8_t rows: The number of rows in the field.                                                                                                            //
- uint8_t cols: The number of columns in the field.                                                                                                         //
                                                                                                                                                            //
Return type:                                                                                                                                                //
- void: The function does not return any value, but it outputs the current game field and player information to the console.                                //
------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void printField(square field[][mMaxSize],player &s_player1,player &s_player2, uint8_t rows, uint8_t cols)
{
    for (uint8 i = mZero; i < rows; i++) {
        for (uint8 j = mZero; j < cols; j++) {
            if (i == s_player1.playerX && j == s_player1.playerY) {
                std::cout << "[" << s_player1.color << s_player1.score << "\033[0m" << "] ";
            } else if (i == s_player2.playerX && j == s_player2.playerY) {
                std::cout << "[" << s_player2.color << s_player2.score << "\033[0m" << "] ";
            } else {
                if(field[i][j].hasPassed == true)
                {
                    if(field[i][j].playerOnePassed == true)
                    {
                        std::cout << "[" << s_player1.color << field[i][j].val[mZero] << field[i][j].val[mOne] << "\033[0m" << "] ";
                        std::cout << field[i][j].playerOnePassed;
                    }
                    else
                    {
                        std::cout << "[" << s_player2.color << field[i][j].val[mZero] << field[i][j].val[mOne] << "\033[0m" << "] ";
                    }
                }
                else
                {
                    std::cout << "[" << field[i][j].val[mZero] << field[i][j].val[mOne] << "] ";
                }
            }
        }
        std::cout << '\n';
    }
}

/* -------------------------------------------------------------------------------------------------------------------------------
checkGameOver - Checks if all squares around the player's current position have been visited, determining if the game is over.  //
                                                                                                                                //
This function checks the 3x3 neighborhood around the player's current position. If all surrounding squares have been visited,   //
the game is over                                                                                                                //
If there is at least one unvisited square, the game continues.                                                                  //
                                                                                                                                //
Parameters:                                                                                                                     //
- square field[][100]: A 2D array representing the game field.                                                                  //
- player &s_player: A reference to the player object whose position is checked.                                                 //
- uint8 u8_rows: The number of rows in the field.                                                                               //
- uint8 u8_cols: The number of columns in the field.                                                                            //
- bool b_isGameOver: A reference to a boolean variable indicating if the game is over.                                          //
                                                                                                                                //
Return type:                                                                                                                    //
- bool: Returns true if the game is over, meaning there are no unvisited squares around the player, otherwise returns false.    //
--------------------------------------------------------------------------------------------------------------------------------*/
bool checkGameOver(square field[][mMaxSize],player &s_player, uint8 u8_rows, uint8 u8_cols, bool b_isGameOver)
{
    // Iterate over the 3x3 neighborhood around the player's current position
    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
        for (int offsetY = -1; offsetY <= 1; ++offsetY) {
            // Calculate the neighbor's position
            int neighborX = s_player.playerX + offsetX;
            int neighborY = s_player.playerY + offsetY;

            // Skip the player's current position and out-of-bounds positions
            if ((offsetX == 0 && offsetY == 0) || 
                neighborX < 0 || neighborX >= u8_rows || 
                neighborY < 0 || neighborY >= u8_cols) {
                continue;
            }

            // Return false if an unvisited square is found
            if (!field[neighborX][neighborY].hasPassed) {
                return false;
            }
        }
    }
    // No unvisited squares found, return true
    return true;
}

/* --------------------------------------------------------------------------------------------------------------------------------------
movePlayer - Moves the player in the specified direction, updating their position and applying any effects from the square they land on//
                                                                                                                                       //
This function updates the player's position based on the input direction and checks if the move is valid                               //
It then applies the effect of the square (e.g., arithmetic operations that change the player's score).                                 //
                                                                                                                                       //
Parameters:                                                                                                                            //
- square field[][100]: A 2D array representing the game field.                                                                         //
- player &s_player: A reference to the player object whose position is updated.                                                        //
- uint8 rows: The number of rows in the field.                                                                                         //
- uint8 cols: The number of columns in the field.                                                                                      //
- const char c_direction[2]: A string representing the direction the player wants to move ('u', 'd', 'l', 'r', etc.).                  //
- bool &isGameOver: A reference to a boolean variable indicating if the game is over.                                                  //
                                                                                                                                       //
Return type:                                                                                                                           //
- bool: Returns true if the move was successful, otherwise returns false.                                                              //
---------------------------------------------------------------------------------------------------------------------------------------*/
bool movePlayer(square field[][mMaxSize],player &s_player, uint8 rows, uint8 cols, const char c_direction[mForTwo], bool &isGameOver,bool b_isFirst)
{
    uint8 newRow = s_player.playerX;
    uint8 newCol = s_player.playerY;

    // Update position based on direction
    if (c_direction[mZero] == 'u' && c_direction[mOne] == '\0') {
        newRow--;
    } else if (c_direction[mZero] == 'd' && c_direction[mOne] == '\0') {
        newRow++;
    } else if (c_direction[mZero] == 'l' && c_direction[mOne] == '\0') {
        newCol--;
    } else if (c_direction[mZero] == 'r' && c_direction[mOne] == '\0') {
        newCol++;
    } else if (c_direction[mZero] == 'u' && c_direction[mOne] == 'l') {
        newRow--;
        newCol--;
    } else if (c_direction[mZero] == 'u' && c_direction[mOne] == 'r') {
        newRow--;
        newCol++;
    } else if (c_direction[mZero] == 'd' && c_direction[mOne] == 'l') {
        newRow++;
        newCol--;
    } else if (c_direction[mZero] == 'd' && c_direction[mOne] == 'r') {
        newRow++;
        newCol++;
    } else {
        std::cout << "Invalid direction. Try again.\n";
        return false;
    }

    // Check boundaries
    if (newRow < mZero || newRow >= rows || newCol < mZero || newCol >= cols) {
        std::cout << "Move out of bounds! Pick another direction.\n";
        return false;
    }

    // Check if the square was already visited
    square& targetSquare = field[newRow][newCol];
    if (targetSquare.hasPassed) {
        std::cout << "You cannot move to a square you've already visited. Pick another direction.\n";
        return false;
    }

    // Update the current position to an empty state
    field[s_player.playerX][s_player.playerY].val[mZero] = ' ';
    field[s_player.playerX][s_player.playerY].val[mOne] = ' ';

    // Move player to the new square
    s_player.playerX = newRow;
    s_player.playerY = newCol;

    // Apply the effects of the square
    targetSquare.hasPassed = true; // Mark square as visited
    char op = targetSquare.val[0];
    uint8 num = targetSquare.val[1] - '0'; // Convert char to integer

    switch (op) {
        case '+':
            s_player.score += num;
            break;
        case '-':
            s_player.score -= num;
            break;
        case '*':
            s_player.score *= num;
            break;
        case '/':
            if (num != 0) s_player.score /= num;
            break;
        default:
            break;
    }
    // Display player's score on the new square
    if(b_isFirst == true)
    {
        targetSquare.playerOnePassed == true;
    }
    else
    {
        targetSquare.playerOnePassed == false;
    } 
    if(s_player.score < mTens)
    {
        targetSquare.val[mZero] = s_player.score - '0';
    }
    else
    {
        targetSquare.val[mZero] = (s_player.score / mTens) - '0';
    }  // Mark as score cell
    targetSquare.val[mOne] = (s_player.score < mTens) ? '0' : ' ';
    std::cout << "\033[0m";
    return true;
}

/* ---------------------------------------------------------------------------------------
clear - Clears the terminal screen                                                      //
                                                                                        //
This function clears the console screen, allowing for a fresh display of the game state // 
It uses ANSI escape codes to perform the clear operation                                //
                                                                                        //
Parameters:                                                                             //
- None                                                                                  //
                                                                                        //
Return type:                                                                            //
- void: The function does not return any value.                                         //
----------------------------------------------------------------------------------------*/
void clear()
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
    //https://stackoverflow.com/questions/6486289/how-can-i-clear-console
}

/* ---------------------------------------------------------------------------------------
gameStart - Clears the terminal screen                                                  //
                                                                                        //
This function starts the game and clears the matrix on each turn start, after that it   //
starts a series of commands which move the different players around                     //
Parameters:                                                                             //
- None                                                                                  //
                                                                                        //
Return type:                                                                            //
- void: The function does not return any value.                                         //
----------------------------------------------------------------------------------------*/
void gameStart(square field[][mMaxSize],player &s_player1,player &s_player2, uint8 u8_rowsForCreation,uint8 u8_colsForCreation,char c_direction[2],bool b_isFirst,bool b_isGameOver)
{
    while (!b_isGameOver) {
        clear();
        if(b_isFirst == true)
        {
            printField(field, s_player1, s_player2, u8_rowsForCreation, u8_colsForCreation);
        
            std::cout << "Player 1, enter your direction (u, d, l, r, ul, ur, dl, dr): ";
            while (true)
            {
                std::cin >> c_direction;
                if ((c_direction[mZero] == 'u' || c_direction[mZero] == 'd' || c_direction[mZero] == 'l' || c_direction[mZero] == 'r') && c_direction[1] == '\0')
                {
                    if(b_isGameOver != true)
                    {
                        if(movePlayer(field, s_player1, u8_rowsForCreation, u8_colsForCreation, c_direction, b_isGameOver,b_isFirst) == true)
                        {
                            field[s_player1.playerX][s_player1.playerY].hasPassed = true;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                } 
                else if ((c_direction[mZero] == 'u' || c_direction[mZero] == 'd') && (c_direction[mOne] == 'l' || c_direction[mOne] == 'r')) 
                {
                    if(b_isGameOver != true)
                    {
                        if(movePlayer(field,s_player1, u8_rowsForCreation, u8_colsForCreation, c_direction, b_isGameOver,b_isFirst) == true)
                        {
                            field[s_player1.playerX][s_player1.playerY].hasPassed = true;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                else 
                {
                    std::cout << "Invalid direction! Try again: ";
                    continue;
                }
            }
        }
        else
        {
            printField(field, s_player1, s_player2, u8_rowsForCreation, u8_colsForCreation);
            std::cout << "Player 2, enter your direction (u, d, l, r, ul, ur, dl, dr): ";
            while (true)
            {
                std::cin >> c_direction;
                if((c_direction[mZero] == 'u' || c_direction[mZero] == 'd' || c_direction[mZero] == 'l' || c_direction[mZero] == 'r') && c_direction[mOne] == '\0')
                {
                    if(b_isGameOver != true)
                    {    
                        if(movePlayer(field, s_player2,u8_rowsForCreation, u8_colsForCreation, c_direction, b_isGameOver,b_isFirst) == true)
                        {
                            field[s_player2.playerX][s_player2.playerY].hasPassed = true;
                            break;
                        }
                        else
                        {
                            field[s_player2.playerX][s_player2.playerY].hasPassed = true;
                            continue;
                        }
                    }
                }
                else if ((c_direction[mZero] == 'u' || c_direction[mZero] == 'd') && (c_direction[mOne] == 'l' || c_direction[mOne] == 'r')) 
                {
                    if(b_isGameOver != true)
                    {
                        if(movePlayer(field,s_player2, u8_rowsForCreation, u8_colsForCreation, c_direction, b_isGameOver,b_isFirst) == true)
                        {
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                } 
                else 
                {
                    std::cout << "Invalid direction! Try again: ";
                    continue;
                }   
            }
        }
        if(b_isFirst == true)
        {
            if(checkGameOver(field, s_player1, u8_rowsForCreation, u8_colsForCreation,b_isGameOver) == true)
            {
                b_isGameOver = true;
                std::cout << "No more available moves! Game over.\n";
            }
        }
        else
        {
            if(checkGameOver(field, s_player1, u8_rowsForCreation, u8_colsForCreation, b_isGameOver) == true)
            {
                b_isGameOver = true;
                std::cout << "No more available moves! Game over.\n";
            }
        }
        b_isFirst = !b_isFirst;
    }
}
int main() {
    srand(time(0));

    int n = 0, m = 0;
    player s_player1;
    s_player1 = {0, 0, 0.0, "\033[34m"};

    std::cout << "Enter the size of the matrix: ";
    std::cin >> n >> m;
    while(n > mMaxSize || m > mMaxSize)
    {
        std::cout << "Enter numbers smaller than 100" << '\n';
        std::cin >> n >> m;
    }
    fieldChecker(n,m);
    player s_player2;
    s_player2.playerX = n - 1;
    s_player2.playerY = m - 1;
    s_player2.color = "\033[31m";
    bool b_isFirst = true;
    bool b_isGameOver = false;
    char c_direction[mForTwo];

    const uint8 u8_rowsForCreation = n;
    const uint8 u8_colsForCreation = n;
    square field[mMaxSize][mMaxSize];
    createField(field, u8_rowsForCreation, u8_colsForCreation);
    field[mZero][mZero].hasPassed = true;
    field[n-1][m-1].hasPassed = true;
    gameStart(field,s_player1,s_player2, u8_rowsForCreation,u8_colsForCreation,c_direction, b_isFirst, b_isGameOver);
    if(s_player1.score < s_player2.score)
    {
        std::cout << "Player1 wins" << '\n';
    }
    if(s_player2.score < s_player1.score)
    {
        std::cout << "Player2 wins" << '\n';
    }
    if(s_player1.score == s_player2.score)
    {
        std::cout << "Draw!" << '\n';
    }
    return 0;
}