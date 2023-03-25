/*  
    when the problem mentions a bitstring, N = 1e5 and the words "the
    output is 1 if exactly one of the inputs is 1", you should think
    of XOR (razzle dazzle).
    
    lets call the og string C, its first generation C1, second generation
    C2 and so on and so forth
    
    C1[i] = C[i-1] XOR C[i+1]
    C2[i] = C1[i-1] XOR C1[i+1]
    
    by substituting the correspoinding values of C[] into C1[i-1] and C1[i+1],
    we get
    C2[i] = C[i-2] XOR C[i] XOR C[i] XOR C[i+2]
          = C[i-2] XOR C[i+2]
          
          
   to generalise the equation, we get
   Ck[i] = C[i - k] XOR C[i + k] 
   where k is the generation number
   
   so for each bit in the of bitstring, we apply the above equation to get the answer
   BUT WAIT
   it's not so simple (because it's 20pts)... k must be a power of 2 (because of 
   some weird empirical conclusion), so we break T into its powers of 2 and 
   apply the above equation.
   
   for example, if T = 10;
   we apply the equation for T = 8, calculate the answer as if we only had 8 generations,
   and then apply T = 2 on the last answer.
    
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ll = long long;

int main() {
    ll N, T;
    cin >> N >> T;
    vector <int> nums(N);
    string s;
    cin >> s;
    for (int i = 0; i < N; i++)
        nums[i] = s[i] - '0';

    vector <int> tp(N);
    
    for (ll i = 0; i < 50; i++) { // 50 is log2(1e15)
        if ((1LL << i) & T) {
            ll k = 1LL << i;
            k %= N;
            for (ll j = 0; j < N; j++) {
                int d = nums[(j - k + N) % N] ^ nums[(j + k) % N];
                tp[j] = d;
            }
            nums = tp;
        }
    }
    for (int i = 0; i < N; i++)
        cout << nums[i];
    cout << '\n';


}
