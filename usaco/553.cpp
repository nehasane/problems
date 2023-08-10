#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int mod = 1e9 + 7;
int n;
vector <string> grid;
vector <vector <vector <int>>> dp;
int center = 0;
int solve(int r1, int r2, int a) {
    int c1 = n - center - (a - (center - r1)) - 1;
    int c2 = n - abs(center - (a - (r2 - center))) - 1;
    if (grid[r1][c1] != grid[r2][c2])
        return 0;
    if (r1 == 0 && c1 == 0 && r2 == n-1 && c2 == n-1)
        return 1;
    if (dp[r1][r2][a] != -1)
        return dp[r1][r2][a];
    int ans = 0;
    if (r1 > 0 && r2+1 < n) {
        // up down
        ans += solve(r1-1, r2+1, a+1);
        ans %= mod;
    }
    if (r1 > 0 && c2+1 < n) {
        // up right
        ans += solve(r1-1, r2, a+1);
        ans %= mod;
    }
    if (c1-1 >= 0 && r2+1 < n) {
        // left down
        ans += solve(r1, r2+1, a+1);
        ans %= mod;
    }
    if (c1-1 >= 0 && c2+1 < n) {
        // left right
        ans += solve(r1, r2, a+1);
        ans %= mod;
    }
    dp[r1][r2][a] = ans;
    return ans;
}
int main() {
    // freopen("palpath.in", "r", stdin);
    // freopen("palpath.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    grid.resize(n);
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
        for (int j = 0; j < n; j++)
            dp[i][j].resize(n, -1);
    }
    for (int i = 0; i < n; i++)
        cin >> grid[i];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        center = i;
        ans += solve(i, i, 0);
        ans %= mod;
    }
    cout << ans << '\n';



}


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
const int mod = 1e9 + 7;
int n;
vector <string> grid;
vector <vector <unordered_map <int, int>>> dp;
int solve(int r1, int r2, int a) {
    int c1 = (n-1) - a - r1;
    int c2 = n - ((n-1) - a - (n-1-r2)) - 1;
    if (r1 < 0 || r2 < 0 || r1 >= n || r2 >= n || a < 0)
        return 0;
    if (grid[r1][c1] != grid[r2][c2])
        return 0;
    if (r1 == r2 && c1 == c2)
        return 1;
    if (dp[r1][r2].find(a) != dp[r1][r2].end())
        return dp[r1][r2][a];
    int ans = solve(r1, r2, a-1);
    ans = (ans + solve(r1+1, r2, a-1)) % mod;
    ans = (ans + solve(r1+1, r2-1, a-1)) % mod;
    ans = (ans + solve(r1, r2-1, a-1)) % mod;
    dp[r1][r2][a] = ans;
    return ans;

}
int main() {
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    grid.resize(n);
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
    }
    for (int i = 0; i < n; i++)
        cin >> grid[i];
    int ans = solve(0, n-1, n-1);
    cout << ans << '\n';




}
