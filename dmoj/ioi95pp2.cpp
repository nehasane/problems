/*

think of this as a graph proble, where the words are nodes, and a directed edge is drawn from word1 to word2, if by adding some letters to the end of word1, we get word2.
In other words, a directed edge is drawn from word1 to word2 if word1 is a subtring of word2.

in the end, there will be a directed acyclic graph(s) of words. all that's left to do is run a dfs from every node(not visited!) and calculate the length of the 
longest path, assuming that the current node is the end of the path.

BUT WAIT
i tried that, but i got MLE in the last test case:(.
so, instead of doing a dfs(which requires a visited array, and adjacency list and stuff that requires loads of memory), do this:
since the parent of the node (which is also the end of the path) is a substring of the node, we can pop_back() letters from the current word (let's call this modifed word mword),
and find the length of the longest path that ended mword.

this is dp, with an underlying logic of graphs
dp equation for this is:
    dp[curr_word_index] = max(dp[curr_word_index], dp[mword_index] + 1);
   
to quickly (and straightforwardly) find out the index of mword, i use a map, where mword is the key and the index of mword in the dp array is the mapped value.

*/
#include <bits/stdc++.h>
using namespace std;
vector <int> dp;
map <string, int> id;
vector <int> came_from;
vector <string> ss;
int main() {
    int i = 0;
    string mword;
    cin >> mword;
    int max_len = 0, end_node = 0;
    while (mword != ".") {
        dp.push_back(1);
        ss.push_back(mword);
        came_from.push_back(0);
        int parent = -1;
        id[mword] = i;
        while (mword.size() > 0) {
            mword.pop_back();
            if (id.find(mword) != id.end()) {
                if (dp[id[mword]] + 1 > dp[i]) {
                    parent = id[mword];
                    dp[i] = dp[id[mword]] + 1;
                }
            }
            came_from[i] = parent;
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            end_node = i;
        }
        i++;
        cin >> mword;
    }
    vector <string> ans;
    while (end_node != -1) {
        ans.push_back(ss[end_node]);
        end_node = came_from[end_node];
    }
    reverse(ans.begin(), ans.end());
    for (auto i : ans)
        cout << i << '\n';
}
