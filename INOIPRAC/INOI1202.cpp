/*
    the algorithm for this problem is pretty straightforward: for each of the possible N rows, calculate the maximum possible sum.
    if we compare the ith row configuration with the (i-1)th configuration, we notice the certain ranges are getting updated.
    
    suppose N = 5, configuration 2 (0 indexed)
    3 4 5 1 2;
    the 2nd configuration is
    4 5 1 2 3
    notice that the values from position 0 to 1 are incremented by 1, value 2 is decremented by 3, and position 3 to 4 are incremented by 1.
    if we compare any two consecutive configuration, we can divide the row into 3 ranges, where all values in first range are incremented by 1,
    all in second range (there will be exactly one value in this range) will be decremented by (N-1), and all in the thrid range will be incremented
    by 1.
    this prompts a range update solution, where we use a segment tree to quickly perform updates, and quickly perform a maximum query. However, since
    a range of values must be updated at the same time in O(log N) time, we use lazy propagation.
    
    for an explanation of the template for lazy propragation on segment trees, go to (LINK)
    
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct node {
    ll num;
    int z;
};
vector <node> seg_tree;
int seg_sz;
void pushup(int k) {
    if (k*2+1 >= seg_tree.size())
        return;
    seg_tree[k].num = max(seg_tree[k*2].num, seg_tree[k*2+1].num);
}
void push_down(int k) {
    if (k*2+1 >= seg_tree.size())
        return;
    // get sum of children
    seg_tree[k*2].num += seg_tree[k].z;
    seg_tree[k*2].z += seg_tree[k].z;
    seg_tree[k*2+1].num += seg_tree[k].z;
    seg_tree[k*2+1].z += seg_tree[k].z;
    seg_tree[k].z = 0;
    
}
void update(int node_id, int subtree_l, int subtree_r, int l, int r, int inc) {
    if (l > r)
        return;
    if (subtree_l == l && subtree_r == r) {
        seg_tree[node_id].num += inc;
        seg_tree[node_id].z += inc;
    } else {
        push_down(node_id);
        int mid = (subtree_l + subtree_r) / 2;
        update(node_id*2, subtree_l, mid, l, min(r, mid), inc);
        update(node_id*2+1, mid+1, subtree_r, max(l, mid+1), r, inc);
        pushup(node_id);
    }
}
int query(int node_id, int subtree_l, int subtree_r, int l, int r) {
    if (l > r)
        return 0;
    if (l >= subtree_l && r >= subtree_r)
        return seg_tree[node_id].num;
    push_down(node_id);
    int mid = (subtree_l + subtree_r) / 2;
    return max(query(node_id*2, subtree_l, mid, l, min(r, mid)), query(node_id*2+1, mid+1, subtree_r, max(l, mid+1), r));
}
void build_seg_tree(int node_id) {
    if (node_id*2+1 >= seg_tree.size())
        return;
    build_seg_tree(node_id*2);
    build_seg_tree(node_id*2+1);
    pushup(node_id);
}
int main() {
    int N;
    cin >> N;
    seg_sz = pow(2, ceil(log2(N)));
    seg_tree.resize(seg_sz*2);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        seg_tree[i + seg_sz].num = x+i+1;
    }
    build_seg_tree(1);
    for (int i = N-1; i >= 0; i--) {
        int max_v = seg_tree[1].num;
        update(1, 0, seg_sz-1, 0, i-1, 1);
        update(1, 0, seg_sz-1, i, i, -N+1);
        update(1, 0, seg_sz-1, i+1, seg_sz-1, +1);
        cout << max_v;
        if (i == 0)
            cout << '\n';
        else
            cout << ' ';
    }
}
