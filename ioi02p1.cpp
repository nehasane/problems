/*  
    a simle brute force solution (O(N^3)) is enough to score all
    the points.
    for each pair of unique points, a line can be drawn. extend that
    line, and count the number of points that fall on that line.
    ensure the points are of equidistance from each other, and that
    they go all te way to the two ends of the line, since the frogs
    start hoppoing from one end of the board and continue till the end.
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_RC = 5000 + 1;
bool flattened[MAX_RC][MAX_RC];
struct square {
    int x, y;
};
vector <square> grass;
int R, C, N;

int get_dis(int x, int y, int dx, int dy) {
    int ans = 0;
    x += dx;
    y += dy;
    while (x >= 1 && x <= C && y >= 1 && y <= R) {
        if (!flattened[x][y]) {
            return -1e9;
        }
        ans++;
        x += dx;
        y += dy;
    }  
    return ans;
}

int main() {
    cin >> R >> C >> N;
    grass.resize(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> y >> x;
        flattened[x][y] = true;
        grass[i] = {x, y};
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;
            square sq1 = grass[i];
            square sq2 = grass[j];
            int tp = 2;
            
            if (sq1.x > sq2.x && sq1.y < sq2.y) {
                /*
                    line is like this
                       ../ sq1
                       ./.
                    sq2/..
                */
               int dx = abs(sq1.x - sq2.x);
               int dy = -abs(sq1.y - sq2.y);
               tp += (get_dis(sq1.x, sq1.y, dx, dy) + get_dis(sq2.x, sq2.y, -dx, -dy));
            } else if (sq2.x > sq1.x && sq2.y < sq1.y) {
                /*
                    line is like this
                       ../sq2
                       ./.
                    sq1/..
                */
               int dx = abs(sq1.x - sq2.x);
               int dy = -abs(sq1.y - sq2.y);
               tp += (get_dis(sq2.x, sq2.y, dx, dy) + get_dis(sq1.x, sq1.y, -dx, -dy));
            } else if (sq1.x < sq2.x && sq1.y < sq2.y) {
                /*
                    line is like this
                    sq1\..
                       .\.
                       ..\sq2
                */
               int dx = -abs(sq1.x - sq2.x);
               int dy = -abs(sq1.y - sq2.y);
               tp += (get_dis(sq1.x, sq1.y, dx, dy) + get_dis(sq2.x, sq2.y, -dx, -dy));
            } else if (sq2.x < sq1.x && sq2.y < sq1.y) {
                /*
                    line is like this
                    sq2\..
                       .\.
                       ..\sq1
                */
                int dx = -abs(sq1.x - sq2.x);
                int dy = -abs(sq1.y - sq2.y);
                tp += (get_dis(sq2.x, sq2.y, dx, dy) + get_dis(sq1.x, sq1.y, -dx, -dy));
            } else if (sq1.y == sq2.y && sq1.x < sq2.x) {
                /*
                    line is like this
                    sq1-----sq2
                */
               int dx = abs(sq1.x - sq2.x);
               tp += (get_dis(sq1.x, sq1.y, -dx, 0) + get_dis(sq2.x, sq2.y, dx, 0));
            } else if (sq1.y == sq2.y && sq2.x < sq1.x) {
                /*
                    line is like this
                    sq2-----sq1
                */
               int dx = abs(sq1.x - sq2.x);
               tp += (get_dis(sq2.x, sq2.y, -dx, 0) + get_dis(sq1.x, sq1.y, dx, 0));
            } else if (sq1.x == sq2.x && sq1.y < sq2.y) {
                /*
                    line is like this
                    sq1
                    |
                    |
                    |
                    sq2
                */
               int dy = abs(sq1.y - sq2.y);
               tp += (get_dis(sq1.x, sq1.y, 0, -dy) + get_dis(sq2.x, sq2.y, 0, dy));
            } else {
                /*
                    line is like this
                    sq2
                    |
                    |
                    |
                    sq1
                */
               int dy = abs(sq1.y - sq2.y);
               tp += (get_dis(sq2.x, sq2.y, 0, -dy) + get_dis(sq1.x, sq1.y, 0, dy));
            }
            ans = max(ans, tp);
        }
    }
    if (ans <= 2)   
        cout << 0 << '\n';
    else
        cout << ans << '\n';
}
