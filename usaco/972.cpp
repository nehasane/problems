// O (2^m * m)
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;
using ll = long long;
vector <ll> rng_mask, w;
int main() {
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
    // freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    w.resize(m);
    rng_mask.resize(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> w[i] >> l >> r;
        for (int j = l; j <= r; j++)
            rng_mask[i] += ((ll)1 << j);
    }
    ll ans = 0;
    vector <pair <ll, ll>> dp(1 << m);
    for (int s = 1; s < (1 << m); s++) {
        for (int b = 0; b < m; b++) {
            if (!(s & (1 << b)))
                continue;
            int excl = s ^ (1 << b);
            ll occ = dp[excl].second;
            ll combined = (occ | rng_mask[b]);
            if (combined != occ) {
                pair <ll, ll> tp = {dp[excl].first + w[b], combined};
                dp[s] = max(dp[s], tp);
            }
        }
        ans = max(ans, dp[s].first);
    }
    cout << ans << '\n';
}
