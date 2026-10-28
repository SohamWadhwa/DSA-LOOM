// Minimum Window Substring | Brute force: recount every candidate substring
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
            for (int right = left; right < m; ++right) {
                array<int, 128> have{};
                for (int i = left; i <= right; ++i) ++have[static_cast<unsigned char>(s[i])];
                bool valid = true;
                for (int c = 0; c < 128; ++c) if (have[c] < need[c]) valid = false;
                if (valid && right - left + 1 < bestLength) {
                    bestStart = left;
                    bestLength = right - left + 1;
                }
            }
        }
        return bestLength == m + 1 ? "" : s.substr(bestStart, bestLength);
    }
};
