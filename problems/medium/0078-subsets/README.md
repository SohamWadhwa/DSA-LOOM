# 78. Subsets

**Medium · Bit manipulation, backtracking**

[Solve on LeetCode](https://leetcode.com/problems/subsets/) · [Curriculum](../../../README.md)

## Question Explanation

List every subset of an array of distinct integers. A subset may contain none, some, or all values. Return each subset once; the order of the subsets and the order of their values are unrestricted.

**Input constraints:** 1 ≤ n ≤ 10; values lie between −10 and 10 and are distinct. There are exactly 2ⁿ subsets.

### Example

`nums = [2, 5]` → `[[], [2], [5], [2,5]]`, in any order.

### Concepts before coding

Each value creates an independent include/exclude choice. A bitmask encodes those choices as binary digits. Backtracking explores choices by extending a partial answer and undoing that extension before trying the next branch.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Enumeration: interpret a bitmask as a subset | Θ(n·2ⁿ) | O(1) control space excluding each output row; Θ(n·2ⁿ) total output |
| Output-optimal alternative: backtracking | Θ(n·2ⁿ), tied with bitmask enumeration | O(n) recursion and path; plus Θ(n·2ⁿ) output |

### 1. Enumeration: interpret a bitmask as a subset

Assign one bit to each input index. Every bit pattern represents one subset.

**Algorithm**

1. Enumerate masks from 0 to 2ⁿ − 1.
2. For each index i, test whether bit i is set.
3. Include nums[i] exactly when that bit is set.
4. Append the completed subset.

**Why it works:** Choosing a subset uniquely determines its mask, and every possible mask is generated exactly once. This one-to-one correspondence guarantees completeness without duplicates.

**Dry run:** For [2,5], masks 00,01,10,11 represent [], [2], [5], and [2,5].

**Complexity:** Θ(n·2ⁿ) time; O(1) control space excluding each output row; Θ(n·2ⁿ) total output space.

**Detailed implementations:** [C](c/bitmask.c) · [C++](cpp/bitmask.cpp) · [Python](python/bitmask.py)

### 2. Output-optimal alternative: backtracking

Generate increasing sequences of selected indices. At every recursive node, the current path is already a valid subset.

**Algorithm**

1. Append a copy of the current path, including the initial empty path.
2. Try every index at or after start.
3. Append the chosen value and recurse from the next index.
4. Pop the value to restore the path before the next choice.

**Why it works:** Every subset has a unique increasing sequence of input indices. The recursion generates exactly those sequences, and copying the path preserves each answer when subsequent backtracking mutates the working path.

**Dry run:** Record []; choose 2 and record [2]; choose 5 and record [2,5]; undo both choices; then choose 5 directly and record [5].

**Complexity:** Θ(n·2ⁿ), tied with bitmask enumeration time; O(n) recursion and path; plus Θ(n·2ⁿ) output space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

One element; negative values; zero; the empty subset; duplicate output rows caused by forgetting to copy a mutable path. An empty input defensively returns `[[]]`.

## Implementation Notes

Both implementations take Θ(n·2ⁿ) time when materializing all subset values, and Θ(n·2ⁿ) output space. Backtracking is an alternative representation, not a faster asymptotic solution. Across all subsets, n·2ⁿ⁻¹ element occurrences must be written when n > 0. C allocates every row and the column sizes; the caller frees all rows, the outer array, and sizes. Inputs are preserved.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

For enumeration problems, output size can impose an exponential lower bound; an exponential algorithm can still be optimal.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
