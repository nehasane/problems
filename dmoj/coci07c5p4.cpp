/*
  
  if a number does not appear in the second or third row, then we know that
  we have to remove any columns containing that number. after deleting those
  columns we check if there are any more numbers that are not present in the
  second or third rows and then repeat the same process.
  
  simulating this will take too long, so instead we have this concept of keeping
  two queues that refill eachother and eventually empty out. one queue contains 
  the numbers we need to delete, and the other contains the columns that we need
  to delete. first we go through all the numbers that we need to delete and
  "delete" them and fill the columns_to_delete queue with the columns that contain
  the numbers that we deleted. then we go through the columns that we need to
  delete and fill the numbers_to_delete queue with the numbers that are absent in
  any row after deleting a column. so we add this number to the numbers_to_delete 
  queue. we also makr the column as "deleted" to prevent recomputation.

*/
#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <vector>
using namespace std;
vector <vector <int>> num_rows, num_cols, grid;
vector <bool> col_deleted, num_deleted;
int main() {
    // freopen("in.txt", "r", stdin);
    
    int n;
    cin >> n;

    grid = vector <vector <int>> (3, vector <int> (n));
    num_rows = vector <vector <int>> (n+1, vector <int> (3));
    num_cols = vector <vector <int>> (n+1);
    col_deleted = vector <bool> (n+1);
    num_deleted = vector <bool> (n+1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            num_rows[grid[i][j]][i]++;
            num_cols[grid[i][j]].push_back(j);
        }
    }

    queue <int> nums_to_delete, cols_to_delete;
    for (int i = 1; i <= n; i++) {
        if (num_rows[i][1] == 0 || num_rows[i][2] == 0)
            nums_to_delete.push(i);
    }

    int ans = 0;
    while (!nums_to_delete.empty() || !cols_to_delete.empty()) {
        while (!nums_to_delete.empty()) {
            int x = nums_to_delete.front();
            nums_to_delete.pop();
            if (num_deleted[x])
                continue;
            num_deleted[x] = true;
            while (!num_cols[x].empty()) {
                cols_to_delete.push(num_cols[x].back());
                num_cols[x].pop_back();
            }
        }
        while (!cols_to_delete.empty()) {
            int col = cols_to_delete.front();
            cols_to_delete.pop();
            if (col_deleted[col])
                continue;
            col_deleted[col] = true;
            ans++;
            for (int i = 0; i < 3; i++) {
                num_rows[grid[i][col]][i]--;
                if (num_rows[grid[i][col]][i] == 0) {
                    nums_to_delete.push(grid[i][col]);
                }
            }
        }
    }
    cout << ans << '\n';
}
