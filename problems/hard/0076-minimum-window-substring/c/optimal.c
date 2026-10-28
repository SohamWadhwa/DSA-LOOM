// Minimum Window Substring | Optimal: expand and shrink a sliding window
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
    int m = (int)strlen(s), n = (int)strlen(t), balance[128] = {0};
    if (n == 0 || m < n) return copyWindow(s, 0, 0);
    for (int i = 0; i < n; ++i) ++balance[(unsigned char)t[i]];
    int left = 0, missing = n, bestStart = 0, bestLength = m + 1;
    for (int right = 0; right < m; ++right) {
        unsigned char ch = (unsigned char)s[right];
        if (balance[ch] > 0) --missing;
        --balance[ch]; // A negative balance represents surplus copies.
        while (missing == 0) {
            if (right - left + 1 < bestLength) {
                bestStart = left;
                bestLength = right - left + 1;
            }
            unsigned char removed = (unsigned char)s[left++];
            if (++balance[removed] > 0) ++missing;
        }
    }
    return copyWindow(s, bestStart, bestLength == m + 1 ? 0 : bestLength);
}
