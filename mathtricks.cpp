#include <iostream>
#include <ctime>

typedef struct {
    bool hasPassed = false;
    char val[2];
} square;

typedef struct {
    bool hasPassed;
    double val;
} player;

void assignValue(square *field) {
    char math_op = "+-*/"[rand() % 4];
    int randomNumber = (rand() % 10) + 1;
    field->val[0] = math_op;
    field->val[1] = '0' + randomNumber;
}

int main() {
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

    // Create a 2D array of squares
    square field[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            assignValue(&field[i][j]);
        }
    }

    // Print the field
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << "[" << field[i][j].val[0] << field[i][j].val[1] << "] ";
        }
        std::cout << '\n';
    }

    return 0;
}
