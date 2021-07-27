//
//  main.cpp
//  782 TransformToChessboard
//
//  Created by Aaron on 2021/7/23.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int isRawSame(const vector<vector<int>> &vec, const int &a, const int &b){
    for (int col=0; col<vec[a].size(); ++col) {
        if (vec[a][col] != vec[b][col]) {return false;}
    }
    return true;
}

// Find the min number of swaping of vec to fit ans1 {0, 1, 0, 1, .....} or ans2 {1, 0, 1, 0, .....}.
int minSwap(const vector<int> &vec){
    int ans1 = 0;
    int ans2 = 0;
    for (int i=0; i<vec.size(); ++i) {
        if (vec[i] != i % 2) {++ans1;} // {0, 1, 0, 1, .....}
        if (vec[i] != (i + 1) % 2) {++ans2;} // {1, 0, 1, 0, .....}
    }
    
    // If ans1 and ans2 are valid, they must be EVEN.
    if (ans1 % 2 != 0) {
        return ans2 / 2;
    }else if (ans2 % 2 != 0) {
        return ans1 / 2;
    }else{
        return min(ans1 / 2, ans2 / 2);
    }
    
}

// The size of difference of vec is smaller 1, the vec is valid.
// The value of vec must be 0 or 1
int isValid(const vector<int> &vec){
    int c1 = 0;
    int c2 = 0;
    for (const auto &v : vec) {
        v == 0 ? ++c1 : ++c2;
    }
    return abs(c1 - c2) <= 1;
}

int findRawDiff(const vector<vector<int>> &board, vector<int> &diffRaw, vector<int> &raw){
    diffRaw.push_back(0);
    for (int i=1; i<board.size(); ++i) {
        int d = 0;
        
        for (d=0; d<diffRaw.size(); ++d) {
            if ( isRawSame(board, i, diffRaw[d]) ){break;}
        }
        
        // If d > 1, d is not valid.
        if (d > 1) {
            return -1;
        }else if (d == diffRaw.size()) {
            diffRaw.push_back(i);
        }
        
        raw[i] = d;
    }
    
    return 1;
}

int movesToChessboard(vector<vector<int>>& board) {
    const int size = static_cast<int>(board.size());
    
    // 1. Check if the raw and col of board is same and record corresponding index to diff.
    vector<int> raw(size, 0);
    vector<int> col(size, 0);
    vector<int> diffRaw;
    vector<int> diffCol;
    
    // 1.1 Find the difference of raw
    if (findRawDiff(board, diffRaw, raw) == -1) {return -1;}
    
    // 1.2 Transpose (raw <-> col)
    vector<vector<int>> tBoard(size, vector<int>(size));
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.size(); ++j) {
            tBoard[j][i] =  board[i][j];
        }
    }
    
    // 1.3 Find the difference of col
    if (findRawDiff(tBoard, diffCol, col) == -1) {return -1;}
    
    // 1.4 If the size of the difference type is 2 or the size of difference of raws / cols is smaller than 1, the vector is valid.
    if (diffRaw.size() != 2 || diffCol.size() != 2 || !isValid(raw) || !isValid(col)) {return -1;}
    
    // 2. Return min number of swapping
    return minSwap(raw) + minSwap(col);
}


int main(int argc, const char * argv[]) {
    vector<vector<int>> a;
    
    a = {{0, 0, 1, 0, 1, 1}, {1, 1, 0, 1, 0, 0}, {1, 1, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 1}, {1, 1, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 1}};
    cout << movesToChessboard(a) << endl; // 2
    
    a = {{1, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 1}, {0, 0, 0, 1}};
    cout << movesToChessboard(a) << endl; // -1
    
    a = {{1, 1, 1, 1}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    cout << movesToChessboard(a) << endl; // -1
    
    a = {{0, 1}, {1, 0}};
    cout << movesToChessboard(a) << endl; // 0
    
    a = {{1, 0}, {1, 0}};
    cout << movesToChessboard(a) << endl; // -1
    
    a = {{0, 1, 1, 0}, {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}};
    cout << movesToChessboard(a) << endl; // 2
    
    a = {{1, 1, 0}, {0, 0, 1}, {0, 0, 1}};
    cout << movesToChessboard(a) << endl; // 2

    return 0;
}
