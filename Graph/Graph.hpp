/*
Generic directed graph which implements BFS and DFS
Author: Andrew Burger
*/

#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <string>

template<typename Data>
struct GraphNode {

    GraphNode() = default;

    explicit GraphNode(size_t id) : id_{id} {}

    GraphNode(size_t id, std::shared_ptr<Data> data) :
        id_{id}, data_{data} {}

    GraphNode(size_t id, std::shared_ptr<Data> data,
        std::vector<size_t> adjacent) :
        id_{id}, data_{data}, adjacent_{adjacent}
        {}

    size_t id_{};
    std::shared_ptr<Data> data_{nullptr};
    std::vector<size_t> adjacent_{};
};

template<typename Data>
class Graph {

    public:

    Graph<Data>() = default;
    ~Graph<Data>() = default;

    Graph<Data>(std::string name);

    void create_node(size_t id, std::shared_ptr<Data> data);

    // Add edge from v to w: v->w
    void add_edge(size_t v, size_t w);

    // Using DFS algorithm print out all ids
    void depth_first_search(size_t id);

    // Using BFS algorithm print out all ids
    void breadth_first_search(size_t id);

    private:
        std::string name_{};
        std::map<size_t, std::shared_ptr<GraphNode<Data>>> nodes_{};
        std::map<size_t, bool> visited_{};
};

template<typename Data>
Graph<Data>::Graph(std::string name) :
    name_{std::move(name)} {}

template<typename Data>
void Graph<Data>::create_node(size_t id, std::shared_ptr<Data> data) {

    auto p_new_node = std::make_shared<GraphNode<Data>>(id, data);
    nodes_.insert(std::pair<size_t,std::shared_ptr<GraphNode<Data>>>(id, p_new_node));
    visited_.insert(std::pair<size_t, bool>(id, false));

    std::cout << id << " Node created in the graph" << std::endl;
}

template<typename Data>
void Graph<Data>::add_edge(size_t v, size_t w) {

        assert(nodes_.contains(v) && nodes_.contains(w));

        auto node_1 = nodes_.at(v);
        auto node_2 = nodes_.at(w);

        node_1->adjacent_.push_back(w);
        std::cout << w << " Added to " << v << " adjacency list" << std::endl;
}

template<typename Data>
void Graph<Data>::depth_first_search(size_t id) {

    assert(nodes_.contains(id));

    auto node = nodes_.at(id);
    auto adjacent_list = node->adjacent_;

    visited_.at(id) = true;

    std::cout << "Visiting node " << id << std::endl;

    for (auto &adjacent_node : adjacent_list) {

        if(!visited_.at(adjacent_node)) {
            depth_first_search(adjacent_node);
        }
    }
}

template<typename Data>
void Graph<Data>::breadth_first_search(size_t id) {

}