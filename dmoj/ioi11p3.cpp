/*
    notive that if it's possible to buy x fields, then it's also possible to buy x-1, x-2, x-3 ...
    fields. this means we can binary search on the number of fields to buy.
    also notice that it's always optimal to place a field in the middle of all fields being bought
    (in other words, it's optimal to place the field in the median of all fields begin bought)
    say we had to buy "mid" number of fields. we can maintain a sliding window of size mid and
    calculate the minimum cost of all windows. if the minimum cost fits in the budget, then we could
    try buying for rice hubs. otherwise, we would have to reduce the number of fields we buy.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int besthub(int R, int L, int X[], ll B);

int besthub(int R, int L, int X[], ll B) {
    int lo = 1, hi = R;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        ll cost = 0;
        ll min_cost = 0;
        for (int i = 0; i < mid; i++)
            cost += abs(X[i] - X[mid/2]);
        min_cost = cost;
        int prev_med = mid/2;
        for (int i = mid; i < R; i++) {
            int curr_med = prev_med + 1;
            cost -= abs(X[i - mid] - X[prev_med]);
            cost += abs(X[i] - X[curr_med]);
            cost += abs(X[prev_med] - X[curr_med]) * (prev_med - (i - mid));
            cost -= abs(X[prev_med] - X[curr_med]) * ((i-1) - (prev_med));
            min_cost = min(min_cost, cost);
            prev_med = curr_med;
        }
        if (min_cost <= B)
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}

int main() {
    int R, L, B;
    cin >> R >> L >> B;
    int X[R];
    for (int i = 0; i < R; i++)
        cin >> X[i];
    cout << besthub(R, L, X, B);
}
