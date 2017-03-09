//
// Created by Kristian Snyder on 2/27/17.
//

#ifndef LAB07_ORDEREDLIST_H
#define LAB07_ORDEREDLIST_H

#include <iostream>
using namespace std;

class NotFoundException {};
class EmptyListException {};
class FullListException {};
class IndexException {};

/// \brief OrderedList implements an ordered list for a variety of data types.
/// \tparam T: The underlying data type in the list.
template <class T>
class OrderedList {
protected:
    T** list;
    // the current length of the list and the next open position
    int next;
    // maximum length of the list
    int capacity;
    // the number of operations performed in insertion and deletion
    int operations;
public:

    /// \brief Initialize a list with a defined capacity.
    /// \param maxLen: the capacity of the list
    OrderedList(int maxLen);

    /// \brief Destroy the list. Safely disposes of the contents of the list.
    ~OrderedList();

    ///////////////////////
    /// List manipulation
    ///////////////////////

    /// \brief AddItem adds an item to the correct position in the list
    /// \param item: The item to add to the list.
    /// \throw FullListError ...
    virtual void AddItem(T* item);

    /// \brief RemoveItem removes and returns an item in the list
    /// \param item: The item to return from the list.
    /// \throw NotFoundError ...
    /// \throw EmptyListError
    /// \returns a pointer to an item equal to item, if it exists
    virtual T* RemoveItem(T* item);

    /// \brief RemoveItem removes an item at a position in the list
    /// \param pos: the position to remove from
    /// \throw IndexError ...
    /// \throw EmptyListError ...
    /// \returns The item at pos
    virtual T* RemoveItem(int pos);

    /// \brief TopItem returns the item at the end of the list
    /// \throw EmptyListError ...
    /// \returns The item at the end of the list
    virtual T* TopItem() const;

    /// \brief TopItem returns the item at a position in the list
    /// \param pos: the position to remove from
    /// \throw IndexError ...
    /// \throw EmptyListError ...
    /// \returns The item at pos
    virtual T* ItemAt(int pos) const;

    /// \brief RemoveItem removes an item at a position in the list
    /// \throw IndexError ...
    /// \throw EmptyListError ...
    void MakeEmpty();

    ///////////////////////
    /// Status conditions
    ///////////////////////

    /// \brief Checks if the list is empty
    /// \returns Whether the list is empty
    bool IsEmpty() const;

    /// \brief Checks if the list is full
    /// \returns Whether the list is full
    bool IsFull() const;

    /// \brief Gets the length of the list
    /// \returns Length of the list
    int Length() const;

    /// \brief Compares two lists based on their length first and then the value
    /// of the last element in each list.
    bool operator< (OrderedList<T> &rhs) const;

    /// \brief Compares two lists based on their length first and then the value
    /// of the last element in each list.
    bool operator> (OrderedList<T> &rhs) const;

    /// \brief Compares two lists based on length and whether all values are the same.
    bool operator== (OrderedList<T> &rhs) const;

    /////////////////////////
    /// Operations Checking
    /////////////////////////

    /// \brief Retrieves the number of operations performed since the last reset
    ///        and resets the counter.
    /// \returns Number of operations
    int GetOperationsAndReset();

    /////////////
    /// Display
    /////////////
    void PrintList();
};

template <class T>
OrderedList<T>::OrderedList(int maxLen) {
    capacity = maxLen;
    list = new T*[maxLen];
    for (int i = 0; i < capacity; i++) {
        list[i] = nullptr;
    }
    next = 0;
    operations = 0;
}

template <class T>
OrderedList<T>::~OrderedList() {
    this->MakeEmpty();
}

///////////////////////
/// List manipulation
///////////////////////

template <class T>
void OrderedList<T>::AddItem(T* item) {
    if (IsFull()) {
        // cannot add item to a full list
        throw FullListException();
    } else {
        // walk through the list from the beginning
        // until we find a spot where the item belongs
        // (which could be at the end of the array)
        int i = 0;
        while (i < next && *item > *list[i]) {
            // count this operation
            operations++;
            i++;
        }
        // now shift the array to the right of the
        // correct position right one
        // if this is at the end, the block will be
        // skipped automatically.
        for (int j = next; j > i; j--) {
            // count this operation
            operations++;
            list[j] = list[j-1];
        }
        // increase the length
        next++;
        // and place the item into the correct position
        // (counting it as a move)
        operations++;
        list[i] = item;
    }
}

