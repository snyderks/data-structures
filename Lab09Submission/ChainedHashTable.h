//
// Created by Kristian Snyder on 3/26/17.
//

#ifndef LAB09_CHAINEDHASHTABLE_H
#define LAB09_CHAINEDHASHTABLE_H


#include "HashTable.h"

template <class T>
class ChainedHashTable : public HashTable<T> {
private:
    class CellNode {
    public:
        T* data;
        CellNode* next;
        CellNode(T* item) {
            data = item;
            next = nullptr;
        }
        ~CellNode() {
            data = nullptr;
            delete next;
            next = nullptr;
        }
    };
    CellNode** dataTable;
    bool occupied(int key) {
        return dataTable[key] != nullptr;
    }
public:
    class FullTableException {};

    /// \brief ChainedHashTable initializes the table
    ChainedHashTable(int maxItems = DEFAULTMAXITEMS);

    ~ChainedHashTable();

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

    /// \brief Prints the table.
    void PrintTable();
};

template <class T>
ChainedHashTable<T>::ChainedHashTable(int maxItems) : HashTable<T>(maxItems) {
    this->tableLength = maxItems;
    this->length = 0;
    dataTable = new CellNode*[maxItems];
    for (int i = 0; i < this->tableLength; i++) {
        dataTable[i] = nullptr;
    }
}

template <class T>
ChainedHashTable<T>::~ChainedHashTable() {
    for (int i = 0; i < this->tableLength; i++) {
        delete this->dataTable[i];
        this->dataTable[i] = nullptr;
    }
    delete this->dataTable;
    this->dataTable = nullptr;
}

template <class T>
void ChainedHashTable<T>::AddItem(T *item) {
    if (this->length < this->tableLength) {
        int index = this->hash(*item);

        if (this->occupied(index)) {
            auto node = dataTable[index];
            while (*node->data != *item && node->next != nullptr) {
                node = node->next;
            }
            // replace if the same
            if (*node->data == *item) {
                delete node->data;
                node->data = item;
            // we reached the end of the list
            } else {
                node->next = new CellNode(item);
            }
        } else {
            dataTable[index] = new CellNode(item);
            // increment length ONLY if a new array location is assigned to
            this->length++;
        }

    } else {
        throw FullTableException();
    }
}

template <class T>
T* ChainedHashTable<T>::RemoveItem(T* item) {
    int index = this->hash(*item);

    if (!(this->occupied(index))) {
        return nullptr;
    } else {
        auto node = this->dataTable[index];
        // special case for list of length 1
        if (node->next == nullptr) {
            if (*node->data != *item) {
                return nullptr;
            } else {
                auto temp = node;
                this->dataTable[index] = nullptr;
                return temp->data;
            }
        }
        // 2 length location
        if (node->next->next == nullptr) {
            if (*node->data == *item) {
                auto temp = node->data;
                dataTable[index] = node->next;
                return temp;
            } else if (*node->next->data == *item) {
                auto temp = node->next->data;
                node->next = nullptr;
                return temp;
            } else {
                return nullptr;
            }
        }
        // 3+ length location
        while (node->next->next != nullptr &&
               *node->next->data != *item) {
            node = node->next;
        }
        if (*node->next->data != *item) {
            return nullptr;
        } else {
            auto temp = node->next->data;
            node->next = node->next->next;
            return temp;
        }
    }
}

template <class T>
T* ChainedHashTable<T>::GetItem(T* item) {
    int index = this->hash(*item);

    if (!this->occupied(index)) {
        return nullptr;
    } else {
        auto node = this->dataTable[index];
        this->additionalChecks++;
        while (*node->data != *item && node->next != nullptr) {
            this->additionalChecks++;
            node = node->next;
        }
        if (*node->data == *item) {
            return node->data;
        } else {
            return nullptr;
        }
    }
}

template <class T>
void ChainedHashTable<T>::PrintTable() {
    for (int i = 0; i < this->tableLength; i++) {
        if (dataTable[i] != nullptr && dataTable[i]->data != nullptr) {
            std::cout << "at index " << i << ":" << std::endl;
            auto node = dataTable[i];
            while (node != nullptr && node->data != nullptr) {
                std::cout << *node->data
                          << "\n\n";
                node = node->next;
            }
        }
    }
}


#endif //LAB09_CHAINEDHASHTABLE_H
