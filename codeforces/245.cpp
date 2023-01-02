/*
    overall algorithm is simple and straightforward:
    let dp[l][r] be the number of subtrings of palindromes that
    occur in the range l..r
    
    since we need to go over all substrings, one quick way to
    do this is: solve(l, r) = solve(l+1, r) + solve(l, r-1)
    but at the same time, we are double counting the 
    palindromes in the range (l+1..r-1). so we subtract
    solve(l+1, r-1) from the answer.
    
    we also need to know whether the string[l..r] is a
    palindrome or not.
    one way to do this is to have a simple loop that checks this.
    however this would give us a time complexity of O(N^3),
    which won't pass the time limit.
    
    instead, we have another recursive function which checks whether
    or not a subtring S[l..r] is a palindrome or not.
    S[l..r] can only be a palindrome is S[l] = S[r]. if it is, then
    the answer depends on S[l+1, r-1]. otherwise, S[l..r] can
    never be a palidrome.
    
    this function also has a time complexity of O(N^2). so the overall
    time complexity of the program is O(N^2) for solve() + O(N^2) for
    check_palidrome + Q ofr number of queries.
    
*/
#include <bits/stdc++.h>
using namespace std;
string S;
const int MAX_N = 5000 + 1;
int dp[MAX_N][MAX_N];
bool ready_palin[MAX_N][MAX_N];
bool ready[MAX_N][MAX_N];
bool dp_palin[MAX_N][MAX_N];
bool is_palin(int l, int r) {
    if (l == r)
        return true;
    if (l+1 == r) {
        if (S[l] == S[r])
            return true;
        return false;
    }
    if (ready_palin[l][r])    
        return dp_palin[l][r];
    bool ans = false;
    if (S[l] == S[r])
        ans = is_palin(l+1, r-1);
    ready_palin[l][r] = true;
    dp_palin[l][r] = ans;
    return ans;
}
int solve(int l, int r) {
    if (l > r)
        return 0;
    if (ready[l][r])
        return dp[l][r];
    int ans = is_palin(l, r);
    ans += solve(l+1, r);
    ans += solve(l, r-1);
    ans -= solve(l+1, r-1);
    ready[l][r] = true;
    dp[l][r] = ans;
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> S;
    S.insert(0, "0");
    int Q;
    cin >> Q;
    solve(1, S.size()-1);
    while (Q--) {
        int a, b;
        cin >> a >> b;
        cout << dp[a][b] << '\n';
    }
}
