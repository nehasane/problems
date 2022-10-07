/*

this is a graph problem, where the people are the nodes and bidirectional edges are drawn between two people depending on whether they're related or not.
determining whether or not two people are related is pretty straightforward: count the number of common elements and check if it's greater than K or not.

based on this, create an adjacency list and start a dfs from person1 (the president) and count the number of nodes visited. that's your answer!

just to make counting the number of common elements between two people a little faster, i store the elements of each person in a set; that way i can check whether an
element is common or not in log(E) time, where E is the number of elements a person has.

*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 300 + 1;
vector <set <int>> peeps;
vector <vector <int>> adj;
bool vis[MAX_N];
int dfs(int s) {
    if (vis[s])
        return 0;
    vis[s] = true;
    int ans = 1;
    for (auto i : adj[s])
        ans += dfs(i);
    return ans;
}
int main() {
    int N, K;
    cin >> N >> K;
    peeps.resize(N+1);
    adj.resize(N+1);
    for (int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        for (int j = 0; j < x; j++) {
            int y;
            cin >> y;
            peeps[i].insert(y);
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            int c = 0;
            for (auto l : peeps[i]) {
                if (peeps[j].find(l) != peeps[j].end())
                    c++;
            }
            if (c >= K) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    cout << dfs(1) << '\n';
}
