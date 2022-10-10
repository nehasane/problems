/*

this one was a real doozy with all the nitty-gritties...took me 1.5+ hours to understand this completely

intial thought process: typical dp - if we had to form a sequence of length l from the first n numbers, what would be the minimum cost?
once i tried implementing this (for a while), i finally realised that this approach to the problem wasn't going to work.

correct approach: if we had to keep the cost of the sequence was at least mid, is it possible for the length of that sequence to be
at least L?

after trying out a few test cases by hand, you can figure out that if a sequence of length at least L can be made with cost at least mid,
then a sequence of length at least L with cost mid-1, mid-2, mid-3 ... can also be made. This observation prompts a binary search + something else algorithm.

we have no way of knowing which indices to make part of a sequence, so we try them all. this observation prompts a binary search + dp algorithm.

now that the basic pieces are in order, here's the final algorithm:
    first of all, sort the array in descending order, so that we fulfil the first condition of the problem.
    next, binary search on the cost of the sequence: make sure to initialise lo to the maximum difference in indices positions between two numbers of the same value. why?
    read on. the cost for the current checking is called "mid"
    let dp[i] = the length of the longest sequence of numbers such that the number at position i (after sorting) is at the end of the sequence.
    the length of the longest sequence that has a cost of at least mid.
        if this length is < L, then the cost of the sequence must be lowered, to accomodate more numbers.
    otherwise 
        the length of the sequence is fine, but could maybe be reduced further.
    
(read the code, and observe:
    a) the funky initilisation of "lo" for the binary search
    b) the weird binary search modifications, namely:
        i) "while (lo < hi)" instead of "while (lo <= hi)"
        ii) "mid = (lo + hi + 1) / 2" instead of "mid = (lo + hi) / 2"
        iii) "lo = mid" instead of "lo = mid - 1"
   - first of all, the funky initilisation of "lo"
      I first initilsed lo to 1, because the minimum difference between any 2 indices is 1. this will work, if L < N.
      but, if L > N, then some numbers will definitely have to be repeated. in this case, "len" will never satisfy the
      length condition, causing the value of lo to dwindle down to 1.
      in this cases, it is better to toggle between two numbers whose values are the same and whose difference in indices is greatest. the dp
      array, doesn't account for toggling between two numbers, since it only considers each pair of numbers once.
      still, the answer may not require to toggle between two numbers (if L = N), so it's easier to just set the minimum possible answer to "base_ans".
   - the binary search modifications
      while i didn't completely understand why the standard (https://usaco.guide/CPH.pdf page 32, method 1) binary search implementation didn't work, i did understand
      how to get to one that DID work.
      
      let's say that i wanted my sure-shot final answer to be "lo". so in the binary search, if the length condition was satisfied, then i set "lo" to mid, since 
      we know that a sequence with cost at least mid has a length of at least L. 
      
      now if we don't increase lo, then there's a chance of the binary loop entering an infinite loop. so we take the ceiling of mid, and then similar things happen:
      if this checks out too, then the binary search could set into a infinite loop. so finally, we change the binary search condition to "lo < mid" to finally fix that.
      why didn't we just directly change the binary search condition instead of changing the "mid" calculation method? idk honestly.

*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3000 + 1;
pair <int, int> nums[MAX_N];
int N, L;
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> L;
        // L = min(L, N);
        for (int i = 1; i <= N; i++) {
            cin >> nums[i].first;
            nums[i].second = i;
        }
        sort(nums + 1, nums + N + 1, greater <pair <int, int>> ());
        int base_ans = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = i+1; j <= N; j++) {
                if (nums[i].first == nums[j].first)
                    base_ans = max(base_ans, abs(nums[i].second - nums[j].second));
            }
        }
        int lo = base_ans, hi = N;
        while (lo < hi) {
            int mid = (lo + hi+1) / 2;
            vector <int> dp(N+1);
            
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j < i; j++) {
                    if (abs(nums[i].second - nums[j].second) >= mid)
                        dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            int len = *max_element(dp.begin(), dp.end()) + 1;
            if (len >= L)
                lo = mid;
            else
                hi = mid-1;
        }
        cout << lo << '\n';

    }
}
