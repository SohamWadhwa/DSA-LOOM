// Subsets | Output-optimal alternative: backtracking
// See ../README.md for reasoning, complexity, and ownership.
#include <vector>
using namespace std;

class Solution {
    void visit(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& result) {
        result.push_back(path); // Copy before path changes.
        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            path.push_back(nums[i]);
            visit(nums, i + 1, path, result);
            path.pop_back(); // Undo this choice.
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        visit(nums, 0, path, result);
        return result;
    }
};
