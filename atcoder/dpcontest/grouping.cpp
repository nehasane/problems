/*
    n <= 16, so OBVIOUSLY we need to incorporate bitmasking in some way
    or the other.
    
    consider a mask, where each of the one bits show that rabbit[i] is
    being considered. 
    
    first, put all the rabbits in the mask in one group, and calculate the 
    cost. this is the base case for dp[mask].
    
    a submask is a mask where all the elements in the mask are in the ogmask,
    but not elements in the ogmask are in the submask.
    
    consider two submasks such that when the OR operator is performed on the
    two, the resultant mask is the same as the og mask. lets consider each of
    these submasks as different groups. the total score of these would be 
    the sum of the two dp values represented by these submasks.
    
    consider all the submasks and take the maximum value over all pairs.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX_N = 16;
const int MAX_MASK = (1 << 16);
int N;
ll pts[16][16];
ll dp[MAX_MASK];
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cin >> pts[i][j];
    }
    for (int mask = 1; mask < (1 << N); mask++) {
        for (int j = 0; j < N; j++) {
            if (!((1 << j) & mask))
                continue;
            for (int k = j+1; k < N; k++) {
                if (!((1 << k) & mask))
                    continue;
                dp[mask] += pts[j][k];
            }
        }
        for (int s = mask; s != 0; s = (s-1)&mask) {
            dp[mask] = max(dp[mask], dp[s] + dp[mask ^ s]);
        }
    }
    cout << dp[(1 << N) - 1] << '\n';
}
