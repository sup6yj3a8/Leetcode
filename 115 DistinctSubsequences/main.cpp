//
//  main.cpp
//  115 DistinctSubsequences
//
//  Created by Aaron on 2021/7/9.
//

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// All reasionable permutation
void permutation(int &count, const vector<int> &target, const vector<vector<int>> &letter, const int level = 0, const int prev = 0){
    if (level == target.size() - 1) {
        count += letter[ target[level] ].size() - prev;
    }else{
        for (int i=prev; i<letter[ target[level] ].size(); ++i) {
            for (int j=0; j<letter[ target[level + 1] ].size(); ++j) {
                if (letter[ target[level] ][i] < letter[ target[level + 1] ][j]) {
                    permutation(count, target, letter, level + 1, j);
                    break;
                }
            }
        }
    }
}

// DFS recursion (slower)
int numDistinct1(string s, string t) {
    // Collect the index each letter (A-Za-z)
    vector<vector<int>> letter;
    letter.resize(52);
    for (int i=0; i<s.length(); ++i) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            letter[s[i] - 'A'].push_back(i);
        }else if ('a' <= s[i] && s[i] <='z') {
            letter[s[i] - 'a' + 26].push_back(i);
        }
    }
    
    // Char -> ASCII -> index of letter (A-Za-z)
    vector<int> tar;
    for ( auto &iter : t) {
        if ('A' <= iter && iter <= 'Z') {
            tar.push_back(iter - 'A');
        }else if ('a' <= iter && iter <='z') {
            tar.push_back(iter - 'a' + 26);
            
        }
    }

    // Count the number of reasonable perutations
    int count = 0;
    permutation(count, tar, letter);
    
    return count;
}

// Dynamic programing (fastr)
int numDistinct2(string s, string t) {
    // Initailization
    const int n = s.size();
    const int m = t.size();
    unsigned long long dp[n+1][m+1];
    memset(dp,0,sizeof(dp));
    for(int i=0;i<=n;i++){dp[i][0]=1;}
    
    // DP
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1]==t[j-1]){
                dp[i][j]=dp[i-1][j-1] + dp[i-1][j];
            }
            else{
                dp[i][j]= dp[i-1][j] ;
            }
        }
    }
    
    // Print DP table
//    for (int i=0; i<=n; ++i) {
//        for (int j=0; j<=m; ++j) {
//            cout << dp[i][j] << " ";
//        }
//        cout << endl;
//    }
    
    return (int)dp[n][m];
}

int main(int argc, const char * argv[]) {
    string s = "rabbbit";
    string t = "rabbit";
    int ans = 0;
    ans = numDistinct1(s, t);
    cout << ans << endl;

    s = "babgbagg";
    t = "bag";
    ans = numDistinct1(s, t);
    cout << ans << endl;

    s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    t =  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    ans = numDistinct2(s, t);
    cout << ans << endl;
    
    return 0;
}
