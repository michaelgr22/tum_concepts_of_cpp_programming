#pragma once

#include <cstddef>
#include <memory>

namespace binary_tree {
class Tree
{
public:
    enum class Traversal
    {
        PREORDER,
        INORDER,
        POSTORDER
    };

    class Node
    {
        friend class Tree;

    public:
        explicit Node(int v) : data(v)
        {
        }

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&& other) = delete; // move constructor
        Node& operator=(Node&& other) = delete; // move assignment

    private:
        int data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    /// do a pre/in/post-order traversal of the tree and print each node
    /// @param traversal the type of traversal
    void traverse(Traversal traversal) const;

    /// Create a new Node for the value and insert it into the existing tree
    /// @param value the new value
    /// @return a reference to the inserted Node
    Node& insert(int value);

    /// Insert the new node into the existing tree (and take over the ownership)
    /// In other words: it is the Trees responsibility to call delete on that node
    /// @param node a new node (without any children)
    /// @return a reference to the inserted Node
    Node& insert(Node* node);

    /// Remove the node from the tree and replace it with the smallest tree
    /// node from the right subtree if the right subtree isn't empty, otherwise
    /// take the root from the left subtree as a replacement
    /// @param value the value/node to be removed
    /// @throws an exception in case of a non-existing element
    void remove(int value);

    /// find a value
    /// @throws an exception in case of a non-existing element
    const Node& find(int value) const;

    /// create a new tree, that is mirrored

    /// create a mirrored version of the current tree
    /// The returned tree of course does no longer fullfill the sorting properties according to the binary search tree
    /// (smaller values to the left, larger ones to the right).
    //  This shouldn't be a concern, as the mirrored tree is only ever used for determining its size and traversing it
    /// - no further find, insert or remove calls are going to follow.
    /// @return the newly created tree
    Tree mirror() const;

    /// Compute the number of elements currently in the tree
    /// @return number of elements
    std::size_t size() const;

    Tree() = default;

private:
    std::unique_ptr<Node> root;

    int countNodes(Node* root) const;
};
} // namespace binary_tree