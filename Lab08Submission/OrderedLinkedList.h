//
// Created by Kristian Snyder
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

        ~Node() {
            delete data;
            data = nullptr;
            delete next;
            next = nullptr;
        }

        bool operator< (U &rhs) const {
            return rhs > *data;
        };

        bool operator> (U &rhs) const {
            return !(*this < rhs);
        };

        bool operator== (U &rhs) const {
            return *data == rhs;
        }

        bool operator!= (U &rhs) const {
            return !(*this == rhs);
        }
    };

    Node<T>* head;
    int length;

    /// Node used for tracking SeeNext
    Node<T>* current;
    bool atBeginning;

    /// \brief get the end of the list
    /// \returns pointer to end of the list
    Node<T>* tail();

public:
    class NotFoundException {};
    class EmptyListException {};
    class IndexException {};

    OrderedLinkedList();
    ~OrderedLinkedList();

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

    /// \brief get the next item after the previously returned item in the list
    /// Memorizes its state, so multiple calls will result in different results.
    /// State is altered if the next item to be returned is removed.
    /// \returns the next item in the list
    /// \throws EmptyListException
    T* SeeNext();

    /// \brief return the item at that index without removal
    /// Also sets next item returned to SeeNext to the item after the index returned.
    /// \param index
    /// \returns item at that index
    /// \throws IndexException
    T* SeeAt(int index);

    /// \brief returns next item to be returned by SeeNext() to the beginning
    /// of the list.
    void Reset();

    /// \brief determine if an item is in the list
    /// \param item
    /// \returns if the item is in the list
    bool IsInList(T* item);

    /// \brief determine if the list is empty
    /// \returns whether the list is empty
    bool IsEmpty();

    /// \brief get the length of the list
    /// \returns the length of the list
    int Size();

    /// \brief print the contents of the list
    void PrintList();

};

/// Private functions
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

/// Public functions
template<class T>
OrderedLinkedList<T>::OrderedLinkedList() {
    length = 0;
    head = nullptr;
    current = head;
    atBeginning = true;
}

template<class T>
OrderedLinkedList<T>::~OrderedLinkedList() {
    delete head;
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
            // we have to change the next item to return from
            // SeeNext, since it now points to something no longer
            // in the list. Choosing to shift right by 1.
            if (current != nullptr && current == head) {
                current = next->next;
            }
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
            // we have to change the next item to return from
            // SeeNext, since it now points to something no longer
            // in the list. Choosing to shift right by 1.
            if (current != nullptr && current == retval) {
                 current = next->next->next;
            }
            next->next = next->next->next;
            retval->next = nullptr;
            length--;

            return retval->data;
        }
    }
}

template<class T>
T* OrderedLinkedList<T>::SeeNext() {
    if (IsEmpty()) {
        throw EmptyListException();
    } else if (current == nullptr && !atBeginning) {
        return nullptr;
    } else {
        if (atBeginning) {
            current = head;
            atBeginning = false;
        }
        T* data = current->data;
        current = current->next;
        return data;
    }
}

template<class T>
T* OrderedLinkedList<T>::SeeAt(int index) {
    if (index >= length) {
        throw IndexException();
    } else {
        int i = 0;
        Node<T>* retval = head;
        while (i < index) {
            retval = retval->next;
            i++;
        }
        // set next value to return from SeeNext()
        current = retval->next;
        return retval->data;
    }
}

template<class T>
void OrderedLinkedList<T>::Reset() {
    atBeginning = true;
    current = head;
}

template<class T>
bool OrderedLinkedList<T>::IsInList(T* item) {
    if (IsEmpty()) {
        return false;
    } else {
        Node<T>* node = head;
        // return true as soon as we find it
        while (node != nullptr) {
            if (*node->data == *item) {
                return true;
            }
            node = node->next;
        }
        // didn't find it
        return false;
    }
}

template<class T>
int OrderedLinkedList<T>::Size() {
    return length;
}

template<class T>
bool OrderedLinkedList<T>::IsEmpty() {
    return length == 0;
}


#endif //LAB08_ORDEREDLINKEDLIST_H
