/*
    2D SEGMENT TREES!!
    
    a naive solution we precompute 2D prefix sums for the entire matrix,
    calculate the sum of values for every possible b*a square and
    for each of these squares, calculate the minimum possible sum of a
    d*c tomb. the maximum different of all these is the answer. This will
    fetch 62 points
    
    to get a full 100, we ned to find the optimal tomb faster - for this
    we use a 2d segment tree - pretty standard. just fill the tree with the
    value of the tombs rather than the values of the individual blocks
    
    loop over each of b*a blocks and query the segment tree for the optimal
    tomb (remember to leave a one cell thick border in the query). take the 
    maximum possible block and record its top-left coordinates.
    
    to find the coordinates of the tomb, loop over every possible tomb in the
    block to find the right one.
  
    
*/
#include <bits/stdc++.h>
using namespace std;
vector <vector <int>> grid, tree, pfx;
int seg_szN, seg_szM;
int M, N, A, B, C, D;
void build() {
    // fill the sum of values in a D*C tomb in the segment tree
    for (int i = 1; i + 1 + D <= N; i++) {
        for (int j = 1; j + 1 + C <= M; j++) {
            int edx = i + D;
            int edy = j + C;
            tree[i + seg_szN][j + seg_szM] =  pfx[edx][edy] - pfx[i][edy] - pfx[edx][j] + pfx[i][j];
        }
    }
    // fill regular segment tree values
    for (int i = 0; i < N; i++) {
        for (int j = seg_szM-1; j >= 1; j--)
            tree[i + seg_szN][j] = min(tree[i + seg_szN][j*2], tree[i + seg_szN][j*2+1]);
    }
    // fill in the rest of the numbers in the seg table
    for (int i = seg_szN-1; i >= 1; i--) {
        for (int j = 1; j < seg_szM * 2; j++)
            tree[i][j] = min(tree[i*2][j], tree[i*2+1][j]);
    }
}
int query_second_dimension(int am, int bm, int nodem, int oglm, int ogrm, int n) {
    if (am > ogrm || bm < oglm)
        return INT_MAX;
    if (am >= oglm && bm <= ogrm)
        return tree[n][nodem];
    int mid = (am + bm) / 2;
    int res = min(query_second_dimension(am, mid, nodem * 2, oglm, ogrm, n),
                query_second_dimension(mid+1, bm, nodem*2+1, oglm, ogrm, n));
    return res;
}
int query_first_dimension(int an, int bn, int noden, int ogln, int ogrn, int am, int bm) {
    if (an > ogrn || bn < ogln)
        return INT_MAX;
    if (an >= ogln && bn <= ogrn)
        return query_second_dimension(seg_szM, seg_szM * 2 - 1, 1, am, bm, noden);
    int mid = (an + bn) / 2;
    int res = min(query_first_dimension(an, mid, noden * 2, ogln, ogrn, am, bm),
                query_first_dimension(mid+1, bn, noden*2+1, ogln, ogrn, am, bm));
    return res;
}
int main() {
    cin >> M >> N >> A >> B >> C >> D;
    
    grid.resize(N, vector <int> (M));
    pfx.resize(N+1, vector <int> (M+1));
    seg_szN = pow(2, ceil(log2(N)));
    seg_szM = pow(2, ceil(log2(M)));
    tree.resize(seg_szN * 2, vector <int> (seg_szM * 2, INT_MAX));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
            pfx[i+1][j+1] = grid[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            pfx[i][j] += pfx[i-1][j] + pfx[i][j-1] - pfx[i-1][j-1];
        }
    }
    build();
    // pyramid x, pyramid y, tomb x, tomb y
    int pyx, pyy, tx, ty, area = 0, tomb_area;
    for (int i = 0; i + B <= N; i++) {
        for (int j = 0; j + A <= M; j++) {
            int edx = i + B - 1;
            int edy = j + A - 1;
            int base_area = pfx[edx+1][edy+1] - pfx[i][edy+1] - pfx[edx+1][j] + pfx[i][j];

            int min_tomb_area = query_first_dimension(seg_szN, seg_szN*2-1, 1, i+1+seg_szN, edx-D+seg_szN, j+1+seg_szM, edy-C+seg_szM);
            base_area -= min_tomb_area;
            if (base_area > area) {
                area = base_area;
                pyx = i;
                pyy = j;
                tomb_area = min_tomb_area;
            }           
        }
    }
    for (int i = pyx + 1; i + D < pyx + B; i++) {
        for (int j = pyy + 1; j + C < pyy + A; j++) {
            int edx = i + D - 1;
            int edy = j + C - 1;
            int base_area = pfx[edx+1][edy+1] - pfx[i][edy+1] - pfx[edx+1][j] + pfx[i][j];
            if (base_area == tomb_area) {
                tx = i;
                ty = j;
                break;
            }

        }
    }


    cout << pyy+1 << ' ' << pyx+1 << '\n';
    cout << ty+1 << ' ' << tx+1 << '\n';
    return 0;
}
