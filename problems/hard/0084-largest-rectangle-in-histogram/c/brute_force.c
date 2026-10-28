// Largest Rectangle in Histogram | Brute force: recompute the minimum in every interval
// See ../README.md for reasoning, complexity, and ownership.
int largestRectangleArea(int* heights, int heightsSize) {
    int best = 0;
    for (int left = 0; left < heightsSize; ++left) {
        for (int right = left; right < heightsSize; ++right) {
            int minimum = heights[left];
            for (int i = left + 1; i <= right; ++i)
                if (heights[i] < minimum) minimum = heights[i];
            int area = minimum * (right - left + 1);
            if (area > best) best = area;
        }
    }
    return best;
}
