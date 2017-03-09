//
// Created by Kristian Snyder on 3/6/17.
//

#ifndef LAB08_ORDEREDLINKEDLIST_H
#define LAB08_ORDEREDLINKEDLIST_H

#include <iostream>

class Node;

template <class T>
class OrderedLinkedList {
private:
    template<class U>
    class Node {
    public:
        U* data;
        Node* next;
        /// \brief constructor
        /// \param nextNode
        /// \param nodeData
        Node(U* nodeData, Node* nextNode = nullptr) {
            data = nodeData;
            next = nextNode;
        };

        bool operator< (U &rhs) const {
            return rhs > *data;
        };

        bool operator> (U &rhs) const {
            return !(*this < rhs);
        };

        bool operator== (U &rhs) const {
            return *data = rhs;
        }

        bool operator!= (U &rhs) const {
            return !(*this == rhs);
        }
    };

    Node<T>* head;
    int length;

    /// \brief get the end of the list
    /// \returns pointer to end of the list
    Node<T>* tail();

public:
    class NotFoundException {};

    OrderedLinkedList();

    /// \brief initialize the list with a given item
    /// \param item
    OrderedLinkedList(T* item);

    /// \brief add an item to the list
    /// \param item
    void AddItem(T* item);

    /// \brief get an item from the list
    /// \param item
    /// \returns item in the list if it exists, otherwise nullptr.
    T* GetItem(T* item);

    /// \brief determine if the list is empty
    /// \returns whether the list is empty
    bool IsEmpty();

    /// \brief print the contents of the list
    void PrintList();

};

template<class T>
OrderedLinkedList<T>::Node<T>* OrderedLinkedList<T>::tail() {
    // tail is null if the list is empty
    if (head == nullptr) {
        return head;
    }
    Node<T>* next = head;
    while (next->next != nullptr) {
        next = next->next;
    }
    return next;
}

template<class T>
OrderedLinkedList<T>::OrderedLinkedList() {
    length = 0;
}

template<class T>
OrderedLinkedList<T>::OrderedLinkedList(T* item) {
    head = new Node<T>(item);
    length = 1;
}

template<class T>
void OrderedLinkedList<T>::PrintList() {
    Node<T>* next = head;
    while (next != nullptr) {
        std::cout << *next->data << std::endl;
        next = next->next;
    }
}

template<class T>
void OrderedLinkedList<T>::AddItem(T* item) {
    Node<T>* node = new Node<T>(item);
    if (head == nullptr) {
        head = node;
    } else if (*head > *item) {
        node->next = head;
        head = node;
    } else {
        Node<T>* next = head;
        while (next->next != nullptr && *next->next < *item) {
            next = next->next;
        }
        node->next = next->next;
        next->next = node;
    }
    length++;
}

template<class T>
T* OrderedLinkedList<T>::GetItem(T* item) {
    if (IsEmpty()) {
        return nullptr;
    } else {
        Node<T>* next = head;
        Node<T>* retval;
        // always keep the pointer one space behind the item we're looking for
        while (next->next != nullptr && *next->next != *item) {
            next = next->next;
        }
        if (next == head) {
            // shift head up one space
            head = next->next;
            retval = next;
            retval->next = nullptr;

            length--;
            return retval->data;

        } else if (next->next == nullptr) {
            // didn't find it
            return nullptr;
        } else {
            // next value is the one we want
            // take the node before it and point it to
            // the node after the one we want
            retval = next->next;
            next->next = next->next->next;
            retval->next = nullptr;
            length--;

            return retval;
        }
    }
}

template<class T>
bool OrderedLinkedList<T>::IsEmpty() {
    return length == 0;
}


#endif //LAB08_ORDEREDLINKEDLIST_H

//i.	Constructor
//        ii.	AddItem – adds an item from the list
//iii.	GetItem – searches the list for the given item.  If found, it removes it from the list and returns it.  If not found, it returns a null pointer.
//iv.	IsInlist – returns a bool indicating if the given item is in the list.
//v.	IsEmpty – returns a bool indicating if the list is empty.
//vi.	Size – returns an int indicating the number of items in the list.
//vii.	SeeNext – returns the item without removing it from the list at a given location in the list.  The class will maintain the next location and will start at the first item in the list.  When it gets to the last item in the list, it will return a null pointer after it gets past the last item.  If the list is empty, this will throw an error.  2 calls to SeeNext will return the 2 items next to each other in the list unless SeeAt or Reset is called in between the 2 calls (or the first call returns the last item in the list).
//viii.	SeeAt – Finds an item at a location in the list (int passed in from user), and returns the item without removing it.  If the location passed by the user is past the end of the list, this will throw an error.  This will set the location used by SeeNext to point at the item after the item returned.
//ix.	Reset – resets the location that the SeeNext function uses to point at the first item in the list.
//x.	Destructor
//        b.	All items passed to or from the class should be done so via a pointer rather than by value.
//c.	Make sure you don’t have any memory leaks.
