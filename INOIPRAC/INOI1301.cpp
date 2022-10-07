/*
this one was pretty simple and straightforward.
have two dp arrays: dp_forward and dp_back
dp_forward[i] = maxmimum possible score if a player goes --forward-- from position K (value included) and lands on position i (value included)
dp_back[i] = maximum possible score if a player goes --backward-- from position i (value included) and lands on position 1 (value included)

dp_forward[i] and dp_backward[i] are calculated in a similar way:
  dp[i] = max(dp[i-1], dp[i-2]) + value[i]
  
the only differences between the two are the base cases and starting points
for dp_forward:
    dp_forward[K] = dp_forward[K-1] = 0, since the value at position K isn't included and all values before K are not reachable since you're going --forward--
    starting point = K
for dp_back:
    dp_back[1] = value[1];
    dp_back[2] = value[1] + value[2];
    starting point = 1
to find the final answer, treat each position from K to N (let this be i) as the ending position of the forward phase. the answer for this is
    cost from K -> i + cost from i -> 1 - value[i]
    - the "- value[i]" is there because while calculating both dp values, you're assuming that you're going to include that value at the ending position, so you're
    double counting that ending position (i)
  ans = max(ans, dp_forward[i] + dp_back[1] - value[i])


*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e6 + 1;
int dp_forward[MAX_N];
int dp_back[MAX_N];
int vals[MAX_N];
int main() {
    int N, K;
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> vals[i];
    fill(dp_forward, dp_forward + N + 1, -1e9);
    fill(dp_back, dp_back + N + 1, -1e9);
    dp_forward[K] = dp_forward[K-1] = 0;
    for (int i = K+1; i <= N; i++)
        dp_forward[i] = max(dp_forward[i-1], dp_forward[i-2]) + vals[i];
    dp_back[1] = vals[1];
    dp_back[2] = vals[1] + vals[2];
    for (int i = 3; i <= N; i++)
        dp_back[i] = max(dp_back[i-1], dp_back[i-2]) + vals[i];
    int ans = INT_MIN;
    for (int i = K; i <= N; i++)
        ans = max(ans, dp_forward[i] + dp_back[i] - vals[i]);
    cout << ans << '\n';
}
