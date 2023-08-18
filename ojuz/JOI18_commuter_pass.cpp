/*

    problem link: https://oj.uz/problem/view/JOI18_commuter_pass
    algorithm used: graph theory
    

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
