/*
 * Given a non-negative integer num, repeatedly add all its digits until the 
 * result has only one digit.
 *
 * For example:
 *
 * Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has 
 * only one digit, return it.
 *
 * Follow up:
 * Could you do it without any loop/recursion in O(1) runtime?
 */

#include <stdio.h>

int addDigits(int num) {
    int ret = 0;
    // int m, n;
    if(num < 10)
        return num;
        
    while(num != 0) {
        ret += (num % 10);
        num /= 10;
    }
    
    return addDigits(ret);
}

int main() {
    printf("Result of addDigits 38: %d\n", addDigits(38));
    printf("Result of addDigits 42: %d\n", addDigits(42));
    printf("Result of addDigits 5: %d\n", addDigits(5));
    printf("Result of addDigits 10: %d\n", addDigits(10));
    printf("Result of addDigits 9876543: %d\n", addDigits(9876543));

    return 0;
}
