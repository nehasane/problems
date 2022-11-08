/*
    for each offer we have two choices: pick the offer, or don't pick the 
    offer. if we pick the offer, then we could choose to pick it again
    afterwards or not, but we can take care of that afterwards. 
    
    if we pick an offer, assuming that we have a least those many items of
    each type in the cart, then we just have to take care of the remaining 
    items in the cart. if we don't pick the offer now, then it makes no sense
    to pick it afterwards. therefore, we have the dp equation:
    dp[cart][offer_id] = min(solve(cart ⊄ items_in_offer, offer_id),
        solve(cart, offer_id + 1)
    with this recursive dp equation, we take care of the case we we might have
    to take the same offer mltiple times.
    
    a simple brute force using recursion wil fetch 80 points. to get the 
    remaining 20, we need memoization. one way to do this is to use 
    bitmasking (separate the integer into segments of length five, where each bit
    in a single segment is 1 if a particular product is in the cart, and 0 otherwise.
    this cart will yield a numeric value, which can be used as an index to the dp
    array). this method was too complicated, so i used a 5d array, where each 
    dimension represents the amt of each product cuurently in the cart. this 
    approach got me 80pts again, with 2 WAs, so find the bug out afterwards.
    
*/
#include <bits/stdc++.h>
using namespace std;
int S;
vector <vector <pair <int, int>>> offers;
vector <int> offer_val;
map <int, int> segs;
map <int, int> product_costs;
bool ready[6][6][6][6][6];
int dp[6][6][6][6][6];
int solve(int offer_id, vector <int> amts) {
    int left = 0;
    for (auto i : amts)
        left += i;
    if (left == 0)      
        return 0;
    if (offer_id == S) {
        int cost = 0;
        for (int i = 0; i < 5; i++)
            cost += amts[i] * product_costs[i];
        return cost;
    }
    if (ready[amts[0]][amts[1]][amts[2]][amts[3]][amts[4]])
        return dp[amts[0]][amts[1]][amts[2]][amts[3]][amts[4]];
    bool take_offer = true;
    for (auto i : offers[offer_id]) {
        if (i.second > amts[segs[i.first]]) {
            take_offer = false;
            break;
        }       
    }
    int ans = solve(offer_id+1, amts);
    if (take_offer) {
        for (auto i : offers[offer_id]) {
            amts[segs[i.first]] -= i.second;
        }
        ans = min(solve(offer_id, amts) + offer_val[offer_id], ans);
        for (auto i : offers[offer_id]) {
            amts[segs[i.first]] += i.second;
        }
    }
    ready[amts[0]][amts[1]][amts[2]][amts[3]][amts[4]] = true;
    dp[amts[0]][amts[1]][amts[2]][amts[3]][amts[4]] = ans;
    return ans;
}
int main() {
    cin >> S;
    for (int i = 0; i < S; i++) {
        offers.emplace_back();
        int n;
        cin >> n;
        for (int j = 0; j < n; j++) {
            int code, amt;
            cin >> code >> amt;
            offers.back().push_back({code, amt});
        }
        offer_val.emplace_back();
        cin >> offer_val.back();
    }
    int cart_items;
    cin >> cart_items;
    vector <int> amts(5, 0);
    int cart = 0;
    for (int i = 0; i < cart_items; i++) {
        int code, amt, cost;
        cin >> code >> amt >> cost;
        segs[code] = i;
        product_costs[i] = cost;
        amts[i] = amt;
    }
    cout << solve(0, amts) << '\n';
}
