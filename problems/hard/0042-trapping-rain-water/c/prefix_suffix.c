// Trapping Rain Water | Better: precompute prefix and suffix maxima
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>

int trap(int* height, int heightSize) {
    if (heightSize == 0) return 0;
    int* left = malloc((size_t)heightSize * sizeof(*left));
    int* right = malloc((size_t)heightSize * sizeof(*right));
    left[0] = height[0];
    for (int i = 1; i < heightSize; ++i)
        left[i] = left[i - 1] > height[i] ? left[i - 1] : height[i];
    right[heightSize - 1] = height[heightSize - 1];
    for (int i = heightSize - 2; i >= 0; --i)
        right[i] = right[i + 1] > height[i] ? right[i + 1] : height[i];
    int total = 0;
    for (int i = 0; i < heightSize; ++i)
        total += (left[i] < right[i] ? left[i] : right[i]) - height[i];
    free(left);
    free(right);
    return total;
}
