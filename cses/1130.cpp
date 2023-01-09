/*
    the overall strategy here is to go over the nodes using a dfs and select pairs.
    
    the first piece of code gets a WA while the second gets AC. look at the differences
    and try to figure ou why this is the case. 
    
    in the first piece of code, what's happening is that as soon as we find a parent-child
    pair, we are adding them to the set. this might not be optimal, since a parent might
    form a pair with one if it's other children that ultimately gets more pairings.
    
    this is best explained with an example. consider the test case:
    6
    1 2
    2 3
    1 4
    4 5
    5 6
    suppose the dfs traverse the (1->2) subtree first. the first code will use the pair (1, 2).
    then he dfs will go down the (1->4) subtree. the dfs will use the pair (4, 5). this leaves
    nodes 3 and 6 empty. the optimal answer is to use the pairs (1, 4), (2, 3), (5, 6).
    
    to fix this, the second code first runs all the dfs and selects the pair immediately after
    the call. this ensures that the leaf nodes are used up before the others, allowing fewer
    unused nodes (as 3 and 6 were unused in the test case above).
    
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2 * 1e5 + 1;
vector <int> adj[MAX_N];
bool chosen[MAX_N];
int ans = 0;
void dfs(int s, int p) {
    for (auto i : adj[s]) {
        if (i == p)
            continue;
        if (!chosen[s]) {
            chosen[s] = chosen[i] = true;
            ans++;
        }
        dfs(i, s);
    }
}
int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int N;
    cin >> N;
    for (int i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}


#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2 * 1e5 + 1;
vector <int> adj[MAX_N];
bool chosen[MAX_N];
int ans = 0;
void dfs(int s, int p) {
    for (auto i : adj[s]) {
        if (i == p)
            continue;
        dfs(i, s);
        if (!chosen[s] && !chosen[i]) {
            chosen[s] = chosen[i] = true;
            ans++;
        }
    }
}
int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int N;
    cin >> N;
    for (int i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}
