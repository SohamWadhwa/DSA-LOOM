# 23. Merge k Sorted Lists

**Hard · Linked lists, heaps, divide and conquer**

[Solve on LeetCode](https://leetcode.com/problems/merge-k-sorted-lists/) · [Curriculum](../../../README.md)

## Question Explanation

Merge k individually sorted singly linked lists into one sorted linked list containing every original node. Lists may be empty, and equal values are allowed. Reuse nodes rather than allocating an entirely new output list.

**Input constraints:** 0 ≤ k ≤ 10,000; each list has at most 500 nodes; at most N=10,000 nodes in total; values between −10,000 and 10,000. Input lists are assumed disjoint and acyclic.

### Example

`lists = [[1,6], [2,4], [0,7]]` → `[0,1,2,4,6,7]`.

### Concepts before coding

The smallest remaining node of a sorted list is always its head. A min-heap exposes the smallest of many candidates. Divide and conquer repeatedly combines pairs of already-sorted sequences.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Brute force: scan every current list head | O(k(N+1)) | O(1), reusing input head storage |
| Optimal time: min-heap of current heads | O(k + N log(k+1)) | O(k) |
| Optimal time with constant workspace: bottom-up pairwise merging | O(k + N log(k+1)) | O(1), with the existing head array reused |

### 1. Brute force: scan every current list head

At each output position, scan all current list heads and choose the smallest.

**Algorithm**

1. Use a dummy output head and a tail pointer.
2. Scan the k heads to find the smallest non-null node.
3. Advance that input head and append the chosen node.
4. Stop when every input head is null; terminate the output tail.

**Why it works:** The smallest remaining node of each sorted list is its head. Therefore the smallest among all heads is the global smallest remaining node. Repeating this choice produces sorted output and consumes each node once.

**Dry run:** Heads 1,2,0 choose 0. The heads become 1,2,7, choosing 1 next. Repeated scans then choose 2,4,6,7.

**Complexity:** O(k(N+1)) time; O(1), reusing input head storage space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Optimal time: min-heap of current heads

Store only one candidate per nonempty list in a min-heap. Replacing one candidate no longer requires a full scan.

**Algorithm**

1. Push every nonempty head into a min-heap.
2. Pop the smallest node and append it.
3. Push that node’s successor if it exists.
4. Repeat until the heap is empty.

**Why it works:** The heap contains the first unconsumed node from every active list. Its minimum is the global next output node. Inserting the successor restores the candidate invariant after each removal.

**Dry run:** Heap starts with 0,1,2. Pop 0 and push 7; pop 1 and push 6; pop 2 and push 4. The remaining pops are 4,6,7.

**Complexity:** O(k + N log(k+1)) time; O(k) space.

**Detailed implementations:** [C](c/heap.c) · [C++](cpp/heap.cpp) · [Python](python/heap.py)

### 3. Optimal time with constant workspace: bottom-up pairwise merging

Merge neighboring lists in rounds, doubling the group size after each round. This avoids heap storage while preserving logarithmic rounds.

**Algorithm**

1. Write an iterative helper that merges two sorted linked lists.
2. Merge pairs at distance 1, then distance 2, then distance 4, and so on.
3. Store each merged head in the first slot of its group.
4. Return slot zero after all groups have combined.

**Why it works:** After a round of width w, each surviving head represents the sorted merge of its group of up to 2w original lists. The two-list helper preserves every node. Eventually one group contains all lists.

**Dry run:** First merge [1,6] with [2,4] to get [1,2,4,6]. In the next round, merge that result with [0,7] to get the full sorted list.

**Complexity:** O(k + N log(k+1)) time; O(1), with the existing head array reused space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

No lists; only empty lists; one nonempty list; repeated equal head values; negative values; highly unequal list lengths. Python heaps need a tie-breaker because nodes themselves are not orderable.

## Implementation Notes

All variants rewire existing nodes. The scan and bottom-up versions also mutate the input array of head pointers; the heap version leaves that array intact but consumes the linked structures. Constant workspace for bottom-up merging relies on reusing that head array and iterative two-list merges. Heap and pairwise merging have the same asymptotic worst-case time, so the latter improves auxiliary space rather than time. The total bounds include the O(k) cost of inspecting empty lists.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

Exploit ordering already present in the input. Heaps coordinate several sorted streams; pairwise merging reuses the same two-list primitive.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
