# DSA-LOOM

**Weave the fundamentals into a working understanding of data structures and algorithms.**

[![Solutions](https://github.com/SohamWadhwa/DSA-LOOM/actions/workflows/test.yml/badge.svg)](https://github.com/SohamWadhwa/DSA-LOOM/actions/workflows/test.yml)

A guided overview of DSA through **12 foundational LeetCode problems: 4 Easy, 4 Medium, and 4 Hard**. Each lesson explains the question, develops the algorithms from an exhaustive or direct baseline to improved approaches, and includes working **C, C++, and Python** code for every approach.

There are **31 approaches and 93 implementation files**. Some problems have two useful approaches; others have three. Equal-performance alternatives are identified explicitly, including output-optimal subset enumeration and heap versus pairwise merging.

**Practice directly on LeetCode. No local compiler, installation, or setup is needed.** Open a lesson's LeetCode link, choose C, C++, or Python3, and paste one solution file into the editor. Use the `optimal` version for the recommended submission.

## Who this is for

You should know variables, conditions, loops, arrays, and functions in at least one language. The lessons introduce the needed data structures before using them. C readers will benefit from basic pointer knowledge; the linked-list lesson develops that skill further.

The Hard label describes the LeetCode exercise, not an expectation that beginners should solve it unaided. Read the earlier lessons first and use the Hard problems as guided demonstrations of how basic ideas combine.

## Learning Order

| Order | Difficulty | Lesson | Core ideas | LeetCode |
|---|---|---|---|---|
| 1 | Easy | [1. Two Sum](problems/easy/0001-two-sum/README.md) | Arrays, sorting, hashing | [Practice](https://leetcode.com/problems/two-sum/) |
| 2 | Easy | [20. Valid Parentheses](problems/easy/0020-valid-parentheses/README.md) | Stacks | [Practice](https://leetcode.com/problems/valid-parentheses/) |
| 3 | Easy | [704. Binary Search](problems/easy/0704-binary-search/README.md) | Binary search | [Practice](https://leetcode.com/problems/binary-search/) |
| 4 | Easy | [206. Reverse Linked List](problems/easy/0206-reverse-linked-list/README.md) | Linked lists, recursion | [Practice](https://leetcode.com/problems/reverse-linked-list/) |
| 5 | Medium | [102. Binary Tree Level Order Traversal](problems/medium/0102-binary-tree-level-order-traversal/README.md) | Trees, queues, BFS | [Practice](https://leetcode.com/problems/binary-tree-level-order-traversal/) |
| 6 | Medium | [200. Number of Islands](problems/medium/0200-number-of-islands/README.md) | Graphs, connected components, BFS | [Practice](https://leetcode.com/problems/number-of-islands/) |
| 7 | Medium | [78. Subsets](problems/medium/0078-subsets/README.md) | Bit manipulation, backtracking | [Practice](https://leetcode.com/problems/subsets/) |
| 8 | Medium | [322. Coin Change](problems/medium/0322-coin-change/README.md) | Recursion, memoization, dynamic programming | [Practice](https://leetcode.com/problems/coin-change/) |
| 9 | Hard | [23. Merge k Sorted Lists](problems/hard/0023-merge-k-sorted-lists/README.md) | Linked lists, heaps, divide and conquer | [Practice](https://leetcode.com/problems/merge-k-sorted-lists/) |
| 10 | Hard | [42. Trapping Rain Water](problems/hard/0042-trapping-rain-water/README.md) | Prefix and suffix maxima, two pointers | [Practice](https://leetcode.com/problems/trapping-rain-water/) |
| 11 | Hard | [76. Minimum Window Substring](problems/hard/0076-minimum-window-substring/README.md) | Frequency counting, sliding windows | [Practice](https://leetcode.com/problems/minimum-window-substring/) |
| 12 | Hard | [84. Largest Rectangle in Histogram](problems/hard/0084-largest-rectangle-in-histogram/README.md) | Range enumeration, monotonic stacks | [Practice](https://leetcode.com/problems/largest-rectangle-in-histogram/) |

## How to use a lesson

1. Read the explanation and work through the small example by hand.
2. Understand the direct baseline before studying its limitations.
3. Follow each improvement, its correctness argument, and its dry run.
4. Read one language implementation, then compare the other two if useful.
5. Open the linked LeetCode problem, choose your language, paste one solution, and use LeetCode's Run or Submit button.
6. Explain the final invariant and complexity without looking at the code.

Each lesson includes algorithm steps, correctness reasoning, time and space bounds, edge cases, memory-ownership or mutation notes, and the pattern to remember. Source code is linked beside each approach rather than duplicated inside long Markdown code blocks.

## The big picture

| Fundamental idea | Where to study it |
|---|---|
| Arrays, sorting, and hash lookup | Two Sum |
| Stacks and last-in, first-out ordering | Valid Parentheses |
| Sorted search and interval invariants | Binary Search |
| Pointers and recursive versus iterative state | Reverse Linked List |
| Trees, queues, and breadth-first search | Binary Tree Level Order Traversal |
| Graph traversal and connected components | Number of Islands |
| Bitmasks and backtracking | Subsets |
| Overlapping subproblems and dynamic programming | Coin Change |
| Heaps, merging, and divide and conquer | Merge k Sorted Lists |
| Prefix/suffix summaries and two pointers | Trapping Rain Water |
| Frequency counts and sliding windows | Minimum Window Substring |
| Monotonic stacks and amortized analysis | Largest Rectangle in Histogram |

## Submit on LeetCode

1. Open the **Practice** link for a problem in the table above.
2. Select **C**, **C++**, or **Python3** in LeetCode's editor.
3. Open that language's folder in the lesson and copy exactly one approach file.
4. Paste it into LeetCode and click **Run** or **Submit**.

The `optimal` file is the recommended full-constraint solution. Brute-force and recursive alternatives teach the progression and may exceed LeetCode's time or recursion limits on large inputs.

Files already use LeetCode's function or `Solution` method interfaces. LeetCode supplies the list and tree node definitions when needed. There is no `main` function or custom input/output setup to add.

## Optional repository validation

The [automated checks](https://github.com/SohamWadhwa/DSA-LOOM/actions) are for maintaining and verifying the repository. They are separate from the LeetCode learning workflow. Contributors who want to run those checks locally can follow the optional instructions in [RUNNING.md](RUNNING.md).

## Sources and license

The questions were selected from [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode). All 12 selections were checked on LeetCode on **28 October 2026** and have C, C++, and Python entries in that source repository. [SOURCES.md](SOURCES.md) records pinned source links for all 36 reference files.

Explanations and the self-contained approach implementations were written for DSA-LOOM. Original material is under the [MIT License](LICENSE); the [NeetCode MIT notice](THIRD_PARTY_NOTICES.md) is retained for referenced and adapted material. Full problem statements remain on LeetCode.
