/*
    this code below will solve subtasks 1 and 2.
    observe that it's always optimal to keep on buying horses until some day i, and then sell all the horses
    on day i+1. why? just intuition that works (proven by AC)
    
    let's first determine which day to sell all the horses bought thus far and once we have found this, we can
    multiply all the horses till this day and then sell them all at once.
    
    
*/

// subtasks 1 and 2
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int init(int N, int X[], int Y[]);
int updateX(int pos, int val);
int updateY(int pos, int val);
int solve();
const int MOD = 1e9 + 7;
const int MAX_N = 1000 + 1;
int gblX[MAX_N], gblY[MAX_N], gblN;


int solve() {
    int selling_day = 0;
    ll dp = 1;
    for (int j = 1; j < gblN; j++) {
        if (dp * gblX[j] > gblY[selling_day]) {
            selling_day = j;
            dp = 1;
        } else if (dp * gblX[j] * gblY[j] > gblY[selling_day]) {
            selling_day = j;
            dp = 1;
        } else {
            dp = (dp * gblX[j]) % MOD;
        }
    }
    long long ans = 1;
    for (int i = 0; i <= selling_day; i++)
        ans = (ans * gblX[i]) % MOD;
    ans = (ans * gblY[selling_day]) % MOD;
    return (int)ans;
}
int init(int N, int X[], int Y[]) {
    gblN = N;
    for (int i = 0; i < N; i++) {
        gblX[i] = X[i];
        gblY[i] = Y[i];
    }

    return solve();
}
int updateX(int pos, int val) {
    gblX[pos] = val;
    return solve();
}
int updateY (int pos, int val) {
    gblY[pos] = val;
    return solve();
}
