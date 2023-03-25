/*
    this is a simple a straight range query problem, where we perform a cell update
    and a 2d range query. for this, we use a 2d fenwick tree since the implementation
    is shorter and we only have to perform sum queries.
    
    the 6th last line of the program is the standard way of finding the 2d prefix sum
    (https://usaco.guide/silver/more-prefix-sums?lang=cpp)
*/
#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree2D {
    vector <vector <int>> bit;
    int n, m;
    FenwickTree2D(){}
    FenwickTree2D(int n, int m) : n(n), m(m) {
        bit.assign(n, vector <int> (m));
    }
    int sum(int x, int y) {
        int sum = 0;
        for (int i = x; i > 0; i = (i & (i+1)) - 1) {
            for (int j = y; j > 0; j = (j & (j+1)) - 1)
                sum += bit[i][j];
        }
        return sum;
    }
    // point update
    void update(int x, int y, int a) {
        for (int i = x; i < n; i = i | (i + 1)) {
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += a;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int S;
    cin >> S >> S;
    FenwickTree2D tree2d(S+1, S+1);
    
    int mode;
    cin >> mode;
    while (mode != 3) {
        if (mode == 1) {
            int x, y, a;
            cin >> x >> y >> a;
            x++; y++;
            tree2d.update(x, y, a);
        } else {
            int l, b, r, t;
            cin >> l >> b >> r >> t;
            l++; b++; r++; t++;
            cout << tree2d.sum(r, t) - tree2d.sum(r, b-1) - tree2d.sum(l-1, t) + tree2d.sum(l-1, b-1) << '\n';
        }
        cin >> mode;
    }

}
