//
//  main.cpp
//  866 PrimePalindrome
//
//  Created by Aaron on 2021/7/7.
// 

// Find the smallest prime palindrome greater than or equal to n.

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

// sieve of Eratosthenes
void isPrime(vector<int> &p){
    // Find primes
    for (int i=2; i<=sqrt(p.size()); ++i) {
        if (p[i] == 1) {
            for (int j=2*i; j<p.size(); j+=i) {p[j] = 0;}
        }
    }
    
    // Delete non-primes
    for (int i = p.size() -1; i>=0; --i) {
        if (p[i] == 0) {
            p.erase(p.begin() + i);
        }else{
            p[i] = i;
        }
    }
    p.erase(p.begin());
    p.erase(p.begin());
}

int isPrime(const int n, vector<int> &p){
    if (n <= 2) {
        return n == 2;
    }
    
    for (const auto &iter : p) {
        if ( n % iter == 0 ) {
            if (n / iter == 1) {
                return true;
            }else{
                return false;
            }
        }
    }
    
    p.push_back(n);
    return true;
}

int isPrime(const int n){
    if (n <= 2) {
        return n == 2;
    }
    
    int board = sqrt(n);
    for (int i=2; i<=board; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int isPalindrome(const int n){
    string str = to_string(n);
    const int size = str.size() - 1;
    for (int i=0; i <= size / 2; ++i) {
        if (str[i] != str[size - i]) {return false;}
    }
    return true;
}

int primePalindrome(int n) {
    // Create prime table by sieve of Eratosthenes
    static vector<int> primeTable(n, 1);
    static int finish = 0;
    if (! finish ) {isPrime(primeTable); finish = 1;}

    // Fill primes
    int maxPrime = primeTable[primeTable.size() - 1];
    if (n > maxPrime) {
        while (n >= maxPrime) {
            isPrime(maxPrime++, primeTable);
        }
    }
    
    // Find Prime Palindrome
    while ( ! isPrime(n, primeTable) || ! isPalindrome(n) ) {++n;}
//    while ( ! primeTable[n] || ! isPalindrome(n) ) {++n;}
//    while ( ! isPalindrome(n) || ! isPrime(n) ) {++n;}
    
    return n;
}


int main(int argc, const char * argv[]) {
    
    int n = primePalindrome(8);
    cout << n << endl;
    n = primePalindrome(55);
    cout << n << endl;
    n = primePalindrome(6);
    cout << n << endl;
    return 0;
}
