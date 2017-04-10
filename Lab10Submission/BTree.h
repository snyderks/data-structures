//
// Created by Kristian Snyder on 3/27/17.
//

#ifndef LAB10_BTREE_H
#define LAB10_BTREE_H

#include <cmath>
#include <memory>
#include <vector>
#include <iostream>
#include "Node.h"

template <class T>
class Split {
public:
    Node<T>* lhs;
    Node<T>* rhs;
    T* separator;
    Split(Node<T>* left = nullptr, Node<T>* right = nullptr, T* median = nullptr) {
        lhs = left;
        rhs = right;
        separator = median;
    }

    ~Split() {
        delete lhs;
        lhs = nullptr;
        delete rhs;
        rhs = nullptr;
        delete separator;
        separator = nullptr;
    }

    Split<T>& operator=(const Split<T> &right) {
        if (right.lhs != this->lhs && right.rhs != this->rhs &&
            right.separator != this->separator) {
            if (right.lhs != nullptr) {
                this->lhs = new Node<T>(*right.lhs);
            }
            if (right.rhs != nullptr) {
                this->rhs = new Node<T>(*right.rhs);
            }
            if (right.separator != nullptr) {
                this->separator = new T(*right.separator);
            }
        }
        return *this;
    }
};

template <class T>
class BTree {
private:
    Node<T>* root;
    int totalItems;
    int totalPointerMoves;

    Split<T> insertItemHelper(T* item, Node<T>* subtree);
    Split<T> splitList(T* item, Node<T>* subtree);
    Split<T> addAndSplit(T *item, Node<T>* left, Node<T>* right, int index, Node<T> *subtree);

    T* findItemHelper(T* item, Node<T>* subtree);

    void printSubtree(Node<T> *subtree, int indentLevel);
    void printIndent(int indentLevel);

    int treeHeightHelper(Node<T> *subtree);
public:
    BTree(int degree = 3);
    ~BTree();

    /// \brief InsertItem adds an item to the BTree in the correct position.
    void InsertItem(T* item);

    /// \brief FindItem returns a pointer to the item in the tree matching the argument.
    /// The tree is not modified.
    T* FindItem(T* item);

    /// \brief PrintTree prints the contents of the tree.
    void PrintTree();

    /// \brief Returns the maximum height of the tree. Does not modify the tree.
    int GetTreeHeight();

    /// \brief Returns the total size of the tree. Does not traverse the tree.
    int GetTreeSize();

    /// \brief Retrieve the amount of pointer moves made since the last call. Resets the counter.
    int GetMoves();
};

template <class T>
BTree<T>::BTree(int degree) {
    root = new Node<T>(degree);
    totalItems = 0;
}

template <class T>
BTree<T>::~BTree() {
    delete root;
    root = nullptr;
}

template <class T>
Split<T> BTree<T>::insertItemHelper(T *item, Node<T>* subtree) {
    // check if it is a leaf
    if (subtree->IsLeaf()) {

        // check if it's full
        if (subtree->Keys < subtree->MaxKeys) {
            // insert in correct place
            subtree->InsertKey(item);

            // no split necessary, so return empty split
            return Split<T>();

        } else if (subtree == root) {
            int size = subtree->MaxChildren;
            // can't recurse if it's the root, so have to split the tree
            Split<T> result = splitList(item, subtree);
            delete root;
            root = nullptr;
            subtree = nullptr;

            root = new Node<T>(size);

            // separator is now only element in the root
            root->AppendKey(result.separator);
            // entire left side becomes new branch
            root->AppendChild(result.lhs);
            // entire right side becomes new branch
            root->AppendChild(result.rhs);

        } else {
            // split the list into two and give it to the caller
            Split<T> tmp = splitList(item, subtree);
            return tmp;
        }
    } else {
        // recurse until we reach a leaf
        int childUsed = subtree->FindChildrenIndex(item);
        Split<T> result;
        if (subtree->ChildNodes > childUsed) {
            // increment number of moves
            totalPointerMoves++;
            result = insertItemHelper(item, subtree->children.at(childUsed));
        }

        // see if we need to split this node
        if (result.rhs != nullptr) {
            // must split if currently full
            if(subtree->Keys >= subtree->MaxKeys) {
                Split<T> addAndSplitResults = addAndSplit(result.separator, result.lhs, result.rhs,
                                           subtree->FindChildrenIndex(result.separator), subtree);

                subtree->DeleteContents();

                // now add the split
                // entire left side becomes new branch
                subtree->AppendChild(addAndSplitResults.lhs);

                // entire right side becomes new branch
                subtree->AppendChild(addAndSplitResults.rhs);

                subtree->AppendKey(addAndSplitResults.separator);
            } else {
                // no need to split
                subtree->ReplaceChild(result.lhs, childUsed);
                subtree->InsertChild(result.rhs, childUsed + 1);
                subtree->InsertKey(result.separator);

                return Split<T>();
            }
        }
    }
    return Split<T>();
}

