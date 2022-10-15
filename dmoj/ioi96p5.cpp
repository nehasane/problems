/*
  let dp[i] = true if a valid prefix can be constructed by placing a primitive such that it ends at S[i]
  
  loop over all i from 0 to N-1 and try placing a primitive such that it ends at i. if it can be placed, and
  and a valid prefix exists uptil the position right before the primitive, then the answer is the maximum of
  all such prefixes.
  
*/
#include <bits/stdc++.h>
using namespace std;
vector <string> prims;
string s;
int main() {
    string tp;
    cin >> tp;
    while (tp != ".") {
        prims.push_back(tp);
        cin >> tp;
    }
    getline(cin, tp);
    getline(cin, tp);
    while (tp.size() > 0) {
        s.append(tp);
        getline(cin, tp);
    }
    int N = s.size();
    int ans = 0;
    vector <bool> dp(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < prims.size(); j++) {
            tp = s.substr(i, prims[j].size());
            if (i + prims[j].size() <= N && s.substr(i, prims[j].size()) == prims[j]) {
                if (i-1 >= 0)
                    dp[i + prims[j].size() - 1] = dp[i + prims[j].size() - 1] | dp[i-1];
                else
                    dp[i + prims[j].size() - 1] = true;
                if (dp[i + prims[j].size() - 1])
                    ans = max(ans, (int)(i + prims[j].size()));
            }
        }
    }
    cout << ans << '\n';
}
