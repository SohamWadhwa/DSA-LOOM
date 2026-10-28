// Minimum Window Substring | Better: reuse counts while extending each start position
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>
#include <string.h>

static char* copyWindow(const char* s, int start, int length) {
    char* result = malloc((size_t)length + 1);
    memcpy(result, s + start, length);
    result[length] = '\0';
    return result; // Caller owns this string, including an empty answer.
}

char* minWindow(char* s, char* t) {
    int m = (int)strlen(s), n = (int)strlen(t), need[128] = {0};
    if (n == 0 || m < n) return copyWindow(s, 0, 0);
    for (int i = 0; i < n; ++i) ++need[(unsigned char)t[i]];
    int bestStart = 0, bestLength = m + 1;
    for (int left = 0; left < m; ++left) {
        int have[128] = {0}, missing = n;
        for (int right = left; right < m; ++right) {
            unsigned char ch = (unsigned char)s[right];
            if (have[ch] < need[ch]) --missing;
            ++have[ch];
            if (missing == 0) {
                if (right - left + 1 < bestLength) {
                    bestStart = left;
                    bestLength = right - left + 1;
                }
                break; // Later endpoints cannot improve this start.
            }
        }
    }
    return copyWindow(s, bestStart, bestLength == m + 1 ? 0 : bestLength);
}
