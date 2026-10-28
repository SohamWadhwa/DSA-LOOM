# 206. Reverse Linked List

**Easy · Linked lists, recursion**

[Solve on LeetCode](https://leetcode.com/problems/reverse-linked-list/) · [Curriculum](../../../README.md)

## Question Explanation

Reverse the direction of every next pointer in a singly linked list and return its new head. Preserve the existing nodes and their values. Reversing just the values would hide the pointer operation this lesson teaches.

**Input constraints:** 0–5,000 nodes; node values from −5,000 to 5,000. An empty list is represented by a null head.

### Example

`head = [6, 2, 9]` → `[9, 2, 6]`. The node holding 9 becomes the new head, and the node holding 6 points to null.

### Concepts before coding

A node contains a value and a next pointer. Once a next pointer is overwritten, the old successor is lost unless saved elsewhere. The head is a pointer to the first node, not the entire list.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Baseline: store node pointers and relink | O(n) | O(n) |
| Alternative: recursive rewiring | O(n) | O(n) call stack |
| Optimal auxiliary space: iterative rewiring | O(n) | O(1) |

### 1. Baseline: store node pointers and relink

Record node pointers in encounter order, then connect them in the opposite order.

**Algorithm**

1. Traverse once and store pointers to all nodes.
2. Starting from the final pointer, link each node to its predecessor in the stored sequence.
3. Set the original first node’s next to null and return the final stored node.

**Why it works:** The stored sequence contains every original node exactly once. Relinking adjacent entries backward produces precisely its reversal, and the explicit null tail prevents a cycle.

**Dry run:** Store pointers [node6,node2,node9]. Set node9.next = node2, node2.next = node6, and node6.next = null.

**Complexity:** O(n) time; O(n) space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Alternative: recursive rewiring

Reverse the suffix first. Then attach the current head to the end of that reversed suffix.

**Algorithm**

1. Return immediately for an empty or one-node list.
2. Recursively reverse head.next.
3. Set head.next.next = head.
4. Set head.next = null and return the suffix’s new head.

**Why it works:** Inductively, the recursive call returns a correctly reversed suffix. Its old first node is now the tail; linking that tail to the current head extends the reversal by one node. Clearing the current head’s forward link preserves a null tail.

**Dry run:** For 6→2→9, the suffix becomes 9→2. Set 2.next = 6, then clear 6.next. The recursive new head remains node9.

**Complexity:** O(n) time; O(n) call stack space.

**Detailed implementations:** [C](c/recursive.c) · [C++](cpp/recursive.cpp) · [Python](python/recursive.py)

### 3. Optimal auxiliary space: iterative rewiring

Build a reversed prefix while retaining a pointer to the untouched suffix.

**Algorithm**

1. Initialize previous = null and current = head.
2. Save current.next in following.
3. Point current.next to previous.
4. Move previous to current and current to following.
5. Return previous when current becomes null.

**Why it works:** Before each iteration, previous heads the reversed processed prefix and current heads the untouched suffix. The saved successor allows exactly one node to move from the suffix into the reversed prefix without losing any node.

**Dry run:** Start previous=null, current=6. After the first step: 6→null with current=2. Then 2→6→null, and finally 9→2→6→null.

**Complexity:** O(n) time; O(1) space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

Empty list; one node; two nodes; duplicate values. Verify node identity and absence of cycles rather than checking values alone.

## Implementation Notes

Every approach mutates the next pointers and reuses all original nodes. The stored-pointer and recursive versions both take linear extra space; recursion is an alternative, not an asymptotic improvement. Python recursion may fail before 5,000 nodes, and native recursion also depends on available stack space. Use the iterative version for the full range. The caller owns and eventually frees nodes; only temporary pointer storage is freed inside C.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

Save the part you still need before modifying a pointer. An invariant makes local rewiring manageable.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
