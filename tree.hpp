// Omer Cohen
// omer7530@gmail.com

#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <typeinfo>
#include <stdexcept>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>

using namespace std;

int pngs_counter = 1; // Counter for the PNG files

template <typename T, int K = 2>
class Tree {
private:
    Node<T>* root;
    size_t max_children;

    // delete all nodes in the tree
    void delete_all_nodes(Node<T>* node) 
    {
        if (node == nullptr) 
        {
            return;
        }
        for (Node<T>* child : node->get_children()) 
        {
            delete_all_nodes(child);
        }
        delete node;
    }

    // Find a node in the tree
    Node<T>* find_node(Node<T>* node, const Node<T>& target) 
    {
        if (node == nullptr) 
        {
            return nullptr;
        }

        // By Binjamin we can assume that the value is unique
        if (node->get_value() == target.get_value()) 
        {
            return node;
        }

        for (Node<T>* child : node->get_children()) 
        {
            Node<T>* temp = find_node(child, target);
            if (temp != nullptr) 
            {
                return temp;
            }
        }
        return nullptr;
    }

    // Generate and open PNG file
    static void generate_and_open_png(const Tree<T, K>& tree, const std::string& dot_filename, const std::string& png_filename) 
    {
        // יצירת קובץ DOT
        std::ofstream file(dot_filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing" << std::endl;
            return;
        }

        // הגדרת צבע רקע לגרף
        file << "digraph G {" << std::endl;
        file << "    bgcolor=\"gray\";" << std::endl; // צבע רקע אפור #########

        // הוספת טקסט בפינה השמאלית העליונה
        file << "    label = \"Omer Cohen\\n\nTree " + to_string(pngs_counter) + " \";" << std::endl; // הוספת טקסט #########
        file << "    labelloc = \"t\";" << std::endl; // מיקום הטקסט #########
        file << "    labeljust = \"l\";" << std::endl; // יישור לשמאל #########


        std::function<void(Node<T>*, std::ofstream&)> write_node = [&](Node<T>* node, std::ofstream& file) 
        {
            if (!node) return;
            for (auto child : node->get_children()) {
                // הוספת צבע לצמתים, לקווים ולטקסט
                file << "    \"" << node->get_value() << "\" [color=black, style=filled, fillcolor=orange, fontcolor=black];" << std::endl;  // צבע צמתים #########
                file << "    \"" << child->get_value() << "\" [color=black, style=filled, fillcolor=orange, fontcolor=black];" << std::endl; // צבע צמתים #########
                file << "    \"" << node->get_value() << "\" -> \"" << child->get_value() << "\" [color=black];" << std::endl; // צבע קווים #########
                write_node(child, file);
            }
        };

        write_node(tree.get_root(), file);
        file << "}" << std::endl;

        file.close();
        std::cout << "DOT file generated successfully." << std::endl;

        // המרת קובץ DOT ל-PNG
        std::string command = "dot -Tpng " + dot_filename + " -o " + png_filename;
        std::cout << "Running command: " << command << std::endl;
        int result = system(command.c_str());
        if (result != 0) {
            std::cerr << "Failed to generate PNG. Command returned: " << result << std::endl;
            return;
        }

        std::cout << "PNG file generated successfully." << std::endl;
    }

    // // Genery tree if k > 2
    // bool is_binary_tree(int t) 
    // {
    //     return t == 2;
    // }
public:
    // Constructor
    explicit Tree(): root(nullptr), max_children(K){}

    // Destructor
    ~Tree()
    {
        if (root != nullptr) 
        {
            delete_all_nodes(root);
        }
    }

    // Add root node
    void add_root(Node<T>& node) {
        if (root != nullptr) {
            throw std::runtime_error("Root node already exists");
        }
        if (typeid(node) != typeid(Node<T>)) {
            throw std::runtime_error("Node type does not match tree type");
        }
        // root = &node;
        root = new Node<T>(node.get_value());
    }

    // Add child node
    void add_sub_node(Node<T>& parent, Node<T>& child) 
    {
        if (root == nullptr) 
        {
            throw std::runtime_error("Add root node first");
        }
        if (typeid(parent) != typeid(Node<T>) || typeid(child) != typeid(Node<T>)) 
        {
            throw std::runtime_error("Parent or child node type does not match");
        }

        Node<T>* ParentNode = find_node(root, parent);
        if (ParentNode == nullptr) 
        {
            throw std::runtime_error("Parent node does not exist in the tree");
        }
        if ((*ParentNode).get_children().size() >= max_children) 
        {
            throw std::runtime_error("Parent node children size exceeds the limit");
        }
        ParentNode->add_child(&child);
    }

