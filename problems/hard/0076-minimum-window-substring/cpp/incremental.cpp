// Minimum Window Substring | Better: reuse counts while extending each start position
// See ../README.md for reasoning, complexity, and ownership.
#include <array>
#include <string>
using namespace std;

class Solution {
public:

    string minWindow(string s, string t) {
        int m = static_cast<int>(s.size());
        if (t.empty() || s.size() < t.size()) return "";
        array<int, 128> need{};
        for (unsigned char ch : t) ++need[ch];
        int bestStart = 0, bestLength = m + 1;
        for (int left = 0; left < m; ++left) {
            array<int, 128> have{};
            int missing = static_cast<int>(t.size());
            for (int right = left; right < m; ++right) {
                unsigned char ch = s[right];
                if (have[ch] < need[ch]) --missing;
                ++have[ch];
                if (missing == 0) {
                    if (right - left + 1 < bestLength) {
                        bestStart = left;
                        bestLength = right - left + 1;
                    }
                    break;
                }
            }
        }
        return bestLength == m + 1 ? "" : s.substr(bestStart, bestLength);
    }
};
