#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isPalindrome(int x) {
    // 负数直接排除
    if (x < 0) {
        return false;
    }
    char str[20];  // 足够存储int的最大位数（10位）
    sprintf(str, "%d", x);  // 转换为字符串
    
    int left = 0;
    int right = strlen(str) - 1;  // 右指针指向最后一个字符
    
    // 首尾对比
    while (left < right) {
        if (str[left] != str[right]) {
            return false;  // 字符不等，不是回文数
        }
        left++;
        right--;
    }
    return true;
}