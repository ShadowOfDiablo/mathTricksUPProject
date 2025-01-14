#include <iostream>
#include <ctime>
#include "inttypes.h"
#include <stdlib.h> 

typedef struct {
    bool hasPassed = false;
    char val[2];
} square;

typedef struct {
    bool hasPassed;
    double val;
} player;

void assignValue(square *field, uint8_t rows, uint8_t cols) {
    int specialNumberIndex;
    uint8_t negativeNumberIndex;
    uint8_t positiveNumberIndex;
    uint8_t multiplicationByTwoIndex;
    uint8_t devisionByTwoIndex;
    const uint8_t maxOperators = 4U;
    specialNumberIndex = (rand() % ((rows * cols) - 2));

    field[specialNumberIndex / cols].val[0] = '*';
    field[specialNumberIndex / cols].val[1] = '0';

    negativeNumberIndex = (rand() % ((rows * cols) - 2));
    while (negativeNumberIndex == specialNumberIndex) {
        negativeNumberIndex = (rand() % ((rows * cols) - 2));
    }

    positiveNumberIndex = (rand() % ((rows * cols) - 2));
    while ((positiveNumberIndex == specialNumberIndex) || (positiveNumberIndex == negativeNumberIndex)) {
        positiveNumberIndex = (rand() % ((rows * cols) - 2));
    }

    multiplicationByTwoIndex = (rand() % ((rows * cols) - 2));
    while ((multiplicationByTwoIndex == specialNumberIndex) ||
           (multiplicationByTwoIndex == negativeNumberIndex) ||
           (multiplicationByTwoIndex == positiveNumberIndex)) {
        multiplicationByTwoIndex = (rand() % ((rows * cols) - 2));
    }

    devisionByTwoIndex = (rand() % ((rows * cols) - 2));
    while ((devisionByTwoIndex == specialNumberIndex) ||
           (devisionByTwoIndex == negativeNumberIndex) ||
           (devisionByTwoIndex == positiveNumberIndex) ||
           (devisionByTwoIndex == multiplicationByTwoIndex)) {
        devisionByTwoIndex = (rand() % ((rows * cols) - 2));
    }

    char math_op = "+-*/"[rand() % maxOperators];
    int randomNumber = (math_op == '/') ? (rand() % 9 + 1) : (rand() % 10);

    switch (randomNumber) {
    case 0:
    case 2:
        field->val[0U] = math_op;
        field->val[1U] = randomNumber + '0';
        break;
    default:
        field->val[0U] = math_op;
        field->val[1U] = randomNumber + '0';
        break;
    }

    field[specialNumberIndex / cols].val[0] = '*';
    field[specialNumberIndex / cols].val[1] = '0';

    field[negativeNumberIndex / cols].val[0] = '-';
    field[negativeNumberIndex / cols].val[1] = (rand() % 10) + '0';

    field[positiveNumberIndex / cols].val[0] = '+';
    field[positiveNumberIndex / cols].val[1] = (rand() % 10) + '0';

    field[multiplicationByTwoIndex / cols].val[0] = '*';
    field[multiplicationByTwoIndex / cols].val[1] = '2';

    field[devisionByTwoIndex / cols].val[0] = '/';
    field[devisionByTwoIndex / cols].val[1] = '2';
}

