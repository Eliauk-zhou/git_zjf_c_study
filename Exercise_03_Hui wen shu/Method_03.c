#include <stdbool.h>

bool isPalindrome(int x) {
    // 排除负数和末尾为0的非0数
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }
    
    int rev = 0;  // 存储反转的后半部分
    
    // 反转后半部分（原数 > 反转数时继续）
    while (x > rev) {
        rev = rev * 10 + x % 10;  // 取最后一位加入反转数
        x = x / 10;               // 原数去掉最后一位
    }
    
    // 偶数位：x == rev；奇数位：x == rev / 10（去掉中间位）
    return x == rev || x == rev / 10;
}