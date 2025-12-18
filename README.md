# 红黑树 (Red-Black Tree) C++ 实现

这是一个完整的C++红黑树实现，包含所有基本操作。

## 特性

- ✅ 插入操作 (Insert)
- ✅ 删除操作 (Delete)
- ✅ 查找操作 (Search)
- ✅ 中序遍历 (In-order Traversal)
- ✅ 层序遍历 (Level-order Traversal)
- ✅ 获取最小值和最大值
- ✅ 模板类，支持任意可比较类型

## 红黑树性质

1. 每个节点是红色或黑色
2. 根节点是黑色
3. 每个叶子节点（NIL）是黑色
4. 如果一个节点是红色，那么它的两个子节点都是黑色
5. 从任意节点到其每个叶子的所有简单路径都包含相同数目的黑色节点

## 编译和运行

```bash
# 使用 g++
g++ -std=c++11 main.cpp -o red_black_tree
./red_black_tree

# 或使用 clang++
clang++ -std=c++11 main.cpp -o red_black_tree
./red_black_tree
```

## 使用示例

```cpp
#include "RedBlackTree.h"

// 创建红黑树
RedBlackTree<int> tree;

// 插入元素
tree.insert(10);
tree.insert(20);
tree.insert(30);

// 查找元素
bool found = tree.search(20);

// 删除元素
tree.remove(20);

// 遍历
tree.printInOrder();      // 中序遍历
tree.printLevelOrder();   // 层序遍历

// 获取最值
int min = tree.getMin();
int max = tree.getMax();
```

## 文件说明

- `RedBlackTree.h`: 红黑树的完整实现（头文件）
- `main.cpp`: 测试程序，演示各种操作
- `README.md`: 说明文档
