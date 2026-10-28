// Trapping Rain Water | Optimal auxiliary space: two pointers
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = static_cast<int>(height.size()) - 1;
        int leftMax = 0, rightMax = 0, total = 0;
        while (left <= right) {
            if (height[left] <= height[right]) {
                leftMax = max(leftMax, height[left]);
                total += leftMax - height[left++];
            } else {
                rightMax = max(rightMax, height[right]);
                total += rightMax - height[right--];
            }
        }
        return total;
    }
};
