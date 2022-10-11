/*
  note to self in future: do this in 30 minutes, problem logic isn't hard, but implementation was a doozy
  
  subtask 1 is pretty straightforward: what would be the sum of the range l to r? this prompts a simple prefix sum solution where
  ans = max(ans, a[l] + a[r] + (b[r-1] - b[l])); where b is a prefix sum of the b array.
  subtask 2 is also pretty straightforward: textbook kadane's algorithm, since a[i] = b[i]
  
  big solution: just a modification of kadane's algorithm
  think of a "V" formation like this:
  --x-x---
  ---x---- where a"V" consists of a[i], then b[i+1[, then a[i+2].
  
  in kadane's algorithm, we choose to either add number[i] to the current subarray, or start a new subarray with this. here, choose
  to add the current V to the subarray of Vs, or the start a new subarray with this.
  
  if we add a V to the previous subarray, then we need to remove the "ending a[] value" and add the additional b[] value to the subarray,
  as well as the new a[] ending.
  if we don't, then the new subarray just consists of a simple V.
  
  since the subarray could wrap around, a simple implementation trick is the append the first N elements of each array to the end of each.
  the new length of each array will be 2N
  
  because of this, the length of the subrray with the maximum sum could exceed N. keep track of the length of the current subarray
  while processing. if the length is N, then pop the last element (do not pop the last V! pop the starting a[] value of the current subarray,
  remove the first b[] value (let this be b[p]) and add a[p] as the new starting of the subarray).
  
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX_N = 2 * 1e6 + 2;
ll a[MAX_N], b[MAX_N];
int main() {
    int N;
    cin >> N;
    ll best = LONG_LONG_MIN, sum = 0, len = 2;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        a[i + N] = a[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> b[i];
        b[i + N] = b[i];
    }
    for (int i = 1; i+2 <= N*2; i++) {
        best = max(best, a[i] + b[i+1] + a[i+2]);
        best = max({best, a[i], a[i] + a[i+1]});
    }
    if (N <= 3)  {
        cout << best << '\n';
        return 0;
    }
    len = 1;
    sum = a[1] + b[2] + a[3];
    best = max(best, sum);
    for (int i = 2; i + 2 <= N*2; i++) {
        if (len + 2 == N) {
            // pop first number of subarray
            sum = sum - a[i - len];
            // add a[p]
            sum = sum + a[i - len + 1];
            // remove b[p]
            sum = sum - b[i - len + 1];
            len--;
        }
        if (sum + b[i+1] + a[i+2] - a[i+1] > a[i] + b[i+1] + a[i+2]) {
            // append current V to current subarray
            sum = sum + b[i+1] + a[i+2] - a[i+1];
            len++;
        } else {
          // create new subarray consisting of only the current V
            sum = a[i] + b[i+1] + a[i+2];
            len = 1;
        }
        best = max(best, sum);
    }
    cout << best << '\n';
}
