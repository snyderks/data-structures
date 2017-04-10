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

    Node(const Node<T> &node);

    ~Node();

    void DeleteContents();

    int FindChildrenIndex(T* item);

    bool IsLeaf();

    void AppendKey(T* item);

    void InsertKey(T *item);

    void AppendChild(Node<T>* item);

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
Node<T>::Node(const Node<T> &node) {
    MaxKeys = node.MaxKeys;
    MaxChildren = node.MaxChildren;
    Keys = node.Keys;
    ChildNodes = node.ChildNodes;

    items.resize(node.items.size());

    for (int i = 0; i < node.items.size(); i++) {
        items.at(i) = new T(*node.items.at(i));
    }

    children.resize(node.children.size());

    for (int i = 0; i < node.children.size(); i++) {
        children.at(i) = new Node<T>(*node.children.at(i));
    }
}

template <class T>
Node<T>::~Node() {
    DeleteContents();
}

template <class T>
void Node<T>::DeleteContents() {
    for (int i = 0; i < items.size(); i++){
        delete items.at(i);
        items.at(i) = nullptr;
    }
    items.clear();
    for (int i = 0; i < children.size(); i++){
        delete children.at(i);
        children.at(i) = nullptr;
    }
    children.clear();

    Keys = 0;
    ChildNodes = 0;
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
        items.push_back(new T(*item));
        Keys++;
    } else if (Keys >= MaxKeys) {
        throw;
    }
}

template <class T>
void Node<T>::InsertKey(T *item) {
    items.insert(items.begin()+FindChildrenIndex(item), new T(*item));
    Keys++;
}

template <class T>
void Node<T>::InsertChild(Node<T>* item, int pos) {
    children.insert(children.begin()+pos, new Node<T>(*item));
    ChildNodes++;
}

template <class T>
void Node<T>::ReplaceChild(Node<T> *item, int pos) {
    // erase first so the vector destroys that item
    children.erase(children.begin() + pos);
    children.insert(children.begin()+pos, new Node<T>(*item));
}

template <class T>
void Node<T>::AppendChild(Node<T> *item) {
    if (ChildNodes < MaxChildren && item != nullptr) {
        children.push_back(new Node<T>(*item));
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
