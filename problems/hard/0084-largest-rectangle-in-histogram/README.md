# 84. Largest Rectangle in Histogram

**Hard · Range enumeration, monotonic stacks**

[Solve on LeetCode](https://leetcode.com/problems/largest-rectangle-in-histogram/) · [Curriculum](../../../README.md)

## Question Explanation

Find the maximum-area rectangle that fits under consecutive unit-width histogram bars. A rectangle covering an interval can be no taller than the shortest bar in that interval.

**Input constraints:** 1 ≤ n ≤ 100,000; 0 ≤ height ≤ 10,000. Area is at most 10⁹, fitting a signed 32-bit integer.

### Example

`heights = [2,4,4,1]` → `8`. The two middle bars support a rectangle of height 4 and width 2.

### Concepts before coding

A monotonic stack retains candidates in nondecreasing height order. Encountering a shorter bar reveals where taller candidates must stop. The stack allows each candidate to be finalized only once.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Brute force: recompute the minimum in every interval | O(n³) | O(1) in C/C++; O(n) temporary slice space in Python |
| Better: maintain the interval minimum as it grows | O(n²) | O(1) |
| Optimal: increasing stack of bar indices | O(n) | O(n) |

### 1. Brute force: recompute the minimum in every interval

Consider every contiguous interval and independently find its shortest bar.

**Algorithm**

1. Choose a left endpoint and a right endpoint.
2. Scan the interval to find its minimum height.
3. Compute minimum × interval width.
4. Retain the greatest area.

**Why it works:** Every legal rectangle occupies some contiguous interval and has height at most that interval’s minimum. The maximal-height rectangle for every interval is examined, so the global optimum is included.

**Dry run:** For the interval [1,2] in [2,4,4,1], minimum=4 and width=2, giving area 8. The full interval gives only 1×4=4.

**Complexity:** O(n³) time; O(1) in C/C++; O(n) temporary slice space in Python space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Better: maintain the interval minimum as it grows

As the right endpoint extends, update the current minimum instead of scanning the interval again.

**Algorithm**

1. For each left endpoint, initialize minimum to its bar height.
2. Extend right from left through the final bar.
3. Update minimum=min(minimum,height[right]).
4. Evaluate the current interval’s area and update the maximum.

**Why it works:** The maintained minimum is exactly the interval minimum by induction on its right endpoint. Every interval is still examined, so this reuses work without changing the set of candidate rectangles.

**Dry run:** With left=1, the running minima for right=1,2,3 are 4,4,1, giving areas 4,8,3. No interval rescan is required.

**Complexity:** O(n²) time; O(1) space.

**Detailed implementations:** [C](c/incremental.c) · [C++](cpp/incremental.cpp) · [Python](python/incremental.py)

### 3. Optimal: increasing stack of bar indices

Keep unresolved bar indices in nondecreasing height order. A lower bar fixes the right boundary for every taller stack top.

**Algorithm**

1. Scan real indices and one virtual final index with height zero.
2. While the top bar is taller than the current height, pop its index.
3. After popping, let left be the new top or −1 if the stack is empty.
4. Evaluate poppedHeight × (currentIndex−left−1).
5. Push real indices and keep the best area.

**Why it works:** A popped bar cannot extend through the shorter current bar, so its right boundary is fixed. The remaining top bounds how far that candidate can extend left under the stack’s tie convention. For equal heights, the leftmost remaining equal bar eventually receives the full possible span. Every limiting height is therefore considered, and every index is pushed and popped at most once.

**Dry run:** Push indices 0,1,2 for heights 2,4,4. At height 1, pop index 2 (area 4), then index 1 (area 8), then index 0 (area 6). The best is 8.

**Complexity:** O(n) time; O(n) space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

Zero heights; one bar; equal bars; increasing and decreasing sequences; the best rectangle reaches an endpoint; leftover candidates at the end.

## Implementation Notes

The stack stores indices, so widths can be computed from boundaries. It pops only strictly taller bars; equal-height indices may remain, and a later pop eventually gives the leftmost equal-height bar the full width. A virtual zero-height final bar flushes all positive-height candidates without modifying the input. The quadratic and stack C/C++ versions use constant and linear auxiliary space respectively; Python’s cubic baseline additionally slices each candidate interval.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

A stack can defer a decision until the first value that resolves it; count total pushes and pops to prove linear time.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
