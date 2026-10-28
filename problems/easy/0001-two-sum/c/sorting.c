// Two Sum | Better: sort indexed values and use two pointers
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>

typedef struct { int value, index; } Pair;
static int compare(const void* left, const void* right) {
    int a = ((const Pair*)left)->value;
    int b = ((const Pair*)right)->value;
    return (a > b) - (a < b); // Avoid subtraction overflow.
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Pair* pairs = malloc((size_t)numsSize * sizeof(*pairs));
    for (int i = 0; i < numsSize; ++i) pairs[i] = (Pair){nums[i], i};
    qsort(pairs, numsSize, sizeof(*pairs), compare);
    int left = 0, right = numsSize - 1;
    *returnSize = 0;
    while (left < right) {
        long long sum = (long long)pairs[left].value + pairs[right].value;
        if (sum == target) {
            int* answer = malloc(2 * sizeof(*answer));
            answer[0] = pairs[left].index;
            answer[1] = pairs[right].index;
            *returnSize = 2;
            free(pairs);
            return answer;
        }
        if (sum < target) ++left;
        else --right;
    }
    free(pairs);
    return NULL;
}
