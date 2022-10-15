#include <bits/stdc++.h>
using namespace std;
int N;
string S;
const int MAX_N = 5000;
int dp[MAX_N][MAX_N];
bool ready[MAX_N][MAX_N];
int solve(int l, int r) {
    if (l < 0)
        return N - r;
    if (r == N)
        return l+1;
    if (ready[l][r])
        return dp[l][r];
    int ans = 1e9;
    if (S[l] == S[r])
        ans = solve(l-1, r+1);
    else
        ans = min(solve(l, r+1), solve(l-1, r)) + 1;
    ready[l][r] = true;
    dp[l][r] = ans;
    return ans;
}
int main() {
    cin >> N >> S;
    int ans = INT_MAX;
    for (int i = 0; i < N; i++) {
        ans = min({ans, solve(i-1, i+1), solve(i, i+1)});
    }
    cout << ans << '\n';
}
