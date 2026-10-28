# 76. Minimum Window Substring

**Hard · Frequency counting, sliding windows**

[Solve on LeetCode](https://leetcode.com/problems/minimum-window-substring/) · [Curriculum](../../../README.md)

## Question Explanation

Find the shortest contiguous part of s that contains every character of t with at least its required multiplicity. Character case matters. Return an empty string when no valid window exists.

**Input constraints:** 1 ≤ len(s), len(t) ≤ 100,000; uppercase and lowercase English letters. LeetCode guarantees a unique answer. Let m=len(s), n=len(t), and Σ be the character alphabet.

### Example

`s = "CABAAC"`, `t = "AAC"` → `"AAC"`. A window containing only one A is insufficient because t requires two.

### Concepts before coding

A frequency table counts repeated requirements. A sliding window is a contiguous interval whose endpoints move forward. Keep only the information needed to decide when the current interval covers the requirements.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Brute force: recount every candidate substring | O(m³ + n) for the fixed alphabet | O(Σ) counting tables; Python candidate slices use O(m) temporary space; output O(m) |
| Better: reuse counts while extending each start position | O(m² + n) | O(Σ) counters, plus output |
| Optimal: expand and shrink a sliding window | O(m+n) | O(Σ) counters, plus output |

### 1. Brute force: recount every candidate substring

Enumerate every candidate interval, rebuild its character counts, and test whether it covers t.

**Algorithm**

1. Build the target frequency table once.
2. Choose every left and right endpoint.
3. Count all characters inside that substring.
4. If every required count is met, retain it when shorter than the best seen.

**Why it works:** Every possible contiguous substring is tested. A candidate passes exactly when all required multiplicities are satisfied. Keeping the shortest passing candidate therefore solves the problem.

**Dry run:** For CABAAC and AAC, candidates with only one A fail. The interval at positions 3..5 contains AAC and passes with length 3, which no shorter interval can match.

**Complexity:** O(m³ + n) for the fixed alphabet time; O(Σ) counting tables; Python candidate slices use O(m) temporary space; output O(m) space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Better: reuse counts while extending each start position

For each starting position, reuse character counts while extending its ending position.

**Algorithm**

1. Reset a window counter and missing=len(t) for the chosen start.
2. Extend right by one character at a time.
3. Decrease missing only when the newly added character fills an unmet required occurrence.
4. When missing reaches zero, record the window and stop extending this start.

**Why it works:** Incremental counts exactly match the current interval. The first valid endpoint for a fixed start gives its shortest valid window, so later endpoints cannot improve it. Comparing these shortest windows over all starts finds the global minimum.

**Dry run:** Starting at position 3, read A (one A missing), A (only C missing), then C (nothing missing). Record AAC without recounting its earlier characters.

**Complexity:** O(m² + n) time; O(Σ) counters, plus output space.

**Detailed implementations:** [C](c/incremental.c) · [C++](cpp/incremental.cpp) · [Python](python/incremental.py)

### 3. Optimal: expand and shrink a sliding window

Avoid resetting the start. Expand until the window is valid, then shrink from the left as far as possible while recording candidates.

**Algorithm**

1. Initialize balance from t and missing=len(t).
2. Add each right character: if its balance was positive, one requirement was filled; then decrement its balance.
3. While missing is zero, record the candidate and remove the leftmost character.
4. Removing a character makes the window invalid only when its updated balance becomes positive.

**Why it works:** Balances equal required counts minus current-window counts, so missing is zero exactly for valid windows. Every valid window ending at right is shortened until removing another required occurrence would break validity. Each left position is removed only once; later right endpoints cannot make an already-longer window at that discarded start preferable.

**Dry run:** The first valid window is CABAA. Remove its C and validity breaks. After adding the final C, shrink past surplus A and irrelevant B, then record AAC before removing a required A.

**Complexity:** O(m+n) time; O(Σ) counters, plus output space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

Repeated characters in t; t longer than s; no solution; uppercase versus lowercase; the entire string is needed; surplus required characters at the left boundary.

## Implementation Notes

The implementations keep the earliest minimum window for defensive inputs with ties. C/C++ use 128-entry arrays, which cover the problem’s English-letter alphabet; they are not general UTF-8 implementations. Python uses Counter. Balance-based sliding windows track missing character occurrences, not merely distinct character types. C always returns an allocated, null-terminated string, including for an empty answer; the caller frees it. Inputs are preserved.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

When extending a window can establish validity and shrinking it can improve the objective, track validity incrementally with two forward-moving pointers.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
