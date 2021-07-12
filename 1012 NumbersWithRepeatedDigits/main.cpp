//
//  main.cpp
//  1012 NumbersWithRepeatedDigits
//
//  Created by Aaron on 2021/7/11.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


// Check if N is without repeated digits.
int isRepeated(const vector<int> &num){
    const int size = static_cast<int>(num.size());
    vector<int> digit(10, 0);
    for (int i=0; i<size; ++i) {
        if (digit[num[i]] > 0) {return true;}
        ++digit[num[i]];
    }
    return false;
}

int numDupDigitsAtMostN(int n) {
    if (n == 0) {return 0;}
    
    // Int -> int vector
    const int N = n;
    int size = 0;
    vector<int> num;
    while (n != 0) {
        num.push_back(n % 10);
        n /= 10;
        ++ size;
    }
    reverse(num.begin(), num.end());
    
    // Calculate the number of 1 ~ (size - 1) digits without repeated digits.
    int noRepeated = 0;
    for (int i=1; i<=size-1; ++i) {
        int remain = 9;
        int count = 9;
        for (int j=2; j<=i; ++j) {
            count *= remain--;
        }
        noRepeated += count;
    }
    
    // Calculate the number of size digits without repeated digits.
    for (int i=0; i<size; ++i) {
        // Initialization of remain
        int remain;
        i == 0 ? remain = num[i] - 1 : remain = num[i];
        
        // If prefix is the number with repaeted digits, the loop break
        vector<int> prefix(i);
        copy(num.begin(), num.begin() + i, prefix.begin());
        if (isRepeated(prefix)) {break;}
        
        // Delete choosen numbers from remain
        for (int j=0; j<i; ++j) {
            if (num[j] <= num[i] - 1) {--remain;}
        }
        
        // Count
        int count = remain;
        for (int j=i+1; j<size; ++j) {
            count *= (10 - j);
        }
        noRepeated += count;
    }
    
    // Check if N is the number without repeated digits.
    isRepeated(num) ? 1 : ++noRepeated;
    
    return N - noRepeated;
}


int main(int argc, const char * argv[]) {
    cout << numDupDigitsAtMostN(0) << " "; // 0
    cout << numDupDigitsAtMostN(1) << " "; // 0
    cout << numDupDigitsAtMostN(3) << " "; // 0
    cout << numDupDigitsAtMostN(10) << " "; // 0
    cout << numDupDigitsAtMostN(11) << " "; // 1
    cout << numDupDigitsAtMostN(20) << " "; // 1
    cout << numDupDigitsAtMostN(100) << " "; // 10
    cout << numDupDigitsAtMostN(101) << " "; // 11
    cout << numDupDigitsAtMostN(1000) << " "; // 262
    cout << numDupDigitsAtMostN(1001) << " "; // 263
    cout << endl;
    return 0;
}
