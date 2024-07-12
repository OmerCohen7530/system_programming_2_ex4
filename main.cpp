// Omer Cohen
// omer7530@gmail.com

#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

int main()
{

    Node<double> root_node = Node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node(1.2);
    Node<double> n2 = Node(1.3);
    Node<double> n3 = Node(1.4);
    Node<double> n4 = Node(1.5);
    Node<double> n5 = Node(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);


    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    cout << "Pre-order traversal: " << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "-------------------------------------------" << endl;

    cout << "Post-order traversal: " << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "-------------------------------------------" << endl;

    cout << "In-order traversal: " << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << "-------------------------------------------" << endl;

    cout << "BFS traversal: " << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "-------------------------------------------" << endl;

    cout << "DFS traversal: " << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "-------------------------------------------" << endl;

    cout << "Heap: " << endl;
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "-------------------------------------------" << endl;

    for (auto node : tree)
    {
        cout << node.get_value() << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << tree; // Should print the graph using GUI.



    Tree<double,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

     // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
    
    cout << three_ary_tree;


    Node<int> root_node_int = Node(1);
    Tree<int> tree_int; // Binary tree that contains integers.
    tree_int.add_root(root_node_int);
    Node<int> n1_int = Node(2);
    Node<int> n2_int = Node(3);
    Node<int> n3_int = Node(4);
    Node<int> n4_int = Node(5);
    Node<int> n5_int = Node(6);

    tree_int.add_sub_node(root_node_int, n1_int);
    tree_int.add_sub_node(root_node_int, n2_int);
    tree_int.add_sub_node(n1_int, n3_int);
    tree_int.add_sub_node(n1_int, n4_int);
    tree_int.add_sub_node(n2_int, n5_int);

    cout << tree_int;


    // Complex tree type.
    Node<Complex> root_node_complex = Node(Complex(1.1, 2.2));
    Tree<Complex> tree_complex; // Binary tree that contains complex numbers.
    tree_complex.add_root(root_node_complex);
    Node<Complex> n1_complex = Node(Complex(1.2, 2.3));
    Node<Complex> n2_complex = Node(Complex(1.3, 2.4));
    Node<Complex> n3_complex = Node(Complex(1.4, 2.5));
    Node<Complex> n4_complex = Node(Complex(1.5, 2.6));
    Node<Complex> n5_complex = Node(Complex(1.6, 2.7));

    tree_complex.add_sub_node(root_node_complex, n1_complex);
    tree_complex.add_sub_node(root_node_complex, n2_complex);
    tree_complex.add_sub_node(n1_complex, n3_complex);
    tree_complex.add_sub_node(n1_complex, n4_complex);
    tree_complex.add_sub_node(n2_complex, n5_complex);

    cout << tree_complex;


    // string tree type.
    Node<string> root_node_string = Node<string>("root");
    Tree<string, 5> tree_string; // Binary tree that contains strings.
    tree_string.add_root(root_node_string);
    Node<string> n1_string = Node<string>("BRING");
    Node<string> n2_string = Node<string>("THEM");
    Node<string> n3_string = Node<string>("HOME");
    Node<string> n4_string = Node<string>("NOW");
    Node<string> n5_string = Node<string>("!");

    tree_string.add_sub_node(root_node_string, n1_string);
    tree_string.add_sub_node(root_node_string, n2_string);
    tree_string.add_sub_node(root_node_string, n3_string);
    tree_string.add_sub_node(root_node_string, n4_string);
    tree_string.add_sub_node(root_node_string, n5_string);

    cout << tree_string;

    return 0;
}