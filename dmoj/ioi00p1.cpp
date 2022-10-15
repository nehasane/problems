/*

without the memory constraints, the problem is quite simple to solve (v1):
    loop over each character S[i] from 0 TO n-1 and treat it as either the
    middle of the palindrome or the left of the two middle elements of the
    palindrome. then, have a left and right pointer: if the two characters
    pointed by the pointers are the same, then there's no need to add an 
    extra character. otherwuse, we need to add either an extra S[l] character,
    or an extra S[r] character.
    
    basically,
        dp[l][r] = minimum number of characters that need to be added if we
        consider the string S[l...r]
    implementing this using tabular or recursive dp will reult in MLE.
    memory = (5000 * 5000 * 4 * 2) / (1024 * 1024) ~~ 96 MB
    
    instead, think of this as an LCS problem.
    have two strings: S and Sr, where S is the original string and Sr is
    the reverse of S. Let's find the length of the LCS of the two strings.
    the LCS will tell us number of characters that don't need to be added,
    because if a character is common between a string and its reverse, then
    we know that that character is already paired up, and that it will read 
    the same left to right.
    
    a typical implementation will also run in MLE, but there's a neat trick for
    that (v2)
        the dp formula for calulating length of LCS where i is the index of the
        ith character of the first string, and j is the index of the jth 
        character of the second string.
        if (S[i] == Sr[j])
            dp[i][j] = dp[i-1][j-1] + 1;
        else
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        notice that in any case we are only accessing the previous row (or column)
        so we use only two rows in our dp table, where one row contains the dp
        values for the previous i, while the second row contains the dp values for
        the current i. we can alternate between the two rows.
        
        so the dp table will look like this: dp[2][MAX_COLUMN]
        and the dp formula like this
            if (S[i] == Sr[j])
                dp[curr_row][j] = dp[prev_row][j] + 1;
            else
                dp[curr_row][j] = dp[prev_row][j], dp[i][j-1];
                
     NOTE: in v2's implementation, i have added a dummy character at the start of 
     S and Sr, just so that the strings will be 1-indexed.
        

*/
// v1
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
// v2
#include <bits/stdc++.h>
using namespace std;
int N;
string S, Sr;
const int MAX_N = 5001;
int dp[2][MAX_N];
int main() {
    cin >> N >> S;
    Sr = S;
    reverse(Sr.begin(), Sr.end());
    S.insert(0, "0");
    Sr.insert(0, "0");
    int curr = 1, prev = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (S[i] == Sr[j])
                dp[curr][j] = dp[prev][j-1] + 1;
            else
                dp[curr][j] = max(dp[prev][j], dp[curr][j-1]);
        }
        swap(curr, prev);
    }
    cout << N - dp[prev][N] << '\n';
}
