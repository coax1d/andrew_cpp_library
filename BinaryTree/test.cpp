#include "BinaryTree.hpp"
#include <iostream>
#include <string>

int main(void) {


    std::vector<size_t> m_vec = {1,2,3,4,5};

    BinaryTree<char, size_t> my_tree(m_vec);

    return 0;
}