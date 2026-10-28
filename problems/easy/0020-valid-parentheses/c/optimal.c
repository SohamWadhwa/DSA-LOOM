// Valid Parentheses | Optimal: stack of unmatched openings
// See ../README.md for reasoning, complexity, and ownership.
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char* s) {
    char* stack = malloc(strlen(s) + 1);
    size_t top = 0;
    for (size_t i = 0; s[i]; ++i) {
        char ch = s[i];
        if (ch == '(' || ch == '[' || ch == '{') stack[top++] = ch;
        else {
            char need = ch == ')' ? '(' : ch == ']' ? '[' : '{';
            if (top == 0 || stack[top - 1] != need) {
                free(stack);
                return false;
            }
            --top;
        }
    }
    free(stack);
    return top == 0;
}
