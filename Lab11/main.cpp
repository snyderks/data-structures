#include <iostream>
#include <cstdlib>
#include "Node.h"

int main() {
    std::shared_ptr<int> i = std::make_shared<int>(3);
    Node node = Node(i);
    std::cout << "value: " << *node.getData() << std::endl;

    int* j = new int(4);
    node.addSuffix(j);
    delete j;

    j = new int(5);
    node.addSuffix(j);
    delete j;

    node.printSuffixes();
    return 0;
}