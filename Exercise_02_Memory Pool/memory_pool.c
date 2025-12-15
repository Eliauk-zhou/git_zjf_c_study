#include <stddef.h>   // 定义NULL、size_t等基础类型
#include <stdio.h>    // 标准输入输出（printf、strcpy）
#include <stdlib.h>   // 动态内存管理（malloc、free）
#include <string.h>   // 字符串操作（strcpy）

// 内存池中的单个对象（存储数据+空闲标记）
typedef struct{
  int is_free;        // 1=空闲，0=占用
  char data[256];     // 数据存储区（256字节）
} object;

// 内存池管理器（管理所有对象）
typedef struct{
  object *pool;       // 指向对象数组的首地址
  int pool_size;      // 内存池总容量（对象总数）
  int used_count;     // 已分配的对象数
} objectpool;

// 初始化内存池：创建管理器+对象数组，标记所有对象为空闲
objectpool *pool_init(int size){
  // 申请管理器内存
  objectpool *p = (objectpool *)malloc(sizeof(objectpool));
  if(NULL == p){
    printf("内存池管理器申请失败！\n");
    return NULL;
  }

  // 申请size个object的连续内存
  p->pool = (object *)malloc(sizeof(object) * size);
  if(NULL == p->pool){
    printf("内存池申请失败！\n");
    free(p);  // 回滚：释放已申请的管理器内存
    return NULL;
  }

  // 初始化管理器状态
  p->pool_size = size;
  p->used_count = 0;

  // 所有对象标记为空闲
  for(int i = 0; i < size; i++){
    p->pool[i].is_free = 1;
  }

  return p;
}

// 从内存池分配对象：找第一个空闲对象，标记为占用并返回
object *pool_alloc(objectpool *p){
  if(NULL == p) return NULL;

  // 遍历找空闲对象
  for(int i = 0; i < p->pool_size; i++){
    if(p->pool[i].is_free == 1){
      p->pool[i].is_free = 0;  // 标记为占用
      p->used_count++;         // 已用数+1
      return &p->pool[i];      // 返回对象地址
    }
  }

  return NULL;  // 无空闲对象
}

// 释放对象：验证合法性后，标记为空闲
void pool_free(objectpool *p, object *obj){
  // 参数无效直接返回（修正原代码&&为||）
  if(NULL == p || NULL == obj) return;

  // 检查obj是否在内存池地址范围内
  if(obj >= p->pool && obj < p->pool + p->pool_size){
    if(obj->is_free == 0){  // 仅释放占用状态的对象
      obj->is_free = 1;     // 标记为空闲
      p->used_count--;      // 已用数-1
    }
  }
}

// 销毁内存池：释放对象数组+管理器内存
void pool_destroy(objectpool *p){
  if(NULL == p) return;
  free(p->pool);  // 先释放对象数组
  free(p);        // 再释放管理器
}

// 主函数：测试内存池完整流程
int main(){
  // 创建容量为6的内存池
  objectpool *pool = pool_init(6);
  if(NULL == pool){
    printf("内存池创建失败！\n");
    return -1;
  }

  // 分配3个对象
  object *obj1 = pool_alloc(pool);
  object *obj2 = pool_alloc(pool);
  object *obj3 = pool_alloc(pool);

  if(obj1 && obj2 && obj3){
    printf("成功分配3个对象，已使用%d/6\n", pool->used_count);
    // 给对象赋值并打印
    strcpy(obj1->data, "我是第1个对象！");
    strcpy(obj2->data, "我是第2个对象！");
    strcpy(obj3->data, "我是第3个对象！");
    printf("obj1: %s, obj2: %s, obj3: %s\n", obj1->data, obj2->data, obj3->data);
  }

  // 释放obj2
  pool_free(pool, obj2);
  printf("释放obj2后，已使用%d/6\n", pool->used_count);

  // 再次分配obj4（复用obj2的空闲位置）
  object *obj4 = pool_alloc(pool);
  strcpy(obj4->data, "我是第4个对象！");
  printf("obj4: %s\n", obj4->data);
  printf("创建obj4后，已使用%d/6\n", pool->used_count);

  // 销毁内存池
  pool_destroy(pool);

  return 0;
}