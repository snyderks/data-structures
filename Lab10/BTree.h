//
// Created by Kristian Snyder on 3/27/17.
//

#ifndef LAB10_BTREE_H
#define LAB10_BTREE_H

#include <cmath>

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
public:
    BTree(int degree = 3);

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
Split<T> BTree<T>::insertItemHelper(T *item, Node<T>* subtree) {
    // check if it is a leaf
    if (subtree->IsLeaf()) {

        // check if it's full
        if (subtree->Keys < subtree->MaxKeys) {
            // find the place to insert
            auto indexToInsert = subtree->FindChildrenIndex(item);

            if (indexToInsert < subtree->Keys) {
                // make a spot
                for (int i = subtree->Keys; i > indexToInsert; i--) {
                    subtree->items[i] = subtree->items[i - 1];
                    // offset by 1 for the children
                    subtree->children[i + 1] = subtree->children[i];
                }
            }

            // insert in correct place
            subtree->items[indexToInsert] = item;
            subtree->Keys++;

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
        auto childUsed = subtree->FindChildrenIndex(item);
        auto result = insertItemHelper(item, subtree->children[childUsed]);
        // see if we need to split this node
        if (result.rhs != nullptr) {
            // must split if currently full
            if(subtree->Keys == subtree->MaxKeys) {
                auto results = addAndSplit(result.separator, result.lhs, result.rhs,
                                           subtree->FindChildrenIndex(result.separator), subtree);
                // empty the keys and children of the subtree temporarily
                for (int i = 0; i < subtree->MaxKeys; i++) {
                    subtree->items[i] = nullptr;
                    subtree->children[i] = nullptr;
                }
                // still need to empty the last location
                subtree->children[subtree->MaxChildren-1] = nullptr;

                // zero out the counts
                subtree->Keys = 0;
                subtree->ChildNodes = 0;

                // now add the split
                subtree->AppendChild(results.lhs);
                subtree->AppendChild(results.rhs);
                subtree->AppendKey(results.separator);
            } else {
                // no need to split, so make a space for both the new children
                // and the new key
                for (int i = subtree->Keys; i > childUsed; i--) {
                    subtree->items[i] = subtree->items[i - 1];
                    // offset by 1 for the children
                    subtree->children[i + 1] = subtree->children[i];
                }
                subtree->children[childUsed]  = result.lhs;
                subtree->children[childUsed + 1] = result.rhs;
                subtree->items[childUsed] = result.separator;
                // need to increment keys
                subtree->Keys++;
                subtree->ChildNodes++;
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
    T** arr = new T*[subtree->MaxKeys + 1];
    int i = 0;
    int itemsIndex = 0;
    int indexToInsertItem = subtree->FindChildrenIndex(item);
    while (i < subtree->MaxKeys + 1) {
        if (i == indexToInsertItem) {
            arr[i] = item;
        } else {
            arr[i] = subtree->items[itemsIndex];
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
            left->AppendKey(arr[j]);
            left->AppendChild(subtree->children[j]);
        } else if (j > median) {
            right->AppendChild(subtree->children[j]);
            // keys greater than the median go right
            right->AppendKey(arr[j]);
        } else {
            // special case: children with the same index go to the left.
            left->AppendChild(subtree->children[j]);
        }
    }
    // return the nodes to use and the median to put in the parent node
    return Split<T>(left, right, arr[median]);
}

template<class T>
Split<T> BTree<T>::addAndSplit(T *item, Node<T>* left, Node<T>* right, int index, Node<T> *subtree) {
    // make a new array with all the items in it, but with a length 1 larger.
    T** keys = new T*[subtree->MaxKeys + 1];
    // fill the keys with the old array and the new spot.
    int itemsIndex = 0; // the position to add from the subtree
    for (int i = 0; i < subtree->MaxKeys + 1; i++) {
        if (i == index) {
            keys[i] = item;
        } else {
            keys[i] = subtree->items[itemsIndex];
            itemsIndex++;
        }
    }

    // make a new array with all the children in it, but with a length 1 larger.
    Node<T>** children = new Node<T>*[subtree->MaxChildren + 1];
    int childIndex = 0;
    for (int i = 0; i < subtree->MaxChildren + 1; i++) {
        if (i == index) {
            children[i] = left;
            // need to skip the original child there
            childIndex++;
        } else if (i == index + 1) {
            children[i] = right;
        } else {
            children[i] = subtree->children[childIndex];
            childIndex++;
        }
    }

    auto lhs = new Node<T>(subtree->MaxChildren);
    auto rhs = new Node<T>(subtree->MaxChildren);

    int median = subtree->MaxChildren / 2;

    // add elements to the sides
    for (int i = 0; i < subtree->MaxChildren + 1; i++) {
        if (i < median) {
            lhs->AppendKey(keys[i]);
            lhs->AppendChild(children[i]);
        } else if (i > median) {
            rhs->AppendChild(children[i]);
            rhs->AppendKey(keys[i]);
        } else {
            // children with the same index go to the left.
            lhs->AppendChild(children[i]);
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
        printSubtree(subtree->children[i], indentLevel + 2);
        for (int j = 0; j < indentLevel; j++) {
            std::cout << " ";
        }
        std::cout << *subtree->items[i] << std::endl;
    }
    printSubtree(subtree->children[subtree->Keys], indentLevel + 2);
}


#endif //LAB10_BTREE_H
