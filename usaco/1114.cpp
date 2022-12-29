/*
    similar yet different problem: https://codeforces.com/problemset/problem/607/B
    let dp[l][r] be the minimum number of strokes required to paint the range
    l..r
    
    intuitively, you might do something like this:
        if (color[l] == color[r])
            dp[l][r] = dp[l+1][r-1] + 1;
        for l <= m < r  
            dp[l][r] = min(dp[l][r], dp[l][m] + dp[m+1][r])
    but this won't work for the following test case:
        5
        12221
        the program would output 3 when the real answer is 2
        
    this problem arises becuase we are trying to find ways to ADD moves to the
    answer of a range. instead, try REMOVING moves.
    
    if we had to separate a range into 2 and paint each a different color ('cause
    it doesn't make sense to paint two adjacent ranges the same color and
    unecessarily waste an extra move when we could've just consider the whole
    range as one), the dp equation would look like this:
    for all l <= m < r:
        dp[l][r] = min(dp[l][m] + dp[m+1][r])
    but if the leftmost value of the left range and the rightmost value of the
    right range are the same color, then we could want to paint the whole
    range the same color and then deal with the two smaller ranges separately.
    here, instead of taking two moves to paint the underlying color of both,
    we only take one. so we can subtract 1 from the answer to the sum of the
    two smaller ranges (excluding the two extremes)
    
    if (color[l] == color[r])
        dp[l][r] = min(dp[l][r], dp[l+1][m] + dp[m+1][r-1] - 1
    
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 300;
int nums[MAX_N];
int dp[MAX_N][MAX_N];
bool ready[MAX_N][MAX_N];
int solve(int l, int r) {
    if (l > r)
        return 0;
    if (l == r)
        return 1;
    if (ready[l][r])
        return dp[l][r];
    int ans = INT_MAX;
    for (int i = l; i < r; i++) {
        if (nums[l] == nums[r])
            ans = min(ans, solve(l, i) + solve(i+1, r) - 1);
        else
            ans = min(ans, solve(l, i) + solve(i+1, r));
    }
    ready[l][r] = true;
    dp[l][r] = ans;
    return ans;
}
int main() {
    // freopen("in.txt", "r" ,stdin);
    // freopen("out.txt", "w", stdout);
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> nums[i];
    cout << solve(0, N-1) << '\n';
}
