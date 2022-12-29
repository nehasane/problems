/*
    let dp[l][r] be the minimum number of moves required to destroy
    all the stones in the range l..r.
    
    if two stones on the extremes of the range are the same color,
    then we can remove those in a single move. the dp equation
    for this is: dp[l][r] = dp[l+1][r-1]
    it might seem like it should be dp[l+1][r-1] + 1, where the
    additional 1 is because we need one more move to destroy these
    2 stones, but according to the implementation, the sequence will 
    eventually reduce down to a single (or two) stones where the move
    will be counted. 
    
    if the two stones on the extremes of the range are not the same,
    then we must divide the range into 2, solve each separately and
    then combine the 2 answers.
    for all m from l <= m < r:
    dp[l][r] = dp[l][m] + dp[m+1][r]
    dp[l][r] is the min over all m
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 500 + 1;
int dp[MAX_N][MAX_N];
bool ready[MAX_N][MAX_N];
int nums[MAX_N];
int solve(int l, int r) {
    if (l == r)
        return 1;
    else if (l+1 == r) {
        if (nums[l] == nums[r])
            return 1;
        return 2;
    }
    if (ready[l][r])
        return dp[l][r];
    int ans = r - l + 1;
    if (nums[l] == nums[r])
        ans = min(ans, solve(l+1, r-1));
    for (int m = l; m < r; m++)
        ans = min(ans, solve(l, m) + solve(m+1, r));
    ready[l][r] = true;
    dp[l][r] = ans;
    return ans;
}
int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> nums[i];
    cout << solve(1, N) << '\n';
}
