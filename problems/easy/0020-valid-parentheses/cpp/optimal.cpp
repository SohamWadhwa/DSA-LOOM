// Valid Parentheses | Optimal: stack of unmatched openings
// See ../README.md for reasoning, complexity, and ownership.
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        vector<char> stack;
        for (char ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') stack.push_back(ch);
            else {
                char need = ch == ')' ? '(' : ch == ']' ? '[' : '{';
                if (stack.empty() || stack.back() != need) return false;
                stack.pop_back();
            }
        }
        return stack.empty();
    }
};
