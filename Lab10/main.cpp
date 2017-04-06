#include <iostream>
#include "Node.h"
#include "BTree.h"

int main() {
    auto tree = new BTree<int>();

    tree->InsertItem(new int(3));
    tree->InsertItem(new int(1));
    tree->InsertItem(new int(4));
    tree->InsertItem(new int(10));
    tree->InsertItem(new int(5));
    tree->InsertItem(new int(6));
    tree->InsertItem(new int(2));
    tree->InsertItem(new int(12));
    tree->InsertItem(new int(8));
    tree->InsertItem(new int(9));

    tree->RemoveItem(new int(12));
    tree->RemoveItem(new int(1));

    tree->PrintTree();

    return 0;
}