/*
    this problem requires straightforward complete search using recusrion, with some simple memoization (aka dp).
    have a recursive function (since complete search is easier to implement with recursion).
    assign a mission to each bond, so long as each mission is assigned to exactly on Jimmy Bond. Without memoization, this
    will exceed time limit. Notice that N <= 20. we can keep track of the number of missions that have been completed using an integer. for example,
    if the ith mission has been completed, set the ith bit of the integer to 1 (true).
  */
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 20;
const int MAX_VIS = (1 << 20);
int N;
double probs[MAX_N][MAX_N];
double dp[MAX_VIS];
bool ready[MAX_VIS];
double solve(int vis) {
    if (__builtin_popcount(vis) == N)
        return 1;
    if (ready[vis])
        return dp[vis];
    double ans = 0;
    for (int j = 0; j < N; j++) {
        if (!(vis & (1 << j))) {
            int i = __builtin_popcount(vis);
            int og_vis = vis;
            vis |= (1 << j);
            ans = max(ans, solve(vis) * (probs[i][j] / (double)100));
            vis = og_vis;
        }
    }
    dp[vis] = ans;
    ready[vis] = true;
    return ans;
}
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cin >> probs[i][j];
    }
    cout << fixed << setprecision(6) << (double)(solve(0) * 100) << '\n';
}
