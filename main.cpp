#include "RedBlackTree.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== 红黑树测试程序 ===" << std::endl;
    
    RedBlackTree<int> tree;
    
    // 测试插入
    std::cout << "\n1. 插入元素: 10, 20, 30, 15, 25, 5, 35" << std::endl;
    std::vector<int> values = {10, 20, 30, 15, 25, 5, 35};
    for (int val : values) {
        tree.insert(val);
        std::cout << "插入 " << val << " 后，中序遍历: ";
        tree.printInOrder();
    }
    
    // 测试查找
    std::cout << "\n2. 查找测试:" << std::endl;
    std::cout << "查找 15: " << (tree.search(15) ? "找到" : "未找到") << std::endl;
    std::cout << "查找 100: " << (tree.search(100) ? "找到" : "未找到") << std::endl;
    
    // 测试最小值和最大值
    std::cout << "\n3. 最小值和最大值:" << std::endl;
    try {
        std::cout << "最小值: " << tree.getMin() << std::endl;
        std::cout << "最大值: " << tree.getMax() << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    // 测试删除
    std::cout << "\n4. 删除测试:" << std::endl;
    std::cout << "删除 20 前，中序遍历: ";
    tree.printInOrder();
    tree.remove(20);
    std::cout << "删除 20 后，中序遍历: ";
    tree.printInOrder();
    
    std::cout << "删除 5 前，中序遍历: ";
    tree.printInOrder();
    tree.remove(5);
    std::cout << "删除 5 后，中序遍历: ";
    tree.printInOrder();
    
    // 层序遍历显示
    std::cout << "\n5. 层序遍历 (显示颜色):" << std::endl;
    tree.printLevelOrder();
    
    // 测试字符串类型
    std::cout << "\n=== 字符串类型测试 ===" << std::endl;
    RedBlackTree<std::string> strTree;
    strTree.insert("apple");
    strTree.insert("banana");
    strTree.insert("cherry");
    strTree.insert("date");
    
    std::cout << "中序遍历: ";
    strTree.printInOrder();
    
    std::cout << "\n查找 'banana': " << (strTree.search("banana") ? "找到" : "未找到") << std::endl;
    
    return 0;
}

