// Trapping Rain Water | Brute force: scan left and right boundaries for every bar
// See ../README.md for reasoning, complexity, and ownership.
int trap(int* height, int heightSize) {
    int total = 0;
    for (int i = 0; i < heightSize; ++i) {
        int left = height[i], right = height[i];
        for (int j = 0; j < i; ++j) if (height[j] > left) left = height[j];
        for (int j = i + 1; j < heightSize; ++j) if (height[j] > right) right = height[j];
        total += (left < right ? left : right) - height[i];
    }
    return total;
}
