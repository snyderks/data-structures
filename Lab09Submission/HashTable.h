//
// Created by Kristian Snyder on 3/20/17.
//

#ifndef LAB09_HASHTABLE_H
#define LAB09_HASHTABLE_H

#define DEFAULTMAXITEMS 100

#include <string>
#include <iostream>

template <class T>
class HashTable {
private:
    class Cell {
    public:
        T* data;
        bool removed;
        Cell(T* item) {
            data = item;
            removed = false;
        }
        ~Cell() {
            data = nullptr;
        }
    };
    Cell** dataTable;
    bool occupied(int key) {
        return dataTable[key] != nullptr;
    }
protected:
    int tableLength;
    int length;
    int numItems;
    int hash(std::string s);
    int findLocation(int key, const T* item);
    int additionalChecks;
public:
    class FullTableException{};

    /// \brief Constructor
    /// \param maxItems set the maximum number of items the table can hold
    HashTable(int maxItems = DEFAULTMAXITEMS);

    /// \brief Destructor
    ~HashTable();

    /// \brief AddItem inserts an item into the table.
    /// \param item the data to insert.
    /// \throws FullTableException
    void AddItem(T* item);

    /// \brief RemoveItem locates the item passed and removes it from the table.
    /// \param item the item to search for
    /// \returns the item from the table if found, nullptr if not.
    T* RemoveItem(T* item);

    /// \brief GetItem locates the item passed and returns the item it matches in the table.
    /// \param item the item to search for
    /// \returns the item from the table if found, nullptr if not.
    T* GetItem(T* item);

    /// \brief GetLength gets the current number of items in the hash table.
    /// \returns number of items in the hash table
    int GetLength();

    /// \brief Prints the table.
    void PrintTable();

    /// \brief Returns the number of checks made by the hash table
    ///        since the last call.
    int getChecks() {
        auto temp =  additionalChecks;
        additionalChecks = 0;
        return temp;
    }
};

template <class T>
int HashTable<T>::hash(std::string s) {
    int sum = 0;
    for (int i = 0; i < s.length(); i++) {
        sum += s[i];
    }
    return sum % tableLength;
}

template <class T>
int HashTable<T>::findLocation(int key, const T* item) {
    // skip if occupied
    while (dataTable[key] != nullptr && (dataTable[key]->removed || *dataTable[key]->data != *item)) {
        key = (key + 1) % tableLength;
    }
    return key;
}

template <class T>
HashTable<T>::HashTable(int maxItems) {
    dataTable = new Cell*[maxItems];
    for (int i = 0; i < maxItems; i++) {
        dataTable[i] = nullptr;
    }
    tableLength = maxItems;
    length = 0;
}

template <class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < tableLength; i++) {
        delete dataTable[i];
        dataTable[i] = nullptr;
    }
    delete dataTable;
    dataTable = nullptr;
}

template <class T>
void HashTable<T>::AddItem(T *item) {
    if (length < tableLength) {
        int index = hash(*item);
        index = findLocation(index, item);

        if (occupied(index)) {
            // avoids a memory leak
            delete dataTable[index]->data;
            dataTable[index]->data = item;
            dataTable[index]->removed = false;
        } else {
            dataTable[index] = new Cell(item);
        }
        // track current length
        length++;
    } else {
        throw FullTableException();
    }
}

template <class T>
T* HashTable<T>::RemoveItem(T* item) {
    int index = hash(*item);

    if (!occupied(index)) {
        return nullptr;
    } else {
        int j = index;
        bool cycled = false;
        // cycle through until we either hit an empty spot,
        // the item, or the original index.
        while (dataTable[j] != nullptr && *dataTable[j]->data != *item) {
            j = (j + 1) % tableLength;
            if (j == index) {
                cycled = true;
                break;
            }
        }

        if (cycled || dataTable[j] == nullptr) {
            return nullptr;
        } else {
            // track current length
            length--;

            // clear out the cell and mark it as deleted, returning the pointer.
            auto retptr = dataTable[j]->data;
            dataTable[j]->removed = true;
            dataTable[j]->data = nullptr;
            return retptr;
        }
    }
}

template <class T>
T* HashTable<T>::GetItem(T* item) {
    int index = hash(*item);

    if (!occupied(index)) {
        return nullptr;
    } else {
        int j = index;
        bool cycled = false;
        // cycle through until we either hit an empty spot,
        // the item, or the original index.
        // increment the number of checks made.
        additionalChecks++;
        while (dataTable[j] != nullptr && *dataTable[j]->data != *item) {
            additionalChecks++;
            j = (j + 1) % tableLength;
            if (j == index) {
                cycled = true;
                break;
            }
        }

        if (cycled || dataTable[j] == nullptr) {
            return nullptr;
        } else {
            // return a pointer to the item
            return dataTable[j]->data;
        }
    }
}

template <class T>
int HashTable<T>::GetLength() {
    return length;
}

template <class T>
void HashTable<T>::PrintTable() {
    for (int i = 0; i < tableLength; i++) {
        if (dataTable[i] != nullptr && dataTable[i]->data != nullptr) {
            std::cout << std::endl
                      << *dataTable[i]->data << std::endl
                      << "at index " << i << std::endl;
        }
    }
}

#endif //LAB09_HASHTABLE_H
