//
//  main.cpp
//  704 BinarySearch
//
//  Created by Aaron on 2021/9/17.
//

#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>& nums, int target) {
    int l = 0; // left
    int r = static_cast<int>(nums.size()) - 1; // right
    int m; // middle
    
    while (l <= r) {
        m = (l + r) >> 1; // It is equal (l + r) / 2
        if (target == nums[m]) {
            return m;
        } else if (target < nums[m]) {
            r = m - 1;
        } else { // target > nums[m]
            l = m + 1;
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    vector<int> nums;
    int target;
    
    nums = {-1,0,3,5,9,12};
    target = 9;
    cout << search(nums, target) << endl; // 4
    
    nums = {-1,0,3,5,9,12};
    target = 2;
    cout << search(nums, target) << endl; // -1
    
    return 0;
}
