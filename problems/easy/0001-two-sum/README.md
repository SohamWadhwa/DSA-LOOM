# 1. Two Sum

**Easy · Arrays, sorting, hashing**

[Solve on LeetCode](https://leetcode.com/problems/two-sum/) · [Curriculum](../../../README.md)

## Question Explanation

Find two different positions in an integer array whose values add to a target. Return the positions, not the values. The input guarantees exactly one valid pair; the order of the two returned positions does not matter.

**Input constraints:** 2 ≤ n ≤ 10,000; values and target are between −10⁹ and 10⁹. The same position cannot be used twice.

### Example

`nums = [4, 9, 2, 8]`, `target = 12` → `[0, 3]` or `[3, 0]`. The values at positions 0 and 3 are 4 and 8.

### Concepts before coding

An array gives constant-time access by index. A hash map stores key/value pairs; here it maps a value to a previously visited index. A two-pointer scan exploits sorted order to discard impossible pairs.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Brute force: enumerate pairs | O(n²) | O(1), excluding the two-index answer |
| Better: sort indexed values and use two pointers | O(n log n) with comparison sorting | O(n) for indexed copies and sorting workspace |
| Optimal expected time: one-pass hash map | Expected O(n); worst-case O(n²) | O(n) |

### 1. Brute force: enumerate pairs

Try each unordered pair once. This is the clearest way to translate the question directly into code.

**Algorithm**

1. Choose an index i.
2. Choose every j greater than i.
3. Return i and j as soon as their sum equals the target.

**Why it works:** Every pair of different indices has exactly one ordering with i < j. The loops therefore examine the guaranteed answer without ever pairing an element with itself.

**Dry run:** At i = 0, check 4 + 9, then 4 + 2, then 4 + 8. The third check finds 12.

**Complexity:** O(n²) time; O(1), excluding the two-index answer space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Better: sort indexed values and use two pointers

Sorting makes the direction of improvement predictable. Keep original indices beside the values so the required answer survives reordering.

**Algorithm**

1. Create (value, original index) pairs and sort them by value.
2. Start one pointer at each end.
3. Move the left pointer right if the sum is too small; move the right pointer left if it is too large.
4. On equality, return the stored original indices.

**Why it works:** When the smallest-plus-largest sum is too small, the smallest value cannot succeed with any smaller partner. When it is too large, the largest value cannot succeed with any larger partner. Each discarded endpoint is therefore safe.

**Dry run:** Sorted pairs are (2,2), (4,0), (8,3), (9,1). Discard 2 after 2 + 9 = 11, then discard 9 after 4 + 9 = 13, and find 4 + 8 = 12. Return original indices [0,3].

**Complexity:** O(n log n) with comparison sorting time; O(n) for indexed copies and sorting workspace space.

**Detailed implementations:** [C](c/sorting.c) · [C++](cpp/sorting.cpp) · [Python](python/sorting.py)

### 3. Optimal expected time: one-pass hash map

For a value x, the only useful partner value is target − x. Remember previously visited values instead of scanning them again.

**Algorithm**

1. Create an empty map from value to index.
2. Before inserting the current value, look up its complement.
3. Return the stored index and current index if the complement exists.
4. Otherwise store the current value and continue.

**Why it works:** Before each iteration, the map represents earlier positions only. If a complement is found, the positions are distinct and their values sum to the target. When the second member of the unique pair is reached, its partner is already available.

**Dry run:** For [4,9,2,8], target 12: store 4→0, 9→1, and 2→2. At 8, complement 4 is present, so return [0,3].

**Complexity:** Expected O(n); worst-case O(n²) time; O(n) space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

Two equal values at different positions; negative numbers; zeros; a pair at the ends. Use wider arithmetic for addition in C/C++; do not return positions from the sorted array.

## Implementation Notes

The sorted version copies indexed values, so it preserves the input. All C versions return a heap-allocated array; free it after use. Hash-based linear time is expected rather than a worst-case guarantee: pathological collisions can produce O(n²) total work. C uses an explicit open-addressed table with at most 50% load. The sorting bound assumes an O(n log n) sorting implementation; ISO C does not specify a worst-case bound for qsort. The numerical constraints keep target − value within a 32-bit signed integer.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

Replace a repeated search for a partner with a direct lookup of the required complement.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
