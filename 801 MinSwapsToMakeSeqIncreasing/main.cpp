//
//  main.cpp
//  801 MinSwapsToMakeSeqIncreasing
//
//  Created by Aaron on 2021/7/31.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void print(const vector<int>& a){
    for (const auto & v : a) {
        cout << v << " ";
    }
    cout << endl;
}

void greaterGraph(const vector<int> &a){
    cout << a[0] << " ";
    for (int i=1; i<a.size(); ++i) {
        if (a[i-1] >= a[i]) {
            cout << "- ";
        }else{
            cout << "  ";
        }
        cout << setw(2) << a[i] << " ";
    }
    cout << endl;
}

// Check if swaping vec[i] is safe
bool isSafe(const vector<int> &vec1, const vector<int> &vec2, const int &i){
    if (i == 0) {
        // 1. i is head
        return vec1[i] < vec2[i+1] && vec2[i] < vec1[i+1];
    }else if (i == vec1.size()-1){
        // 2. i is tail
        return vec1[i-1] < vec2[i] && vec2[i-1] < vec1[i];
    }else{
        return vec1[i-1] < vec2[i] && vec2[i] < vec1[i+1] &&
               vec2[i-1] < vec1[i] && vec1[i] < vec2[i+1];
    }
}

bool isAscend(const vector<int> &vec1, const vector<int> &vec2){
    for (int i=1; i<vec1.size(); ++i) {
        if (vec1[i-1] >= vec1[i] || vec2[i-1] >= vec2[i]) {
            return false;
        }
    }
    return true;
}

int countSwap(const vector<int> &swapTable){
    int count = 0;
    for (const auto s : swapTable) {
        if (s % 2 == 1) {++count;}
    }
    return count;
}

// An original idea that falls LeetCode tests.
int minSwap1(vector<int>& nums1, vector<int>& nums2) {
    const int size = static_cast<int>(nums1.size());
    vector<int> swapTable(size, 0);
    
    // 1. Swap num1 & num2 to make seqence Increasing
    while (!isAscend(nums1, nums2)) {
        for (int i=1; i<size; ++i) {
            if ( (nums1[i-1] >= nums1[i] || nums2[i-1] >= nums2[i]) ) {
                if (isSafe(nums1, nums2, i) && i+1<size && ((nums1[i] >= nums1[i+1] || nums2[i] >= nums2[i+1]))) {
                    // 1.1 If i is safe and (i,i+1) is descending, swap i
                    swap(nums1[i], nums2[i]);
                    ++swapTable[i-1];
                }else if (isSafe(nums1, nums2, i-1)) {
                    // 1.2 If i-1 is safe, swap i-1
                    swap(nums1[i-1], nums2[i-1]);
                    ++swapTable[i-1];
                }else if (isSafe(nums1, nums2, i)){
                    // 1.3 If i is safe, swap i
                    swap(nums1[i], nums2[i]);
                    ++swapTable[i];
                }else{
                    // 1.4 If i and i-1 are not safe, find left and right boundaries that have a max number of continuous dangerous indexes.
                    int jl = i-1; // left boundary
                    int jr = i; // right boundary
                    while (!isSafe(nums1, nums2, --jl) && jl > 0) {}
                    while (!isSafe(nums1, nums2, ++jr) && jr < size) {}
                    
                    if (left < right) {
                        for (int j=i-1; j>jl; --j) {
                            swap(nums1[j], nums2[j]);
                            ++swapTable[j];
                        }
                    }else{
                        for (; i<jr; ++i) {
                            swap(nums1[i], nums2[i]);
                            ++swapTable[i];
                        }
                    }
                }
            }
        }
    }
    
    // 2. Count the number of swap
    return countSwap(swapTable);
}

// Dynamic programing
int minSwap2(vector<int>& A, vector<int>& B) {
    int N = A.size();
    vector<int> notSwap(N, 0);
    vector<int> swap(N, 1);
    for (int i = 1; i < N; ++i) {
        notSwap[i] = swap[i] = N;
        if (A[i - 1] < A[i] && B[i - 1] < B[i]) {
            swap[i] = swap[i - 1] + 1;
            notSwap[i] = notSwap[i - 1];
        }
        cout << endl;
        if (A[i - 1] < B[i] && B[i - 1] < A[i]) {
            swap[i] = min(swap[i], notSwap[i - 1] + 1);
            notSwap[i] = min(notSwap[i], swap[i - 1]);
        }
    }
    return min(swap[N - 1], notSwap[N - 1]);
}


int main(int argc, const char * argv[]) {
    vector<int> a, b;
    
    a = {2,1,6,7,8,13,15,11,18,13,20,24,17,28,22,23,36,37,39,34,43,38,48,41,46,48,49,50,56,55,59,60,62,64,66,75,69,70,71,74,87,78,95,97,81,99,85,101,90,91,93,95,107,109,101,111,106,114,115,117,118,115,121,122,123,124,125,126,134,131,133,136,142,149,151,152,145,156,158,150,162,159,161,165,169,170,169,174,172,176,177,181,183,192,186,188,189,196,198,200};
    b = {0,4,10,11,12,9,10,16,12,19,15,16,25,20,33,34,27,29,32,40,35,45,40,50,51,52,53,55,52,58,58,61,62,66,71,68,78,81,83,84,75,91,79,80,98,83,100,89,102,103,105,106,96,98,110,105,113,109,110,111,112,120,116,118,126,130,131,133,129,137,138,140,137,138,140,142,154,147,149,159,152,163,164,163,166,168,171,170,175,176,177,181,186,184,193,194,195,190,195,200};
    cout << minSwap1(a, b) << endl; // 45
    cout << minSwap2(a, b) << endl; // 43
    
    a = {0,3,4,5,9,10,13,16,19,24,22,24,28,28,31,32,33,34,36,38};
    b = {0,2,4,11,13,16,17,19,23,20,25,26,27,30,30,31,33,36,37,38};
    cout << minSwap1(a, b) << endl; // 2

    
    a = {0,7,8,10,10};
    b = {4,4,5,7,11};
    cout << minSwap2(a, b) << endl; // 4
    
    a = {0,7,8,10,10,11,12,13,19,18};
    b = {4,4,5,7,11,14,15,16,17,20};
    cout << minSwap2(a, b) << endl; // 4

    a = {2,1,6,9,10,13,13,16,19,26,23,24,25,27,32,31,35,36,37,39};
    b = {0,5,8,8,10,12,14,15,22,22,28,29,30,31,30,33,33,36,37,38};
    cout << minSwap1(a, b) << endl; // 6

    a = {0,3,4,9,10};
    b = {2,3,7,5,6};
    cout << minSwap1(a, b) << endl; // 1 [2]

    a = {3,3,8,9,10};
    b = {1,7,4,6,8};
    cout << minSwap1(a, b) << endl; // 1 [1]

    a = {0,4,4,5,9};
    b = {0,1,6,8,10};
    cout << minSwap1(a, b) << endl; // 1 [1]

    a = {1,3,5,4};
    b = {1,2,3,7};
    cout << minSwap1(a, b) << endl; // 1 [3]

    a = {0,3,5,8,9};
    b = {2,1,4,6,9};
    cout << minSwap1(a, b) << endl; // 1 [1]
    
    return 0;
}
