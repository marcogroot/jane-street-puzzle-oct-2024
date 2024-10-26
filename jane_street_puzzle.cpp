#include <iostream>
#include <array>
#include <utility>
#include <set>
#include <bit>
#include <bitset>
#include <cstdint>
#include <vector>

using namespace std;

int grid[6][6];

const pair<int, int> a_coords[12] = {
    {0, 0},
    {1, 0},
    {2, 0}, {2, 1},
    {3, 0}, {3, 1},
    {4, 0}, {4, 1}, {4, 2},
    {5, 0}, {5, 1}, {5, 2},
};

const pair<int, int> b_coords[12] = {
    {0, 1}, {0, 2},
    {1, 1}, {1, 2},
    {2, 2}, {2, 3},
    {3, 2}, {3, 3},
    {4, 3}, {4, 4},
    {5, 3}, {5, 4},
};

const pair<int, int> c_coords[12] = {
    {0, 3}, {0, 4}, {0, 5},
    {1, 3}, {1, 4}, {1, 5},
    {2, 4}, {2, 5},
    {3, 4}, {3, 5},
    {4, 5},
    {5, 5},
};

const pair<int, int> moves[8] = {
    {-2, -1}, {-2, 1},
    {-1, 2}, {1, 2},
    {2, 1}, {2, -1},
    {1, -2}, {-1, -2},
};

void fill_grid(const int& a, const int& b, const int& c) {

    for (pair<int, int> coord : a_coords) {
        grid[coord.first][coord.second] = a;
    }

    for (pair<int, int> coord : b_coords) {
        grid[coord.first][coord.second] = b;
    }

    for (pair<int, int> coord : c_coords) {
        grid[coord.first][coord.second] = c;
    }
    return;
}

bool vector_contains(const vector<pair<int, int>>& visited, const pair<int, int>& p) {
    for (const pair<int, int>& v : visited) {
        if ((v.first == p.first) && (v.second == p.second)) {
            return true;
        }
    }

    return false;
}

void print_grid() {
    for (int i = 0; i < 6; i++ ) {
        for (int j = 0; j < 6; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}

vector<pair<int, int>> journey_a;
vector<pair<int, int>> journey_b;


void update_best_journey(const vector<pair<int, int>>& visited, int goal_row) {
    if (goal_row == 0) journey_a = visited;
    else journey_b = visited;
}

void print_journey(const vector<pair<int, int>>& visited) {
    // cout << "Journey to end: \n";
    // for(int i = 0; i < visited.size(); i++) {
    //     const pair<int, int> p = visited[i];
    //     cout << p.first << " " <<  p.second << endl;
    // }
    int score = 0;
    int previous = 2;
    for(int i = 0; i < visited.size(); i++) {
        const pair<int, int> p = visited[i];
        int curr = grid[p.first][p.second];
        if (curr == previous) score += curr;
        else score *= curr;
        previous = curr;

        // for (const pair<int, int>& p2 : a_coords) {
        //     if (p == p2) {
        //         cout << "a ";
        //     }
        // }
        // for (const pair<int, int>& p2 : b_coords) {
        //     if (p == p2) {
        //         cout << "b ";
        //     }
        // }
        // for (const pair<int, int>& p2 : c_coords) {
        //     if (p == p2) {
        //         cout << "c ";
        //     }
        // }
        char ch = 'a' + p.second;
        int num = 6 - p.first;
        cout << ch << num << ",";
    }
}

void dfs(
    const int row,
    const int col,
    int prev,
    int score,
    vector<pair<int, int>> visited,
    const int goal_row,
    const int goal_col,
    bool& found
) {
    if (found) return;
    int curr = grid[row][col];
    if (curr == prev) {
        score += curr;
    } else score *= curr;

    visited.push_back({row, col});
    // cout << "visiting current {" << row << " " << col << "} with a score of " << score << endl;
    if (score > 2024) return;

    if ((row == goal_row) && (col == goal_col) && (score == 2024)) {
        //cout << "reached the goal {" << goal_row << " " << goal_col << "} with a score of 2048!\n";
        //print_journey(visited);
        update_best_journey(visited, goal_row);
        found = true;
        return;
    }
    // cout << " abc " << endl;

    for (pair<int, int> move  : moves) {
        int new_row = row + move.first;
        int new_col = col + move.second;
        if (new_row < 0 || new_row >= 6) continue;
        if (new_col < 0 || new_col >= 6) continue;
        if (!vector_contains(visited, {new_row, new_col})) {
            dfs(new_row, new_col, curr, score, visited, goal_row, goal_col, found);
        }
    }

    return;
}

// int main() {
//     int best_total = 51, best_a = 51, best_b = 51, best_c = 51;

//     vector<pair<int, int>> visited = {};
//     for (int a = 1; a <= 10; a++) {
//         for (int b = 1; b <= 10; b++) {
//             for (int c = 1; c <= 10; c++) {
//                 if (a + b + c > 13) continue;
//                 if (a + b + c > best_total) continue;
//                 if (a == b || a == c || b == c) continue;
//                 fill_grid(a, b, c);
//                 print_grid();
//                 cout << "Trying " << a << " " << b << " " << c << endl;
//                 bool trip_1_result = false;
//                 dfs(5, 0, a, 0, visited, 0, 5, trip_1_result);
//                 bool trip_2_result = false;
//                 dfs(0, 0, a, 0, visited, 5, 5, trip_2_result);

//                 if ((trip_1_result && trip_2_result) && ((a+b+c) < best_total)) {
//                     best_a = a;
//                     best_b = b;
//                     best_c = c;
//                     best_total = a+b+c;
//                 }

//                 cout << "Best total " << best_total << "\n";
//                 cout << "a: " << best_a << " b: " << best_b << " c: " << best_c << endl;
//             }
//         }
//     }

//     cout << "Best total " << best_total << "\n";
//     cout << "a: " << best_a << " b: " << best_b << " c: " << best_c << endl;
//     print_journey(journey_a);
//     cout << "---------------" << endl;
//     print_journey(journey_b);
// }

int main() {
    int best_total = 51, best_a = 51, best_b = 51, best_c = 51;
    int a =  2, b = 3, c = 1;
    vector<pair<int, int>> visited = {};
    fill_grid(a, b, c);
    print_grid();
    cout << "Trying " << a << " " << b << " " << c << endl;
    bool trip_1_result = false;
    dfs(5, 0, a, 0, visited, 0, 5, trip_1_result);
    bool trip_2_result = false;
    dfs(0, 0, a, 0, visited, 5, 5, trip_2_result);

    if ((trip_1_result && trip_2_result) && ((a+b+c) < best_total)) {
      best_a = a;
      best_b = b;
      best_c = c;
      best_total = a+b+c;
      // cout << "Success!" << endl;
    }

    // cout << "Best total " << best_total << "\n";
    // cout << "a: " << best_a << " b: " << best_b << " c: " << best_c << endl;

    // cout << "Best total " << best_total << "\n";
    // cout << "a: " << best_a << " b: " << best_b << " c: " << best_c << endl;
    cout << a << "," << b << "," << c << ",";
    print_journey(journey_a);
    print_journey(journey_b);
}
