//
// Created by Kristian Snyder on 2/27/17.
//

#ifndef LAB07_ORDEREDLISTOPENSPACES_H
#define LAB07_ORDEREDLISTOPENSPACES_H

#include "OrderedList.h"

template <class T>
class OrderedListOpenSpaces : public OrderedList<T> {
public:
    /// \brief Initialize a list with a defined capacity.
    /// \param maxLen: the capacity of the list
    OrderedListOpenSpaces(int maxLen);

    /// \brief AddItem adds an item to the correct position in the list
    /// \param item: The item to add to the list.
    /// \throw FullListError ...
    void AddItem(T* item);

    /// \brief RemoveItem removes and returns an item in the list
    /// \param item: The item to return from the list.
    /// \throw NotFoundError ...
    /// \throw EmptyListError
    /// \returns a pointer to an item equal to item, if it exists
    T* RemoveItem(T* item);

    /// \brief RemoveItem removes an item at a position in the list
    /// \param pos: the position to remove from
    /// \throw IndexError ...
    /// \throw EmptyListError ...
    /// \returns The item at pos
    T* RemoveItem(int pos);

    /// \brief Determines if the list is full
    /// \returns Whether the list if full
    bool IsFull();
};

template <class T>
OrderedListOpenSpaces<T>::OrderedListOpenSpaces(int maxLen) : OrderedList<T>(maxLen) {
    // nothing to do here
}

template <class T>
void OrderedListOpenSpaces<T>::AddItem(T *item) {
    if (this->IsFull()) {
        // cannot add item to a full list
        throw FullListException();
    } else {
        if (this->IsEmpty()) {
            this->list[0] = item;
            this->operations++;
            this->next++;
        } else {
            // walk through the list from the beginning
            // until we find a spot where the item belongs
            // (which could be at the end of the array)
            int rightItem = 0;

            while (rightItem < this->next && (this->list[rightItem] == nullptr || *item > *(this->list[rightItem]))) {
                // count this check if it's not a nullptr
                if (this->list[rightItem] != nullptr) {
                    this->operations++;
                }
                rightItem++;
            }
            // now find the previous item in the array that is valid
            int leftItem = rightItem > 0 ? rightItem - 1 : 0;

            while (leftItem > 0 && rightItem > 0 && this->list[leftItem] == nullptr) {
                // count this check if it's not a nullptr
                if (this->list[rightItem] != nullptr) {
                    this->operations++;
                }
                leftItem--;
            }

            // check if the place to insert the item is at the end or doesn't have a free space
            if (rightItem - leftItem == 1 || rightItem < this->next - 1) {
                // now determine if we can shift right or left
                // check left side first
                int firstNull = leftItem;
                while (firstNull > -1 && this->list[firstNull] != nullptr) {
                    this->operations++;
                    firstNull--;
                }
                // null must be on right side if this is true
                if (firstNull == -1) {
                    firstNull = rightItem;
                    while (firstNull < this->next && this->list[firstNull] != nullptr) {
                        this->operations++;
                        firstNull++;
                    }
                }
                // at this point, firstNull is the null location to shift into.
                // now shift everything between firstNull through one of the boundaries
                // depending on which side firstNull is on.
                if (firstNull < leftItem) {
                    for (int j = firstNull; j < leftItem; j++) {
                        this->operations++;
                        this->list[j] = this->list[j+1];
                    }
                    this->list[leftItem] = item;
                } else if (firstNull > rightItem) {
                    for (int j = firstNull; j > rightItem; j--) {
                        this->operations++;
                        this->list[j] = this->list[j-1];
                    }
                    this->list[rightItem] = item;
                } else { // one of them is actually a null location, so no shifting
                    if (this->list[leftItem] == nullptr) {
                        this->operations++;
                        this->list[leftItem] = item;
                    } else {
                        this->operations++;
                        this->list[rightItem] = item;
                    }
                }

                if (firstNull > this->next) {
                    // increase the length
                    this->next++;
                }
            } else {
                // otherwise insert it between the two correct spaces
                // or at the two spaces if they are the same
                // note: this is heavily left-biased.
                this->list[rightItem - (rightItem - leftItem) / 2] = item;
                // this only increases the length if the list is empty.
                if (this->IsEmpty() || rightItem >= this->next) {
                    this->next++;
                }
            }
            // count an insert
            this->operations++;
        }
    }
}

template <class T>
T* OrderedListOpenSpaces<T>::RemoveItem(T* item) {
    if (this->IsEmpty()) {
        // item cannot be in the list
        throw EmptyListException();
    } else {
        // walk through the list from the beginning
        // until we find the spot where the item is
        // or we hit the end of the array.
        int i = 0;
        while (i < this->next && (this->list[i] == nullptr || *item != *(this->list[i]))) {
            // count this check if it's not a nullptr
            if (this->list[i] != nullptr) {
                this->operations++;
            }
            i++;
        }
        if (i >= this->next) {
            // item isn't in the list
            throw NotFoundException();
        } else {
            // store item at the found position
            // count this operation
            this->operations++;
            T* temp = this->list[i];

            // set item at that location to null
            if (this->list[i] != nullptr) {
                this->list[i] = nullptr;
            }

            // and return the item
            return item;
        }
    }
}

template <class T>
T* OrderedListOpenSpaces<T>::RemoveItem(int pos) {
    if (this->IsEmpty()) {
        throw EmptyListException();
    } else {
        if (pos >= this->next) {
            // attempted to retrieve from a position outside the array
            throw IndexException();
        } else {
            // store item at pos
            // count this operation
            this->operations++;
            T* temp = this->list[pos];

            // set item at that location to null
            this->list[pos] = nullptr;

            // and return the item
            return temp;
        }
    }
}

template <class T>
bool OrderedListOpenSpaces<T>::IsFull() {
    if (this->Length() == this->capacity) {
        // if there aren't nulls, it's true
        for (int i = 0; i < this->next; i++) {
            if (this->list[i] == nullptr) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}


#endif //LAB07_ORDEREDLISTOPENSPACES_H
