//
// Created by Kristian Snyder on 3/27/17.
//

#ifndef LAB10_BTREE_H
#define LAB10_BTREE_H

#include <cmath>
#include <memory>
#include <vector>

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
};

template <class T>
class BTree {
private:
    Node<T>* root;
    Split<T> insertItemHelper(T* item, Node<T>* subtree);
    Split<T> splitList(T* item, Node<T>* subtree);
    Split<T> addAndSplit(T *item, Node<T>* left, Node<T>* right, int index, Node<T> *subtree);

    T* removeItemHelper(T* item, Node<T>* subtree);

    void printSubtree(Node<T> *subtree, int indentLevel);

    void emptyTreeHelper(Node<T>* subtree);
public:
    BTree(int degree = 3);
    ~BTree();

    /// \brief InsertItem adds an item to the BTree in the correct position.
    void InsertItem(T* item);

    T* RemoveItem(T* item);

    /// \brief PrintTree prints the contents of the tree.
    void PrintTree();
};

template <class T>
BTree<T>::BTree(int degree) {
    root = new Node<T>(degree);
}

template <class T>
BTree<T>::~BTree() {
    emptyTreeHelper(root);
    delete root;
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
            // can't recurse if it's the root, so have to split the tree
            auto result = splitList(item, subtree);
            root = new Node<T>(subtree->MaxChildren);

            // separator is now only element in the root
            root->AppendKey(result.separator);
            // entire left side becomes new branch
            root->AppendChild(result.lhs);
            // entire right side becomes new branch
            root->AppendChild(result.rhs);

        } else {
            // split the list into two and give it to the caller
            return splitList(item, subtree);
        }
    } else {
        // recurse until we reach a leaf
        int childUsed = subtree->FindChildrenIndex(item);
        Split<T> result = Split<T>();
        if (subtree->ChildNodes > childUsed) {
            result = insertItemHelper(item, subtree->children.at(childUsed));
        }
        // see if we need to split this node
        if (result.rhs != nullptr) {
            // must split if currently full
            if(subtree->Keys >= subtree->MaxKeys) {
                auto results = addAndSplit(result.separator, result.lhs, result.rhs,
                                           subtree->FindChildrenIndex(result.separator), subtree);
                // empty the keys and children of the subtree temporarily
                subtree->items.clear();
                subtree->children.clear();

                // zero out the counts
                subtree->Keys = 0;
                subtree->ChildNodes = 0;

                // now add the split
                subtree->AppendChild(results.lhs);
                subtree->AppendChild(results.rhs);
                subtree->AppendKey(results.separator);
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
    insertItemHelper(item, root);
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
            arr.push_back(item);
        } else {
            arr.push_back(subtree->items.at(itemsIndex));
            itemsIndex++;
        }
        i++;
    }

    // split
    int median = (subtree->MaxKeys + 1) / 2;

    auto left = new Node<T>(subtree->MaxChildren);
    auto right = new Node<T>(subtree->MaxChildren);

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
    // return the nodes to use and the median to put in the parent node
    return Split<T>(left, right, arr.at(median));
}

template<class T>
Split<T> BTree<T>::addAndSplit(T *item, Node<T>* left, Node<T>* right, int index, Node<T> *subtree) {
    // make a new array with all the items in it
    std::vector<T*> keys = std::vector<T*>();
    // fill the keys with the old array and the new spot.
    int itemsIndex = 0; // the position to add from the subtree
    for (int i = 0; i < subtree->MaxKeys + 1; i++) {
        if (i == index) {
            keys.push_back(item);
        } else {
            keys.push_back(subtree->items.at(itemsIndex));
            itemsIndex++;
        }
    }

    // make a new array with all the children in it, but with a length 1 larger.
    std::vector<Node<T>*>children = std::vector<Node<T>*>();
    int childIndex = 0;
    for (int i = 0; i < subtree->MaxChildren + 1; i++) {
        if (i == index) {
            children.push_back(left);
            // need to skip the original child there
            childIndex++;
        } else if (i == index + 1) {
            children.push_back(right);
        } else {
            children.push_back(subtree->children.at(childIndex));
            childIndex++;
        }
    }

    auto lhs = new Node<T>(subtree->MaxChildren);
    auto rhs = new Node<T>(subtree->MaxChildren);

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
    for (int i = 0; i < subtree->ChildNodes; i++) {
        if (i < median) {
            lhs->AppendChild(children.at(i));
        } else if (i > median) {
            rhs->AppendChild(children.at(i));
        } else {
            // children with the same index go to the left.
            lhs->AppendChild(children.at(i));
        }
    }

    return Split<T>(lhs, rhs, keys[median]);
}

template<class T>
T* BTree<T>::removeItemHelper(T *item, Node<T> *subtree) {
    if (subtree->IsLeaf()) {
        // handle removing the item
        return subtree->RemoveKeyFromLeaf(item);
    } else {
        // need to see if we have it
        int index = subtree->FindKey(item);
        if (index != subtree->Keys) {

        } else {
            // keep moving down the tree
            return removeItemHelper(item,
                     subtree->children[subtree->FindChildrenIndex(item)]);
        }
    }
    return nullptr;
}

template<class T>
T* BTree<T>::RemoveItem(T *item) {
    return removeItemHelper(item, root);
}


template<class T>
void BTree<T>::PrintTree() {
    printSubtree(root, 0);
    std::cout << std::endl;
}

template<class T>
void BTree<T>::printSubtree(Node<T> *subtree, int indentLevel) {
    if (subtree == nullptr) {
        return;
    }
    for (int i = 0; i < subtree->Keys; i++) {
        if (i < subtree->ChildNodes) {
            printSubtree(subtree->children.at(i), indentLevel + 2);
        }
        for (int j = 0; j < indentLevel; j++) {
            std::cout << " ";
        }
        std::cout << *subtree->items.at(i) << std::endl;
    }
    if (subtree->Keys < subtree->ChildNodes) {
        printSubtree(subtree->children.at(subtree->Keys), indentLevel + 2);
    }
}

template<class T>
void BTree<T>::emptyTreeHelper(Node<T>* subtree) {
    for (int i = 0; i < subtree->Keys; i++) {
        delete subtree->items[i];
        subtree->items[i] = nullptr;
    }

    for (int i = 0; i < subtree->ChildNodes; i++) {
        emptyTreeHelper(subtree->children[i]);
        delete subtree->children[i];
        subtree->children[i] = nullptr;
    }
}


#endif //LAB10_BTREE_H
