/*
    this is a quite simple problem, if you make this one key observation: if we had 
    to pair two shoes, then it is always optimal to move the pair to either side of 
    the line, so that we don't have to move the other shoes over this pair. with this
    greedy observation, all we have to do it generate a list of the "partners" for
    each shoe, iterate over each shoe in the OG line, and calculate the cost of the 
    pair to the extreme of the line (for simplcicity, i move all pairs of shoes to 
    the left of the line). actually "moving" the shoes would take far too much time,
    so instead we keep track of the positions where we are moving a shoe to the left
    of the line, and the difference between the OG positions of the two shoes in the
    pair, and subtract the former from the latter to get the actual number of swaps
    needed to move the shoe on the right next to the shoe on the left.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector <ll> seg_tree;
int seg_sz;
void update(int x, int a) {
    x += seg_sz;
    seg_tree[x] = a;
    for (x /= 2; x >= 1; x /= 2)
        seg_tree[x] = seg_tree[x*2] + seg_tree[x*2+1];
}
ll sum(int a, int b) {
    a += seg_sz;
    b += seg_sz;
    int ans = 0;
    while (a <= b) {
        if (a % 2 == 1)
            ans += seg_tree[a++];
        if (b % 2 == 0)
            ans += seg_tree[b--];
        a /= 2;
        b /= 2;
    }
    return ans;
}
ll count_swaps(vector<int> S) {
    int N = S.size() / 2;
    seg_sz = pow(2, ceil(log2(N*2)));
    seg_tree.resize(seg_sz*2);
    
    vector <array <int, 3>> partners;
    set <pair <int, int>> pairs;
    for (int i = 0; i < N*2; i++) {
        auto x = pairs.lower_bound({-S[i], 0});
        if (x == pairs.end() || x->first != -S[i])
            pairs.insert({S[i], i});
        else {
            partners.push_back({x->second, i, S[i]});
            pairs.erase(x);
        }
    }
    ll ans = 0;
    sort(partners.begin(), partners.end());
    for (int i = 0; i < N; i++) {
        if (partners[i][2] < 0) {
            ans += partners[i][1] - partners[i][0] + sum(partners[i][0]+1, partners[i][1]);
            update(partners[i][1], -1);
        } else {
            ans += partners[i][1] - partners[i][0] - 1 + sum(partners[i][0]+1, partners[i][1]);
            update(partners[i][1], -1);
        }
    }
    return ans;
}
