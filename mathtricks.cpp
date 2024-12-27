#include <iostream>
#include <ctime>
#include "inttypes.h"

typedef struct
{
    bool hasPassed = false;
    char val[2];
} square;

typedef struct
{
    bool hasPassed;
    double val;
} player;

void assignValue(square *field, uint8_t rows, uint8_t cols)
{
    int specialNumberIndex;
    uint8_t negativeNumberIndex;
    uint8_t positiveNumberIndex;
    uint8_t multiplicationByTwoIndex;
    uint8_t devisionByTwoIndex;
    const uint8_t maxOperators = 4U;
    specialNumberIndex = (rand() % ((rows * cols) - 2));
    field[specialNumberIndex/rows][specialNumberIndex % cols].val[0] = '*'; 
    field[specialNumberIndex/rows][specialNumberIndex % cols].val[1] = '0';
    negativeNumberIndex = (rand() % ((rows * cols) - 2));
    while (negativeNumberIndex == specialNumberIndex)
    {
        negativeNumberIndex = (rand() % ((rows * cols) - 2));
    }
    positiveNumberIndex = (rand() % ((rows * cols) - 2));
    while ((positiveNumberIndex == specialNumberIndex) || (positiveNumberIndex == negativeNumberIndex))
    {
        positiveNumberIndex = (rand() % ((rows * cols) - 2));
    }
    multiplicationByTwoIndex = (rand() % ((rows * cols) - 2));
    while ((multiplicationByTwoIndex == specialNumberIndex) ||
           (multiplicationByTwoIndex == negativeNumberIndex) ||
           (multiplicationByTwoIndex == positiveNumberIndex))
    {    
        multiplicationByTwoIndex = (rand() % ((rows * cols) - 2));
    }
    devisionByTwoIndex = (rand() % ((rows * cols) - 2));
    while ((devisionByTwoIndex == specialNumberIndex) ||
           (devisionByTwoIndex == negativeNumberIndex) ||
           (devisionByTwoIndex == positiveNumberIndex) ||
           (devisionByTwoIndex == multiplicationByTwoIndex))
    {    
        devisionByTwoIndex = (rand() % ((rows * cols) - 2));
    }

    char math_op = "+-*/"[rand() % maxOperators];
    int randomNumber = (math_op == '/') ? (rand() % 9 + 1) : (rand() % 10);

    switch (randomNumber)
    {
    case 0:
        if(math_op == '*'){
            field->val[0U] = math_op;
            field->val[1U] = randomNumber + '0';
        }
        else
        {
            field->val[0U] = math_op;
            field->val[1U] = randomNumber + '0';
        }
    case 2:
        if (math_op == '/')
        {
            field->val[0U] = math_op;
            field->val[1U] = randomNumber + '0';
        }
        if (math_op == '*')
        {
            field->val[0U] = math_op;
            field->val[1U] = randomNumber + '0';
        }
        if (math_op == '+') 
        {
            field->val[0U] = math_op;
            field->val[1U] = randomNumber + '0';
        }
        if (math_op == '-')
        {
            field->val[0U] = math_op;
            field->val[1U] = randomNumber + '0';
        }
        break;
    default:
        field->val[0U] = math_op;
        field->val[1U] = randomNumber + '0';
        break;
    }

    field[specialNumberIndex / cols][specialNumberIndex % cols].val[0] = '*'; 
    field[specialNumberIndex / cols][specialNumberIndex % cols].val[1] = '0';

    field[negativeNumberIndex / cols][negativeNumberIndex % cols].val[0] = '-';
    field[negativeNumberIndex / cols][negativeNumberIndex % cols].val[1] = (rand() % 10) + '48';

    field[positiveNumberIndex / cols][positiveNumberIndex % cols].val[0] = '+';
    field[positiveNumberIndex / cols][positiveNumberIndex % cols].val[1] = (rand() % 10) + '48';

    field[multiplicationByTwoIndex / cols][multiplicationByTwoIndex % cols].val[0] = '*';
    field[multiplicationByTwoIndex / cols][multiplicationByTwoIndex % cols].val[1] = '2';

    field[devisionByTwoIndex / cols][devisionByTwoIndex % cols].val[0] = '/';
    field[devisionByTwoIndex / cols][devisionByTwoIndex % cols].val[1] = '2';
}

void createField(square *field,uint8_t rows, uint8_t cols){
    for (int i = 0; i < rows; i++)
    {
        if(i == 0){
            for (int j = 1; j < cols; j++)
            {
                assignValue(*field[i][j],rows,cols);
            }
        }else{
            if(i == n-1)
            {
                for (int j = 0; j < cols-1; j++) {
                    assignValue(field[i][j],rows,cols);
                }
            }else{
                for (int j = 0; j < cols; j++)
                {
                    assignValue(field[i][j],rows,cols);
                }
            }
        }
    }
}

void printField(square *field,uint8_t rows, uint8_t cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "[" << field[i][j].val[0] << field[i][j].val[1] << "] ";
        }
        std::cout << '\n';
    }
}
int main()
{
    srand(time(0)); // Initialize random seed

    int n = 0, m = 0;

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

    square field[n][m];
    field[0][0].val[1] = '0';
    field[n-1][m-1].val[1] = '0';
    createField(&field[0][0],n, m);

    printField(&field[0][0], n, m);
    return 0;
}