template <class T>
void BTree<T>::InsertItem(T *item) {
    // increment number of moves
    totalPointerMoves++;
    insertItemHelper(item, root);
    totalItems++;
}

template <class T>
Split<T> BTree<T>::splitList(T *item, Node<T> *subtree) {
    // make a new array with all the items in it
    std::vector<T*> arr = std::vector<T*>();
    int i = 0;
    int itemsIndex = 0;
    int indexToInsertItem = subtree->FindChildrenIndex(item);

    while (i < subtree->MaxKeys + 1) {
        if (i == indexToInsertItem) {
            arr.push_back(new T(*item));
        } else {
            arr.push_back(new T(*subtree->items.at(itemsIndex)));
            itemsIndex++;
        }
        i++;
    }

    // split
    int median = (subtree->MaxKeys + 1) / 2;

    Node<T>* left = new Node<T>(subtree->MaxChildren);
    Node<T>* right = new Node<T>(subtree->MaxChildren);

    // divide the node
    for (int j = 0; j < subtree->MaxKeys + 1; j++) {
        // if on the left of the median
        if (j < median) {
            // append the keys and children to that node
            left->AppendKey(arr.at(j));
        } else if (j > median) {
            // keys greater than the median go right
            right->AppendKey(arr.at(j));
        }
    }

    // match up the children with the keys on the correct side
    for (int j = 0; j < subtree->ChildNodes; j++) {
        if (j < median) {
            left->AppendChild(subtree->children.at(j));
        } else if (j > median) {
            right->AppendChild(subtree->children.at(j));
        } else {
            // special case: children with the same index go to the left.
            left->AppendChild(subtree->children.at(j));
        }
    }

    T* ret = new T(*arr.at(median));

    for (int j = 0; j < arr.size(); j++) {
        delete arr.at(j);
        arr.at(j) = nullptr;
    }

    // return the nodes to use and the median to put in the parent node
    return Split<T>(left, right, ret);
}

template<class T>
Split<T> BTree<T>::addAndSplit(T *item, Node<T>* left, Node<T>* right, int index, Node<T> *subtree) {
    // make a new array with all the children in it, but with a length 1 larger.
    std::vector<Node<T>*>children = std::vector<Node<T>*>();
    int childIndex = 0;
    for (int i = 0; i < subtree->MaxChildren + 1; i++) {
        if (i == index) {
            children.push_back(new Node<T>(*left));
            // need to skip the original child there
            childIndex++;
        } else if (i == index + 1) {
            children.push_back(new Node<T>(*right));
        } else {
            if (childIndex < subtree->ChildNodes) {
                children.push_back(new Node<T>(*subtree->children.at(childIndex)));
            }
            childIndex++;
        }
    }

    // make a new array with all the items in it
    std::vector<T*> keys = std::vector<T*>();
    // fill the keys with the old array and the new spot.
    int itemsIndex = 0; // the position to add from the subtree
    for (int i = 0; i < subtree->MaxKeys + 1; i++) {
        if (i == index) {
            keys.push_back(new T(*item));
        } else {
            keys.push_back(new T(*subtree->items.at(itemsIndex)));
            itemsIndex++;
        }
    }

    Node<T>* lhs = new Node<T>(subtree->MaxChildren);
    Node<T>* rhs = new Node<T>(subtree->MaxChildren);

    int median = subtree->MaxChildren / 2;

    // add elements to the sides
    for (int i = 0; i < subtree->MaxChildren; i++) {
        if (i < median) {
            lhs->AppendKey(keys.at(i));
        } else if (i > median) {
            rhs->AppendKey(keys.at(i));
        }
    }

    // move children to correct spots
    for (int i = 0; i < subtree->MaxChildren + 1; i++) {
        if (i < median) {
            lhs->AppendChild(children.at(i));
        } else if (i > median) {
            rhs->AppendChild(children.at(i));
        } else {
            // children with the same index go to the left.
            lhs->AppendChild(children.at(i));
        }
    }

    for (int i = 0; i < children.size(); i++) {
        delete children.at(i);
        children.at(i) = nullptr;
    }

    // copy for returning
    T* separator = new T(*keys.at(median));

    for (int i = 0; i < keys.size(); i++) {
        delete keys.at(i);
        keys.at(i) = nullptr;
    }

    return Split<T>(lhs, rhs, separator);
}

