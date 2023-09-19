/*
    this is a dp problem.

    to score 35 points we can do this:
    let dp[i][j] be the minimum number of modifications needed such that the ith
    building has height j.
    if the ith building is not already at height j, then we need to modify it.
    order for the rabbit to jump to building of height j, the previous building
    must be either taller than or the same height as j and if it is not, then the
    shortest height it can be is j - m, since any height shorter than that will
    not allow the rabbit to jump. this gives us the dp recursion as follows:

    dp[i][j] = min(dp[i][j], dp[i-1][k]) + 1 for all k from j-m to maxa, where maxa is the
    maximum height of the building. the  +1 is the move required to adjust building i
    to height j.

    notice how we simply want the minimum dp value for the the previous row from j-m to
    the end. to quickly calculate this, we can keep an array that stores the minimum dp
    value for a row from j to maxa (the end).

    this gives a time complexity of O(N * maxA) which will fetch 35 points.

    for the full solution, we're going to write down a bunch of equations and modify them
    to reduce the problem down to finding the longest non decreasing subsequence.

    usaco editorial is quite good - https://usaco.guide/problems/lmio-2019triusis/solution

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector <int> nums(n+1);
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    vector <int> b(n+1); // refer to usaco editorial for this
    for (int i = 1; i <= n; i++) {
        if (m * i - nums[i] >= 0)
            b[i] = m * i - nums[i];
        else
            b[i] = -1;
    }
    // find longest non decreasing subsequence
    vector <int> dp;
    for (int i = 1; i <= n; i++) {
        if (b[i] == -1)
            continue;
        auto x = upper_bound(dp.begin(), dp.end(), b[i]);
        if (x == dp.end())
            dp.push_back(b[i]);
        else
            *x = b[i];
    }
    cout << n - dp.size() << '\n';
}
