// Number of Islands | Brute force: rediscover each component from every land cell
// See ../README.md for reasoning, complexity, and ownership.
#include <stdbool.h>
#include <stdlib.h>

// Return the smallest row-major position reachable from start.
static int explore(char** grid, int rows, int cols, int start, bool* seen, int* queue) {
    int head = 0, tail = 0, smallest = start;
    queue[tail++] = start;
    seen[start] = true;
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (head < tail) {
        int position = queue[head++], row = position / cols, col = position % cols;
        if (position < smallest) smallest = position;
        for (int d = 0; d < 4; ++d) {
            int r = row + dr[d], c = col + dc[d];
            if (r < 0 || r >= rows || c < 0 || c >= cols) continue;
            int next = r * cols + c;
            if (!seen[next] && grid[r][c] == '1') {
                seen[next] = true; // Mark on enqueue to prevent duplicate entries.
                queue[tail++] = next;
            }
        }
    }
    return smallest;
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    if (!gridSize || !gridColSize[0]) return 0;
    int cols = gridColSize[0], cells = gridSize * cols, islands = 0;
    int* queue = malloc((size_t)cells * sizeof(*queue));
    for (int start = 0; start < cells; ++start) {
        if (grid[start / cols][start % cols] != '1') continue;
        bool* seen = calloc(cells, sizeof(*seen));
        if (explore(grid, gridSize, cols, start, seen, queue) == start) ++islands;
        free(seen);
    }
    free(queue);
    return islands;
}
