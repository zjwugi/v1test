#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <queue>

enum Color { RED, BLACK };

template <typename T>
class RedBlackTree {
private:
    struct Node {
        T data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(T val, Color c = RED, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
            : data(val), color(c), parent(p), left(l), right(r) {}
    };

    Node* root;
    Node* nil; // 哨兵节点，表示NIL节点

    // 辅助函数
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void insertFixup(Node* z);
    void deleteFixup(Node* x);
    void transplant(Node* u, Node* v);
    Node* minimum(Node* x);
    Node* maximum(Node* x);
    void destroyTree(Node* node);
    Node* searchNode(Node* node, const T& val) const;
    void printInOrder(Node* node) const;
    void printLevelOrder() const;

public:
    RedBlackTree();
    ~RedBlackTree();
    
    // 基本操作
    void insert(const T& val);
    void remove(const T& val);
    bool search(const T& val) const;
    
    // 遍历
    void printInOrder() const;
    void printLevelOrder() const;
    
    // 工具函数
    bool isEmpty() const;
    T getMin() const;
    T getMax() const;
};

// 构造函数
template <typename T>
RedBlackTree<T>::RedBlackTree() {
    nil = new Node(T(), BLACK);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
    root = nil;
}

// 析构函数
template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    destroyTree(root);
    delete nil;
}

// 销毁树
template <typename T>
void RedBlackTree<T>::destroyTree(Node* node) {
    if (node != nil) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// 左旋
template <typename T>
void RedBlackTree<T>::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    
    if (y->left != nil) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

// 右旋
template <typename T>
void RedBlackTree<T>::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    
    if (y->right != nil) {
        y->right->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y;
}

// 插入节点
template <typename T>
void RedBlackTree<T>::insert(const T& val) {
    Node* z = new Node(val, RED, nil, nil, nil);
    Node* y = nil;
    Node* x = root;
    
    // 找到插入位置
    while (x != nil) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    
    if (y == nil) {
        root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    z->left = nil;
    z->right = nil;
    z->color = RED;
    
    insertFixup(z);
}

// 插入后修复红黑树性质
template <typename T>
void RedBlackTree<T>::insertFixup(Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            
            if (y->color == RED) {
                // Case 1: 叔叔节点是红色
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2: z是右子节点
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3: z是左子节点
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            // 对称情况
            Node* y = z->parent->parent->left;
            
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// 查找最小节点
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::minimum(Node* x) {
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

// 查找最大节点
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::maximum(Node* x) {
    while (x->right != nil) {
        x = x->right;
    }
    return x;
}

// 替换节点
template <typename T>
void RedBlackTree<T>::transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// 删除节点
template <typename T>
void RedBlackTree<T>::remove(const T& val) {
    Node* z = searchNode(root, val);
    if (z == nil) {
        return; // 节点不存在
    }
    
    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;
    
    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    
    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }
    
    delete z;
}

// 删除后修复红黑树性质
template <typename T>
void RedBlackTree<T>::deleteFixup(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            
            if (w->color == RED) {
                // Case 1: 兄弟节点是红色
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // Case 2: 兄弟节点的两个子节点都是黑色
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // Case 3: 兄弟节点的右子节点是黑色
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // Case 4: 兄弟节点的右子节点是红色
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            // 对称情况
            Node* w = x->parent->left;
            
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// 查找节点
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::searchNode(Node* node, const T& val) const {
    if (node == nil || node->data == val) {
        return node;
    }
    
    if (val < node->data) {
        return searchNode(node->left, val);
    } else {
        return searchNode(node->right, val);
    }
}

// 查找
template <typename T>
bool RedBlackTree<T>::search(const T& val) const {
    return searchNode(root, val) != nil;
}

// 中序遍历
template <typename T>
void RedBlackTree<T>::printInOrder(Node* node) const {
    if (node != nil) {
        printInOrder(node->left);
        std::cout << node->data << " ";
        printInOrder(node->right);
    }
}

template <typename T>
void RedBlackTree<T>::printInOrder() const {
    printInOrder(root);
    std::cout << std::endl;
}

// 层序遍历
template <typename T>
void RedBlackTree<T>::printLevelOrder() const {
    if (root == nil) {
        std::cout << "树为空" << std::endl;
        return;
    }
    
    std::queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        
        std::cout << node->data << "(" << (node->color == RED ? "红" : "黑") << ") ";
        
        if (node->left != nil) {
            q.push(node->left);
        }
        if (node->right != nil) {
            q.push(node->right);
        }
    }
    std::cout << std::endl;
}

// 判断是否为空
template <typename T>
bool RedBlackTree<T>::isEmpty() const {
    return root == nil;
}

// 获取最小值
template <typename T>
T RedBlackTree<T>::getMin() const {
    if (root == nil) {
        throw std::runtime_error("树为空");
    }
    return minimum(root)->data;
}

// 获取最大值
template <typename T>
T RedBlackTree<T>::getMax() const {
    if (root == nil) {
        throw std::runtime_error("树为空");
    }
    return maximum(root)->data;
}

#endif // RED_BLACK_TREE_H

