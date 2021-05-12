/*  Binary Tree Implementation
    Author: Andrew Burger */

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

template<typename T, typename U>
struct TreeNode {

    TreeNode<T, U>() = default;

    TreeNode<T,U> (U id,
                   std::shared_ptr<T> data,
                   std::shared_ptr<T> left,
                   std::shared_ptr<T> right)
        : id_{id},
          data_{data},
          left_{left},
          right_{right}
        {}

    U id_{};
    std::shared_ptr<T> data_;
    std::shared_ptr<T> left_;
    std::shared_ptr<T> right_;
};

template<typename T, typename U>
class BinaryTree {

    public:
        BinaryTree<T, U>();
        ~BinaryTree<T, U>();

        explicit BinaryTree<T, U>(std::vector<U> &array);

        std::shared_ptr<TreeNode<T, U>>
        array_to_bst(std::vector<U> &array, int start, int end);

        void add_node(U id, T *data);
        TreeNode<T, U> find_node();
        void delete_node(U id);
        void replace_node(U id, U new_id, T *data);
        void balance_tree();

    private:
        size_t depth_{};
        std::shared_ptr<TreeNode<T, U>> root_;
};

template<typename T, typename U>
BinaryTree<T, U>::BinaryTree() :
    root_{std::make_shared<TreeNode<T, U>>},
    depth_{0} {}

template<typename T, typename U>
BinaryTree<T, U>::BinaryTree(std::vector<U> &array) :
    depth_{0} {

    // std::cout << "array[1] is " << temp_array[1] << std::endl;

    root_ = array_to_bst(array, 0, array.size() - 1);
}

template<typename T, typename U>
std::shared_ptr<TreeNode<T, U>>
BinaryTree<T, U>::array_to_bst(std::vector<U> &array, int start, int end) {

    if (start > end) {
        return nullptr;
    }

    auto mid = (start + end) / 2;

    auto root = std::make_shared<TreeNode<T, U>>(array[mid]);

    std::cout << root->id_ << " was put into the tree" << std::endl;

    root->left_ = array_to_bst(array, start, mid - 1);
    root->right_ = array_to_bst(array, mid + 1, end);

    return root;
}
