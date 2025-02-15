#include "binary-tree.hpp"
#include <cstddef>
#include <memory>
#include <print>

using binary_tree::Tree;

int Tree::countNodes(Node* root) const
{
    if (root == nullptr) {
        return 0;
    }
    return 1 + countNodes(root->left.get()) + countNodes(root->right.get());
}

std::size_t Tree::size() const
{
    return countNodes(root.get());
}

Tree::Node& Tree::insert(int value)
{
    if (!root) {
        root = std::make_unique<Node>(value);
        return *root;
    }

    Node* current = root.get();
    Node* next = nullptr;

    while (true) {
        if (value < current->data) {
            next = current->left.get();
            if (!next) {
                current->left = std::make_unique<Node>(value);
                return *current->left;
            }
            current = current->left.get();
        } else {
            next = current->right.get();
            if (!next) {
                current->right = std::make_unique<Node>(value);
                return *current->right;
            }
            current = current->right.get();
        }
    };
}

Tree::Node& Tree::insert(Node* node)
{
    std::unique_ptr<Node> new_node(node);

    if (!root) {
        root = std::move(new_node);
        return *root;
    }

    Node* current = root.get();
    Node* next = nullptr;

    while (true) {
        if (new_node->data < current->data) {
            next = current->left.get();
            if (!next) {
                current->left = std::make_unique<Node>(new_node->data);
                return *current->left;
            }
            current = current->left.get();
        } else {
            next = current->right.get();
            if (!next) {
                current->right = std::make_unique<Node>(new_node->data);
                return *current->right;
            }
            current = current->right.get();
        }
    };
}

Tree Tree::mirror() const
{
    Tree mirroredTree;

    struct MirrorHelper
    {
        static std::unique_ptr<Node> mirrorNode(const std::unique_ptr<Node>& node)
        {
            if (!node) return nullptr;

            auto newNode = std::make_unique<Node>(node->data);
            newNode->left = mirrorNode(node->right);
            newNode->right = mirrorNode(node->left);

            return newNode;
        }
    };

    mirroredTree.root = MirrorHelper::mirrorNode(root);
    return mirroredTree;
}

void Tree::traverse(Traversal traversal) const
{
    /*if (root && root->left && root->right) {
        std::println("Root Left {}", root->left->data);
        std::println("Root Right {}", root->right->data);
    }*/
    struct TraversalHelper
    {
        static void traverseNode(const std::unique_ptr<Node>& node, Traversal traversal)
        {
            if (!node) return;

            if (traversal == Traversal::PREORDER) {
                std::print("({})", node->data);
                traverseNode(node->left, traversal);
                traverseNode(node->right, traversal);
            } else if (traversal == Traversal::INORDER) {
                traverseNode(node->left, traversal);
                std::print("({})", node->data);
                traverseNode(node->right, traversal);
            } else if (traversal == Traversal::POSTORDER) {
                traverseNode(node->left, traversal);
                traverseNode(node->right, traversal);
                std::print("({})", node->data);
            }
        }
    };

    TraversalHelper::traverseNode(root, traversal);
}

const Tree::Node& Tree::find(int value) const
{
    if (!root) {
        throw std::runtime_error("unable to find element");
    }
    if (root->data == value) {
        return *root;
    }
    Node* current = root.get();

    while (true) {
        if (value == current->data) {
            return *current;
        }
        if (value < current->data) {
            current = current->left.get();
        } else {
            current = current->right.get();
        }
        if (!current) {
            throw std::runtime_error("unable to find element");
        }
    };
}

void Tree::remove(int value)
{
    if (!root) {
        throw std::runtime_error("unable to remove element");
    }

    Node* current = root.get();
    Node* parent = nullptr;
    bool right = false;

    while (current && current->data != value) {
        parent = current;
        if (value < current->data) {
            current = current->left.get();
            right = false;
        } else {
            current = current->right.get();
            right = true;
        }
    }

    if (!current) {
        throw std::runtime_error("unable to remove element");
    }

    // Case 1: Node has no children (leaf node)
    if (!current->left && !current->right) {
        if (!parent) { // If removing root
            root.reset();
        } else if (right) {
            parent->right.reset();
        } else {
            parent->left.reset();
        }
    }
    // Case 2: Node has only a right child
    else if (!current->left) {
        if (!parent) {
            root = std::move(current->right);
        } else if (right) {
            parent->right = std::move(current->right);
        } else {
            parent->left = std::move(current->right);
        }
    }
    // Case 3: Node has only a left child
    else if (!current->right) {
        if (!parent) {
            root = std::move(current->left);
        } else if (right) {
            parent->right = std::move(current->left);
        } else {
            parent->left = std::move(current->left);
        }
    }
    // Case 4: Node has both left and right children
    else {
        Node* successorParent = current;
        Node* successor = current->right.get();

        while (successor->left) {
            successorParent = successor;
            successor = successor->left.get();
        }

        current->data = successor->data; // Replace value

        // Remove the in-order successor node
        if (successorParent->left.get() == successor) {
            successorParent->left = std::move(successor->right);
        } else {
            successorParent->right = std::move(successor->right);
        }
    }
}
