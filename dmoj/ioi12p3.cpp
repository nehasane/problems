/*

    surprisingly, this is a graph problem, where edges represent letters.
    every time you add a letter, we draw a new edge. when we undo x
    commands, we walk up x edges. to get a letter, we walk down those many
    steps (or basically, walk up length_of_path - inputed_steps number of
    steps).
  
*/
#include <bits/stdc++.h>
using namespace std;
struct node {
    int depth;
    char curr_letter;
    int parent;
    int id;
};
vector <node> tree;
int ptr, id = 0;
const int MAX_N = 1e6;
int succ[MAX_N][20];
vector <int> commands;
void build_succ(int node) {
    succ[node][0] = tree[node].parent;
    int depth = tree[node].depth;
    for (int i = 1; i <= log2(depth); i++)
        succ[node][i] = succ[succ[node][i-1]][i-1];
}
char walk_back(int k) {
    int ans = ptr;
    while (k > 0) {
        int x = (int)log2(k);
        ans = succ[ans][x];
        k -= pow(2,x);
    }
    return tree[ans].curr_letter;
}
void Init() {
    tree.emplace_back();
    commands.push_back(0);
    tree[0].depth = 0;
    tree[0].parent = -1;
    tree[0].id = 0;
    ptr = 0;
}
void TypeLetter(char L) {
    tree.emplace_back();
    tree.back().depth = tree[ptr].depth + 1;
    tree.back().parent = tree[ptr].id;
    id++;
    tree.back().id = id;
    ptr = id;
    tree[ptr].curr_letter = L;
    build_succ(id);
    commands.push_back(id);
}
void UndoCommands(int U) {
    ptr = commands[commands.size() - U - 1];
    commands.push_back(ptr);
}
char GetLetter(int P) {
    int steps_to_walk = tree[ptr].depth - P - 1;
    return walk_back(steps_to_walk);
}

// int main() {
//     Init();
//     int Q;
//     cin >> Q;
//     while (Q--) {
//         int type;
//         cin >> type;
//         if (type == 1) {
//             char L;
//             cin >> L;
//             TypeLetter(L);
//         } else if (type == 2) {
//             int U;
//             cin >> U;
//             UndoCommands(U);
//         } else {
//             int P;
//             cin >> P;
//             cout << GetLetter(P) << '\n';
//         }
//     }
// }
