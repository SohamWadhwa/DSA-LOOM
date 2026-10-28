// Valid Parentheses | Brute force: repeated pair removal
// See ../README.md for reasoning, complexity, and ownership.
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool matches(char a, char b) {
    return (a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}');
}

bool isValid(char* s) {
    size_t length = strlen(s);
    char* work = malloc(length + 1);
    memcpy(work, s, length + 1);
    bool changed = true;
    while (length && changed) {
        changed = false;
        for (size_t i = 0; i + 1 < length; ++i) {
            if (matches(work[i], work[i + 1])) {
                memmove(work + i, work + i + 2, length - i - 1);
                length -= 2;
                changed = true;
                break; // Restart, because a new adjacent pair may exist.
            }
        }
    }
    free(work);
    return length == 0;
}
