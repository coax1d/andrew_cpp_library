#include "Graph.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

int main(void) {

    auto m_graph = Graph<std::string>("Strings");

    m_graph.create_node(0, std::make_shared<std::string>("Melissa"));
    m_graph.create_node(1, std::make_shared<std::string>("Andrew"));
    m_graph.create_node(2, std::make_shared<std::string>("Michael"));
    m_graph.create_node(3, std::make_shared<std::string>("David"));
    m_graph.create_node(9, std::make_shared<std::string>("Sam"));

    m_graph.add_edge(0, 1);
    m_graph.add_edge(0, 9);
    m_graph.add_edge(1, 2);
    m_graph.add_edge(2, 0);
    m_graph.add_edge(2, 3);
    m_graph.add_edge(9, 3);

    std::cout << "Depth first search results:" << std::endl;
    m_graph.depth_first_search(2);

    m_graph.clear_visited();

    std::cout << "Breadth first search results:" << std::endl;
    m_graph.breadth_first_search(2);

    return 0;
}