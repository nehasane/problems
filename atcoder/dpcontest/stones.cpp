/*
    let DP[x] be 0 if the first person can win when the height of the
    tower is x, and 1 if the first cannot win when the height of the
    tower is x.
    
    if the height of a tower is 0, then the first player cannot win,
    so DP[0] = 1
    
    loop over every value in set A. when we play that value, the height of
    the tower decreases by A[i]. if after playing that stone the tower 
    height becomes such that the second player wins, then that means the
    the first player can win.
    
    
*/
#include <bits/stdc++.h>
using namespace std;
int N, K;
const int MAX_K = 1e5 + 1;
const int MAX_N = 100;
 
int nums[MAX_N];
bool dp[MAX_K];
int main() {
    cin >> N >> K;
    for (int i = 0; i < N; i++)
        cin >> nums[i];
    dp[0] = 1;
    for (int k = 1; k <= K; k++) {
        dp[k] = 1;
        for (int i = 0; i < N; i++) {
            if (nums[i] <= k && dp[k - nums[i]] == 1)
                dp[k] = 0;
        }
    }
    if (dp[K] == 0)
        cout << "First\n";
    else
        cout << "Second\n";
}
