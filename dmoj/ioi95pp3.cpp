/*

this was a good problem

first, of all solve this: if we had a barcode of length n, and the barcode had to have k bars,
how many possible barcodes can we build?

simple. say you had to have a bar of length i (1 to M) taking up the last i units of the barcode.
then all you have to do is fill first N - i units using K - 1 units.
for all i from 1 to M
    dp[n][k] += dp[n - i][k - 1]
 
 next is the hard part: figuring out the rank of the barcode.
 right of the bat, it may seem like you need to binary search on the rank of the barcode, since they
 are all sorted lexicographically, but that's not going to work (mainly because i couldn't think of
 way to do it).
 
instead, try find out the number of barcodes that have a lower rank (come after the barcode in the
sorted list).

loop through the bars in the barcode.
    if the bar consists of 1s, then any barcodes that contain a bar of 1s with a length greater than
    the length of the current bar that also starts at the same position as the current bar in the
    barcode, then we know that they will be ranked lower than the queried barcode. In this case, we
    can eliminate all those bars.
    
    if the bar consists of 0s, then any barcodes than contains a bar of 0s with a length less than
    the length of the current bar that also starts at the same position as the current bar in the
    barcodes, then we know that they will be ranked lower than the queried barcode. In this case, we
    can eliminate all those bars too.
    
    eventually you will have eliminated all the bars with a lower rank you possibly can.

*/
#include <bits/stdc++.h>
using namespace std;
int N, K, M, Q;
const int MAX_N_K_M = 33;
int dp[MAX_N_K_M][MAX_N_K_M];
bool ready[MAX_N_K_M][MAX_N_K_M];
int solve(int n, int k) {
    if (n <= 0)
        return 0;
    if (k == 1) {
        if (n <= M) {
            dp[n][k] = 1;
            ready[n][k] = true;
            return 1;
        }
        return 0;
    }
    if (ready[n][k])
        return dp[n][k];
    int ans = 0;
    for (int i = 1; i <= M; i++) {
        ans += solve(n-i, k-1);
    }
    dp[n][k] = ans;
    ready[n][k] = true;
    return ans;
}
int main() {
    cin >> N >> K >> M >> Q;
    int lowest_rank = solve(N, K);
    cout << lowest_rank << '\n';
    while (Q--) {
        string s;
        cin >> s;
        int bar_len = 1, bars = 1;
        int rank = lowest_rank;
        for (int i = 1; i < N; i++) {
            if (s[i] == s[i-1])
                bar_len++;
            else {
                if (s[i-1] == '1') {
                    for (int j = 1; j <= M - bar_len && N - i - j >= 1 && K - bars >= 1; j++)
                        rank -= dp[N - i - j][K - bars];
                    bars++;
                    bar_len = 1;
                } else {
                    for (int j = 1; j < bar_len && N - i + j >= 1 && K - bars >= 1; j++)
                        rank -= dp[N - i + j][K - bars];
                    bars++;
                    bar_len = 1;
                }
            }
        }
        cout << rank - 1 << '\n';
    }
}
