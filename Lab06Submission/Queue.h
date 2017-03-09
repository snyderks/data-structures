//
// Created by Kristian Snyder on 2/26/17.
//

#ifndef LAB06_QUEUE_H
#define LAB06_QUEUE_H

#include <vector>
using namespace std;

class EmptyQueue {};

// implements a FIFO queue
template <class T>
class Queue {
private:
    vector<T> queue;
public:
    // adds item to queue
    void enqueue(T item);
    // returns item first added to the queue and removes it
    T dequeue();
    // returns item first added to the queue without removal
    T top();
    unsigned long length();
    bool isEmpty();
    void empty();
};

template <class T>
void Queue<T>::enqueue(T item) {
    // inserts the item at the very beginning of the queue.
    // most recently added items are at beginning of queue.
    queue.insert(queue.begin(), item);
}

template <class T>
T Queue<T>::dequeue() {
    // throw exception if the queue is empty and we try to remove an item
    if (isEmpty()) {
        throw EmptyQueue();
    }
    // removes item at the end of the queue and returns it
    T temp = queue.back();
    queue.pop_back();
    return temp;
}

template <class T>
T Queue<T>::top() {
    // throw exception if the queue is empty and we try to access anything
    if (isEmpty()) {
        throw EmptyQueue();
    }
    // accesses end of queue
    return queue.back();
}

template <class T>
unsigned long Queue<T>::length() {
    return queue.size();
}

template <class T>
bool Queue<T>::isEmpty() {
    return queue.empty();
}

template <class T>
void Queue<T>::empty() {
    queue.clear();
}

#endif //LAB06_QUEUE_H
