// Minimum Window Substring | Brute force: recount every candidate substring
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
        for (int right = left; right < m; ++right) {
            int have[128] = {0};
            for (int i = left; i <= right; ++i) ++have[(unsigned char)s[i]];
            int valid = 1;
            for (int c = 0; c < 128; ++c) if (have[c] < need[c]) valid = 0;
            if (valid && right - left + 1 < bestLength) {
                bestStart = left;
                bestLength = right - left + 1;
            }
        }
    }
    return copyWindow(s, bestStart, bestLength == m + 1 ? 0 : bestLength);
}
