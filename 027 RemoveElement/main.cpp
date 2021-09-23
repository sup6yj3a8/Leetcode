//
//  main.cpp
//  027 RemoveElement
//
//  Created by Aaron on 2021/9/20.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printVec(vector<int> vec) {
    for (const auto v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

int removeElement(vector<int>& nums, int val) {
    int front = 0;
    int rear = 0;
    for ( ; rear < nums.size(); ++rear) {
        if (nums[rear] != val) {
            nums[front++] = nums[rear];
        }
    }
    nums.resize(front);
    return front;
}

int removeElement2(vector<int>& nums, int val) {
    vector<int>::iterator numsEnd = remove(nums.begin(), nums.end(), val);
    nums.resize(numsEnd - nums.begin());
    return nums.size();
}

int main(int argc, const char * argv[]) {
    vector<int> nums;
    int val;
    
    nums = {3,2,2,3};
    val = 3;
    cout << removeElement2(nums, val) << endl; // 2
    printVec(nums); // 2 2
    
    nums = {0,1,2,2,3,0,4,2};
    val = 2;
    cout << removeElement2(nums, val) << endl; // 5
    printVec(nums); // 0 1 3 0 4
    
    nums = {2,2};
    val = 2;
    cout << removeElement2(nums, val) << endl; // 0
    printVec(nums); //
    
    return 0;
}
