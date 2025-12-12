/*
解法2:一维数组优化法
*/
#include <stdio.h>
#define rows 10

int main() {
    //int rows = 10; // 目标行数
    int arr[rows]; // 一维数组存储当前行，大小为总行数即可

    // 初始化第0行（只有1个元素）
    arr[0] = 1;
    printf("杨辉三角（一维数组优化版）：\n");

    // 逐行构建（i表示当前行号，从0到rows-1）
    for (int i = 0; i < rows; i++) {
        // 步骤1：输出前导空格（保持三角形状）
        for (int k = 0; k < rows - i - 1; k++) {
            printf(" ");
        }

        // 步骤2：输出当前行的所有元素
        for (int j = 0; j <= i; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");

        // 步骤3：更新为下一行（从后往前，避免覆盖）
        // 下一行有i+2个元素，先把最后一个元素置1
        arr[i+1] = 1;
        // 从倒数第二个位置往前更新（j从i到1）
        for (int j = i; j >= 1; j--) {
            arr[j] = arr[j] + arr[j-1];
        }
    }

    return 0;
}