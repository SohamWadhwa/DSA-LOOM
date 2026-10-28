# 42. Trapping Rain Water

**Hard · Prefix and suffix maxima, two pointers**

[Solve on LeetCode](https://leetcode.com/problems/trapping-rain-water/) · [Curriculum](../../../README.md)

## Question Explanation

Treat each nonnegative array value as a unit-width wall height. Compute the total water held between walls after rain. Water above a position is limited by the shorter of the tallest boundary on its left and right.

**Input constraints:** 1 ≤ n ≤ 20,000; heights from 0 to 100,000. The maximum total fits a signed 32-bit integer under these bounds.

### Example

`height = [4,1,2,4]` → `5`. Positions 1 and 2 hold 3 and 2 units respectively.

### Concepts before coding

A prefix maximum summarizes everything up to an index; a suffix maximum summarizes everything from that index onward. Two pointers can sometimes replace full summary arrays when one side is already decisive.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Brute force: scan left and right boundaries for every bar | O(n²) | O(1) |
| Better: precompute prefix and suffix maxima | O(n) | O(n) |
| Optimal auxiliary space: two pointers | O(n) | O(1) |

### 1. Brute force: scan left and right boundaries for every bar

For every bar, independently find the highest boundary on each side.

**Algorithm**

1. Choose a bar i.
2. Scan the prefix through i for its maximum height.
3. Scan the suffix from i for its maximum height.
4. Add the shorter maximum minus height[i].

**Why it works:** Water cannot rise above either side’s highest boundary or it would escape. It can reach the shorter boundary, so their minimum gives the exact water surface at that position.

**Dry run:** For [4,1,2,4], each interior position has boundary maxima 4 and 4. Contributions are 4−1=3 and 4−2=2.

**Complexity:** O(n²) time; O(1) space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Better: precompute prefix and suffix maxima

Reuse maxima from neighboring positions instead of rescanning the same prefixes and suffixes.

**Algorithm**

1. Build leftMax[i]=max(leftMax[i−1],height[i]) from left to right.
2. Build rightMax[i]=max(rightMax[i+1],height[i]) from right to left.
3. Sum the same per-position formula using constant-time lookups.

**Why it works:** The recurrences compute the exact prefix and suffix maxima by induction. Substituting those stored maxima into the proven water formula preserves the answer.

**Dry run:** leftMax is [4,4,4,4] and rightMax is [4,4,4,4]. Subtracting the heights from their minima gives [0,3,2,0].

**Complexity:** O(n) time; O(n) space.

**Detailed implementations:** [C](c/prefix_suffix.c) · [C++](cpp/prefix_suffix.cpp) · [Python](python/prefix_suffix.py)

### 3. Optimal auxiliary space: two pointers

Process the side with the smaller current endpoint height, keeping only running maxima for the two processed sides.

**Algorithm**

1. Place left and right pointers at the ends; initialize both running maxima and total to zero.
2. If the left height is no greater than the right height, update leftMax, add leftMax−height[left], and advance left.
3. Otherwise update rightMax, add rightMax−height[right], and retreat right.
4. Stop after the pointers cross.

**Why it works:** When processing a side, an opposing boundary at least as tall as that side’s running maximum is guaranteed by the previous endpoint choices. The opposite boundary therefore cannot lower the water below the running maximum on the processed side. That position’s contribution is final.

**Dry run:** For [4,1,2,4], process the left 4 and set leftMax=4. The next two left positions contribute 3 then 2. The final boundary contributes zero.

**Complexity:** O(n) time; O(1) space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

One bar; all equal bars; monotonically rising or falling heights; zero-height valleys; multiple basins; tall boundaries with a long interior.

## Implementation Notes

At index i, water = min(leftMax[i], rightMax[i]) − height[i], with each maximum including the current bar. The result is nonnegative by construction. All variants preserve the input. The optimal method improves space over prefix/suffix arrays while retaining linear time.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

Compute a local contribution using global summaries, then ask whether both summaries really need to be stored.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
