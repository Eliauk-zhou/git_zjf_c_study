/*
解法1：二维数组解法
*/

#include <stdio.h>
#define rows 10

int main() {
    // 定义杨辉三角的行数
    //int rows = 10;

    // 二维数组存储杨辉三角，行数+1避免越界（数组下标从0开始）
    int triangle[rows][rows];

    // 步骤1：初始化并计算杨辉三角
    for (int i = 0; i < rows; i++) { // i表示行号（0~rows-1）
        for (int j = 0; j <= i; j++) { // j表示列号（0~i），每行只有i+1个元素
            // 边界条件：每行第一个/最后一个元素为1
            if (j == 0 || j == i) {
                triangle[i][j] = 1;
            } else {
                // 递推公式：当前值 = 上一行前一列 + 上一行同列
                triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
        }
    }

    // 步骤2：格式化输出杨辉三角（三角形状）
    printf("杨辉三角（%d行）：\n", rows);
    for (int i = 0; i < rows; i++) {
        // 前导空格：行数越多，前面空格越少，形成三角
        for (int k = 0; k < rows - i - 1; k++) {
            printf(" ");
        }
        // 输出当前行的数字
        for (int j = 0; j <= i; j++) {
            printf("%d ", triangle[i][j]);
        }
        // 换行
        printf("\n");
    }

    return 0;
}