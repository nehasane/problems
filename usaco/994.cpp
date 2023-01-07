/*
    this is a typical (just speeded up) 3SUM problem,
    coupled with 2D prefix sums
    
    in 3SUM, we usually have a map containing the frequency of
    pairs of sum x for all pairs of numbers up to but not
    including i. if for nums[i] we can find -nums[i] in the map,
    then we add those to out answer and then add all pairs of
    numbers that include nums[i] in it to the map
    
    however in this version, we also need to know the range in
    which the numbers in the triplets fall. we could do this
    by storing the left and right values of the pair along 
    with the sum in the map, but with the tight constraints, this
    will get a TLE and MLE.
    
    instead, we have two nested loops: the outer signifies the 
    start of the range of numbers and the inner loop signifies the
    end of the range of numbers. all numbers inside the range (but
    excluding the start and end) can be considered as the 3rd
    number in the triplet.
    
    every time we find a triplet, we add it to a 2D pfx sum table,
    where pfx[i][j] represents the number of triplets that are 
    present in the range i..j
    
    calculate the 2D pfx sums the standard way
   
    the range l..r contains all the ranges l+1..r, l+2..r, l..l,
    r..r, l..r-1 etc.
    
    when you draw out the table and check, you'll see that
    the answer to the query l..r is the sum of all the boxes in
    the pfx sum square (l, l), (l, r), (r, l), (r, r). just
    query this box and that's the answer.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX_N = 5000 + 2;
const int MAXA = 1e6 + 1;
int nums[MAX_N];
ll pfx[MAX_N][MAX_N];
ll freq[2*MAXA];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    
    int N, Q;
    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
        cin >> nums[i];
    
    for (int i = 1; i <= N; i++) {
        for (int j = i+2; j <= N; j++) {
            int n1 = nums[i];
            int n2 = nums[j];
            int n3 = -(n1 + n2);
            freq[nums[j-1] + MAXA]++;
            if (n3 + MAXA < 2*MAXA && n3 + MAXA >= 0)
                pfx[i][j] = freq[n3 + MAXA];
        }
        for (int j = i+1; j < N; j++)
            freq[nums[j] + MAXA]--;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            pfx[i][j] = pfx[i][j] + pfx[i-1][j] + pfx[i][j-1] - pfx[i-1][j-1];
        }
    }
    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << pfx[r][r] - pfx[r][l-1] - pfx[l-1][r] + pfx[l-1][l-1] << '\n';
    }
    return 0;
}
