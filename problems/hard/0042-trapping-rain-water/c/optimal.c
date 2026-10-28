// Trapping Rain Water | Optimal auxiliary space: two pointers
// See ../README.md for reasoning, complexity, and ownership.
int trap(int* height, int heightSize) {
    int left = 0, right = heightSize - 1, leftMax = 0, rightMax = 0, total = 0;
    while (left <= right) {
        if (height[left] <= height[right]) {
            if (height[left] > leftMax) leftMax = height[left];
            total += leftMax - height[left++];
        } else {
            if (height[right] > rightMax) rightMax = height[right];
            total += rightMax - height[right--];
        }
    }
    return total;
}
