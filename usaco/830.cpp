#include <bits/stdc++.h>
using namespace std;
const int MAX_T = 1e3 * 250 + 1;
const int MAX_N = 250;
int dp[MAX_T];
pair <int, int> cows[MAX_N];
int main() {
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    int N, W;
    cin >> N >> W;
    for (int i = 0; i < N; i++)
        cin >> cows[i].first >> cows[i].second;
    fill(dp, dp + MAX_T, 2 * 1e9);
    for (int i = 0; i < N; i++) {
        for (int j = MAX_T - 1; j >= 1; j--)
            dp[j] = min(dp[j], dp[j - cows[i].second] + cows[i].first);
        dp[cows[i].second] = min(dp[cows[i].second], cows[i].first);
    }
    double ans = 0;
    for (int i = 1; i < MAX_T; i++) {
        if (dp[i] >= W)
            ans = max(ans, (double)i / (double)dp[i]);
    }
    ans *= 1000;
    cout << (int)ans << '\n';
    return 0;
}
