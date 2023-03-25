/*
    i wrote two soultions to this problem; the first code is the second version,
    from daddy's solution and the second code is mine, that had a crucial bug in it.
    
    the overall idea was this: let dp[s][mask] be the maximum of a path from 0 to s,
    with all the cities covered being described in mask.
    
    in my solution, i structured this as a graph problem and used a dfs to go through
    the cities and add the length of a path whenever it was traversed. my solution
    however also counted journeys that did not reach the end city, so the answer was
    higher than expected. to fix this, i had the dfs return a pair of int and bool,
    where the int was the length of the path and the bool was true if the journey
    reached the end city. (basically, look at my previous submissions where the dfs
    simply returned an int and you'll get it [hopefully]). it took quite a while to 
    catch this bug.
    
    instead, just do the iteratiive simple textbook method of generating masks. for
    each mask, iterate over all the cities in it and for each of those check if any
    of the cities in its adjacency list are there in the mask too. if they are, then
    assume that in the  journey described by the mask, you're from that city to the
    current city. exclude that city from the mask and use the new mask and add the
    length to the dp bitmask.
    
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

vector <vector <pair <int, int>>> adj;
vector <vector <int>> dp;

int main() {
    int n, m;
    cin >> n >> m;
    adj = vector <vector <pair <int, int>>> (n);

    for (int i = 0; i < m; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        adj[b].push_back({a, l});
    }

    dp = vector <vector <int>> (n, vector <int> (1 << n, -1e9));
    dp[0][1] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask & 1))
            continue;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                /*
                    let city j be the last city visited on the tour.
                    loop over its adjacency list and see if any of the
                    cities in its list have already been visited on
                    the tour.
                */
                int mask_excluding_j = mask ^ (1 << j);
                for (auto k : adj[j]) {
                    if (mask & (1 << k.first)) {
                        dp[j][mask] = max(dp[j][mask], dp[k.first][mask_excluding_j] + k.second);
                    }
                }
            }
        }
    }
    
    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (mask & (1 << (n-1)))
            ans = max(ans, dp[n-1][mask]);
    }
    cout << ans << '\n';
}

#include <iostream>
#include <vector>
using namespace std;

vector <vector <bool>> ready;
vector <vector <pair <int, bool>>> dp;

vector <vector <pair <int, int>>> adj;
int n, m;

pair <int, bool> dfs(int s, int mask) {
    if (s == n-1)
        return {0, true};
    if (ready[s][mask])
        return dp[s][mask];
    pair <int, bool> ans = {0, false};
    for (auto i : adj[s]) {
        if (mask & (1 << i.first))
            continue;
        auto res = dfs(i.first, mask | (1 << i.first));
        if (res.second == true) {
            ans.first = max(ans.first, res.first + i.second);
            ans.second = true;
        }
    }
    dp[s][mask] = ans;
    ready[s][mask] = true;
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    
    cin >> n >> m;

    ready = vector <vector <bool>> (n, vector <bool> (1 << (n+1)));
    dp = vector <vector <pair <int, bool>>> (n, vector <pair <int, bool>> (1 << (n+1)));
    adj = vector <vector <pair <int, int>>> (n);

    for (int i = 0; i < m; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        adj[a].push_back({b, l});
    }

    cout << dfs(0, 1).first << '\n';
}
