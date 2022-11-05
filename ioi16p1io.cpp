/*

    first look and i thought it was knapsack, but the constraints don't support a
    knapsack solution. 
    
    sort the molecules based on their weight. all we have to do now is find a subarray
    where the sum of the weights falls within the given range. A 2P range can do this.

*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX_N = 2 * 1e5;
pair <int, int> moles[MAX_N];
int main() {
    int N;
    ll L, R;
    cin >> N >> L >> R;
    for (int i = 0; i < N; i++) {
        cin >> moles[i].first;
        moles[i].second = i;
    }
    sort(moles, moles + N);
    bool ans = false;
    int l = 0, r = 1;
    ll sum = moles[0].first;
    while (l <= r) {
        if (sum >= L && sum <= R) {
            ans = true;
            break;
        }
        if (r >= N && sum < L)
            break;
        if (sum < L) {
            sum += moles[r].first;
            r++;
        } else if (sum > R) {
            sum -= moles[l].first;
            l++;
        } else {
            ans = true;
            break;
        }
    }
    if (ans) {
        cout << r - l << '\n';
        for (int i = l; i < r; i++)
            cout << moles[i].second << ' ';
        cout << '\n';
    } else
        cout << 0 << '\n';
}
