### Omer Cohen
### omer7530@gmail.com
##
# Tree Data Structure and Traversal Iterators

## Overview

This project involves developing a versatile tree data structure in C++ that can handle various node types and offers multiple traversal methods. The tree can support multiple child nodes per node and includes iterators for pre-order, post-order, in-order, depth-first search (DFS), and breadth-first search (BFS) traversals. For non-binary trees, pre-order, post-order, and in-order traversals are substituted with DFS traversal.

## File Descriptions

- `Node.hpp`: Defines and implements the `Node` class.
- `Tree.hpp`: Defines and implements the `Tree` class and its associated iterators.
- `complex.hpp`: Defines and implements the `Complex` class used for testing purposes.
- `main.cpp`: Contains the main function to showcase and test the tree functionalities.
- `test.cpp`: Includes various test cases to verify the tree functionalities.
- `makefile`: Provides the makefile for compiling the project and running tests.

## Node Class

The `Node` class represents a node within the tree. Each node contains a value and a collection of child nodes.

### Key Functions

- `Node(T val)`: Constructor to initialize a node with a specific value.
- `~Node()`: Destructor to clean up the node and its children.
- `void add_child(Node<T>* child)`: Adds a child node to the current node.
- `T get_value() const`: Returns the value stored in the node.

## Tree Class

The `Tree` class represents the tree structure. It supports adding nodes, clearing the tree, and generating DOT files for visualization purposes.

### Key Functions

- `Tree()`: Constructor to initialize an empty tree.
- `~Tree()`: Destructor to clean up the entire tree.
- `void clear()`: Clears all nodes in the tree.
- `void clear(Node<T>* node)`: Clears a specific node and all its children.
- `void add_root(const Node<T>& node)`: Adds a root node to the tree.
- `Node<T>* get_root() const`: Returns the root node of the tree.
- `void add_sub_node(const Node<T>& parent, const Node<T>& child)`: Adds a child node to a specified parent node.
- `Node<T>* find_node(Node<T>* current, const Node<T>& target)`: Finds a node in the tree using DFS.
- `void to_dot(const std::string& filename) const`: Generates a DOT file representing the tree structure.
- `void to_dot_helper(std::ofstream& file, Node<T>* node) const`: Helper function to create edges between nodes in the DOT file.

## Iterators

### PreOrderIterator

Iterates through the tree in pre-order (current node -> left subtree -> right subtree). This traversal is only supported for binary trees. For non-binary trees, DFS traversal is used instead.

### PostOrderIterator

Iterates through the tree in post-order (left subtree -> right subtree -> current node). This traversal is only supported for binary trees. For non-binary trees, DFS traversal is used instead.

### InOrderIterator

Iterates through the tree in in-order (left subtree -> current node -> right subtree). This traversal is only supported for binary trees. For non-binary trees, DFS traversal is used instead.

### DFSIterator

Iterates through the tree using Depth-First Search (DFS) traversal.

### BFSIterator

Iterates through the tree using Breadth-First Search (BFS) traversal.

### HeapIterator

Iterates through the tree nodes in a heap-like order.

## Assignment Requirements

- Implement a generic tree structure supporting multiple node types.
- Provide various traversal methods: pre-order, post-order, in-order, DFS, and BFS.
- Ensure that pre-order, post-order, and in-order traversals are only applied to binary trees. For non-binary trees, switch to DFS traversal.
- Implement test functions to verify the functionality of the tree and its iterators.

## Generating Tree Visualizations

The `to_dot` function in the `Tree` class enables the creation of a DOT file that represents the tree. This DOT file can be converted to an image using the `dot` command from the Graphviz toolkit.

### Steps to Generate Images

1. After executing the main program, DOT files for each tree will be created (e.g., `tree_int.dot`, `tree_double.dot`, etc.).
2. The `dot` command converts these DOT files to PNG images. This conversion is automatically handled in the code via system calls:
   ```cpp
   system("dot -Tpng tree_int.dot -o tree_int.png");
   system("dot -Tpng tree_double.dot -o tree_double.png");
   system("dot -Tpng tree_string.dot -o tree_string.png");
   system("dot -Tpng tree_complex.dot -o tree_complex.png");
   ```

## Running the Project

1. Compile the project using the makefile:
   ```sh
   make
   ```
   Then, execute the program:
   ```sh
   ./tree
   ```
2. To run the tests, compile using the makefile:
   ```sh
   make test
   ```
