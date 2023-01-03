/*
    for each person, there will be a certain number of spots available.
    let dp[n][mask] be the maximum score achievable if we have processed 
    n-1 people and there are certain spots in the football team that are
    available (represented by mask). for each person we have two options:
    put them on the team, or don't. if we put them in the team then we
    have another P options. we can try each of them out (if those spot
    s are available). this gives us the dp equation: 
    dp[n][mask] = max(dp[n][mask], dp[n+1][mask including pth spot]) 
    for all p available spots.
    
    if we choose not to put the person in the team, then we must decide 
    whether to put them in the audience or not. here's greedy logic: since
    the player has not been pu on the team, it must be part of the top K 
    people in terms of score added by being placed in the audience. we can
    determine this by sorting the people in decreasing audience value, and
    then using the mask to determine whether we need to place more people 
    in the audience or not: count the number of ones in the mas. this tells
    us the number of people put in the team. since we have processed n people
    so far, and anybody that is not on the team must be in the audience 
    (assuming that we haven't fill the K spots so far, the number of spots 
    left on the team is (number of people processed so far - number of 
    people on the team) if this value is postive, that means that there are
    some spots in the audience. since the people are sorted in descending 
    order of audience values, it is always optimal to place a player in the
    audience if they aren't in the team.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N, P, K;
struct person {
    ll audience;
    vector <ll> team;
};
const int MAX_N = 1e5;
person people[MAX_N];
bool comp(person a, person b) {
    return a.audience > b.audience;
}
const int MAX_MASK = (1 << 7);
ll dp[MAX_N][MAX_MASK];
bool ready[MAX_N][MAX_MASK];
ll solve(int n, int mask) {
    if (n == N)
        return 0;
    if (ready[n][mask])
        return dp[n][mask];
    ll ans = solve(n+1, mask);
    if (K - (n - __builtin_popcount(mask)) > 0)
        ans += people[n].audience;
    for (int i = 0; i < P; i++) {
        if (!((1 << i) & mask)) {
            ans = max(ans, solve(n+1, mask | (1 << i)) + people[n].team[i]);
        }
    }
    ready[n][mask] = true;
    dp[n][mask] = ans;
    return ans;
}
int main() {
    cin >> N >> P >> K;
    for (int i = 0; i < N; i++) {
        cin >> people[i].audience;
    }
    for (int i = 0; i < N; i++) {
        people[i].team.resize(P);
        for (int j = 0; j < P; j++)
            cin >> people[i].team[j];
    }
    sort(people, people + N, comp);
    cout << solve(0, 0) << '\n';
}
