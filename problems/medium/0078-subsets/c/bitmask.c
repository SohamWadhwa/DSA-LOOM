// Subsets | Enumeration: interpret a bitmask as a subset
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int total = 1 << numsSize;
    int** result = malloc((size_t)total * sizeof(*result));
    *returnColumnSizes = malloc((size_t)total * sizeof(**returnColumnSizes));
    *returnSize = total;
    for (int mask = 0; mask < total; ++mask) {
        int count = 0;
        for (int bit = 0; bit < numsSize; ++bit) if (mask & (1 << bit)) ++count;
        result[mask] = malloc((size_t)(count ? count : 1) * sizeof(**result));
        (*returnColumnSizes)[mask] = count;
        int used = 0;
        for (int bit = 0; bit < numsSize; ++bit)
            if (mask & (1 << bit)) result[mask][used++] = nums[bit];
    }
    return result;
}
