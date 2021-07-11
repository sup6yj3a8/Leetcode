//
//  main.cpp
//  354 RussianDollEnvelopes
//
//  Created by Aaron on 2021/7/9.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

typedef struct Fit{
    int fit;
    int fitted;
    int maxFit;
} Fit;

int greatrFitted(const unordered_map<int, Fit>::iterator a, const unordered_map<int, Fit>::iterator b){
    return a->second.fitted > b->second.fitted;
}

// Check if a dominates b
int isFit(const vector<int> &a, const vector<int> &b){
    return a[0] > b[0] && a[1] > b[1];
}

// Slower
int maxEnvelopes1(vector<vector<int>>& envelopes) {
    // Ceate  a siez * size fit table
    const int size = envelopes.size();
    vector<vector<int>> fitTable (size, vector<int> (size));
    
    // Check if a dominates b
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            fitTable[i][j] = isFit(envelopes[i], envelopes[j]);
        }
    }
    
    // Calculate fit and fitted value
    unordered_map<int, Fit> fitValue;
    for (int i=0; i<size; ++i) {
        // Initialzation
        fitValue[i] = {0, 0, 0};
        
        // Calculate fit and fitted value
        for (int j=0; j<size; ++j) {
            fitValue[i].fit += fitTable[i][j];
            fitValue[i].fitted += fitTable[j][i];
        }
        
        // Initialization : fit = 0 -> maxFit = 1, fit = 1 -> maxFit = 2.
        if (fitValue[i].fit == 0) {
            fitValue[i].maxFit = 1;
        }else if (fitValue[i].fit == 1) {
            fitValue[i].maxFit = 2;
        }
    }
    
    // Descend fitted order
    vector<unordered_map<int, Fit>::iterator> orderedFitValue;
    for (auto iter = fitValue.begin(); iter != fitValue.end(); ++iter) {
        orderedFitValue.push_back(iter);
    }
    sort(orderedFitValue.begin(), orderedFitValue.end(), greatrFitted);
    
    // Dynamic programing : max fit value
    int currMaxFit = 0;
    for (auto &i : orderedFitValue) {
        // If maxFit = 0, count its maxFit.
        if (i->second.maxFit == 0) {
            for (int j=0; j<size; ++j) {
                if (fitTable[i->first][j] == 1 && fitValue[j].maxFit > i->second.maxFit) {
                    i->second.maxFit = fitValue[j].maxFit;
                }
            }
            ++i->second.maxFit;
        }
        
        // Update current max fit value.
        if (i->second.maxFit > currMaxFit) {currMaxFit = i->second.maxFit;}
    }
    
    return currMaxFit;
}


bool comp(const vector<int>&a,const vector<int>&b){
    return a[0]<b[0];
}
bool comp1(const vector<int>&a,const vector<int>&b){
    return a[1]<b[1];
}

// Faster
int maxEnvelopes2(vector<vector<int>>& envelopes) {
    sort(envelopes.begin(),envelopes.end(),comp);
    sort(envelopes.begin(),envelopes.end(),comp1);
    vector<int>dp(envelopes.size(),1);
    int ans=1;
    for(int i=1;i<envelopes.size();i++){
        int res=0;
        for(int j=i-1;j>=0;j--){
            if(envelopes[j][0]<envelopes[i][0]&&envelopes[j][1]<envelopes[i][1]){
                res=max(res,dp[j]);
            }
        }
        dp[i]=res+1;
        ans=max(ans,dp[i]);
    }
    return ans;
}


int main(int argc, const char * argv[]) {
    vector<vector<int>> dolls = {{5,4},{6,4},{6,7},{2,3}};
    cout << maxEnvelopes1(dolls) << endl;
    
    dolls = {{1,1}, {1,1}, {1,1}};
    cout << maxEnvelopes2(dolls) << endl;
    
    return 0;
}
