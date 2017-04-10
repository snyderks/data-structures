//
// Created by Kristian Snyder on 4/10/17.
//

#include "Node.h"
#include <iostream>

Node::Node(int *value) {
    // copy the int into a new unique pointer.
    data = std::make_shared<int>(*value);
}

Node::Node(std::shared_ptr<int> &value) {
    // move the int into data.
    data = value;
}

std::shared_ptr<int> Node::getData() {
    return data;
}

void Node::addSuffix(int *suffix) {
    if (std::find(suffixes.begin(), suffixes.end(), std::make_shared<int>(*suffix))
        == suffixes.end()) {
        suffixes.push_front(std::make_shared<int>(*suffix));
    }
}

void Node::removeSuffix(int *suffix) {
    for (auto i = suffixes.begin(); i != suffixes.end(); ++i) {
        // need to double dereference the iterator to do a value-based comparison
        if (**i == *suffix) {
            suffixes.remove(*i);
            break;
        }
    }
}

void Node::printSuffixes() {
    for (auto i = suffixes.begin(); i != suffixes.end(); ++i) {
        std::cout << **i << std::endl;
    }
}