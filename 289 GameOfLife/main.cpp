//
//  main.cpp
//  289 GameOfLife
//
//  Created by Aaron on 2021/6/28.
//

#include <iostream>
#include <vector>
using namespace std;

void print(vector<vector<int>> &v){
    for (int i=0; i<v.size(); ++i) {
        for (int j=0; j<v[i].size(); ++j) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int inBound(const int raw, const int sizeRaw, const int col, const int sizeCol){
    return !(raw < 0 || raw >= sizeRaw || col < 0 || col >= sizeCol);
}

void gameOfLife(vector<vector<int>>& board) {
    
    // Sum
    vector<vector<int>> sum(board);
    vector<int> position {-1, -1, -1, 0, -1, 1,
                           0, -1,         0, 1,
                           1, -1,  1, 0,  1, 1};
    for (int i=0; i<sum.size(); ++i) {
        for (int j=0; j<sum[i].size(); ++j) {
            sum[i][j] = 0;
            for (int k=0; k<16; k+=2) {
                if (inBound(i + position[k], sum.size(),
                            j + position[k + 1], sum[i].size())) {
                    sum[i][j] += board[i + position[k]][j + position[k + 1]];
                }
            }
        }
    }
    
    // Determin life or die
    for (int i=0; i<board.size(); ++i) {
        for (int j=0; j<board[i].size(); ++j) {
            if (board[i][j] == 1) {
                if (sum[i][j] < 2 || sum[i][j] > 3) {board[i][j] = 0;}
            }else{
                if (sum[i][j] == 3) {board[i][j] = 1;}
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    vector<vector<int>> v {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};
    gameOfLife(v);
    print(v);
    
    
    return 0;
}
