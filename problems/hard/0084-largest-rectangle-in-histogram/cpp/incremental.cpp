// Largest Rectangle in Histogram | Better: maintain the interval minimum as it grows
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = static_cast<int>(heights.size()), best = 0;
        for (int left = 0; left < n; ++left) {
            int minimum = heights[left];
            for (int right = left; right < n; ++right) {
                minimum = min(minimum, heights[right]);
                best = max(best, minimum * (right - left + 1));
            }
        }
        return best;
    }
};
