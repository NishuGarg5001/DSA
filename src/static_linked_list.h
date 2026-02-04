#ifndef STATIC_LINKED_LIST_H
#define STATIC_LINKED_LIST_H

#include <limits>
#include "static_array.h"

template<typename T>
requires (!std::is_const_v<T>)
struct Node
{
    T data{};
    Node<T> *next = nullptr;

    Node() = default;

    explicit Node(T data, Node<T> *next = nullptr) : data(data), next(next)
    {}
};

template<typename T, size_t N>
requires (!std::is_const_v<T>)
class StaticLinkedList
{
    StaticArray<Node<T>, N> nodes;
    Node<T> *head = nullptr;

    public:
    static_assert(N > 0, "LinkedList must not be empty");

    explicit StaticLinkedList(T (&data)[N])
    {
        for(size_t i = 0; i < N; i++)
        {
            nodes[i] = Node(data[i]);
            if(i > 0)
                nodes[i-1].next = &nodes[i];
        }
        head = &(*this).nodes[0];
    }

    T &operator [](size_t i)
    {
        if (i >= N)
            throw std::out_of_range("LinkedList index out of range");
        Node<T> *temp = head;
        size_t j = 0;
        while(j < i)
        {
            temp = temp->next;
            j++;
        }
        return temp->data;
    }

    const T &operator [](size_t i) const
    {
        if (i >= N)
            throw std::out_of_range("LinkedList index out of range");
        const Node<T> *temp = head;
        size_t j = 0;
        while(j < i)
        {
            temp = temp->next;
            j++;
        }
        return temp->data;
    }

    void reverse()
    {
        if(N > 1)
        {
            Node<T> *p = nullptr;
            Node<T> *c = head;
            Node<T> *n = head->next;
            
            while(n)
            {
                c->next = p;
                p = c;
                c = n;
                n = n->next;
            }
            c->next = p;
            head = c;
        }
    }

    void print() const requires AlphaNumericComplete<T>
    {
        const Node<T> *temp = head;
        while(temp)
        {
            std::cout << temp->data << "->";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }
};

#endif