//
// Created by Kristian Snyder on 3/27/17.
//

#ifndef LAB10_NODE_H
#define LAB10_NODE_H

template <class T>
class Node {
public:
    T** items;
    Node** children;
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

    void AppendChild(Node* item);

    T* RemoveKeyFromLeaf(T* item);

    int FindKey(T* key);
};

template <class T>
Node<T>::Node(int maxItems) {
    MaxKeys = maxItems - 1;
    MaxChildren = maxItems;
    Keys = 0;
    ChildNodes = 0;
    items = new T*[MaxKeys];
    for (int i = 0; i < MaxKeys; i++) {
        items[i] = nullptr;
    }
    children = new Node<T>*[MaxChildren];
    for (int i = 0; i < MaxChildren; i++) {
        children[i] = nullptr;
    }
}

template <class T>
Node<T>::~Node() {
    delete items;
    items = nullptr;
}

template <class T>
int Node<T>::FindChildrenIndex(T *item) {
    int i = 0;
    while (i < Keys && *item > *items[i]) {
        i++;
    }
    return i;
}

template <class T>
bool Node<T>::IsLeaf() {
    for (int i = 0; i < Keys + 1; i++) {
        if (children[i] != nullptr) {
            return false;
        }
    }
    return true;
}

template <class T>
void Node<T>::AppendKey(T *item) {
    if (Keys < MaxKeys && item != nullptr) {
        items[Keys] = item;
        Keys++;
    } else if (Keys >= MaxKeys) {
        throw;
    }
}

template <class T>
void Node<T>::AppendChild(Node *item) {
    if (ChildNodes < MaxChildren && item != nullptr) {
        children[ChildNodes] = item;
        ChildNodes++;
    } else if (ChildNodes >= MaxChildren) {
        throw;
    }
}

template <class T>
T* Node<T>::RemoveKeyFromLeaf(T* key) {
    for (int i = 0; i < Keys; i++) {
        if (*items[i] == *key) {
            T *temp = items[i];
            // collapse the keys
            for (int j = i; j < Keys; j++) {
                items[j] = items[j + 1];
            }
            Keys--;
            return temp;
        }
    }
    return nullptr;
}

template <class T>
int Node<T>::FindKey(T* key) {
    for (int i = 0; i < Keys; i++) {
        if (*items[i] == *key) {
            return i;
        }
    }
    return Keys;
}


#endif //LAB10_NODE_H
