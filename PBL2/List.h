#ifndef LIST_H_
#define LIST_H_

#include <iostream>

template<typename T>
struct Node
{
    T index;
    Node<T>* next;
    Node<T>* pre;
};

template<typename T>
class List
{
private:
    Node<T> data;
    int size;

public:
    List();
    ~List();
    Node<T>* Search(const int&);
    void Push(const T&);
    void Pop(const int&);
    void Clear();
    bool isEmpty() const;
    T& operator[](int);

    int Size() const;
};

#endif