/*
    first of all, it obvious that the problem's a graph problem: the schools are the nodes,
    and directed edges are drawn between nodes depending on whether a school sends software
    to the other school or not.
    for subtask A:
        there are only 2 scenarios where we'll have to send a package to a particular node:
        either that node never receives a package from another node (in which case the
        only way that node receives a package is if it was given a package in the first place),
        or if the package is part of a connected component (so exactly one package must be
        sent in that component, and all nodes will still receive a package).
        
        first run a dfs on all nodes that will never receive a package from another node (can
        be done by checking the size of the reverse adjcency list for the node). then run a
        dfs on all nodes that haven't been visited yet: if a node hasn't been visited, then
        that node must be part of a component where all nodes a part of the same cycle. each
        time a dfs is run starting from node i, a package has been delivered to node i.
  for subtask B:
        the goal is to create one component where all nodes are a part of some cycle. 
        - if a node only sends packages, then in order for it to be made part of a cycle, it
        must receive a package from another node.
        - if a node only receives packages, then in order for it to be made part of a cycle,
        it must send a package to another node.
        
        seeing the connection? one node needs to receive and another needs to send. to fulfil
        this, we can draw an edge from a "receiver" node to a "sender" node. if the number
        of sender and receiver nodes aren't equal, then edges can be drawn between the extras.
        
        this will work if all components contains at least one sender or receiver node. but in
        the case all components are connected graphs, the number of sender and receiver nodes
        would be 0. BUT... edges need to drawn between the components. in this case, the answer
        would be the answer to subtask A: the number of nodes that need to be sent a package will
        be the number of edges that need to be drawn. BUT (again), that will give you WA if the
        graph is a directed tree.
        
        so finally,
            if exactly one dfs run visits all nodes AND there are no sender and no receiver nodes,
                then the graph consits of exactly one connected component.
            otherwise
                the graph consists of at least one component with at least one sender or receiver node.
        
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 100 + 1;
int N;
vector <vector <int>> adj, adjr;
bool vis[MAX_N];
void dfs(int s) {
    if (vis[s])
        return;
    vis[s] = true;
    for (auto i : adj[s])
        dfs(i);
}
int main() {
    cin >> N;
    adj.resize(N+1);
    adjr.resize(N+1);
    for (int a = 1; a <= N; a++) {
        int b;
        cin >> b;
        while (b != 0) {
            adj[a].push_back(b);
            adjr[b].push_back(a);
            cin >> b;
        }
    }
    int subtaskA = 0;
    int dfs_runs = 0;
    for (int i = 1; i <= N; i++) {
        if (adjr[i].size() == 0) {
            subtaskA++;
            dfs(i);
            dfs_runs++;
        }
    }
    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            subtaskA++;
            dfs(i);
            dfs_runs++;
        }
    }
    int indegree0 = 0, outdegree0 = 0;
    for (int i = 1; i <= N; i++) {
        if (adj[i].size() == 0)
            outdegree0++;
        if (adjr[i].size() == 0)
            indegree0++;
    }
    if (dfs_runs == 1 && max({indegree0, outdegree0}) == 0) // one connected component
        cout << subtaskA << '\n' << 0 << '\n';
    else // NOT
        cout << subtaskA << '\n' << max({subtaskA, indegree0, outdegree0}) << '\n';
    
}
