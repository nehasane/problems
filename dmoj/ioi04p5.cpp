/*

  the idea is quite simple, but the implementation had quite a few nuisances.
  
  if we choose a field of size x, then get x points. but if we choose a strip
  of size x, we only get x-1 points. so if we have to spend x cypress trees and
  have to choose between a field and a strip of equal size, we should choose the
  field.
  
  a regular greedy won't work, since the optimal answer might need us to but
  a combination of fields and strips. here's a sample test case where greedy
  fails:
      20 2 1
      12 12
      8
      
      here the optimal answer is to choose a field of size 12 and a strip of size 8.
      
  remember that we can also take parts of a field or strip. if we take a part of a
  field, then the resultant is a strip, so we get x-1 poits, where x is the size
  of the part of the field we're taking.
  
  so of course, dp comes to the rescue.
  
  let dp[i] = maximum number of points we can get is we can spend i cypress trees.
  
  try every possible field and strip, and add the points that you will get if we spend
  them. remember, we can pbut partial fields and strips, so if either is greater than
  i, then we spend i cypress trees, but get only i-1 points (since the field turns into
  a strip).
  
  now the nuisances:
      we have to combine the fields and strips into one big superset of land, since
      we have to consider them together.
      
      we also have to consider the strips first, be we favour the fields (tabular dp
      only works when you evaluate the favoured parts last. in recursion you can
      evaluate either way)

*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_Q = 150000 + 1;
int dp[MAX_Q];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int Q, M, K;
    cin >> Q >> M >> K;

    vector <int> olive_grps(M+K);
    for (int i = 0; i < M; i++)
        cin >> olive_grps[i];
    for (int i = 0; i < K; i++)
        cin >> olive_grps[i + M];

    fill(dp, dp + Q + 1, INT_MIN);
    dp[0] = 0;
    
    for (int i = M + K - 1; i >= 0; i--) {
        for (int j = Q; j >= 1; j--) {
            if (i >= M) {
                // strip
                if (olive_grps[i] > j)
                    dp[j] = max(dp[j], j - 1);
                else
                    dp[j] = max(dp[j], dp[j - olive_grps[i]] + olive_grps[i] - 1);
            } else {
                // field
                if (olive_grps[i] > j)
                    dp[j] = max(dp[j], j-1);
                else
                    dp[j] = max(dp[j], dp[j - olive_grps[i]] + olive_grps[i]);
            }
        }
    }
    
    cout << dp[Q] << '\n';
}