template<class T>
void BTree<T>::PrintTree() {
    printSubtree(root, 0);
    std::cout << std::endl;
}

template<class T>
void BTree<T>::printIndent(int indentLevel) {
    for (int j = 0; j < indentLevel; j++) {
        if (j % 2 == 0) {
            std::cout << "|";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "| ";
}

template<class T>
void BTree<T>::printSubtree(Node<T> *subtree, int indentLevel) {
    if (subtree == nullptr) {
        return;
    }
    printIndent(indentLevel);
    std::cout << "---------------------" << std::endl;

    // before everything, print the indent
    printIndent(indentLevel);

    // no indent is only at beginning
    if (indentLevel == 0) {
        std::cout << "Root node:" << std::endl;
    } else if (subtree->ChildNodes == 0) {
        std::cout << "Leaf node:" << std::endl;
    } else {
        std::cout << "Intermediate node:" << std::endl;
    }

    // print the keys of the node
    printIndent(indentLevel);
    std::cout << "Keys:" << std::endl;
    for (int i = 0; i < subtree->Keys; i++) {
        printIndent(indentLevel);
        std::cout << *subtree->items.at(i) << std::endl;
    }

    printIndent(indentLevel);
    if (subtree->ChildNodes == 0) {
        std::cout << "No children";
    } else {
        std::cout << "Children:";
    }
    std::cout << std::endl;
    // print each of the children of the node
    for (int i = 0; i < subtree->ChildNodes; i++) {
        printSubtree(subtree->children.at(i), indentLevel + 2);
    }

    printIndent(indentLevel);
    std::cout << "---------------------" << std::endl;
}

template<class T>
T* BTree<T>::FindItem(T *item) {
    // increment number of moves
    totalPointerMoves++;
    return findItemHelper(item, root);
}

template<class T>
T* BTree<T>::findItemHelper(T *item, Node<T> *subtree) {
    if (subtree == nullptr) {
        return nullptr;
    }
    int i = 0;
    for (; i < subtree->Keys; i++) {
        if (*item == *subtree->items.at(i)) {
            return subtree->items.at(i);
        } else if (*item < *subtree->items.at(i)) {
            break;
        }
    }
    if (i < subtree->ChildNodes) {
        // increment number of moves
        totalPointerMoves++;
        return findItemHelper(item, subtree->children.at(i));
    } else {
        return nullptr;
    }
}

template<class T>
int BTree<T>::GetTreeHeight() {
    if (root->Keys > 0) {
        return treeHeightHelper(root);
    } else {
        return 0;
    }
}

template<class T>
int BTree<T>::treeHeightHelper(Node<T> *subtree) {
    if (subtree->ChildNodes == 0) {
        return 1;
    } else {
        // get max heights for each and then return the highest
        // (+1 to include current node)
        int maxHeight = 0;
        for (int i = 0; i < subtree->ChildNodes; i++) {
            int h = treeHeightHelper(subtree->children.at(i));
            if (h > maxHeight) {
                maxHeight = h;
            }
        }
        return maxHeight + 1;
    }
}

template<class T>
int BTree<T>::GetTreeSize() {
    return totalItems;
}

template<class T>
int BTree<T>::GetMoves() {
    int temp = totalPointerMoves;
    totalPointerMoves = 0;
    return temp;
}


#endif //LAB10_BTREE_H