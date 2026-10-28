// Largest Rectangle in Histogram | Optimal: increasing stack of bar indices
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>

int largestRectangleArea(int* heights, int heightsSize) {
    int* stack = malloc(((size_t)heightsSize + 1) * sizeof(*stack));
    int top = 0, best = 0;
    for (int i = 0; i <= heightsSize; ++i) {
        int current = i == heightsSize ? 0 : heights[i]; // Virtual final bar.
        while (top && heights[stack[top - 1]] > current) {
            int height = heights[stack[--top]];
            int left = top ? stack[top - 1] : -1;
            int area = height * (i - left - 1);
            if (area > best) best = area;
        }
        if (i < heightsSize) stack[top++] = i;
    }
    free(stack);
    return best;
}
