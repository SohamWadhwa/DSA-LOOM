// Valid Parentheses | Brute force: repeated pair removal
// See ../README.md for reasoning, complexity, and ownership.
#include <string>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        while (!s.empty()) {
            bool removed = false;
            for (size_t i = 0; i + 1 < s.size(); ++i) {
                string pair = s.substr(i, 2);
                if (pair == "()" || pair == "[]" || pair == "{}") {
                    s.erase(i, 2);
                    removed = true;
                    break;
                }
            }
            if (!removed) return false;
        }
        return true;
    }
};
