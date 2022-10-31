/*
    this code below will solve subtasks 1 and 2.
    observe that it's always optimal to keep on buying horses until some day i, and then sell all the horses
    on day i+1. why? just intuition that works (proven by AC)
    
    let's first determine which day to sell all the horses bought thus far and once we have found this, we can
    multiply all the horses till this day and then sell them all at once.
    this solution has a time complexity of O(NM), which is enough for subtasks 1 and 2
    
    
    
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

/* 
    for subtask 3, here's a crucial observation: since the number of horses must at least double, the largest 
    number of horses that can be sold on any day is guaranteed to be greater than the number of horses that could
    have been sold on the previous day.
    since the number of horses at least doubles, the answer will be amongst the last 30 days (since 2^30 is 
    approximately 10^9, which is the largest value of X[i] is 10^9
    
    
*/
// subtasks 1, 3
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int init(int N, int X[], int Y[]);
int updateX(int pos, int val);
int updateY(int pos, int val);
int solve(bool recalculate, int new_val, int og_val);
ll mod_div(int base, int exp);

const int MOD = 1e9 + 7;
const int MAX_N = 5 * 1e5 + 1;
int gblX[MAX_N], gblY[MAX_N], gblN;
ll modX = 1;
ll mod_div(int base, int exp) {
    if (exp == 0)   
        return 1;
    long long tp = mod_div(base, exp / 2);
    ll ans = (tp * tp) % MOD;
    if (exp % 2 == 1)
        ans = (ans * base) % MOD;
    return ans;
}
int solve(bool recalculate, int new_val, int og_val) {
    if (recalculate) {
        modX = (modX * new_val) % MOD;
        modX = (modX * mod_div(og_val, MOD - 2)) % MOD;
    }
    ll dp = 1;
    int selling_day = max(0, gblN - 30);
    for (int j = max(0, gblN - 30); j < gblN; j++) {
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
    ll ans = modX;
    for (int i = max(0, gblN - 30); i <= selling_day; i++)
        ans = (ans * gblX[i]) % MOD;
    ans = (ans * gblY[selling_day]) % MOD;
    return (int)ans;
}
int init(int N, int X[], int Y[]) {
    gblN = N;
    for (int i = 0; i < N; i++) {
        gblX[i] = X[i];
        if (i < max(0, N - 30))
            modX = (modX * gblX[i]) % MOD;
        gblY[i] = Y[i];
    }

    return solve(false, 0, 0);
}
int updateX(int pos, int val) {
    int og = gblX[pos];
    gblX[pos] = val;
    if (pos < max(0, gblN - 30))
        return solve(true, val, og);
    else
        return solve(false, val, og);
}
int updateY (int pos, int val) {
    gblY[pos] = val;
    return solve(false, 0, 0);
}
