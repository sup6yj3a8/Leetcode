//
//  main.cpp
//  060 PermutationSequence
//
//  Created by Aaron on 2021/6/28.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void permutation(const int head, const int tail, string str){
    if (head == tail) {
        cout << str << endl;
    }else{
        for (int i=head ; i<=tail; ++i) {
            swap(str[head], str[i]);
            permutation(head+1, tail, str);
        }
    }
}

string getPermutation(int n, int k) {
    // Calculate n! and create an number sequences (1~n)
    int fact = 1;
    vector<int> numbers;
    for (int i=1; i<n; ++i) {
        fact *= i;
        numbers.push_back(i);
    }
    numbers.push_back(n);
    
    --k;
    // Make n-th permutation string
    string ans = "";
    for (int i=0; i<n; ++i) {
        ans += to_string(numbers[k / fact]);
        numbers.erase(numbers.begin() + k / fact);
        k %= fact;
        if (numbers.size() != 0) {fact /= numbers.size();}
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    string s1 = getPermutation(4, 4);
    cout << s1 << endl;
    
    string s2 {"123"};
    permutation(0, 2, s2);
    
    return 0;
}
