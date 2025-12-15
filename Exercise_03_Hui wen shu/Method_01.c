#include <stdbool.h>

bool isPalindrome(int x) {
    // 负数直接排除
    if (x < 0) {
        return false;
    }
    long original = x;  // 用long存储原数，避免反转时溢出
    long rev = 0;       // 存储反转后的数
    
    // 反转数字
    while (x > 0) {
        rev = rev * 10 + x % 10;  // 取最后一位加到反转数末尾
        x = x / 10;               // 去掉最后一位
    }
    
    // 比较反转后与原数是否相等
    return rev == original;
}