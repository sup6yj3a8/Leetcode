//
//  main.cpp
//  001 TwoSum
//
//  Created by Aaron on 2021/6/28.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    // Copy
    vector<int*> numsP;
    for (int i=0; i<nums.size(); ++i){numsP.push_back(&nums[i]);}
    
    // Sort
    sort(numsP.begin(), numsP.end(), [](int *a, int *b){return *a<*b;});
    
    // Sum
    int *n1 = nullptr;
    int *n2 = nullptr;
    int remain;
    for (int i=0; i<numsP.size(); ++i){
        n1 = numsP[i];
        remain = target - *n1; // Reset remain
        for (int j=i+1; j<numsP.size(); ++j){
            if (remain == *numsP[j]){
                n2 = numsP[j];
                return vector<int> {static_cast<int>(n1 - &nums[0]), static_cast<int>(n2 - &nums[0])};
            }
        }
    }
    return vector<int> ();
}

int main() {
    vector<int> a {2,7,11,15};
    int t = 9;
    vector<int> b = twoSum(a, t);
    for (auto i : b) {
        cout << i << " ";
    }
    
    return 0;
}

