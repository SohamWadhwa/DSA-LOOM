# Number of Islands | Optimal: discover each component once using shared visitation
# See ../README.md for reasoning and complexity.
from collections import deque
from typing import List

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        if not grid or not grid[0]:
            return 0
        rows, cols = len(grid), len(grid[0])

        def explore(start, seen):
            pending = deque([start])
            seen.add(start)
            smallest = start
            while pending:
                position = pending.popleft()
                smallest = min(smallest, position)
                row, col = divmod(position, cols)
                for r, c in ((row - 1, col), (row + 1, col), (row, col - 1), (row, col + 1)):
                    next_position = r * cols + c
                    if (0 <= r < rows and 0 <= c < cols and
                            grid[r][c] == '1' and next_position not in seen):
                        seen.add(next_position)
                        pending.append(next_position)
            return smallest

        seen = set()
        islands = 0
        for start in range(rows * cols):
            if grid[start // cols][start % cols] == '1' and start not in seen:
                islands += 1
                explore(start, seen)
        return islands
