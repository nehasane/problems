/*
    problem link: http://www.usaco.org/index.php?page=viewproblem2&cpid=1014
    this one is good. it uses binary exponentiation

    simulate the swaps for one iteration of the exercise. you will get the
    positions where the cows landed up after this one iteration. let's say these
    were the positions of the cows:
    1 7 5 6 4 2 3
    from this, we can tell that cow 7, which was at position 7 originally, moved 
    to position 2. if we do one more iteration of the exercise, the cow at position
    7 will follow the same path that cow 7 took in the first iteration, and land
    up at position 2 too. so we can say that in the second iteration, the positions
    will look like this
    * 3 * * * * *

    this is how we can find out the positions of thw cows after one iteration without
    actually moving them. we can similarly find the positions of the cows after 2, 4,
    8 and other iterations that are a power of 2 in the same way we calculate the calculate
    the values in a successor graph table.

    to find out the final positions of cows after k iterations, all we need to do is break 
    down k into powers of 2 that sum up to k and use the same logic to find the positions.
    
    
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxexp = 30; // log2(k)
int main() {
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector <int> nums(n+1);
    for (int i = 1; i <= n; i++)
        nums[i] = i;
    vector <pair <int, int>> swaps(m);
    for (int i = 0; i < m; i++)
        cin >> swaps[i].first >> swaps[i].second;
    vector <vector <int>> bin_exp(maxexp, vector <int> (n+1));
    for (int i = 0; i < m; i++) {
        reverse(nums.begin() + swaps[i].first, nums.begin() + swaps[i].second + 1);
    }
    bin_exp[0] = nums;
    for (int i = 1; i < maxexp; i++) {
        for (int j = 1; j <= n; j++) {
            bin_exp[i][j] = bin_exp[i-1][bin_exp[i-1][j]];
        }
    }

    int x = log2(k);
    k -= (1 << x);

    vector <int> ans = bin_exp[x];

    while (k > 0) {
        x = log2(k);
        k -= (1 << x);

        vector <int> cpy = ans;

        for (int i = 1; i <= n; i++) {
            int y = bin_exp[x][i];
            ans[i] = cpy[y];
        }
        
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';

    return 0;
}