template <class T>
T* OrderedList<T>::RemoveItem(T* item) {
    if (IsEmpty()) {
        // item cannot be in the list
        throw EmptyListException();
    } else {
        // walk through the list from the beginning
        // until we find the spot where the item is
        // or we hit the end of the array.
        int i = 0;
        while (i < next && *item != *list[i]) {
            // count this operation
            operations++;
            i++;
        }
        if (i == next) {
            // item isn't in the list
            throw NotFoundException();
        } else {
            // store item at the found position
            // (counting this move)
            operations++;
            T* temp = list[i];

            // now shift the list right of the item left
            for (int j = i; j < next-1; j++) {
                // count this operation
                operations++;
                list[j] = list[j+1];
            }

            // reduce the length
            next--;
            // and return the item
            return temp;
        }
    }
}

template <class T>
T* OrderedList<T>::RemoveItem(int pos) {
    if (IsEmpty()) {
        throw EmptyListException();
    } else {
        if (pos >= next) {
            // attempted to retrieve from a position outside the array
            throw IndexException();
        } else {
            // store item at pos
            // (counting it as a move)
            operations++;
            T* temp = list[pos];

            // now shift the list right of the item left
            for (int j = pos; j < next-1; j++) {
                // count this operation
                operations++;
                list[j] = list[j+1];
            }

            // reduce the length
            next--;
            // and return the item
            return temp;
        }
    }
}

template <class T>
T* OrderedList<T>::TopItem() const {
    if (Length() == 0) {
        throw EmptyListException();
    } else {
        return list[next-1];
    }
}

template <class T>
T* OrderedList<T>::ItemAt(int pos) const {
    if (Length() == 0) {
        throw EmptyListException();
    } else if (pos >= next) {
        throw IndexException();
    } else {
        return list[pos];
    }
}

template <class T>
void OrderedList<T>::MakeEmpty() {
    // just set everything to nullptr.
    // the list does not own any of its pointers.
    for (int i = 0; i < next; i++) {
        list[i] = nullptr;
    }
    // set length to 0
    next = 0;
}

///////////////////////
/// Status conditions
///////////////////////

template <class T>
bool OrderedList<T>::IsEmpty() const {
    return next == 0;
}

template <class T>
bool OrderedList<T>::IsFull() const {
    return next == capacity;
}

template <class T>
int OrderedList<T>::Length() const {
    return next;
}

//////////////////////////
/// Operator overloading
//////////////////////////

template <class T>
bool OrderedList<T>::operator< (OrderedList<T> &rhs) const {
    if (Length() < rhs.Length()) {
        return true;
    } else if (Length() > rhs.Length()) {
        return false;
    } else {
        return TopItem() < rhs.TopItem();
    }
}

template <class T>
bool OrderedList<T>::operator> (OrderedList<T> &rhs) const {
    if (Length() > rhs.Length()) {
        return true;
    } else if (Length() < rhs.Length()) {
        return false;
    } else {
        return TopItem() > rhs.TopItem();
    }
}

template <class T>
bool OrderedList<T>::operator== (OrderedList<T> &rhs) const {
    if (Length() == rhs.Length()) {
        for (int i = 0; i < Length(); i++) {
            if (*ItemAt(i) != *rhs.ItemAt(i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

/////////////////////////
/// Operations Checking
/////////////////////////
template <class T>
int OrderedList<T>::GetOperationsAndReset() {
    int temp = operations;
    operations = 0;
    return temp;
}

/////////////
/// Display
/////////////
template <class T>
void OrderedList<T>::PrintList() {
    for (int i = 0; i < next; i++) {
        if (list[i] != nullptr) {
            cout << *list[i];
            if (i != next-1) {
                cout << ", ";
            }
        }
    }
    cout << endl;
}


#endif //LAB07_ORDEREDLIST_H
