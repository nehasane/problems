/*
    the idea is quite simple, even though the implementation is lengthy.
    but first, a bunch of observations:
        a) it's optimal to connect all components to a single components, which would serve
        as the "main" component
        b) the main component would be the component with the largest diameter, that way the overal
        diameter of the connected components is minimal
        c) it's optimal to connect each component to the main component using exactly road, ergo
        one pair of billabongs (duh)
        d) the billabongs between which the roads will be built (the "connector" nodes) will be chosen
        such that the longest path starting from that node and ending at a node in its component
        will be minimal across all such longest paths of all nodes in that component (let's call
        this smallest of all longest paths in that component the radius of that component).
        e) the answer is either
            - the largest diameter of any component
            - the radius of the main component (aka the largest radius) + next largest radius + L (main
            component and another component with 2nd largest radius joined with single new trail)
            - 2nd largest radius + 3rd largest radius + L + L (two components joined to main component via
            2 new trails)
   
   these are all greedy (and intuition) based observations that work.
   
   now that's left to do is find the radii and diameters of all components, sort them in descending order,
   and evaluate them as shown in obervation e.
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5;
vector <vector <pair <int, int>>> adj;
bool vis[MAX_N];
bool in_subtree[MAX_N];
int node = 0, dis = 0;
void dfs(int s, int p, int len) {
    if (dis < len) {
        dis = len;
        node = s;
    }
    vis[s] = true;
    for (auto i : adj[s]) {
        if (i.first == p)
            continue;
        dfs(i.first, s, len + i.second);
    }
}
bool subs(int s, int p, int goal) {
    if (s == goal) {
        in_subtree[s] = true;
        return true;
    }
    bool ans = false;
    for (auto i : adj[s]) {
        if (i.first == p)
            continue;
        ans |= subs(i.first, s, goal);
    }
    in_subtree[s] = ans;
    return ans;
}
int find_radius(int s, int p, int travelled, int tot_dis) {
    int ans = 1e9;
    for (auto i : adj[s]) {
        if (i.first == p || !in_subtree[i.first])
            continue;
        ans = min(ans, max(travelled, tot_dis - travelled));
        ans = min(ans, find_radius(i.first, s, travelled + i.second, tot_dis));
    }
    return ans;
}
int travelTime(int N, int M, int L, int A[], int B[], int T[]) {

    adj.resize(N);
    for (int i = 0; i < M; i++) {
        adj[A[i]].push_back({B[i], T[i]});
        adj[B[i]].push_back({A[i], T[i]});
    }
    vector <int> radii, diameters;
    for (int i = 0; i < N; i++) {
        if (vis[i])
            continue;
        node = i;
        dis = 0;
        dfs(i, N, 0);
        int start_node = node;
        dis = 0;
        dfs(start_node, N, 0);
        int end_node = node;
        diameters.push_back(dis);
        subs(start_node, N, end_node);
        int radius = find_radius(start_node, N, 0, dis);
        if (radius == 1e9)
            radius = 0;
        radii.push_back(radius);
    }
    sort(radii.begin(), radii.end(), greater <int> ());
    sort(diameters.begin(), diameters.end(), greater <int> ());
    if (radii.size() == 1)
        return max(diameters[0], radii[0]);
    else if (radii.size() == 2)
        return max({diameters[0], radii[0], radii[0] + radii[1] + L});
    return max({diameters[0], radii[0] + radii[1] + L, radii[1] + radii[2] + L * 2});
    
}
