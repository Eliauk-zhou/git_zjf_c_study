/*
解法3：递归法
*/
#include <stdio.h>

// 递归函数：返回杨辉三角第i行第j列的值（i,j从0开始）
int get_val(int i, int j) {
    // 边界条件：每行第一个/最后一个元素为1
    if (j == 0 || j == i) {
        return 1;
    }
    // 递归公式：当前值 = 上一行前一列 + 上一行同列
    return get_val(i-1, j-1) + get_val(i-1, j);
}

int main() {
    int rows = 10;
    printf("杨辉三角（递归版）：\n");

    // 遍历每一行（i为行号，0到rows-1）
    for (int i = 0; i < rows; i++) {
        // 前导空格
        for (int k = 0; k < rows - i - 1; k++) {
            printf(" ");
        }
        // 遍历当前行的每一列（j为列号，0到i）
        for (int j = 0; j <= i; j++) {
            printf("%d ", get_val(i, j));
        }
        printf("\n");
    }

    return 0;
}