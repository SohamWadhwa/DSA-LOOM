// Binary Search | Baseline: linear search
// See ../README.md for reasoning, complexity, and ownership.
int search(int* nums, int numsSize, int target) {
    for (int i = 0; i < numsSize; ++i)
        if (nums[i] == target) return i;
    return -1;
}
