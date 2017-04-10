//
// Created by Kristian Snyder on 4/10/17.
//

#ifndef LAB11_NODE_H
#define LAB11_NODE_H

#include <cstdlib>
#include <memory>
#include <forward_list>


class Node {
private:
    std::shared_ptr<int> data;
    std::forward_list<std::shared_ptr<int>> suffixes;

public:
    // create a new node with a value. Copies the value passed.
    Node(int* value);

    // create a new node with a value. Moves the value passed.
    Node(std::shared_ptr<int> &value);

    // retrieve a pointer to the value inside the node.
    std::shared_ptr<int> getData();

    // add a suffix to the node. Does not do a check to see if the node exists.
    void addSuffix(int* suffix);

    // remove a suffix from the node, if it exists.
    void removeSuffix(int* suffix);

    void printSuffixes();
};

#endif //LAB11_NODE_H