    // Getters
    Node<T>* get_root() const { return root; }
    size_t get_max_children() const { return max_children; }

    // Pre-order iterator
    class PreOrderIterator {
    private:
        stack<Node<T>*> nodeStack;
    public:
        explicit PreOrderIterator(Node<T>* root) 
        {
            if (root != nullptr) {
                nodeStack.push(root);
            }
        }

        Node<T>* operator*() const 
        {
            return nodeStack.top();
        }

        // operator for -> operator
        Node<T>* operator->() const 
        {
            return nodeStack.top();
        }

        PreOrderIterator& operator++() 
        {
            Node<T>* node = nodeStack.top();
            nodeStack.pop();
            for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) {
                nodeStack.push(*it);
            }
            return *this;
        }

        bool operator!=(const PreOrderIterator& other) const 
        {
            return !nodeStack.empty();
        }
    };

    // Post-order iterator
    class PostOrderIterator {
    private:
        std::stack<Node<T>*> nodeStack;
        std::stack<Node<T>*> visited;
        bool is_binary;

            void push_leftmost(Node<T>* node) 
            {
                while (node) 
                {
                    nodeStack.push(node);
                    if (!node->get_children().empty()) 
                    {
                        node = node->get_children().front();
                    } 
                    else 
                    {
                        node = nullptr;
                    }
                }
            }

    public:
        explicit PostOrderIterator(Node<T>* root, bool is_binary): is_binary(is_binary)
        {
            if (root != nullptr) 
            {
                if (is_binary)
                {
                    push_leftmost(root);
                }
                else
                {
                    nodeStack.push(root);
                }
                
            }
        }

        Node<T>* operator*() const 
        {
            return nodeStack.top();
        }

        Node<T>* operator->() const 
        {
            return nodeStack.top();
        }

        PostOrderIterator& operator++() 
        {
            if (is_binary)
            {
                if (!nodeStack.empty()) {
                    Node<T>* currentNode = nodeStack.top();
                    nodeStack.pop();
                    visited.push(currentNode);

                    if (!nodeStack.empty()) 
                    {
                        Node<T>* parentNode = nodeStack.top();
                        auto childIterator = std::find(parentNode->get_children().begin(), parentNode->get_children().end(), currentNode);
                        if (childIterator != parentNode->get_children().end() && ++childIterator != parentNode->get_children().end()) 
                        {
                            push_leftmost(*childIterator);
                        }
                    }
                }
            }
            else
            {
                Node<T>* node = nodeStack.top();
                nodeStack.pop();
                for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) 
                {
                    if (*it != nullptr)
                    {
                        nodeStack.push(*it);
                    }
                }
                
            }
            return *this;
        }

        bool operator!=(const PostOrderIterator& other) const 
        {
            return !nodeStack.empty();
        }
    };

    // In-order iterator
    class InOrderIterator {
    private:
        stack<Node<T>*> nodeStack;
        Node<T>* current;
        bool is_binary;

        void push_left_InOrder(Node<T> *node)
        {
            while (node != nullptr)
            {
                nodeStack.push(node);
                if (node->get_children().size() > 0)
                    node = node->get_children()[0];
                else
                    break;
            }
        }
    public:
        explicit InOrderIterator(Node<T>* root, bool is_binary): is_binary(is_binary)
        {
            current = root;
            if (root) {
                if (is_binary)
                {
                    push_left_InOrder(root);
                }
                else
                {
                    nodeStack.push(root);
                }
            }
        }

        Node<T>* operator*() const 
        {
            return nodeStack.top();
        }

        Node<T>* operator->() const 
        {
            return nodeStack.top();
        }

        InOrderIterator& operator++() 
        {
            if(is_binary){
                if (!nodeStack.empty())
                {
                    Node<T> *node = nodeStack.top();
                    nodeStack.pop();
                    if (node->get_children().size() > 1 && node->get_children()[1] != nullptr)
                    {
                        push_left_InOrder(node->get_children()[1]);
                    }
                }
            }
            else
            {
                Node<T>* node = nodeStack.top();
                nodeStack.pop();
                for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) 
                {
                    if (*it != nullptr)
                    {
                        nodeStack.push(*it);
                    }
                }
            }
            return *this;
        }

        bool operator!=(const InOrderIterator& other) const 
        {
            return !nodeStack.empty();
        }
    };

    // BFS iterator
    class BFSIterator {
    private:
        queue<Node<T>*> nodeQueue;
    public:
        explicit BFSIterator(Node<T>* root) 
        {
            if (root != nullptr) 
            {
                nodeQueue.push(root);
            }
        }

        Node<T>& operator*() const 
        {
            return *nodeQueue.front();
        }

        Node<T>* operator->() const 
        {
            return nodeQueue.front();
        }

        BFSIterator& operator++() 
        {
            Node<T>* node = nodeQueue.front();
            nodeQueue.pop();
            for (Node<T>* child : node->get_children()) 
            {
                nodeQueue.push(child);
            }
            return *this;
        }

        bool operator!=(const BFSIterator& other) const 
        {
            return !nodeQueue.empty();
        }
    };

    // DFS iterator
    class DFSIterator {
    private:
        stack<Node<T>*> nodeStack;
    public:
        explicit DFSIterator(Node<T>* root) 
        {
            if (root != nullptr) 
            {
                nodeStack.push(root);
            }
        }

        Node<T>* operator*() const 
        {
            return nodeStack.top();
        }

        Node<T>* operator->() const 
        {
            return nodeStack.top();
        }

        DFSIterator& operator++() 
        {
            Node<T>* node = nodeStack.top();
            nodeStack.pop();
            for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) 
            {
                if (*it != nullptr)
                {
                    nodeStack.push(*it);
                }
            }
            return *this;
        }

        bool operator!=(const DFSIterator& other) const 
        {
            return !nodeStack.empty();
        }
    };

    // Heap iterator
    class HeapIterator {
    private:
        vector<Node<T>*> nodeHeap;

        void collect_nodes(Node<T> *node)
        {
            if (node != nullptr)
            {
                nodeHeap.push_back(node);
                for (auto child : node->get_children())
                {
                    collect_nodes(child);
                }
            }
        }
    public:
        explicit HeapIterator(Node<T>* root) 
        {
            if (root != nullptr) 
            {
                collect_nodes(root);
                auto compare = [](Node<T>* lhs, Node<T>* rhs) { return lhs->get_value() > rhs->get_value(); };
                std::make_heap(nodeHeap.begin(), nodeHeap.end(), compare);
            }
        }

        Node<T>& operator*() const 
        {
            return *nodeHeap.front();
        }

        Node<T>* operator->() const 
        {
            return nodeHeap.front();
        }

        HeapIterator& operator++() 
        {
            auto compare = [](Node<T>* lhs, Node<T>* rhs) { return lhs->get_value() > rhs->get_value(); };
            std::pop_heap(nodeHeap.begin(), nodeHeap.end(), compare);
            nodeHeap.pop_back();
            return *this;
        }

        bool operator!=(const HeapIterator& other) const 
        {
            return !nodeHeap.empty();
        }
    };




    // Begin and end functions for the iterators

    PreOrderIterator begin_pre_order() 
    {
        return PreOrderIterator(root);
    }
    
    PreOrderIterator end_pre_order() 
    {
        return PreOrderIterator(nullptr);
    }

    PostOrderIterator begin_post_order() 
    {
        return PostOrderIterator(root, K == 2);
    }
    
    PostOrderIterator end_post_order() 
    {
        return PostOrderIterator(nullptr, K == 2);
    }

    InOrderIterator begin_in_order() 
    {
        return InOrderIterator(root, K == 2);
    }

    InOrderIterator end_in_order() 
    {
        return InOrderIterator(nullptr, K == 2);
    }

    BFSIterator begin_bfs_scan() 
    {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() 
    {
        return BFSIterator(nullptr);
    }

    DFSIterator begin_dfs_scan() 
    {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() 
    {
        return DFSIterator(nullptr);
    }

    BFSIterator begin() {
        return BFSIterator(root);
    }

    BFSIterator end() {
        return BFSIterator(nullptr);
    }

    HeapIterator myHeap() 
    {
        if (K == 2)
        {
            return HeapIterator(root);
        }
        else
        {
            throw std::runtime_error("Heap iterator is only for binary trees");
        }
    }

    HeapIterator end_heap() 
    {
        if (K == 2)
        {
            return HeapIterator(nullptr);
        }
        else
        {
            throw std::runtime_error("Heap iterator is only for binary trees");
        }
    }


    friend std::ostream& operator<<(std::ostream& os, const Tree<T, K>& tree) {
        cout << "############################################" << endl;

        string dot = "tree_" + to_string(pngs_counter) + ".dot";
        string png = "tree_" + to_string(pngs_counter) + ".png";
        Tree<T, K>::generate_and_open_png(tree, dot, png);
        pngs_counter++;

        cout << "############################################" << endl;
        return os;
    }
};

#endif // TREE_HPP
