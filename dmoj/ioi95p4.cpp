/*

    the code is quite long (sloppy code), but the idea is quite simple.
    you are given some words, points for each letter you use in a word, and a "dictionary",
    which contains a list of letters that you have chosen. A letter may be used up to those
    many times in a word.
    
    first we need to find out the maximum score achievable. we do this by iterating over
    all words and all pairs of words, checking if they are "valid" (will be explained further
    on) and storing a running maximum of all valid scores.
    
    once we know the maximum score, we need to make a list of words and pairs of words that
    have the maximum score. we repeat the process above, and simply add the words/pair of words
    to an answer array if they have the maximum score.
    
    now to check if a word is valid or not:
        - frequency of each individual letter is not more than the frequency of the same
        individual letter in the dictionary
        - each letter in the word actually exists in the dictionary
    the same goes for checking a pair of words; only keep track of the joint frequency of
    individual letters and compare that against the frequency of the same letter in the 
    dictionary.
    

*/
#include <bits/stdc++.h>
using namespace std;
vector <string> words;
vector <int> scores;
int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    map <char, int> pts;
    vector <int> max_freq(26);
    pts['a'] = 2;
    pts['b'] = 5;
    pts['c'] = 4;
    pts['d'] = 4;
    pts['e'] = 1;
    pts['f'] = 6;
    pts['g'] = 5;
    pts['h'] = 5;
    pts['i'] = 1;
    pts['j'] = 7;
    pts['k'] = 6;
    pts['l'] = 3;
    pts['m'] = 5;
    pts['n'] = 2;
    pts['o'] = 3;
    pts['p'] = 5;
    pts['q'] = 7;
    pts['r'] = 2;
    pts['s'] = 1;
    pts['t'] = 2;
    pts['u'] = 4;
    pts['v'] = 6;
    pts['w'] = 6;
    pts['x'] = 7;
    pts['y'] = 5;
    pts['z'] = 7;
    
    string s;
    cin >> s;
    while (s != ".") {
        words.push_back(s);
        cin >> s;
    }
    scores.resize(words.size());
    string dict;
    cin >> dict;
    vector <bool> present(26);
    vector <bool> all_cov(words.size(), true);
    for (auto i : dict) {
        present[i - 'a'] = true;
        max_freq[i - 'a']++;
    }
    int max_score = 0;
    for (int i = 0; i < words.size(); i++) {
        bool valid = true;
        vector <int> freq(26);
        for (auto x : words[i]) {
            freq[x - 'a']++;
            if (!present[x - 'a'] || freq[x - 'a'] > max_freq[x - 'a'])
                valid = false;
        }
        for (auto j : words[i]) {
            if (present[j - 'a'])
                scores[i] += pts[j];
            else
                all_cov[i] = false;
        }
        if (valid && all_cov[i])
            max_score = max(max_score, scores[i]);
    }
    vector <pair <string, string>> ans;
    for (int i = 0; i < words.size(); i++) {
        if (!all_cov[i])
            continue;
        for (int j = i; j < words.size(); j++) {
            if (!all_cov[j])
                continue;
            int tp_score = scores[i] + scores[j];
            bool valid_pair = true;
            vector <int> freq(26);
            for (auto x : words[i]) {
                if (!present[x - 'a'])
                    valid_pair = false;
                freq[x - 'a']++;
            }
            for (auto x : words[j]) {
                if (!present[x - 'a'])
                    valid_pair = false;
                freq[x - 'a']++;
            }
            for (int x = 0; x < 26; x++) {
                if (freq[x] > max_freq[x]) {
                    valid_pair = false;
                    break;
                }
            }
            if (valid_pair)
                max_score = max(max_score, tp_score);
        }
    }
    for (int i = 0; i < words.size(); i++) {
        bool valid = true;
        vector <int> freq(26);
        for (auto x : words[i]) {
            freq[x - 'a']++;
            if (!present[x - 'a'] || freq[x - 'a'] > max_freq[x - 'a'])
                valid = false;
        }
        if (valid && scores[i] == max_score && all_cov[i]) 
            ans.push_back({words[i], ""});
    }
    for (int i = 0; i < words.size(); i++) {
        if (!all_cov[i])
            continue;
        for (int j = i; j < words.size(); j++) {
            if (!all_cov[j])
                continue;
            int tp_score = scores[i] + scores[j];
            bool valid_pair = true;
            vector <int> freq(26);
            for (auto x : words[i]) {
                freq[x - 'a']++;
                if (!present[x - 'a'])
                    valid_pair = false;
            }
            for (auto x : words[j]) {
                freq[x - 'a']++;
                if (!present[x - 'a'])
                    valid_pair = false;
            }
            for (int x = 0; x < 26; x++) {
                if (freq[x] > max_freq[x]) {
                    valid_pair = false;
                    break;
                }
            }
            if (valid_pair && tp_score == max_score)
                ans.push_back({min(words[i], words[j]), max(words[i], words[j])});
        }
    }
    sort(ans.begin(), ans.end());
    cout << max_score << '\n';
    for (auto i : ans) {
        if (i.second == "")
            cout << i.first << '\n';
        else
            cout << i.first << ' ' << i.second << '\n';
    }
}
