// Minimum Window Substring | Optimal: expand and shrink a sliding window
// See ../README.md for reasoning, complexity, and ownership.
#include <array>
#include <string>
using namespace std;

class Solution {
public:

    string minWindow(string s, string t) {
        int m = static_cast<int>(s.size());
        if (t.empty() || s.size() < t.size()) return "";
        array<int, 128> balance{};
        for (unsigned char ch : t) ++balance[ch];
        int left = 0, missing = static_cast<int>(t.size()), bestStart = 0, bestLength = m + 1;
        for (int right = 0; right < m; ++right) {
            unsigned char ch = s[right];
            if (balance[ch] > 0) --missing;
            --balance[ch];
            while (missing == 0) {
                if (right - left + 1 < bestLength) {
                    bestStart = left;
                    bestLength = right - left + 1;
                }
                unsigned char removed = s[left++];
                if (++balance[removed] > 0) ++missing;
            }
        }
        return bestLength == m + 1 ? "" : s.substr(bestStart, bestLength);
    }
};
