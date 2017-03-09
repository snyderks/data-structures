//
// Created by Kristian Snyder on 2/27/17.
//

#ifndef LAB07_ORDEREDLISTREVERSESEARCH_H
#define LAB07_ORDEREDLISTREVERSESEARCH_H

#include "OrderedList.h"

template <class T>
class OrderedListReverseSearch : public OrderedList<T> {
public:
    /// \brief Initialize a list with a defined capacity.
    /// \param maxLen: the capacity of the list
    OrderedListReverseSearch(int maxLen);

    /// \brief AddItem adds an item to the correct position in the list
    /// \param item: The item to add to the list.
    /// \throw FullListError ...
    void AddItem(T* item);
};

template <class T>
OrderedListReverseSearch<T>::OrderedListReverseSearch(int maxLen) : OrderedList<T>(maxLen) {
    // nothing to do here
}

template <class T>
void OrderedListReverseSearch<T>::AddItem(T *item) {
    if (this->IsFull()) {
        // cannot add item to a full list
        throw FullListException();
    } else if (this->IsEmpty()) {
        // count this insertion
        this->operations++;
        this->next++;
        this->list[0] = item;
    } else {
        // walk through the list from the *end*
        // until we find a spot where the item belongs
        // (which could be at the beginning of the array)
        // make sure to skip over null pointers
        int i = this->next;
        while (i > 0 && *item < *(this->list[i-1])) {
            i--;
        }
        // now shift the array to the right of the
        // correct position right one
        // if this is at the end, the block will be
        // skipped automatically.
        for (int j = this->next; j > i; j--) {
            // count this operation
            this->operations++;
            this->list[j] = this->list[j-1];
        }
        // increase the length
        this->next++;
        // and place the item into the correct position
        // (counting this operation)
        this->operations++;
        this->list[i] = item;
    }
}


#endif //LAB07_ORDEREDLISTREVERSESEARCH_H
