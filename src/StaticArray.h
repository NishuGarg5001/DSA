#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include <iostream>
#include "Concepts.h"

template<typename T, size_t N>
requires (!std::is_const_v<T>)
class StaticArray
{
    void swap(size_t i, size_t j)
    {
        T temp = (*this)[j];
        (*this)[j] = (*this)[i];
        (*this)[i] = temp;
    }

    public:
    static_assert(N > 0, "StaticArray must not be empty");
    T data[N]; //Please don't access directly
    static constexpr size_t size = N;

    T &operator[](size_t i)
    {
        if (i >= N)
            throw std::out_of_range("StaticArray index out of range");
        return data[i];
    }

    const T &operator[](size_t i) const
    {
        if (i >= N)
            throw std::out_of_range("StaticArray index out of range");
        return data[i];
    }

    void print() const requires AlphaNumericComplete<T>
    {
        std::cout << "[";
        for(size_t i = 0; i < N; i++)
            std::cout << (*this)[i] << ((i == N-1) ? "]" : " ");
        std::cout << "\n";
    }

    T min() const requires AlphaNumericComplete<T>
    {
        T m = (*this)[0];
        for(size_t i = 1; i < N; i++)
            if((*this)[i] < m)
                m = (*this)[i];
        return m;
    }

    T max() const requires AlphaNumericComplete<T>
    {
        T m = (*this)[0];
        for(size_t i = 1; i < N; i++)
            if((*this)[i] > m)
                m = (*this)[i];
        return m;
    }

    size_t argmin() const requires AlphaNumericComplete<T>
    {
        size_t m = 0;
        for(size_t i = 1; i < N; i++)
            if((*this)[i] < (*this)[m])
                m = i;
        return m;
    }

    size_t argmax() const requires AlphaNumericComplete<T>
    {
        size_t m = 0;
        for(size_t i = 1; i < N; i++)
            if((*this)[i] > (*this)[m])
                m = i;
        return m;
    }

    void reverse() requires AlphaNumericComplete<T>
    {
        for(size_t i = 0; i < N/2; i++)
            swap(i, N-1-i);
    }

    void exchangeSort() requires AlphaNumericComplete<T>
    {
        if(N > 1)
            for(size_t i = 0; i < N-1; i++)
                for(size_t j = i + 1; j < N; j++)
                    if((*this)[j] < (*this)[i])
                        swap(i, j);
    }

    void bubbleSort() requires AlphaNumericComplete<T>
    {
        for(size_t i = 0; i < N-1; i++)
            for(size_t j = 0; j < N-1-i; j++)
                if((*this)[j] > (*this)[j+1])
                    swap(j, j+1);
    }

    void insertionSort() requires AlphaNumericComplete<T>
    {
        if(N > 1)
            for(size_t i = 1; i < N; i++)
            {
                size_t j = i;
                while(j > 0 && (*this)[j] < (*this)[j-1])
                {
                    swap(j, j-1);
                    j--;
                }
            }
    }

    void selectionSort() requires AlphaNumericComplete<T>
    {
        if(N > 1)
            for(size_t i = 0; i < N-1; i++)
            {
                size_t min_index = i;
                for(size_t j = i + 1; j < N; j++)
                    if((*this)[j] < (*this)[min_index])
                        min_index = j;
                if(min_index != i)
                    swap(i, min_index);
            }
    }

    void cycleSort() requires AlphaNumericComplete<T>
    {
        
    }
};

#endif