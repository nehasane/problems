/*
  this was a very simple problem.
  maintain a "desired frequency" array, which stores the frequencies of the the individual letters in string W.
  next, maintain a sliding window of size G on string S, and increment the frequencies of the the individual 
  letters in the window in a separate frequency array. compare the frequency arrays of the window and string W
  and if they are the same, then increment the answer by 1. every time the window shifts, remove the starting
  letter of window by decrementing the corresponding value in the window's frequency array.
  
  since the time limit is tight and the time complexity is 57N ('A' to 'z' in ascii is 57), make sure to use fastIO.
  
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int G, N;
    cin >> G >> N;
    string W, S;
    cin >> W >> S;
    vector <char> des(123);
    for (int i = 0; i < G; i++)
        des[W[i]]++;
    vector <char> window(123);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        window[S[i]]++;
        if (i >= G-1) {
            bool increment = true;
            for (int i = 'A'; i <= 'z'; i++) {
                if (window[i] != des[i])
                    increment = false;
            }
            if (increment)
                ans++;
            window[S[i - G + 1]]--;
        }
    }
    cout << ans << '\n';
}
