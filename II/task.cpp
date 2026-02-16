// Online C++ compiler to run C++ program online
#include <iostream>

// 1
int addTwo(int, int);
int subTwo(int, int);
int mulTwo(int, int);
int divTwo(int, int);

int addTwo(int a, int b) {
    return a+b;
}
int subTwo(int a, int b){
    return a-b;

}
int mulTwo(int a, int b){
    return a*b;
}
int divTwo(int a, int b){
    return a/b;
}

// 2
bool triangle(float, float, float);
int addVector();

// 3
bool kDel(int n, int k);
int prime(int n);

// 4
void sudoku(int[9][9]);

void sudokuRec(int row, int col, int sudoku[9][9]){
    if(row > 9) {
        return 0;
    }

    if(col > 9) {
        return 1;
    }

    for(int k = 1; k <= 9; k++) {
        sudoku[row, col] = k;
        if(col + 1 >= 9) col = 0, ++row;
        sudokuRec(row, col + 1, sudoku);
    }
}

void sudoku(int[9][9] sudoku) {

}

// 5
int raceGen();

int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro";

    return 0;
}