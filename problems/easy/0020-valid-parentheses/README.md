# 20. Valid Parentheses

**Easy · Stacks**

[Solve on LeetCode](https://leetcode.com/problems/valid-parentheses/) · [Curriculum](../../../README.md)

## Question Explanation

Decide whether a string of round, square, and curly brackets is correctly nested. A closing bracket must match the most recent opening bracket that has not already been closed. Merely counting opening and closing brackets is insufficient.

**Input constraints:** 1 ≤ n ≤ 10,000. Characters are restricted to ()[]{}. The implementations also accept an empty string as a defensive extension.

### Example

`s = "{[()]}"` → `true`; `s = "{[(])}"` → `false`. In the second string, ] tries to close ( before it has been closed.

### Concepts before coding

A stack is a last-in, first-out collection. push remembers a new opening bracket; pop removes the opening that the next closing bracket must match.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Brute force: repeated pair removal | O(n²) worst case from repeated scans and string movement | O(n) for a copy; Python slicing also uses temporary O(n) space |
| Optimal: stack of unmatched openings | O(n) | O(n) |

### 1. Brute force: repeated pair removal

A valid nonempty bracket string always contains an adjacent matching pair. Repeatedly remove such a pair and see whether anything remains.

**Algorithm**

1. Search for (), [], or {} at adjacent positions.
2. Remove one matching pair and restart the scan.
3. If nothing can be removed, return whether the remaining string is empty.

**Why it works:** An innermost pair in any valid nesting is adjacent. Removing it preserves validity. Conversely, inserting an adjacent matched pair into a valid sequence preserves validity, so reducing a string to empty certifies the original.

**Dry run:** {[()]} → {[]} → {} → empty. For ([)], no adjacent pair can be removed, so it is invalid.

**Complexity:** O(n²) worst case from repeated scans and string movement time; O(n) for a copy; Python slicing also uses temporary O(n) space space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Optimal: stack of unmatched openings

Keep the unmatched openings directly, avoiding repeated rescans and string copying.

**Algorithm**

1. Push opening brackets.
2. For a closing bracket, reject if the stack is empty or its top has the wrong type.
3. Otherwise pop the matching opening.
4. After the scan, accept only if the stack is empty.

**Why it works:** After every processed prefix, the stack contains exactly its unmatched openings in encounter order. A closing bracket must match the top to maintain proper nesting. An empty final stack means every opening was matched.

**Dry run:** On {[()]}, stack states are {, {[, {[(, {[, {, empty. Each closing bracket consumes precisely the latest opening.

**Complexity:** O(n) time; O(n) space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

A leading closing bracket; leftover openings; crossing bracket types such as ([)]; nested pairs; adjacent independent pairs; odd string length.

## Implementation Notes

Both versions preserve the caller’s string. C makes a working copy for pair removal and allocates a separate character stack for the optimal method. Neither needs a hash map because there are only three bracket types.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

Whenever the newest unfinished item must be handled first, consider a stack.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
