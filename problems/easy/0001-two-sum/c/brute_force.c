// Two Sum | Brute force: enumerate pairs
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 0;
    for (int i = 0; i < numsSize; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if ((long long)nums[i] + nums[j] == target) {
                int* answer = malloc(2 * sizeof(*answer));
                answer[0] = i;
                answer[1] = j;
                *returnSize = 2;
                return answer; // Caller owns this array.
            }
        }
    }
    return NULL;
}
