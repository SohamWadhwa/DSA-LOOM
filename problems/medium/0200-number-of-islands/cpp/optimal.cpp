// Number of Islands | Optimal: discover each component once using shared visitation
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

class Solution {
    int explore(vector<vector<char>>& grid, int start, vector<bool>& seen) {
        int rows = static_cast<int>(grid.size()), cols = static_cast<int>(grid[0].size());
        queue<int> pending;
        pending.push(start);
        seen[start] = true;
        int smallest = start;
        const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
        while (!pending.empty()) {
            int position = pending.front();
            pending.pop();
            smallest = min(smallest, position);
            for (int d = 0; d < 4; ++d) {
                int r = position / cols + dr[d], c = position % cols + dc[d];
                if (r < 0 || r >= rows || c < 0 || c >= cols) continue;
                int next = r * cols + c;
                if (!seen[next] && grid[r][c] == '1') {
                    seen[next] = true;
                    pending.push(next);
                }
            }
        }
        return smallest;
    }
public:

    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int cols = static_cast<int>(grid[0].size());
        int cells = static_cast<int>(grid.size()) * cols, islands = 0;
        vector<bool> seen(cells, false);
        for (int start = 0; start < cells; ++start) {
            if (grid[start / cols][start % cols] == '1' && !seen[start]) {
                ++islands;
                explore(grid, start, seen);
            }
        }
        return islands;
    }
};
