# 200. Number of Islands

**Medium · Graphs, connected components, BFS**

[Solve on LeetCode](https://leetcode.com/problems/number-of-islands/) · [Curriculum](../../../README.md)

## Question Explanation

Count groups of land in a rectangular grid. Land cells connect only horizontally or vertically; touching diagonally does not join islands. Each maximal connected group contributes exactly one to the answer.

**Input constraints:** 1 ≤ rows, columns ≤ 300. Every cell is the character 0 or 1. Let V = rows × columns.

### Example

Grid `[[1,1,0], [0,1,0], [0,0,1]]` contains 2 islands. The lower-right land cell is diagonally near the larger group but is not connected to it.

### Concepts before coding

Treat a land cell as a graph vertex and each orthogonal land adjacency as an edge. A graph traversal finds the entire connected component of its starting cell. A visited structure records work already completed.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Brute force: rediscover each component from every land cell | O(V²) worst case, including repeated traversal | O(V) |
| Optimal: discover each component once using shared visitation | O(V) | O(V) |

### 1. Brute force: rediscover each component from every land cell

Rediscover an island from every land cell, but choose one canonical representative so only one search contributes to the count.

**Algorithm**

1. Scan every cell in row-major order.
2. For each land cell, create a fresh visited set and explore all connected land.
3. Find the smallest flattened position r × columns + c in that component.
4. Increment the answer only if the starting cell is that smallest position.

**Why it works:** Every finite component has one unique smallest position. Every start discovers that same component and representative, so exactly one start per island satisfies the counting condition.

**Dry run:** In the three-cell island at positions 0,1,4, three searches all find representative 0. Only the search starting at 0 counts. Position 8 counts its separate island.

**Complexity:** O(V²) worst case, including repeated traversal time; O(V) space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Optimal: discover each component once using shared visitation

Retain one visited structure for the entire scan. A new search is needed only when reaching land that no previous search has explored.

**Algorithm**

1. Initialize shared visitation and an island count of zero.
2. On unvisited land, increment the count and enqueue that cell.
3. Expand through valid orthogonal land neighbors, marking each on enqueue.
4. Continue the outer scan after that component is exhausted.

**Why it works:** The traversal marks every cell in the starting component and no cell outside it. That island can never trigger a second search. Any island not yet counted still contains unvisited land and will eventually trigger its first search.

**Dry run:** Starting at position 0 visits positions 0,1,4 in one search. The scan skips 1 and 4 later. Position 8 starts the second search.

**Complexity:** O(V) time; O(V) space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

All water; all land; diagonal-only contact; one row; one column; isolated single cells. Mark a cell visited when adding it to the queue to avoid duplicate entries.

## Implementation Notes

Both implementations preserve the grid and use iterative BFS, avoiding recursion-depth failures on a 300×300 land component. The brute-force method is intentionally redundant: for each land cell it finds the smallest row-major position in that component, then counts only if the starting position is that representative. This produces a correct baseline without counting one island multiple times. Queue and visitation storage are O(V).

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

Share visitation information across searches so each connected component is discovered only once.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
