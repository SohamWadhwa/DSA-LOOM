// Binary Search | Optimal: iterative binary search
// See ../README.md for reasoning, complexity, and ownership.
int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (nums[middle] == target) return middle;
        if (nums[middle] < target) left = middle + 1;
        else right = middle - 1;
    }
    return -1;
}
