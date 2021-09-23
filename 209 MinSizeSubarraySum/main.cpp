//
//  main.cpp
//  209 MinSizeSubarraySum
//
//  Created by Aaron on 2021/9/22.
//

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Sliding window method
int minSubArrayLen(int target, vector<int>& nums) {
    int size = numeric_limits<int>::max();
    int pre = 0,rear = 0, sum = 0;
    
    for ( ; rear < nums.size(); ++rear) {
        sum += nums[rear];
        if (sum >= target) {
            while (sum - nums[pre] > target || sum - nums[pre] ==  target) {
                sum -= nums[pre++];
            }
            size = min(size, rear - pre + 1);
        }
    }
    
    return size == numeric_limits<int>::max() ? 0 : size;
}

int main(int argc, const char * argv[]) {
    int target;
    vector<int> nums;
    
    target = 7;
    nums = {2,3,1,2,4,3};
    cout << minSubArrayLen(target, nums) << endl; // 2 {4,3}

    target = 4;
    nums = {1,4,4};
    cout << minSubArrayLen(target, nums) << endl; // 1 {4}
    
    target = 11;
    nums = {1,2,3,4,5};
    cout << minSubArrayLen(target, nums) << endl; // 3 {3,4,5}
    
    return 0;
}
