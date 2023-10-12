/*
    for subtask 1:
    there are 6 letters in the cowphabet. this means we can iterate over 
    all 6! possible permutations of the cowphabet and find the cost for
    each. we can do this smartly by maintaining a table (in the code
    it's called 'adjacent') where adjacent[a][b] stores the number of 
    occurences where letter b comes exactly before letter a. then while
    looping through the permutations we can do this: suppose according to
    the permutation letter a must come before letter b. if in the
    string the letter b comes before the letter a, then it means that the
    cowphabet is being sung twice: once to cover letter a and once to cover
    letter b. so we can simply add adjacent[a][b] to the answer

    for subtask 2:
    iterating over all the permutations of the cowphabet will take too long
    since the number of letters in the cowphabet is now 20. instead, we can
    figure out the minimum cost when considering only a subset of the letters  
    in the cowphabet. let dp[mask] represent this value.

    let's say we want to add a letter to this mask. we can loop over all
    letters in the mask and add adjacent[new_letter][letter] to 
    dp[mask + (1 << new_letter)].
    note: it doesn't matter whether we add adjacent[new_letter][letter]
    to the answer or adjacent[letter][new_letter] since we don't care
    about the order of the letters in the cowphabet; we only care about
    the cost.

*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
int main() {
    string s;
    cin >> s;
    map <char, int> id;
    int n = 0; // stores number of unique letters
    for (int i = 0; i < s.size(); i++) {
        if (id.find(s[i]) == id.end())
            id[s[i]] = n++;
    }
    vector <vector <int>> adjacent(n, vector <int> (n));
    for (int i = 1; i < s.size(); i++) {
        adjacent[id[s[i]]][id[s[i-1]]]++;
    }
    string uniq;
    for (auto i : id)
        uniq.push_back(i.second);
    int ans = 1e9;
    vector <int> dp((1 << n), 1e9);
    dp[0] = 1;
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (!(i & (1 << j)))
                continue;
            int sum = dp[i ^ (1 << j)];
            for (int k = 0; k < n; k++) {
                if (i & (1 << k))
                    sum += adjacent[j][k];
            }
            dp[i] = min(dp[i], sum);
        }
    }
    cout << dp[(1 << n) - 1] << '\n';
}
