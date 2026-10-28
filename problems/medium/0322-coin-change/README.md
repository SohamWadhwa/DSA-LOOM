# 322. Coin Change

**Medium · Recursion, memoization, dynamic programming**

[Solve on LeetCode](https://leetcode.com/problems/coin-change/) · [Curriculum](../../../README.md)

## Question Explanation

Given positive coin denominations and a target amount, find the fewest coins whose values total exactly that amount. Any denomination may be reused. Return −1 if forming the amount is impossible; return 0 for an amount of zero.

**Input constraints:** 1–12 denominations; 1 ≤ coin ≤ 2³¹ − 1; 0 ≤ amount ≤ 10,000. Let A be the target, c the denomination count, and d the smallest denomination.

### Example

`coins = [1,3,4]`, `amount = 6` → `2`. `coins = [4,6]`, `amount = 5` → `−1`.

### Concepts before coding

Dynamic programming stores the answer to overlapping smaller problems. Here a state is the remaining amount. Greedily taking the largest coin is not generally correct: with [1,3,4] and amount 6, 3+3 beats 4+1+1.

## Approaches

| Approach | Time | Auxiliary space / output notes |
|---|---|---|
| Brute force: enumerate coin choices recursively | Exponential search; O(c^(⌊A/d⌋+1)) upper bound for c≥2; O(A/d) when c=1 | O(A/d) recursion depth |
| Better: memoize each remaining amount | O(cA) | O(A) cache and call stack |
| Optimal practical DP: bottom-up tabulation | O(cA) | O(A) |

### 1. Brute force: enumerate coin choices recursively

Try every possible next coin, recursively solve the remainder, and retain the shortest successful sequence.

**Algorithm**

1. Return zero if the remaining amount is zero.
2. For each coin no larger than the remainder, solve the remainder minus that coin.
3. Add one for the current coin and minimize.
4. Convert an unreachable final result to −1.

**Why it works:** Any valid nonzero solution begins with some allowed coin. The recursion considers each such first choice and, inductively, its best continuation. Taking the minimum therefore gives the fewest coins.

**Dry run:** For 6, the first choices are 1→solve(5), 3→solve(3), and 4→solve(2). The 3 branch reaches another 3 and uses two coins. Many smaller remainders are recomputed.

**Complexity:** Exponential search; O(c^(⌊A/d⌋+1)) upper bound for c≥2; O(A/d) when c=1 time; O(A/d) recursion depth space.

**Detailed implementations:** [C](c/brute_force.c) · [C++](cpp/brute_force.cpp) · [Python](python/brute_force.py)

### 2. Better: memoize each remaining amount

Cache a result for each remaining amount, including unreachable states, to avoid repeating the same search subtree.

**Algorithm**

1. Initialize the base case at remainder zero.
2. Before expanding a remainder, return its cached result if available.
3. Compute the same recurrence as brute force.
4. Store the result before returning it.

**Why it works:** Caching changes only whether a proven subproblem result is recomputed. Each state still evaluates exactly the same recurrence, so correctness follows from the exhaustive version.

**Dry run:** Once solve(2) is evaluated, every later branch needing remainder 2 reuses its answer. At most the remainders 0 through 6 are computed.

**Complexity:** O(cA) time; O(A) cache and call stack space.

**Detailed implementations:** [C](c/memoized.c) · [C++](cpp/memoized.cpp) · [Python](python/memoized.py)

### 3. Optimal practical DP: bottom-up tabulation

Compute smaller amounts first in a table so the recurrence needs no recursive calls.

**Algorithm**

1. Set dp[0]=0 and use A+1 for unknown or unreachable positive amounts.
2. Visit amounts 1 through A in increasing order.
3. For each usable coin, minimize dp[value] with 1+dp[value−coin].
4. Return dp[A], or −1 if its sentinel remains.

**Why it works:** Every dependency value−coin is smaller than value because denominations are positive. By induction, all values used in a transition are already optimal, and the transition considers every possible final coin.

**Dry run:** For [1,3,4], dp[0..6] becomes [0,1,2,1,1,2,2]. At 6, using coin 3 gives 1+dp[3]=2.

**Complexity:** O(cA) time; O(A) space.

**Detailed implementations:** [C](c/optimal.c) · [C++](cpp/optimal.cpp) · [Python](python/optimal.py)

## Edge Cases

Zero amount; impossible totals; a denomination larger than the amount; no denomination 1; a greedy counterexample. Check coin ≤ remaining before subtracting.

## Implementation Notes

Define F(0)=0 and F(a)=min(1+F(a−coin)) over coins ≤ a. Use A+1 as an unreachable sentinel because any feasible answer uses at most A positive-valued coins. Memoization and bottom-up DP share O(cA) time; tabulation is preferred for predictable stack use. Recursive variants are teaching versions for small inputs: Python can hit its recursion limit, including the memoized variant. The iterative optimal version handles A=10,000 without recursion. Inputs are preserved.

The C examples assume allocations succeed under the problem limits; general-purpose production code should handle allocation failure. LeetCode provides ListNode and TreeNode definitions where needed. Local test wrappers supply equivalent definitions. See [running the code](../../../RUNNING.md) for submission and test instructions.

## Pattern to Remember

Identify the state, define its recurrence, and compute each state once. Tabulation can also remove recursion risk.

## Sources

Selection and optimal-pattern reference: [neetcode-gh/leetcode](https://github.com/neetcode-gh/leetcode/tree/8fed5f7daa6a517e375a0562d876e4a72dfdafb8). These explanations and self-contained variants were written for DSA-LOOM. See the [pinned source file links](../../../SOURCES.md) and [NeetCode MIT notice](../../../THIRD_PARTY_NOTICES.md). The LeetCode link above remains the authority for the full problem statement and current constraints.
