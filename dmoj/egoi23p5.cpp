/*
    the main logic: the first two numbers can always stand next to eachother, so we put them in the line
    first. after that we iterate over the remaining people and check if the ith person can be put next to
    the first person and if we can then put them there. if not, check and do the same for the last element.
    if the ith person cannot stand next to any of these, then they can (and will definitly) be placed in
    between two people in the line with whom they are both good. 

    why is it guaranteed that such a pair of people will exist? intuitively, we want to maximize the number
    good people over bad people, where a good person is someone the ith person can stand next to and a bad
    person is someone that the ith person cannot stand next to. now in the case where the list has an odd
    number of people, there will be one more good person than a bad person. this means that two good people
    will stand next to eachother IF they are not already on the ends of the line. if they are on the ends
    of the line, then we can just place the ith person on the end.

    in the case where the number of people in the list are even, the number of good people will be equal to
    the number of bad people. if we arrange the people like this:
    g b g b g b
    we are guaranteed to get a good person on either end, so we can place the ith person on the end next to them.
    but if we have bad people on both ends, then the ordering would be like this:
    b g g b g b
    as shown here, it is guaranteed that two good people will stand next to eachother. this is why the solution 
    described above works.
    
*/
#include <iostream>
#include <vector>
#include <deque>
#include <set>
using namespace std;
int main() {
    int n;
    cin >> n;
    deque <int> dq;
    vector <set <int>> good(n);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int x;
            cin >> x;
            if (j < (i+1)/2)   
                good[i].insert(x);
        }
    }
    dq.push_back(0);
    for (int i = 1; i < n; i++) {
        int a = dq.front();
        int b = dq.back();
        if (good[i].find(a) != good[i].end()) {
            dq.push_front(i);
        } else if (good[i].find(b) != good[i].end()) {
            dq.push_back(i);
        } else {
            for (int j = 1; j + 1 < dq.size(); j++) {
                a = dq[j], b = dq[j+1];
                bool gooda = good[i].find(a) != good[i].end();
                bool goodb = good[i].find(b) != good[i].end();
                if (gooda && goodb) {
                    dq.insert(dq.begin() + j + 1, i);
                    break;
                }
            }
        }
    }
    for (auto i : dq)
        cout << i << ' ';
    cout << '\n';
}
