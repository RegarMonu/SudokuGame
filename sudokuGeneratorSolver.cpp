#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

const int UNASSIGNED=0;

void printSudoku(const vector<vector<int>>& grid) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            cout << grid[row][col] << " ";
        }
        cout << "\n";
    }
}

bool isValid(vector<vector<int>>& grid, int row, int col, int num) {
    for (int x = 0; x < 9; ++x) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}


bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid[row][col] == UNASSIGNED) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid)) {
                            return true;
                        }
                        grid[row][col] = UNASSIGNED;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

//generateSudoku function generate 30 random number according to isValid function constraint. 
void generateSudoku(vector<vector<int>>& grid, int numFilledCells) {
    srand(time(0));
    for (int i = 0; i < numFilledCells; ++i) {
        int row = rand() % 9;
        int col = rand() % 9;
        int num = rand() % 9 + 1;
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
        } else {
            --i;
        }
    }
}

int main(){
    int N=9;
    vector<vector<int>>puzzle(9,vector<int>(9,UNASSIGNED));
    int numFilledCells=30;
    generateSudoku(puzzle,numFilledCells);
    cout << "Generated Sudoku Puzzle:\n";
    printSudoku(puzzle);

    if (solveSudoku(puzzle)) {
        cout << "\nSolved Sudoku Puzzle:\n";
        printSudoku(puzzle);
    } else {
        cout << "\nNo solution exists for the given puzzle.\n";
    }
    return 0;
}