/*
    run a dfs from node 1. at each node store a table that records the number of nodes visited
    so far that have type x of a cow. then while answering the queries, we can lookup the number
    of cows of type C that are present on the path from 1 to A and 1 to B and add these up. Then
    we find the lca of A and B and subtract the number of cows of type C present from 1 to the 
    parent of the lca. this value tells us the number of cows that have type C that are present on
    the path from A to B. if this value is postive then print 1, otherwise we can print 0.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
vector <vector <int>> adj;
vector <int> type;
vector <map <int, int>> cnt;
vector <vector <int>> ancestor;
vector <int> visit, finish;
int n, m, maxc = 0, t = 0;
const int maxanc = 25;
void dfs(int s, int p) {
    cnt[s] = cnt[p];
    cnt[s][type[s]]++;
    visit[s] = t++;
    ancestor[s][0] = p;
    for (int i = 1; i < maxanc; i++)
        ancestor[s][i] = ancestor[ancestor[s][i-1]][i-1];
    for (auto i : adj[s]) {
        if (i == p)
            continue;
        dfs(i, s);
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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    cin >> n >> m;
    adj.resize(n+1);
    type.resize(n+1);
    ancestor = vector <vector <int>> (n+1, vector <int> (maxanc));
    finish = visit = vector <int> (n+1);
    cnt.resize(n+1);
    if (n <= 1000) {
        // subtask 2
        maxc = n;
    } else {
        // subtask 3
        maxc = 10;
    }
    for (int i = 1; i <= n; i++)
        cin >> type[i];
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    visit[0] = -1;
    finish[0] = 1e9;
    dfs(1, 0);

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == b) {
            if (type[a] == c)
                cout << 1;
            else
                cout << 0;
            continue;
        }
        int lca = get_lca(a, b);
        int p = ancestor[lca][0];
        int x = cnt[a][c] + cnt[b][c] - 2 * cnt[p][c];
        if (x > 0)
            cout << 1;
        else
            cout << 0;
        
    }
    return 0;
}
