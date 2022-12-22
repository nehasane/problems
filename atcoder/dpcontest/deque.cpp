/*
    since taro wants to increase the difference between his and jiro's scores,
    he'll want to maximise his own score to get it as far from jiro's as possible.
    since jiro wants to minimise the difference between her's and taro's scores,
    she'll want to maximise her score to get it as close to taro's as possible.
    
    in any case, we must find the maximum score possible. so consider a range(l, r)
    where we can choose to pick either the left value, or the right value. if we
    pck the left value, then any other points we can get must come from the
    range (l+1, r). at the same time, the other player must pick from the same range,
    so we subtract whatever score they get from the total score of the range (l+1, r).
    a similar logic follows if we pick the rightmost number of the range right now
    
    this yields the DP equation:
    DP[l][r] = max(nums[l] + score[l+1, r] - solve(l+1, r),
                  nums[r] + score[l, r-1] - solve(l, r-1));
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
const int MAX_N = 3000 + 1;
ll nums[MAX_N];
ll pfx[MAX_N];
ll dp[MAX_N][MAX_N];
bool ready[MAX_N][MAX_N];
ll solve(int l, int r) {
    if (l > r)
        return 0;
    if (ready[l][r])
        return dp[l][r];
    ll ans = max(nums[l] + pfx[r] - pfx[l] - solve(l+1, r),
            nums[r] + pfx[r-1] - pfx[l-1] - solve(l, r-1));
    ready[l][r] = true;
    dp[l][r] = ans;
    return ans;
}   
int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin  >> nums[i];
        pfx[i] = nums[i] + pfx[i-1];
    }
    ll X = solve(1, N);
    ll Y = pfx[N] - X;
    cout << X - Y << '\n';
}
