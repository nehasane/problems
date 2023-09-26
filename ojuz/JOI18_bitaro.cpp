/*
    in this problem we need to find the longest path possible to go from an unblocked
    node to node t.

    there are two ways of solving this problem: we can precompute all the longest paths
    that end at some node x for all nodes, however this would take O(NM) memory, which is
    far too much. the second way of solving this is to compute dp[x] for all nodes x 
    where dp[x] is the length of the longest path that ends at node x; this would take 
    O(N) time and memory to compute, and if we had to do this for query, it would TLE.

    instead, we use both these approaches. you queries with y < sqrt(n) we use the first method.
    we can use this since it is possible for us to precompute sqrt(n) longest paths for every 
    node in the graph. answering each of these queries would take O(sqrt(n)) and overall it would
    take O(N * sqrt(n)). for queries where y > sqrt(n), we use the second method. this will also
    work in time, since the maximum number of such queries is sqrt(n) (N / sqrt(N) = sqrt(N), look
    at the limits of Y1 + Y2 + Y3....)

    Overall, the time complexity of this solution is O(Nsqrt(N)), which is fast enough to run.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1e5 + 1;
const int sqn = 320;
vector <int> adjr[maxn];
vector <int> dis, curr, vis, dp, blocked;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, Q;
    cin >> n >> m >> Q;
    blocked = dis = vis = dp = vector <int> (n+1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adjr[b].push_back(a);
    }
    vector <vector <pair <int, int>>> longest_paths(n+1);
    for (int i = 1; i <= n; i++) {
        longest_paths[i].push_back({0, i});
        curr.clear();
        for (auto j : adjr[i]) {
            for (auto x : longest_paths[j]) {
                if (vis[x.second] == i)
                    dis[x.second] = max(dis[x.second], x.first + 1);
                else {
                    dis[x.second] = x.first + 1;
                    vis[x.second] = i;
                    curr.push_back(x.second);
                }
            }
        } 
        for (auto j : curr)
            longest_paths[i].push_back({dis[j], j});
        sort(longest_paths[i].begin(), longest_paths[i].end(), greater <pair <int, int>> ());
        if (longest_paths[i].size() > sqn)  
            longest_paths[i].erase(longest_paths[i].begin() + sqn, longest_paths[i].end());
    }
    for (int q = 1; q <= Q; q++) {
        int t, y;
        cin >> t >> y;
        for (int i = 0; i < y; i++) {
            int x;
            cin >> x;
            blocked[x] = q;
        }
        if (y < sqn) {
            int ans = -1;
            for (auto i : longest_paths[t]) {
                if (blocked[i.second] != q) {
                    ans = i.first;
                    break;
                }
            }
            cout << ans << '\n';
        } else {
            fill(dp.begin(), dp.end(), -1);
            for (int i = 1; i <= n; i++) {
                if (blocked[i] != q)
                    dp[i] = 0;
                for (auto j : adjr[i]) {
                    if (dp[j] != -1)
                        dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            cout << dp[t] << '\n';
        }
    }
    
}
