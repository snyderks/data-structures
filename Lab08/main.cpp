#include <iostream>

#include "OrderedLinkedList.h"

int main() {
    int* i = new int(5);
    OrderedLinkedList<int>* list = new OrderedLinkedList<int>(i);

    list->AddItem(new int(4));

    list->AddItem(new int(6));

    list->AddItem(new int(3));

    std::cout << list->GetItem(new int(4));

    list->PrintList();


    return 0;
}