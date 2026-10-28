# 102. Binary Tree Level Order Traversal

**Medium · Trees, queues, BFS**

[Solve on LeetCode](https://leetcode.com/problems/binary-tree-level-order-traversal/) · [Curriculum](../../../README.md)

## Question Explanation

Return the values of a binary tree grouped by depth, from the root downward. Within a level, visit nodes from left to right. The result is a list of lists, not a single flattened traversal.

**Input constraints:** 0–2,000 nodes; values from −1,000 to 1,000. Tree height h is the number of nonempty levels; maximum width w is the largest number of nodes on one level.

### Example

A root 8 with children 3 and 10, where 3 has right child 6, produces `[[8], [3, 10], [6]]`.

### Concepts before coding

A binary tree node has up to two children. Depth counts edges from the root. A queue is first-in, first-out, making it suitable for visiting all current-depth nodes before their children.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Baseline: repeat traversal for every depth | O(nh) upper bound; O(n²) for a chain | O(h) recursion; plus O(n) output |
| Optimal: breadth-first traversal with a queue | O(n) | O(w) queue; plus O(n) output |

### 1. Baseline: repeat traversal for every depth

Compute the height, then start at the root again for every requested depth.

**Algorithm**

1. Find the tree height recursively.
2. For depth 0 through h − 1, recursively collect nodes at exactly that depth.
3. Always recurse into the left child before the right child.
4. Append one row for each depth.

**Why it works:** The depth-limited traversal reaches precisely the nodes at its requested depth. Left-before-right recursion preserves their horizontal order. Repeating for every depth therefore constructs the required rows.

**Dry run:** Depth 0 collects [8]. Restart for depth 1 and collect [3,10]. Restart for depth 2 and collect [6]. Earlier ancestors are revisited.

**Complexity:** O(nh) upper bound; O(n²) for a chain time; O(h) recursion; plus O(n) output space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Optimal: breadth-first traversal with a queue

Keep the next level waiting in a queue rather than rediscovering it from the root.

**Algorithm**

1. Enqueue the root unless the tree is empty.
2. Record the queue’s current size as this level’s width.
3. Pop exactly that many nodes, recording their values and enqueueing left then right children.
4. Append the row and repeat until the queue is empty.

**Why it works:** At the start of a level, the queue contains that level’s nodes from left to right. Processing only its original size prevents children from entering the same row. Enqueueing children in parent order establishes the invariant for the next level.

**Dry run:** Queue [8] yields row [8] and queue [3,10]. Processing those two yields [3,10] and queue [6]. The last row is [6].

**Complexity:** O(n) time; O(w) queue; plus O(n) output space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

Empty tree; root only; a chain leaning left or right; missing children; broad balanced trees. Freeze the current level’s queue size before enqueueing children.

## Implementation Notes

Neither version changes the tree. C returns separately allocated rows plus an allocated column-size array; the caller frees all of them. Output occupies O(n) space. Auxiliary bounds below exclude output. The C optimal queue is a dynamically grown circular buffer; it does not retain all already-visited nodes. The recursive baseline is for small teaching examples and may hit Python’s recursion limit on a deep tree.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

BFS processes a graph or tree in layers when edges represent one unit of distance.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
