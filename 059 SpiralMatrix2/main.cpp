//
//  main.cpp
//  059 SpiralMatrix2
//
//  Created by Aaron on 2021/9/23.
//

#include <iostream>
#include <vector>
using namespace std;

void printVec(const vector<vector<int>> &vec) {
    for (const auto &v : vec) {
        for (const auto w : v) {
            cout << w << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void fill4(const int n, vector<vector<int>> &matrix, const int i1, const int j1, const int num1) {
    const int i2 = i1 + n;
    const int j2 = j1 + n;
    const int num2 = num1 + n;
    const int num3 = num2 + n;
    const int num4 = num3 + n;
    
    for (int c = 0; c < n; ++c) {
        matrix[i1    ][j1 + c] = num1 + c; // right
        matrix[i1 + c][j2    ] = num2 + c; // down
        matrix[i2    ][j2 - c] = num3 + c; // left
        matrix[i2 - c][j1    ] = num4 + c; // up
    }
}

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix (n, vector<int> (n));
    --n;
    int i = 0, j = 0, num = 1;
    for ( ; n >= 0; n -= 2) {
        if (n != 0) {
            fill4(n, matrix, i++, j++, num);
            num += 4 * n;
        } else { // n == 0
            matrix[i][j] = num;
        }
    }
    
    return matrix;
}

int main(int argc, const char * argv[]) {
    int n;
    
    for (n = 1 ; n <= 10; ++n) {
        printVec(generateMatrix(n));
    }
    
    return 0;
}
