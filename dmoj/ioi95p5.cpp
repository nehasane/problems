/*
    to solve the first part of the problem:
        if a node is unavoidable, then if that node is removed, it is
        not possible to reach node N from node 0. iterate through all
        nodes from 1 to N-1, and try "removing" that node from the graph.
        if a path doesn't exist, then the node is unavoidable.
        to "remove" a node, simply stop the dfs when this node is reached.
    to solve the second part of the problem:
        the only nominees for the splitting nodes are the unavoidable nodes.
        iterate over all unavoidable nodes and treat each of them as a
        splitting node. all nodes till that node will be part of the track 
        on day 1, and all others will be part of the track on day 2. if a node
        part of the track on day 1 contains a path that leads to a node part
        of the track on day 2 or vice versa, then the node we're testing is
        not a splitting node.
*/
#include <bits/stdc++.h>
using namespace std;
vector <vector <int>> adj;
int N = -1;
vector <bool> vis;
vector <bool> days;
bool dfs(int s, int skipped) {
    if (s == N)
        return true;
    if (vis[s])
        return false;
    vis[s] = true;
    bool ans = false;
    for (auto i : adj[s]) {
        if (i != skipped)
            ans |= dfs(i, skipped);
    }
    return ans;
}
bool fill_day(int s, int goal, int day, bool check) {
    if (s == goal) {
        return true;
    }
    if (vis[s]) {
        if (days[s] != day)
            return false;
        return true;
    }
    vis[s] = true;
    days[s] = day;
    bool ans = true;
    for (auto i : adj[s]) {
        ans &= fill_day(i, goal, day, check);
    } 
    return ans;
}
int main() {
    while (true) {
        int c;
        cin >> c;
        if (c == -1)
            break;
        N++;
        vector <int> v;
        adj.push_back(v);
        while (true) {
            if (c == -2)
                break;
            adj.back().push_back(c);
            cin >> c;
        }
    }
    vector <int> v;
    adj.push_back(v);
    N++;
    vis.resize(N+1);
    vector <int> unavoidables;
    for (int i = 1; i < N; i++) {
        fill(vis.begin(), vis.end(), false);
        if (!dfs(0, i))
            unavoidables.push_back(i);
    }
    vector <int> splitting_days;
    days.resize(N+1);
    for (int i = 0; i < unavoidables.size(); i++) {
        fill(days.begin(), days.end(), false);
        fill(vis.begin(), vis.end(), false);
        fill_day(0, unavoidables[i], 1, false);
        bool res = fill_day(unavoidables[i], N, 0, true);
        if (res)
            splitting_days.push_back(unavoidables[i]);
    }
    cout << unavoidables.size() << ' ';
    for (auto i : unavoidables)
        cout << i << ' ';
    cout << '\n' << splitting_days.size() << ' ';
    for (auto i : splitting_days)
        cout << i << ' ';
    cout << '\n';
}
