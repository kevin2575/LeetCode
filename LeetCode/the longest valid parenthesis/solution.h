#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;
class Solution {
public:

    struct Info
    {
        Info(char u, int p, int vp, int vl) 
            : c(u), pos(p), last_valid_pos(vp), last_valid_len(vl){};
        char c;
        int pos;
        int last_valid_pos;
        int last_valid_len;

    };

    int longestValidParentheses(string s) {

        if (s.size() == 0)
            return 0;

        int max_len = 0;
        int last_valid_len = 0;
        int last_valid_pos = -1;

        stack <Info> stk;

        for (int i = 0; i < s.size(); ++i) {
            if (stk.empty() || 
                stk.top().c == s[i] ||
                (stk.top().c == ')' && s[i] == '(')) {
                stk.push(Info(s[i], i, last_valid_pos, last_valid_len));
            } else {
                auto top = stk.top();
                stk.pop();
                int n = i - top.pos + 1;
                if (top.last_valid_pos + 1 == top.pos) {
                    last_valid_len = top.last_valid_len + n;
                    last_valid_pos = i;
                    max_len = (last_valid_len > max_len ? last_valid_len : max_len);
                }
                else {
                    max_len = (max_len < n ? n : max_len);
                    last_valid_len = n;
                    last_valid_pos = i;
                }
            }
        }
        return max_len;
    }
};