// Largest Rectangle in Histogram | Optimal: increasing stack of bar indices
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> stack;
        int n = static_cast<int>(heights.size()), best = 0;
        for (int i = 0; i <= n; ++i) {
            int current = i == n ? 0 : heights[i];
            while (!stack.empty() && heights[stack.back()] > current) {
                int height = heights[stack.back()];
                stack.pop_back();
                int left = stack.empty() ? -1 : stack.back();
                best = max(best, height * (i - left - 1));
            }
            if (i < n) stack.push_back(i);
        }
        return best;
    }
};
