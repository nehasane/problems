/*

let dp[l][r] be the maximum score a player can get if they choose either value[l] or value[r], where l and r are the left and right endpoints of the range.

when a problem requires game theory + dp, think how your score will be affected by the other player's move. In this case, in order to maximise your score, you need
to minimise the other player's score.

think of this problem like this: if you choose an element from the extremes of the range, then your opponent must choose from the values not chosen from the remaining
range. For example, if you choose value[l], then the opponent has to choose from the remaining l+1 -> r values. So the maximum possible value that your opponent can
get if you choose the left value is dp[l+1][r]. Similarly, if you choose the value[r], then the opponent has to choose from the remaining l -> r-1 values.

i thought of the problem like this: if a player had to take value[l], what is the minimum possible score the other player could be forced to take from the remaining
range, and likwise if the current player chose value[r].

though this idea was correct, my inital implementation was not:
dp[l][r] = max(value[l] + dp[l+1][r], value[r] + dp[l][r-1])

this didn't work because dp[l+1][r] and dp[l][r-1]  were the --opponent's-- score, which means that I shouldn't have been adding them. instead, i should have
subtracted the opponent's score from the total score of that range. this difference is the maximum possible score the current player can get by making the opponent
get the minimum possible score

final dp equation:
dp[l][r] = pfx[r][l-1] - min(dp[l+1][r], dp[l][r-1])

*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 200 + 1;
int vals[MAX_N];
int dp[MAX_N][MAX_N];
bool ready[MAX_N][MAX_N];
int pfx[MAX_N];
int solve(int l, int r) {
    if (l > r)
        return 0;
    if (ready[l][r])
        return dp[l][r];

    int tot_range_score = pfx[r] - pfx[l-1];
    int ans = tot_range_score - min(solve(l+1, r), solve(l, r-1));

    dp[l][r] = ans;
    ready[l][r] = true;
    return ans;
}
int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> vals[i];
        pfx[i] = pfx[i-1] + vals[i];
    }
    int x = solve(1, N);
    cout << x << ' ' << pfx[N] - x << '\n';
}
