/*
    we will run a dfs and answer all queries where one of the endpoints is the node s that 
    the dfs is on at that moment. while running the dfs, we will also maintain a list of types
    of cows that are on the path from node 1 (root) to s. for the current query, if either of the
    endpoints has the same cow type required, then the answer is 1 for that query. otherwise
    if there is a cow of type c on the path from 1 to s, we need to check if c is on the path of
    the two endpoints. we can check this by calculating the lca of the endpoints and then calculating
    the lca of the other endpoint and c. if these two match, then we know that c is on the path of 
    the two endpoints.
    overall we will be answering each query twice. this is because the first time we answer a query,
    we will only have visited one of the two endpoints. we may not have visited a cow of type c on
    the path from node 1 to s, but we might when we visit the other endpoint. this is why we answer
    each query twice
*/
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
vector <vector <array <int, 3>>> queries;
vector <vector <int>> adj, ancestor, cows;
vector <int> type, visit, finish;
vector <bool> ans;
const int maxanc = 20;
int t = 0;
void dfs(int s, int p, int d) {
    visit[s] = t++;
    ancestor[s][0] = p;
    for (int i = 1; i < maxanc; i++)
        ancestor[s][i] = ancestor[ancestor[s][i-1]][i-1];
    for (auto i : adj[s]) {
        if (i == p)
            continue;
        dfs(i, s, d+1);
    }
    finish[s] = t++;
}
bool is_ancestor(int a, int b) {
    return visit[a] <= visit[b] && finish[a] >= finish[b];
}
int get_lca(int a, int b) {
    if (is_ancestor(a, b))
        return a;
    if (is_ancestor(b, a))
        return b;
    int lca = a;
    for (int i = maxanc-1; i >= 0; i--) {
        if (!is_ancestor(ancestor[lca][i], b))
            lca = ancestor[lca][i];
    }
    return ancestor[lca][0];
}
void dfs2(int s, int p) {
    for (auto i : queries[s]) {
        int c = i[0], b = i[1], id = i[2];
        int a = s;
        if (type[a] == c || type[b] == c)
            ans[id] = 1;
        else if (!cows[c].empty()) {
            int x = cows[c].back();
            int lca = get_lca(a, b);
            int lca2 = get_lca(b, x);
            if (lca == lca2)
                ans[id] = 1;
        }
    }
    cows[type[s]].push_back(s);
    for (auto i : adj[s]) {
        if (i == p)
            continue;
        dfs2(i, s);
    }
    cows[type[s]].pop_back();

}
int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    
    adj.resize(n+1);
    cows.resize(n+1);
    queries.resize(n+1);
    type = visit = finish = vector <int> (n+1);
    ans = vector <bool> (m+1);
    ancestor = vector <vector <int>> (n+1, vector <int> (maxanc));

    for (int i = 1; i <= n; i++)
        cin >> type[i];
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        queries[a].push_back({c, b, i});
        // explain this line in the editorial
        queries[b].push_back({c, a, i});
    }
    
    visit[0] = -1;
    finish[0] = 1e9;

    dfs(1, 0, 1);

    dfs2(1, 0);
    
    for (int i = 0; i < m; i++)
        cout << ans[i];
    cout << '\n';


}
