/*
    the answer to this question is the way to approach this problem:
    if you had to consider a small range of slimes, what would be the
    minimum cost?
    
    consider a range of slimes from l to r. break the range into 2 parts
    such that we merge all the slimes on the left into one slime, and
    all the slimes on the right into one slime, and then merge those 2
    together.
    
    to know the cost of merging two slimes, we need to know 2 things: the
    cost of making each of the individual slimes, and the current size of
    each of the slimes (for that reason my solve() returns a struct 
    subproblem that returns these two values). 
    
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
struct subproblem {
    ll cost, size;
    bool operator< (const subproblem& x) const{
        if (x.cost == cost)
            return size < x.size;
        return cost < x.cost;
    }
};
const int MAX_N = 400;
ll slimes[MAX_N];
subproblem dp[MAX_N][MAX_N];
bool ready[MAX_N][MAX_N];
 
subproblem solve(int l, int r) {
    if (l == r) {
        subproblem tp;
        tp.cost = 0;
        tp.size = slimes[l];
        return tp;
    }
    if (ready[l][r])
        return dp[l][r];
    subproblem ans;
    ans.cost = 1e18;
    ans.size = 1e18;
    for (int i = l; i + 1 <= r; i++) {
        subproblem lc = solve(l, i);
        subproblem rc = solve(i+1, r);
        subproblem megaslime = {lc.cost + rc.cost + lc.size + rc.size, lc.size + rc.size};
        ans = min(ans, megaslime);
    } 
    dp[l][r] = ans;
    ready[l][r] = true;
    return ans;
}
int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> slimes[i];
    cout << solve(0, N-1).cost << '\n';
}
