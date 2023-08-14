#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 100 + 1;
const int maxh = 1000 + 1;
const int mod = 1e9 + 7;
int nums[maxn];
int dp[maxn][maxh];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    int hmin = *min_element(nums + 1, nums + n + 1);
    int hmax = *max_element(nums + 1, nums + n + 1);
    if (n % 2 == 0) {
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= nums[i]; j++) {
                for (int x = 0; x + j <= nums[i]; x++) {
                    dp[i][j] += dp[i-1][x];
                    dp[i][j] %= mod;
                }
            }
        }
        cout << dp[n][0] << '\n';
    } else {
        int ans = 0;
        for (int x = hmin; x >= 0; x--) {
            for (int i = 1; i <= n; i++)
                nums[i] -= x;
            dp[0][0] = 1;
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= nums[i]; j++) {
                    dp[i][j] = 0;
                    for (int y = 0; y + j <= nums[i]; y++) {
                        dp[i][j] += dp[i-1][y];
                        dp[i][j] %= mod;
                    }
                }
            }

            ans += dp[n][0];
            ans %= mod;

            for (int i = 1; i <= n; i++)
                nums[i] += x;
        }
        cout << ans << '\n';
    }
}
