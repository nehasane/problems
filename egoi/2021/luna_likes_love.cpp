/*
  
  getting 15 points (subtask1 and 2) is pretty simple:
    for subtask1: the answer is simply n, as we can directly remove each pair from the group
    for subtask2: we count the number of misplaced pairs (the pairs that are not originally
    next to eachother, and the number of correctly placed pairs (the pairs that are
    originally placed next to eachother. we will only need one move to remove each correctly
    placed pair and 3 moves for each pair of misplaced pairs (1 to swap the pairs into their
    correct places and 1 move to remove each pair)
    
  getting the next 4 subtasks requires making this observation:
  take one couple such that the distance between them is minimal. because their distance is
  minimal, we know that any people located in between them belong to distinct couples. lets
  call the number of people in between this couple x. either of the people in the couple
  will have to make exactly x swaps to be next to their partner. once this is done, we will
  require one more move to remove this couple from the line. so for each couple, we need to 
  sort them in increasing order of distance from eachother, and count the number of people
  in between them. to quickly find out this number, we can use a fenwick or segment tree and
  the positions of each person in the couple when we remove them to indicate that those people
  have been removed. suppose there were originally 5 people in between a couple, but after
  removing some people, we are left with 1. the number of people we removed (4) can be
  determined by running a sum query on the tree and the final number of moves required to 
  remove the current couple will be (5 - 4) + 1 (the +1 is the move to remove them).

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;
using ll = long long;
struct stree {
    #define lc v*2
    #define rc v*2+1
    int sz;
    vector <int> tree;
    stree (int size) {
        sz = size;
        tree = vector <int> (4 * size);
    }
    int combine(int left, int right) {
        return left + right;
    }
    void pushup(int v) {
        tree[v] = combine(tree[lc], tree[rc]);
    }

    // sum query
    int query(int v, int tl, int tr, int l, int r) {
        if (r < tl || l > tr)
            return 0;
        if (tl >= l && tr <= r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return combine(query(lc, tl, tm, l, r), query(rc, tm+1, tr, l, r));
    }

    // point update
    void update(int v, int tl, int tr, int p) {
        if (tr < p || tl > p)
            return;
        if (tl == tr)
            tree[v] = 1;
        else {
            int tm = (tl + tr) / 2;
            update(lc, tl, tm, p);
            update(rc, tm+1, tr, p);
            pushup(v);
        }
    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector <int> nums(2*n+2);
    vector <array <int, 3>> diffs;
    vector <int> pos(n+1);
    for (int i = 1; i <= 2*n; i++) {
        cin >> nums[i];
        if (pos[nums[i]] != 0) {
            diffs.push_back({i - pos[nums[i]] - 1, pos[nums[i]], i});
        } else {
            pos[nums[i]] = i;
        }
    }
    sort(diffs.begin(), diffs.end());

    // declare tree TODO
    stree tree(2*n+1);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int diff = diffs[i][0], a = diffs[i][1], b = diffs[i][2];
        ans = ans + diff - tree.query(1, 0, 2*n, a, b) + 1;
        tree.update(1, 0, 2*n, a);
        tree.update(1, 0, 2*n, b);
    }
    cout << ans << '\n';
}
