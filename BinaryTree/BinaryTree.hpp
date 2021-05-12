/*  Binary Tree Implementation
    Author: Andrew Burger */

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

template<typename DataType, typename IdType>
struct TreeNode {

    TreeNode<DataType, IdType>() = default;

    explicit TreeNode<DataType, IdType>(IdType id)
        : id_{id} {}

    TreeNode<DataType, IdType> (IdType id,
                   std::shared_ptr<DataType> data,
                   std::shared_ptr<TreeNode<DataType, IdType>> left,
                   std::shared_ptr<TreeNode<DataType, IdType>> right)
        : id_{id},
          data_{data},
          left_{left},
          right_{right}
        {}

    IdType id_{};
    std::shared_ptr<DataType> data_{nullptr};
    std::shared_ptr<TreeNode<DataType, IdType>> left_{nullptr};
    std::shared_ptr<TreeNode<DataType, IdType>> right_{nullptr};
};

template<typename DataType, typename IdType>
class BinaryTree {

    public:
        BinaryTree<DataType, IdType>();
        ~BinaryTree<DataType, IdType>();

        explicit BinaryTree<DataType, IdType>(std::vector<IdType> &array);

        std::shared_ptr<TreeNode<DataType, IdType>>
        array_to_bst(std::vector<IdType> &array, int start, int end);

        void add_node(IdType id, DataType *data);
        TreeNode<DataType, IdType> find_node();
        void delete_node(IdType id);
        void replace_node(IdType id, IdType new_id, DataType *data);
        void balance_tree();

    private:
        size_t depth_{};
        std::shared_ptr<TreeNode<DataType, IdType>> root_;
};

template<typename DataType, typename IdType>
BinaryTree<DataType, IdType>::BinaryTree() :
    root_{std::make_shared<TreeNode<DataType, IdType>>},
    depth_{0} {}

template<typename DataType, typename IdType>
BinaryTree<DataType, IdType>::BinaryTree(std::vector<IdType> &array) :
    depth_{0} {

    root_ = array_to_bst(array, 0, array.size() - 1);
}

template<typename DataType, typename IdType>
BinaryTree<DataType, IdType>::~BinaryTree() {}

template<typename DataType, typename IdType>
std::shared_ptr<TreeNode<DataType, IdType>>
BinaryTree<DataType, IdType>::array_to_bst(std::vector<IdType> &array, int start, int end) {

    if (start > end) {
        return nullptr;
    }

    auto mid = (start + end) / 2;

    auto root = std::make_shared<TreeNode<DataType, IdType>>(array[mid]);

    std::cout << root->id_ << " was put into the tree" << std::endl;

    root->left_ = array_to_bst(array, start, mid - 1);
    root->right_ = array_to_bst(array, mid + 1, end);

    return root;
}
