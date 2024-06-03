#include <iostream>
#include <vector>

using namespace std;

void printSudoku(int arr[9][9]) {
    cout << "_________________" << endl << endl;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++)
            cout << arr[r][c] << ' ';
        cout << endl;
    }

    cout << "_________________" << endl;
}

bool canPlace(int arr[9][9], int row, int col, int n) {
    if (arr[row][col] != 0) return false;

    bool status = true;
    int gridx = (col / 3) * 3;
    int gridy = (row / 3) * 3;
    for (int i = 0; i < 9; i++) {
        if (arr[row][i] == n) { status = false; break; }
        if (arr[i][col] == n) { status = false; break; }
        if (arr[gridy + i /3][gridx + i % 3] == n) { status = false; break; }
    }
    return status;
}

std::vector<int> findPlacebles(int arr[9][9], int r, int c) {
    vector<int> cps = {};
    for (int i = 1; i <= 9; i++) {
        if (canPlace(arr, r, c, i))
            cps.push_back(i);
    }
    return cps;
}

void copyArray(int arr[9][9], int arrCopy[9][9]) {
    for (int y = 0; y < 9; y++)
        for (int x = 0; x < 9; x++)
            arrCopy[y][x] = arr[y][x];
}

void nextEmpty(int arr[9][9], int row, int col, int& rowNext, int& colNext) {
    int index = 9 * 9 + 1;
    for (int i = row * 9 + col + 1; i < 9 * 9; i++) {
        if (arr[i / 9][i % 9] == 0) {
            index = i;
            break;
        }
    }
    rowNext = index / 9;
    colNext = index % 9;
}

bool solveSudoku(int arr[9][9], int row, int col) {
    if (row > 8) return true;

    if (arr[row][col] != 0) {
        int rowNext;
        int colNext;
        nextEmpty(arr, row, col, rowNext, colNext);
        return solveSudoku(arr, rowNext, colNext);
    }

    vector<int> placeables = findPlacebles(arr, row, col);
    if (placeables.size() == 0) return false;

    bool status = false;
    for (int i = 0; i < placeables.size(); i++) {
        int n = placeables[i];
        int arrCopy[9][9];
        copyArray(arr, arrCopy);
        arrCopy[row][col] = n;
        int rowNext;
        int colNext;
        nextEmpty(arrCopy, row, col, rowNext, colNext);
        if (solveSudoku(arrCopy, rowNext, colNext)) {
            copyArray(arrCopy, arr);
            status = true;
            break;
        }

    }

    return status;
}

int main()
{
    int board[9][9] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    printSudoku(board);
    solveSudoku(board, 0, 0);
    printSudoku(board);

    return 0;
}

