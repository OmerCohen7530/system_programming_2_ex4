// Omer Cohen
// omer7530@gmail.com

// extream tests: 7, 19

#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

bool passed = true;

// Add a node to the tree before adding the root node. exception should be thrown
void test1()
{
    Tree<double> tree; // Binary tree that contains doubles.
    Node<double> n1 = Node(1.2);
    // check for exception
    try 
    {
        tree.add_sub_node(n1, n1);
    } 
    catch (const std::runtime_error& e) {}

    if (tree.get_root() != nullptr)
    {
        cout << "test1 failed" << endl;
        passed = false;
    }
}

// Add a root node to the tree. check if it was added successfully
void test2()
{
    Tree<double> tree; // Binary tree that contains doubles.
    Node<double> root_node = Node(1.1);
    tree.add_root(root_node);
    if (tree.get_root()->get_value() != root_node.get_value())
    {
        cout << "test2 failed" << endl;
        passed = false;
    }
}

// Add second root node to the tree. exception should be thrown
void test3()
{
    Tree<double> tree; // Binary tree that contains doubles.
    Node<double> root_node1 = Node(1.1);
    Node<double> root_node2 = Node(1.2);
    tree.add_root(root_node1);
    // check for exception
    try 
    {
        tree.add_root(root_node2);
    } 
    catch (const std::runtime_error& e) {}

    if (tree.get_root()->get_value() != root_node1.get_value())
    {
        cout << "test3 failed" << endl;
        passed = false;
    }
}

// Add a root node to the tree and add a sub node to the root node. check if the sub node has the same value as the one added
void test4()
{
    Tree<double> tree; // Binary tree that contains doubles.
    Node<double> root_node = Node(1.1);
    Node<double> sub_node = Node(1.2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node);
    if (tree.get_root()->get_children().at(0)->get_value() != sub_node.get_value())
    {
        cout << "test4 failed" << endl;
        passed = false;
    }
}

// Add a sun node with parent that is not in the tree. exception should be thrown
void test5()
{
    Tree<double> tree; // Binary tree that contains doubles.
    Node<double> root_node = Node(1.1);
    Node<double> sub_node = Node(1.2);
    // check for exception
    try 
    {
        tree.add_sub_node(root_node, sub_node);
    } 
    catch (const std::runtime_error& e) {}

    if (tree.get_root() != nullptr)
    {
        cout << "test5 failed" << endl;
        passed = false;
    }
}

// Add a root node to the tree and add a sub node to the root node. add a sub node to the sub node. check if the sub node has the same value as the one added
void test6()
{
    Tree<double> tree; // Binary tree that contains doubles.
    Node<double> root_node = Node(1.1);
    Node<double> sub_node1 = Node(1.2);
    Node<double> sub_node2 = Node(1.3);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node1);
    tree.add_sub_node(sub_node1, sub_node2);
    if (tree.get_root()->get_children().at(0)->get_children().at(0)->get_value() != sub_node2.get_value())
    {
        cout << "test6 failed" << endl;
        passed = false;
    }
}

// Check limit children. defien 3 children and add 4. exception should be thrown
void test7()
{
    Tree<double,3> tree; // Binary tree that contains doubles.
    Node<double> root_node = Node(1.1);
    Node<double> sub_node1 = Node(1.2);
    Node<double> sub_node2 = Node(1.3);
    Node<double> sub_node3 = Node(1.4);
    Node<double> sub_node4 = Node(1.5);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node1);
    tree.add_sub_node(root_node, sub_node2);
    tree.add_sub_node(root_node, sub_node3);
    // check for exception
    try 
    {
        tree.add_sub_node(root_node, sub_node4);
    } 
    catch (const std::runtime_error& e) {}

    if (tree.get_root()->get_children().size() != 3)
    {
        cout << "test7 failed" << endl;
        passed = false;
    }
}

// Check int type. Define tree with int type, check if no exception is thrown
void test8()
{
    Tree<int> tree; // Binary tree that contains ints.
    Node<int> root_node = Node(1);
    Node<int> sub_node = Node(2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node);
}

// Check complex type. Define tree with complex type, check if no exception is thrown
void test9()
{
    Tree<Complex> tree; // Binary tree that contains complex numbers.
    Node<Complex> root_node = Node(Complex(1, 1));
    Node<Complex> sub_node = Node(Complex(2, 2));
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node);
}

// Check string type. Define tree with string type, check if no exception is thrown
void test10()
{
    Tree<string> tree; // Binary tree that contains strings.
    Node<string> root_node = Node<string>("root");
    Node<string> sub_node = Node<string>("sub");
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node);
}

// Check double type. Define tree with double type, check if no exception is thrown
void test11()
{
    Tree<double> tree; // Binary tree that contains doubles.
    Node<double> root_node = Node(1.1);
    Node<double> sub_node = Node(1.2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node);
}

