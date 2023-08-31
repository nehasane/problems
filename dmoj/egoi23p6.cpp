/*
    let dp[i][j][k] be the largest sum you can make if you only make a 
    sum using the first j numbers of the first i numbers and make exactly
    k swaps.

    we have two options for each number i, either swap it out of its current
    position, or dont.

    if we do apply a swap, it makes sense to swap it to the first j numbers so
    that those swaps actually count for something, and to only swap it to the
    jth position, because its position within the first j doesn't matter and
    the jth position will be the closest for us.

    given that, our dp transition looks like this:
    if we swap
      dp[i][j][k] = dp[i-1][j-1][k - (i - j] + nums[i];
    if we dont swap, then we use the k swaps for the first i-1 numbers
      dp[i][j][k] = dp[i-1][j][k];

    dp[i][j][k] is the max of the two possibilties above.
    
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const int maxn = 100 + 1;
ll dp[maxn][maxn][maxn * maxn];
int main() {
    int n, f;
    ll t;
    cin >> n >> f >> t;
    vector <ll> nums(n+1);
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    int ans = 1e9;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int l = 1; l <= j; l++) {
                dp[i][j][0] += nums[l];
            }
            if (j == f && dp[i][j][0] >= t)
                ans = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            for (int k = 1; k <= n * f; k++) {
                // swap the ith element
                if (k - (i - j) >= 0)
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k - (i - j)] + nums[i]);
                // don't swap the ith element
                dp[i][j][k] = max({dp[i][j][k], dp[i-1][j][k], dp[i][j][k-1]});
                if (j == f && dp[i][j][k] >= t)
                    ans = min(ans, k);
            }
        }
    }
    if (ans == 1e9) {
        cout << "NO\n";
        return 0;
    }
    cout << ans << '\n';
}
