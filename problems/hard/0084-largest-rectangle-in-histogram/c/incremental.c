// Largest Rectangle in Histogram | Better: maintain the interval minimum as it grows
// See ../README.md for reasoning, complexity, and ownership.
int largestRectangleArea(int* heights, int heightsSize) {
    int best = 0;
    for (int left = 0; left < heightsSize; ++left) {
        int minimum = heights[left];
        for (int right = left; right < heightsSize; ++right) {
            if (heights[right] < minimum) minimum = heights[right];
            int area = minimum * (right - left + 1);
            if (area > best) best = area;
        }
    }
    return best;
}