// Check char type. Define tree with char type, check if no exception is thrown
void test12()
{
    Tree<char> tree; // Binary tree that contains chars.
    Node<char> root_node = Node('a');
    Node<char> sub_node = Node('b');
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node);
}

// Check bool type. Define tree with bool type, check if no exception is thrown
void test13()
{
    Tree<bool> tree; // Binary tree that contains bools.
    Node<bool> root_node = Node(true);
    Node<bool> sub_node = Node(false);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, sub_node);
}

// Check PreOrder traversal. Define tree with int type, add nodes and check if the traversal is correct
void test14()
{
    Node<int> root_node = Node(1);
    Tree<int> tree;
    tree.add_root(root_node);
    Node<int> n1 = Node(2);
    Node<int> n2 = Node(3);
    Node<int> n3 = Node(4);
    Node<int> n4 = Node(5);
    Node<int> n5 = Node(6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    vector<int> pre_order = {1, 2, 4, 5, 3, 6};
    int i = 0;

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        if (node->get_value() != pre_order.at(i++))
        {
            cout << "test14 failed" << endl;
            passed = false;
            break;
        }
    } // prints: 1, 2, 3, 4, 5, 6
}

// Check PostOrder traversal. Define tree with int type, add nodes and check if the traversal is correct
void test15()
{
    Node<int> root_node = Node(1);
    Tree<int> tree;
    tree.add_root(root_node);
    Node<int> n1 = Node(2);
    Node<int> n2 = Node(3);
    Node<int> n3 = Node(4);
    Node<int> n4 = Node(5);
    Node<int> n5 = Node(6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    vector<int> post_order = {4, 5, 2, 6, 3, 1};
    int i = 0;

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        if (node->get_value() != post_order.at(i++))
        {
            cout << "test15 failed" << endl;
            passed = false;
            break;
        }
    } // prints: 4, 5, 2, 6, 3, 1
}

// Check InOrder traversal. Define tree with int type, add nodes and check if the traversal is correct
void test16()
{
    Node<int> root_node = Node(1);
    Tree<int> tree;
    tree.add_root(root_node);
    Node<int> n1 = Node(2);
    Node<int> n2 = Node(3);
    Node<int> n3 = Node(4);
    Node<int> n4 = Node(5);
    Node<int> n5 = Node(6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    vector<int> in_order = {4, 2, 5, 1, 6, 3};
    int i = 0;

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        if (node->get_value() != in_order.at(i++))
        {
            cout << "test16 failed" << endl;
            passed = false;
            break;
        }
    } // prints: 4, 2, 5, 1, 6, 3
}

// Check BFS traversal. Define tree with int type, add nodes and check if the traversal is correct
void test17()
{
    Node<int> root_node = Node(1);
    Tree<int> tree;
    tree.add_root(root_node);
    Node<int> n1 = Node(2);
    Node<int> n2 = Node(3);
    Node<int> n3 = Node(4);
    Node<int> n4 = Node(5);
    Node<int> n5 = Node(6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    vector<int> bfs = {1, 2, 3, 4, 5, 6};
    int i = 0;

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        if (node->get_value() != bfs.at(i++))
        {
            cout << "test17 failed" << endl;
            passed = false;
            break;
        }
    } // prints: 1, 2, 3, 4, 5, 6
}

// Check DFS traversal. Define tree with int type, add nodes and check if the traversal is correct
void test18()
{
    Node<int> root_node = Node(1);
    Tree<int> tree;
    tree.add_root(root_node);
    Node<int> n1 = Node(2);
    Node<int> n2 = Node(3);
    Node<int> n3 = Node(4);
    Node<int> n4 = Node(5);
    Node<int> n5 = Node(6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    vector<int> dfs = {1, 2, 4, 5, 3, 6};
    int i = 0;

    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        if (node->get_value() != dfs.at(i++))
        {
            cout << "test18 failed" << endl;
            passed = false;
            break;
        }
    } // prints: 1, 2, 4, 5, 3, 6
}

// 3-ary tree PRE / POST / IN order traversal    =     3-ary tree DFS traversal
void test19()
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

    Tree<double,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    vector<double> dfs_order = {1.1, 1.2, 1.5, 1.3, 1.6, 1.4};
    int i = 0;

    // pre = dfs
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        if (node->get_value() != dfs_order.at(i++))
        {
            cout << "test19 failed" << endl;
            passed = false;
            break;
        }
    }

    i = 0;
    // post = dfs
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        if (node->get_value() != dfs_order.at(i++))
        {
            cout << "test19 failed" << endl;
            passed = false;
            break;
        }
    }

    i = 0;
    // in = dfs
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        if (node->get_value() != dfs_order.at(i++))
        {
            cout << "test19 failed" << endl;
            passed = false;
            break;
        }
    }
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();
    test17();
    test18();

    if (passed)
    {
        cout << "\033[32m******* All tests passed *******\033[0m" << endl;
    }
    else
    {
        cout << "Some tests failed " << endl;
    }

    return 0;
}