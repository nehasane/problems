/*

    problem link: https://oj.uz/problem/view/JOI18_commuter_pass
    algorithm used: graph 

    in this problem, the smallest possible cost of travelling from city U to V
    needs to be computed if roads along the shortest path from city S to T are
    free.

    the obvious approach would be to mark a shortest path from S to T as free and
    then run a dijkstra's to compute the answer. however there could be many
    shortest paths from S to T, so running a dijkstra's for every sp will take
    too long. 

    
    compute distU[] and distV[] which store the shortest distance from U to any node
    and likewise for V.

    think of the answer as travelling from u -> x -> y -> v where the path 
    x -> y in on the shortest path from s -> t. so we need to find a path
    from u -> x and a path from v -> y. let's focus on finding u -> x first.
    let's suppose x is the first node the u visits that is on the shortest path.
    in that case, the cost would be distU[node]. but if x is not the first node that
    u visits that is on the shortest path, but it is on the shortest path, then
    the cost for u is the cost of visiting the parent of x, since the cost of going
    from x's parent to x is free.

    this is how we get the dp equation:
    dpU[node] = min(distU[node], dpU[parent])

    we do the same for calculating dpV[]

    we calculate dpU[] and dpV[] while running a dijkstra's from S so that we can calculate
    the nodes on the shortest path properly. run the dijkstra's from T too. 

    the answer is dpU[end] + dpV[end] for each of the 2 dijkstra runs as the end (which would
    be S or T) is the 
    

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <array>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 1;
vector <pair <int, int>> adj[maxn];
int N, M, S, T, U, V;
vector <ll> distU, distV, dpU, dpV;
void dijkstra1(int st, vector <ll> &dist) {
    priority_queue <pair <ll, int>> pq;
    vector <bool> processed(N+1);
    dist[st] = 0;
    pq.push({0, st});
    while (!pq.empty()) {
        int x = pq.top().second;
        ll d = -pq.top().first;
        pq.pop();
        if (processed[x]) {
            continue;
        }
        processed[x] = true;
        for (auto i : adj[x]) {
            if (dist[x] + i.second < dist[i.first]) {
                dist[i.first] = dist[x] + i.second;
                pq.push({-dist[i.first], i.first});
            }
        }
    }
}
ll ans = 1e16;
void dijkstra2(int st, int ed) {
    priority_queue <array <ll, 3>> pq;
    pq.push({0, st, 0});
    vector <ll> dist(N+1, 1e16);
    dist[st] = 0;
    vector <bool> processed(N+1);
    fill(dpU.begin(), dpU.end(), 1e16);
    fill(dpV.begin(), dpV.end(), 1e16);
    while (!pq.empty()) {
        int a = pq.top()[1], p = pq.top()[2];
        ll d = -pq.top()[0];
        pq.pop();
        if (processed[a]) {
            if (d != dist[a])
                continue;
            ll x = min(distU[a], dpU[p]);
            ll y = min(distV[a], dpV[p]);
            if (x + y <= dpU[a] + dpV[a]) {
                dpU[a] = x;
                dpV[a] = y;
            }
            continue;
        }
        processed[a] = true;
        dpU[a] = min(distU[a], dpU[p]);
        dpV[a] = min(distV[a], dpV[p]);
        dist[a] = d;
        for (auto i : adj[a]) {
            pq.push({-(d + i.second), i.first, a});
        }
    }
    ans = min(ans, dpU[ed] + dpV[ed]);
}
int main() {
    cin >> N >> M >> S >> T >> U >> V;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    dpU = dpV = distU = distV = vector <ll> (N+1, 1e16);
    dijkstra1(U, distU);
    dijkstra1(V, distV);
    ans = distU[V];
    dijkstra2(S, T);
    dijkstra2(T, S);
    cout << ans << '\n';
}
