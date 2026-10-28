// Largest Rectangle in Histogram | Brute force: recompute the minimum in every interval
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = static_cast<int>(heights.size()), best = 0;
        for (int left = 0; left < n; ++left) {
            for (int right = left; right < n; ++right) {
                int minimum = heights[left];
                for (int i = left + 1; i <= right; ++i) minimum = min(minimum, heights[i]);
                best = max(best, minimum * (right - left + 1));
            }
        }
        return best;
    }
};
