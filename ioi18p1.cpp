/*
    my code is quite repetitive, but the idea is simple.
    guess a letter for the first letter of the sequence. if the
    grader returns 0, then that letter is not the first letter of
    the sequence. if the same happens when two other letters are
    guessed, then we know that the fourth letter is the starting
    letter of the sequence.
    
    now for the remaining positions in the string, we only have to 
    choose from 3 letters. if we use the same logic as above, the
    number of queries in the worst case will be 2N + 1, which
    will be enough to fetch 25 points.
    
    for 97 points, we need to find each letter (except the first and
    last letter) using one query. take advantage of the fact that we
     are allowed to pass a large(4N) string to the press() function.
     
     let's assume that the first letter of the sequence is 'A'. This
     means that 'A' will never be repeated in the string again. let s
     be the string that we have determined so far.
     
     to determine the ith letter, pass a query like this:
     s + 'B' + s + 'XB' + s + 'XX' + s + 'XY'
     if the ith letter is 'B', the the press() function will return
     s.size() + 1. if the ith letter is 'X' then the pres() function
     will return s.size() + 2. but if it returns s.size(), the it will
     return 'Y'.
     
*/
#include <bits/stdc++.h>
using namespace std;
// string real_S;
// int press(string s) {
//     for (int i = 1; i <= real_S.size(); i++) {
//         string tp = real_S.substr(0, i);
//         if (s.find(tp) == string::npos)
//             return i-1;
//     }
//     return real_S.size();
// }
char add_letter(string S, int res) {
    if (S[0] == 'A') {
        if (res == S.size() + 1)
            return 'B';
        else if (res == S.size() + 2)
            return 'X';
        else
            return 'Y';
    } else if (S[0] == 'B') {
        if (res == S.size() + 1)
            return 'A';
        else if (res == S.size() + 2)
            return 'X';
        else
            return 'Y';
    } else if (S[0] == 'X') {
        if (res == S.size() + 1)
            return 'A';
        else if (res == S.size() + 2)
            return 'B';
        else
            return 'Y';
    } else {
        if (res == S.size() + 1)
            return 'A';
        else if (res == S.size() + 2)
            return 'B';
        else
            return 'X';
    }
}
string guess_sequence(int N) {
    string S;
    int res;
    S = "A";
    res = press(S);
    if (res == 0) {
        S = "B";
        res = press(S);
        if (res == 0) {
            S = "X";
            res = press(S);
            if (res == 0) {
                S = "Y";
            }
        }
    }
    for (int i = 2; i < N; i++) {
        string tp;
        if (S[0] == 'A') {
            tp.append(S);
            tp.append("B");
            tp.append(S);
            tp.append("XB");
            tp.append(S);
            tp.append("XX");
            tp.append(S);
            tp.append("XY");
        } else if (S[0] == 'B') {
            tp.append(S);
            tp.append("A");
            tp.append(S);
            tp.append("XA");
            tp.append(S);
            tp.append("XX");
            tp.append(S);
            tp.append("XY");
        } else if (S[0] == 'X') {
            tp.append(S);
            tp.append("A");
            tp.append(S);
            tp.append("BA");
            tp.append(S);
            tp.append("BB");
            tp.append(S);
            tp.append("BY");
        } else {
            tp.append(S);
            tp.append("A");
            tp.append(S);
            tp.append("BA");
            tp.append(S);
            tp.append("BB");
            tp.append(S);
            tp.append("BX");
        }
        res = press(tp);
        S.push_back(add_letter(S, res));
    }
    if (N == 1)
        return S;
    vector <char> letters = {'A', 'B', 'X', 'Y'};
    for (int i = 0, done = 0; i < 4 && done < 2; i++) {
        if (letters[i] == S[0])
            continue;
        done++;
        S.push_back(letters[i]);
        res = press(S);
        if (res == N)
            break;
        S.pop_back();
    }
    if (S.size() < N) {
        if (S[0] == 'Y')    
            S.push_back('X');
        else
            S.push_back('Y');
    }
    return S;
}
// int main() {
//     cin >> real_S;
//     cout << guess_sequence(real_S.size()) << '\n';
// }
