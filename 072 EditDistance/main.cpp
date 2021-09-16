//
//  main.cpp
//  072 EditDistance
//
//  Created by Aaron on 2021/9/17.
//

#include <iostream>
#include <algorithm>
using namespace std;

int minDistance(string word1, string word2) {
    const int len1 = static_cast<int>(word1.size() + 1);
    const int len2 = static_cast<int>(word2.size() + 1);
    int DP[len1][len2]; // A dynamic programing table. (len1 * len2)
    
    // 1. Initialization of DP.
    for (int i = 0; i < len1; ++i) {DP[i][0] = i;}
    for (int i = 0; i < len2; ++i) {DP[0][i] = i;}
    
    // 2. Dynamic programing.
    for (int i = 1; i < len1; ++i) {
        for (int j = 1; j < len2; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                DP[i][j] = DP[i - 1][j - 1];
            }else{
                //                Remove    ,     Insert,        Replace
                DP[i][j] = min({DP[i - 1][j], DP[i][j - 1], DP[i - 1][j - 1]}) + 1;
            }
        }
    }
    
    return DP[len1 - 1][len2 - 1];
}

int main(int argc, const char * argv[]) {
    string word1, word2;
    
    word1 = "horse";
    word2 = "ros";
    cout << minDistance(word1, word2) << endl; // 3

    word1 = "intention";
    word2 = "execution";
    cout << minDistance(word1, word2) << endl; // 5
    
    return 0;
}
