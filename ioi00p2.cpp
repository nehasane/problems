/*
    the idea is pretty simple
    
    in order for one car to be sent to its proper position, the car
    already in that position must also be able to sent to its proper
    position in the same move. draw an edge from the car that needs
    to be put into its place to the car that's in its place.
    
    eventually these will form a cycle. for each node (dislocated car)
    you need to find a cycle that it can be a part of and its length.
    we need exactly one worker to move one car, so the number of 
    workers that we would need is the same as the number of nodes in
    the cycle. if the number of nodes is less than W, then we could try
    to fit in another cycle in that move, since we wouldn't want to
    keep some workers idle if we can avoid it. if the cycle length is
    W, then we can't cram any more cycles. but if it's more than W, then
    we can only move the first W cars. In this case, the first W-1 cars
    will be sent to their proper positions, while the Wth car will still
    be dislocated.
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 20000 + 1;
int nums[MAX_N], sorted_nums[MAX_N];
struct car_shift {
    int curr_car_type;
    int position;
    int car_type_that_needs_to_replace;
};
int main() {
    int N, M, W;
    cin >> N >> M >> W;
    vector <queue <pair <int, int>>> car_types(M + 1);
    for (int i = 1; i <= N; i++) {
        cin >> nums[i];
        sorted_nums[i] = nums[i];
    }
    sort(sorted_nums + 1, sorted_nums + N + 1);
    int dislocated = 0;
    for (int i = 1; i <= N; i++) {
        if (nums[i] != sorted_nums[i]) {
            car_types[nums[i]].push({i, sorted_nums[i]});
            dislocated++;
        }
    }
    vector <vector <int>> rounds;
    while (dislocated > 0) {
        vector <int> current_round;
        int workers = 0;
        while (dislocated > 0 && workers + 1 < W) {
            vector <car_shift> cycle;
            for (int i = 1; i <= M; i++) {
                if (!car_types[i].empty()) {
                    car_shift tp;
                    tp.curr_car_type = i;
                    tp.position = car_types[i].front().first;
                    tp.car_type_that_needs_to_replace = car_types[i].front().second;
                    car_types[i].pop();
                    dislocated--;
                    workers++;
                    cycle.push_back(tp);
                    break;
                }
            }
            while (workers < W && cycle[0].curr_car_type != cycle.back().car_type_that_needs_to_replace) {
                car_shift tp;
                tp.curr_car_type = cycle.back().car_type_that_needs_to_replace;
                tp.position = car_types[tp.curr_car_type].front().first;
                tp.car_type_that_needs_to_replace = car_types[tp.curr_car_type].front().second;
                car_types[tp.curr_car_type].pop();
                cycle.push_back(tp);
                dislocated--;
                workers++;
            }
            for (int i = 1; i < cycle.size(); i++) {
                current_round.push_back(cycle[i].position);
                current_round.push_back(cycle[i-1].position);
            }
            current_round.push_back(cycle[0].position);
            current_round.push_back(cycle.back().position);
            if (cycle[0].curr_car_type != cycle.back().car_type_that_needs_to_replace) {
                dislocated++;
                car_types[cycle[0].curr_car_type].push({cycle.back().position, cycle.back().car_type_that_needs_to_replace});
            }
        } 
        rounds.push_back(current_round);  
    }
    if (rounds.size() == 0)
        cout << 1 << '\n' << 0 << '\n';
    else
        cout << rounds.size() << '\n';
    for (auto i : rounds){
        cout << i.size() / 2 << ' ';
        for (auto j : i)
            cout << j << ' ';
        cout << '\n';
    }
}
