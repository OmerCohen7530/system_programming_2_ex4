// Omer Cohen
// omer7530@gmail.com

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <stdexcept>
#include <typeinfo>
#include <iostream>

template <typename T>
class Node {
private:
    T value;
    std::vector<Node<T>*> children;

public:
    explicit Node(T val): value(val) {}

    void add_child(Node<T>* child) {
        if (child == nullptr) {
            throw std::runtime_error("Child node is null");
        }
        if (typeid(*child) != typeid(Node<T>)) {
            throw std::runtime_error("Child node type does not match");
        }
        // children.push_back(child);
        children.push_back(new Node<T>(child->get_value()));
    }

    T get_value() const { return value; }
    const std::vector<Node<T>*>& get_children() const { return children; }

    ~Node(){}
};

#endif // NODE_HPP
