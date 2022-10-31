/*

  this problem was quite simple
  for gondola sequence checking (subtasks 1, 2, 3):
      there are only 2 ways a gondola sequence could be invalid:
           a) it contains repeating nummbers: pretty easy to look for - use a set, while adding
           numbers to the set, check if the number already exists.
           b) the sequence contains OG numbers that are out of order: create a list of all the OGs
           in the sequence, find the position where gondola number 1 is supposed to be, and then
           use that position as a reference to figure out the supposed positions of the other OGs.
      we don't care about the positions of the non-OG gondolas, since the OGs could have broken
      down in any order, which would change the positions of the non-OGs.
  for replacement sequence (subtasks 4, 5, 6):  
      for this problem, a direct simulation would suffice
          first, locate the positions of the OG gondolas and place them in the repalcementSeq array.
          (if none of the OG gondolas exist, then just assign them arbitrarily). create a list of
          all the gondolas that were used to replace the broken ones, and sort them (since they were
          used as a replacement in ascending order).
          then loop over every non-OG gondola from n+1 to the last gondola replacement. check:
              does it exist in the list we made? if it does, then it means that it never broke down,
              and wasn't replaced by another gondola.
              if it doesn't exist in the list, then it means that the gondola broke down at a later time.
              in that case, just assign it to a position where a later gondola will replace it eventually.
   for countReplacement (subtasks 7, 8, 9, 10):
      to get subtasks 7 and 8, answer the following question: if we placed gondola i (i from n+1 to last
      replacement gondola) at position j (j from 0 to n-1), how many possible ways can we place the
      remaining gondolas. this calls for a dp solution:
      for j from 0 to N-1
          sequence[j] = i;
          dp[i] += dp[i+1]
          sequence[j] = og_sequence[j]
      of course, we have to check if it's possible to place a gondola i and position j:
          if the gondola that is already in place is OG, that means it never broke down and therefore
          never needs to be replaced. ignore these gondolas
          if the gondola that is already in place is smaller that the gondola we currently need to place,
          the gondola doesn't break down either, so we can ignore it.
      this approach has a timecomplxity of O(N * maximum value in inputSeq) ~~ O(N^2)
      
      for subtask 9 we need to optimise it further
      notice that, in short, we can place a gondola in any position where in the end a greater gondola
      will be placed. we can binary search on the number of such positions and then just multiply the dp
      answer to this gondola by the number of such states
      dp equation
      dp[i] = dp[i+1] * number_of_greater_gondolas
      but, if the gondola exists in the final sequence, then it has a fixed position, in which case the dp
      answer to this gondolas is simply the answer to the number of ways the next gondola can be placed.
      in the case where none of the OGs exist, multiply the final result by N, since the dp function
      calculates the answer assuming that the OGs have a fixed position.
      this has a time complexity of O (maximum gondola in final sequence)
      
      for subtask 10:
        the previous approach will TLE, since ht maximum gondola in the final sequence here is 10^9.
        instead of looping from every gondola from n+1 to maximum gondola (10^9), we can loop over every
        non OG gondola (in sorted order).
        
        take N to be 3, and the non-OGs to be 70, 110, 10^9
        - all the gondolas from 4 -> 69 can be placed in 3 positions, so number of ways to place all these 
        gondolas is 3^(69-4+1)
        - gondola 70 has one position
        - all the gondolas from 71 -> 109 can be placed in 2 positions, so number of ways to place all these 
        gondolas is 2^(109-71+1)
        - gondola 110 can placed placed in one position
        - all the gondolas from 111 -> 9999999999 can be placed in one position, so number of ways to place all these 
        gondolas is 1^(999999999-111+1)
        - gondola 10^9 can be placed in one position
        the answer is the product of all these numbers
        
        to calculate the exponential numbers quickly (and correctly using modulo), do the typical modular exponential
        thing (see code)

*/
#include <bits/stdc++.h>
using namespace std;
int valid(int n, int inputSeq[]);
int replacement(int n, int gondolaSeq[], int replacementSeq[]);
int countReplacement(int n, int inputSeq[]);
const int MOD = 1e9 + 9;
const int MAX_N = 1e5;
vector <int> replaced;
int valid(int n, int inputSeq[]) {
    vector <pair <int, int>> ogs;
    set <int> seen;
    bool ans = true;
    for (int i = 0; i < n; i++) {
        if (inputSeq[i] <= n) {
            ogs.push_back({inputSeq[i], i});
        }
        if (seen.find(inputSeq[i]) != seen.end())
            ans = false;
        seen.insert(inputSeq[i]);
    }
    if (!ans)
        return ans;
    sort(ogs.begin(), ogs.end());
    for (int i = 0; i + 1 < ogs.size(); i++) {
        if ((ogs[i+1].first - ogs[i].first + ogs[i].second) % n != ogs[i+1].second)
            ans = false;
    }
    if (ogs.size() >= 2 && (ogs.back().second + ogs.front().first + n - ogs.back().first) % n != ogs.front().second)
        ans = false;
    return ans;
}
int replacement(int n, int gondolaSeq[], int replacementSeq[]) {
    vector <pair <int, int>> nums;
    int minv = INT_MAX, pos = 0;
    for (int i = 0; i < n; i++) {
        if (gondolaSeq[i] > n) {
            nums.push_back({gondolaSeq[i], i});
        }
        if (minv > gondolaSeq[i]) {
            minv = gondolaSeq[i];
            pos = i;
        }
    }
    if (nums.size() == 0) {
        return 0;
    }
    sort(nums.begin(), nums.end());
    
    vector <int> og(n);
    if (minv > n)   
        minv = 1;
    pos = (pos - minv + 1 + n) % n;
    for (int i = 0, x = 1; i < n; i++, x++)
        og[(i + pos) % n] = x;
    int p = 0;
    for (int i = n+1; i <= nums.back().first; i++) {
        pair <int, int> tp = {i, 0};
        auto x = lower_bound(nums.begin(), nums.end(), tp);
        replacementSeq[p++] = og[x->second];
        // ans[i - n - 1] = og[x->second];
        og[x->second] = i;
    }

    return nums.back().first - n;

}   
long long exp_mod(long long base, long long exp) {
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    long long tp = exp_mod(base, exp / 2);
    long long ans = (tp * tp) % MOD;
    if (exp % 2 == 1)
        ans = (ans * base) % MOD;
    return ans;
}
int countReplacement(int n, int inputSeq[]) {
    if (!valid(n, inputSeq))
        return 0;
    int minv = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (inputSeq[i] > n)
            replaced.push_back(inputSeq[i]);
        minv = min(minv, inputSeq[i]);
    }
    replaced.push_back(n);
    sort(replaced.begin(), replaced.end());
    long long ans = 1;
    for (int i = 1, p = replaced.size() - 1; i < replaced.size(); i++, p--) {
        ans = (ans * exp_mod(p, replaced[i] - replaced[i-1] - 1)) % MOD;
    }
    if (minv > n)
        ans = (ans * n) % MOD;
    return ans;
}
