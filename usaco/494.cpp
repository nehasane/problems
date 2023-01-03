/*
    say we only have to build a stack of two cows:
    there are only two possible safety values, which
    we can calculate with  1 line brute force code.
    
    let dp[mask] hold three values: the height, weight
    and highest safety of the cows in the stack 
    represented by the mask. iterate over all the masks.
    then iterate over all the cows in the maks. we can
    use two masks that will make up the original mask: 
    one mask containing only the single cow that we are 
    looping over right now, and the mask that excludes 
    this cow. we can treat each of these masks as two 
    "cows" and apply the same brute force logic
    described above. for each combination of "cows" that
    we get, calculate its height and safety and take
    the max safety over all.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX_N = 20;
const int MAX_MASK = (1 << MAX_N);
struct cow {
    ll h, w, strength;
};
struct mask {
    ll h, w, safety;
};
mask dp[MAX_MASK];

cow cows[MAX_N];
int main() {
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);
    int N;
    ll H;
    cin >> N >> H;
    for (int i = 0; i < N; i++)
        cin >> cows[i].h >> cows[i].w >> cows[i].strength;
    ll ans = 0;
    dp[0].safety = INT_MAX;
    dp[0].h = dp[0].w = 0;
    for (int i = 1; i < (1 << N); i++) {
        mask tp;
        tp.safety = INT_MIN;
        tp.h = tp.w = 0;
        for (int j = 0; j < N; j++) {
            if (i & (1 << j)) {
                int mask2 = i ^ (1 << j);
                tp.h = cows[j].h + dp[mask2].h;
                tp.w = cows[j].w + dp[mask2].w;
                // cow j is in subset
                // exclude it
                ll safety = max(min(cows[j].strength, dp[mask2].safety - cows[j].w), 
                    min(dp[mask2].safety, cows[j].strength - dp[mask2].w));
                tp.safety = max(tp.safety, safety);
                if (tp.h >= H)
                    ans = max(ans, safety);
            }
        }
        dp[i] = tp;
    }
    if (ans == 0)
        cout << "Mark is too tall";
    else
        cout << ans;
}
