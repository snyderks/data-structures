//
// Created by Kristian Snyder on 3/27/17.
//

#ifndef LAB10_NODE_H
#define LAB10_NODE_H

#include <vector>

template <class T>
class Node {
public:
    std::vector<T*> items;
    std::vector<Node<T>*> children;
    int MaxKeys;
    int MaxChildren;
    int Keys;
    int ChildNodes;

    /// \brief Constructor takes a maximum number of items per node.
    Node(int maxItems);

    ~Node();

    int FindChildrenIndex(T* item);

    bool IsLeaf();

    void AppendKey(T* item);

    void InsertKey(T *item);

    void AppendChild(Node* item);

    void InsertChild(Node<T>* item, int pos);

    void ReplaceChild(Node<T>* item, int pos);

    T* RemoveKeyFromLeaf(T* item);

    int FindKey(T* key);
};

template <class T>
Node<T>::Node(int maxItems) {
    MaxKeys = maxItems - 1;
    MaxChildren = maxItems;
    Keys = 0;
    ChildNodes = 0;
    items = std::vector<T*>();
    children = std::vector<Node<T>*>();
}

template <class T>
Node<T>::~Node() {
}

template <class T>
int Node<T>::FindChildrenIndex(T *item) {
    int i = 0;
    while (i < Keys && *item > *items.at(i)) {
        i++;
    }
    return i;
}

template <class T>
bool Node<T>::IsLeaf() {
    return children.size() <= 0;
}

template <class T>
void Node<T>::AppendKey(T *item) {
    if (Keys < MaxKeys && item != nullptr) {
        items.push_back(item);
        Keys++;
    } else if (Keys >= MaxKeys) {
        throw;
    }
}

template <class T>
void Node<T>::InsertKey(T *item) {
    items.insert(items.begin()+FindChildrenIndex(item), item);
    Keys++;
}

template <class T>
void Node<T>::InsertChild(Node<T>* item, int pos) {
    children.insert(children.begin()+pos, item);
    ChildNodes++;
}

template <class T>
void Node<T>::ReplaceChild(Node<T> *item, int pos) {
    // erase first so the vector destroys that item
    children.erase(children.begin() + pos);
    children.insert(children.begin()+pos, item);
}

template <class T>
void Node<T>::AppendChild(Node *item) {
    if (ChildNodes < MaxChildren && item != nullptr) {
        children.push_back(item);
        ChildNodes++;
    } else if (ChildNodes >= MaxChildren) {
        throw;
    }
}

template <class T>
T* Node<T>::RemoveKeyFromLeaf(T* key) {
    for (int i = 0; i < Keys; i++) {
        if (*items.at(i) == *key) {
            T *temp = items.at(i);
            // collapse the keys
            for (int j = i; j < Keys; j++) {
                items.at(j) = items.at(j + 1);
            }
            items.pop_back();
            Keys--;
            return temp;
        }
    }
    return nullptr;
}

template <class T>
int Node<T>::FindKey(T* key) {
    for (int i = 0; i < Keys; i++) {
        if (*items.at(i) == *key) {
            return i;
        }
    }
    return Keys;
}


#endif //LAB10_NODE_H
