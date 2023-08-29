/*

    choose one of the m edges and add it to the add it to graph (hypothetically). it
    will form exactly one cycle and all the nodes in that cycle will use that m edge
    if the original edge that is in the cycle breaks down. notice that if an edge is
    part of multiple cycles, their nodes will only use the m edge that has the smallest
    weight.

    a naive algorithm would (hypothetically) add an edge to the graph, go over all the
    edges in the cycle and if that edge has not been part of a cycle with a smaller
    m edge weight, then assign this weight to that edge.

    if we had to go over every possible cycle in the graph, then the code would tle. 
    let's sort the m-edges by weight and then loop over all of these edges. for every
    og edge in the first cycle formed (by the first m-edge), the answer for them will be
    the weight of the current m-edge. we know that there is no point in considering these
    edges again, since an m-edge with a smaller weight has already been assigned.

    so we need to find a way to "skip" these nodes while traversing the path of the
    cycle. to do this, we can construct a dsu. the two nodes of the og edge can be
    called the parent node and child node. we we assign an m-edge to the og edge, we
    add the child node to the parent node in the dsu. so whenever we enocunter the child
    node in another cycle, we use the dsu to jump to its parent, therefore skipping that
    og edge.
    
*/
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
vector <vector <pair <int, int>>> adj_og;
vector <int> ans;
struct DSU {
    vector <int> link, sz;
    DSU () {}
    DSU (int s) {
        link.resize(s+1);
        sz.resize(s+1);
        for (int i = 0; i <= s; i++) {
            link[i] = i;
            sz[i] = 1;
        }
    }
    int head(int x) {
        if (x == link[x])
            return x;
        return link[x] = head(link[x]);
    }
};
vector <vector <int>> anc;
vector <int> visit, finish, depth;
vector <pair <int, int>> parent;
int t = 0, n, m;
void dfs(int s, int p, int d) {
    visit[s] = t++;
    anc[s][0] = p;
    depth[s] = d;
    for (int i = 1; i < 20; i++)
        anc[s][i] = anc[anc[s][i-1]][i-1];
    if (s == 1) {
        parent[1] = {1, n};
    }
    for (auto i : adj_og[s]) {
        if (i.first == p)
            continue;
        parent[i.first] = {s, i.second};
        dfs(i.first, s, d + 1);
    }
    finish[s] = t++;
}
bool is_ancestor(int u, int v) {
    return visit[u] <= finish[v] && finish[u] >= finish[v];
}
int get_lca(int a, int b) {
    if (is_ancestor(a, b))
        return a;
    if (is_ancestor(b, a))
        return b;
    int lca = a;
    for (int i = 19; i >= 0; i--) {
        if (!is_ancestor(anc[lca][i], b))
            lca = anc[lca][i];
    }
    lca = anc[lca][0];
    return lca;
} 
DSU dsu;
void dfs2(int s, int w, int lca) {
    int r = dsu.head(s);
    while (depth[r] > depth[lca]) {
        int edge_id = parent[r].second;
        ans[edge_id] = w;
        dsu.link[r] = parent[r].first;
        r = dsu.head(parent[r].first);
    }
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    cin >> n >> m;
    adj_og.resize(n+1);
    ans.resize(n, -1);
    anc = vector <vector <int>> (n+1, vector <int> (20));
    visit = finish = depth = vector <int> (n+1);
    parent.resize(n+1);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        adj_og[a].push_back({b, i});
        adj_og[b].push_back({a, i});
    }
    vector <array <int, 4>> medges(m);
    for (int i = 0; i < m; i++) {
        cin >> medges[i][1] >> medges[i][2] >> medges[i][0];
        medges[i][3] = i;
    }
    sort(medges.begin(), medges.end());
    
    dfs(1, 1, 0);

    dsu = DSU(n+1);

    for (int i = 0; i < m; i++) {
        int a = medges[i][1], b = medges[i][2], w = medges[i][0];
        int lca = get_lca(a, b);
        dfs2(dsu.head(a), w, lca);
        dfs2(dsu.head(b), w, lca);
        
    }
    for (int i = 0; i < n-1; i++)
        cout << ans[i] << '\n';
    return 0;
}