void createField(square field[][100], uint8_t rows, uint8_t cols) {
    bool hasSpecial0 = false, hasSpecial2 = false, hasSpecialDiv2 = false, 
         hasPositive = false, hasNegative = false;

    // Assign values to all cells except the first and last
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(i == 0 && j == 0) && !(i == rows - 1 && j == cols - 1)) { 
                assignValue(&field[i][j], rows, cols); 

                // Check if the assigned value satisfies any of the special cases
                hasSpecial0 = hasSpecial0 || (field[i][j].val[0] == '*' && field[i][j].val[1] == '0');
                hasSpecial2 = hasSpecial2 || (field[i][j].val[0] == '*' && field[i][j].val[1] == '2');
                hasSpecialDiv2 = hasSpecialDiv2 || (field[i][j].val[0] == '/' && field[i][j].val[1] == '2');
                hasPositive = hasPositive || (field[i][j].val[0] == '+');
                hasNegative = hasNegative || (field[i][j].val[0] == '-');
            }
        }
    }

    // Handle missing special cases
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(i == 0 && j == 0) && !(i == rows - 1 && j == cols - 1)) {
                if (!hasSpecial0) {
                    if (field[i][j].val[0] != '*' || field[i][j].val[1] != '0') {
                        field[i][j].val[0] = '*';
                        field[i][j].val[1] = '0';
                        hasSpecial0 = true;
                    }
                }
                if (!hasSpecial2) {
                    if (field[i][j].val[0] != '*' || field[i][j].val[1] != '2') {
                        field[i][j].val[0] = '*';
                        field[i][j].val[1] = '2';
                        hasSpecial2 = true;
                    }
                }
                if (!hasSpecialDiv2) {
                    if (field[i][j].val[0] != '/' || field[i][j].val[1] != '2') {
                        field[i][j].val[0] = '/';
                        field[i][j].val[1] = '2';
                        hasSpecialDiv2 = true;
                    }
                }
                if (!hasPositive) {
                    if (field[i][j].val[0] != '+') {
                        field[i][j].val[0] = '+';
                        field[i][j].val[1] = (rand() % 10) + '0'; 
                        hasPositive = true;
                    }
                }
                if (!hasNegative) {
                    if (field[i][j].val[0] != '-') {
                        field[i][j].val[0] = '-';
                        field[i][j].val[1] = (rand() % 10) + '0'; 
                        hasNegative = true;
                    }
                }
            }
        }
    }

    // Set first and last cells to '0'
    field[0][0].val[0] = '0';
    field[0][0].val[1] = '0';
    field[rows - 1][cols - 1].val[0] = '0';
    field[rows - 1][cols - 1].val[1] = '0';
}

void printField(square field[][100], uint8_t rows, uint8_t cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "[" << field[i][j].val[0] << field[i][j].val[1] << "] ";
        }
        std::cout << '\n';
    }
}

void handleDirection(bool isFirst) {
    char direction[2];

    if (isFirst) {
        std::cout << "\nPlayer 1 (from the top) is first" << '\n';
        std::cout << "\nPick where to go (u/d/l/r/ul/ur/dl/dr): ";
        std::cin >> direction;
    } else {
        std::cout << "\nPlayer 2 (from the bottom) is first" << '\n';
        std::cout << "\nPick where to go (u/d/l/r/ul/ur/dl/dr): ";
        std::cin >> direction;
    }

    if (direction[0] == 'u' && direction[1] == '\0') {
        std::cout << "You chose up\n";
    } else if (direction[0] == 'd' && direction[1] == '\0') {
        std::cout << "You chose down\n";
    } else if (direction[0] == 'l' && direction[1] == '\0') {
        std::cout << "You chose left\n";
    } else if (direction[0] == 'r' && direction[1] == '\0') {
        std::cout << "You chose right\n";
    } else if (direction[0] == 'u' && direction[1] == 'l' && direction[2] == '\0') {
        std::cout << "You chose upleft\n";
    } else if (direction[0] == 'u' && direction[1] == 'r' && direction[2] == '\0') {
        std::cout << "You chose upright\n";
    } else if (direction[0] == 'd' && direction[1] == 'l' && direction[2] == '\0') {
        std::cout << "You chose downleft\n";
    } else if (direction[0] == 'd' && direction[1] == 'r' && direction[2] == '\0') {
        std::cout << "You chose downright\n";
    } else {
        std::cout << "Invalid direction\n";
    }
}

int main() {
    srand(time(0));

    int n = 0, m = 0;
    bool isFirst = true;
    char direction[2];

    std::cout << "Enter the size of the matrix: ";
    while (n < 4 || m < 4) {
        std::cin >> n >> m;
        if (n < 4 && m < 4) {
            std::cout << "Both n and m are less than 4, the minimum requirement is 4!\n";
            continue;
        }
        if (n < 4) {
            std::cout << "n is less than 4\n";
        }
        if (m < 4) {
            std::cout << "m is less than 4\n";
        }
    }

    square field[100][100];
    field[0][0].val[1] = '0';
    createField(field, n, m);

    while(true)
    {
        printField(field, n, m);
        handleDirection(isFirst);
        isFirst = !isFirst;
        break;
    }
    return 0;
}
