# 704. Binary Search

**Easy · Binary search**

[Solve on LeetCode](https://leetcode.com/problems/binary-search/) · [Curriculum](../../../README.md)

## Question Explanation

Search a strictly increasing integer array for a target. Return its zero-based index if present, otherwise return −1. The required solution must use the sorted order to achieve logarithmic running time.

**Input constraints:** 1 ≤ n ≤ 10,000; values and target lie strictly between −10,000 and 10,000; array values are distinct and sorted.

### Example

`nums = [-5, -1, 3, 8, 12]`, `target = 8` → `3`. Searching the same array for 7 returns −1.

### Concepts before coding

An interval invariant describes where an answer can still exist. Binary search compares the middle value and discards half the candidates after each unsuccessful comparison.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Baseline: linear search | O(n) | O(1) |
| Optimal: iterative binary search | O(log n) | O(1) |

### 1. Baseline: linear search

Compare the target with every value until it is found.

**Algorithm**

1. Visit indices from left to right.
2. Return the first matching index.
3. Return −1 if the loop ends without a match.

**Why it works:** Every position is examined before failure is reported, so a present target cannot be missed.

**Dry run:** For target 8, compare −5, −1, 3, and finally 8 at index 3.

**Complexity:** O(n) time; O(1) space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Optimal: iterative binary search

Maintain the interval in which a target could remain, then halve it after each comparison.

**Algorithm**

1. Initialize left = 0 and right = n − 1.
2. While left ≤ right, inspect the middle index.
3. Return on equality. If the middle value is too small, set left = middle + 1; otherwise set right = middle − 1.
4. Return −1 once the interval is empty.

**Why it works:** If the middle value is smaller than the target, every value at or left of the middle is also smaller; the symmetric argument holds for larger values. Updates preserve the candidate invariant and strictly shrink the interval.

**Dry run:** For target 8, [0,4] has middle 2 with value 3. Keep [3,4], whose middle is 3 with value 8. Return 3.

**Complexity:** O(log n) time; O(1) space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

A one-element array; targets at either endpoint; a missing target between elements; targets outside the value range; even-length intervals.

## Implementation Notes

The linear baseline is educational and does not satisfy LeetCode’s explicit O(log n) requirement. The optimal version uses an inclusive [left,right] interval and middle = left + (right − left)/2. Mixing this with half-open update rules causes off-by-one errors. Neither implementation modifies the input.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

A useful ordering lets one comparison eliminate a whole region of the search space.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
