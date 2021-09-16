//
//  main.cpp
//  990 SatisfiabilityOfEqualityEquations
//
//  Created by Aaron on 2021/9/16.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Find the position of a letter (lett) in the isEqu and record it into j.
void findIsEqu (const vector<unordered_set<int>> &isEqu, const int &lett, int &j) {
    for ( ; j < isEqu.size(); ++j) {
        if (isEqu[j].find(lett) != isEqu[j].end()) {break;}
    }
}

bool equationsPossible (vector<string>& equations) {
    vector<int> notEqu; // Record the index of NOT equations.
    vector<unordered_set<int>> isEqu; // The table only is based on equations (==).
    vector<int> letters(26, 0); // Record whether the letters exist.
    
    // 1. Construct the isEqu and notEqu.
    for (int i = 0; i < equations.size(); ++i) {
        if (equations[i][1] == '!') {
            notEqu.push_back(i);
        }else{
            int lett1 = equations[i][0] - 'a';
            int lett2 = equations[i][3] - 'a';
            int exsit1 = letters[lett1] == 0 ? 0 : 1;
            int exsit2 = letters[lett2] == 0 ? 0 : 1;
            int j1 = 0; // j1 is the position lett1 is in the isEqu.
            int j2 = 0; // j2 is the position lett2 is in the isEqu.
            
            if (!exsit1 && !exsit2) {
                isEqu.push_back({lett1, lett2});
                letters[lett1] = 1; letters[lett2] = 1;
            }else if (exsit1 && !exsit2) {
                findIsEqu(isEqu, lett1, j1);
                isEqu[j1].insert(lett2);
                letters[lett2] = 1;
            }else if (!exsit1 && exsit2) {
                findIsEqu(isEqu, lett2, j2);
                isEqu[j2].insert(lett1);
                letters[lett1] = 1;
            }else{
                findIsEqu(isEqu, lett1, j1);
                findIsEqu(isEqu, lett2, j2);
                if (j1 != j2) { // If j1 != j2, combine isEqu[j1] and isEqu[j2].
                    isEqu[j1].insert(isEqu[j2].begin(), isEqu[j2].end());
                    isEqu.erase(isEqu.begin() + j2);
                }
            }
        }
    }
    
    // 2. Check if all NOT equations are reasonable.
    for (const auto i : notEqu) {
        int lett1 = equations[i][0] - 'a';
        int lett2 = equations[i][3] - 'a';
        int exsit1 = letters[lett1] == 0 ? 0 : 1;
        int exsit2 = letters[lett2] == 0 ? 0 : 1;
        int j1 = 0;
        int j2 = 0;
        
        if (lett1 == lett2) {return false;}
        if (exsit1 && exsit2) {
            findIsEqu(isEqu, lett1, j1);
            findIsEqu(isEqu, lett2, j2);
            if (j1 == j2) {return false;}
        }
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    vector<string> str;
    
    str = {"a==b","b!=a"};
    cout << equationsPossible(str) << endl; // 0

    str = {"b==a","a==b"};
    cout << equationsPossible(str) << endl; // 1

    str = {"a==b","b==c","a==c"};
    cout << equationsPossible(str) << endl; // 1

    str = {"a==b","b!=c","c==a"};
    cout << equationsPossible(str) << endl; // 0
    
    str = {"c==c","b==d","x!=z"};
    cout << equationsPossible(str) << endl; // 1
    
    str = {"a!=b"};
    cout << equationsPossible(str) << endl; // 1
    
    str = {"a!=a"};
    cout << equationsPossible(str) << endl; // 0
    
}
