/**
 * Given a column title as appear in an Excel sheet, return its corresponding
 * column number.
 *
 * For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
 */

class Solution {
public:
    int titleToNumber(string s) {
        int ret = 0;
        for_each (s.begin(), s.end(), [&ret](char ch) { ret = (ch - 'A'  + 1) + 26 * ret ;});
        return ret;
    }
};
