// Subsets | Output-optimal alternative: backtracking
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>
#include <string.h>

static void visit(int* nums, int n, int start, int* path, int used,
                  int** result, int* columns, int* count) {
    int row = (*count)++;
    result[row] = malloc((size_t)(used ? used : 1) * sizeof(**result));
    memcpy(result[row], path, (size_t)used * sizeof(*path));
    columns[row] = used;
    for (int i = start; i < n; ++i) {
        path[used] = nums[i];
        visit(nums, n, i + 1, path, used + 1, result, columns, count);
    }
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int total = 1 << numsSize;
    int** result = malloc((size_t)total * sizeof(*result));
    *returnColumnSizes = malloc((size_t)total * sizeof(**returnColumnSizes));
    int* path = malloc((size_t)(numsSize ? numsSize : 1) * sizeof(*path));
    *returnSize = 0;
    visit(nums, numsSize, 0, path, 0, result, *returnColumnSizes, returnSize);
    free(path);
    return result;
}
