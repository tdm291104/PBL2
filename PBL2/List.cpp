#include "List.h"

template <typename T>
List<T>::List()
{
    this->data.next = NULL;
    this->data.pre = &this->data;
    this->size = 0;
}

template <typename T>
List<T>::~List()
{
    Node<T>* p = this->data.next;
    Node<T>* tmp;
    while (p != nullptr)
    {
        tmp = p;
        p = p->next;
        delete tmp;
    }
}

template <typename T>
bool List<T>::isEmpty() const
{
    return (this->size == 0);
}

template <typename T>
Node<T>* List<T>::Search(const int& i)
{
    int tmp = 0;
    Node<T>* p = this->data.next;
    while (p != NULL)
    {
        if (tmp == i)
            return p;
        tmp++;
        p = p->next;
    }

    return NULL;
}

template <typename T>
void List<T>::Push(const T& i)
{
    Node<T>* tmp = new Node<T>;
    tmp->index = i;
    tmp->next = NULL;
    tmp->pre = NULL;

    Node<T>* p = &this->data;
    while (p->next != NULL)
        p = p->next;

    tmp->pre = p;
    p->next = tmp;

    this->size++;
}

template <typename T>
void List<T>::Pop(const int& i)
{
    if (i < this->size)
    {
        Node<T>* p = Search(i);

        if (p->next != NULL)
        {
            p->pre->next = p->next;
            p->next->pre = p->pre;
        }
        else
        {
            p->pre->next = NULL;
        }
        delete p;
        this->size--;
    }
}

template <typename T>
T& List<T>::operator[](int i)
{
    static T default_value;
    return (i < this->size) ? Search(i)->index : default_value;
}

template <typename T>
int List<T>::Size() const
{
    return this->size;
}

template <typename T>
void List<T>::Clear()
{
    Node<T>* p = this->data.next;
    Node<T>* tmp;
    while (p != nullptr)
    {
        tmp = p;
        p = p->next;
        delete tmp;
    }

    this->data.next = NULL;
    this->data.pre = &this->data;
    this->size = 0;
}