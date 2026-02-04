#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include <iostream>
#include "concepts.h"

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
    T data[N]{}; //Please don't access directly
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
            std::cout << (*this)[i] << ((i == N - 1) ? "]" : " ");
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

    double mean() const requires Numeric<T>
    {
        double sum = 0.0;
        for(size_t i = 0; i < N; i++)
            sum += static_cast<double>((*this)[i]);
        return sum / N;
    }

    double median() const requires Numeric<T>
    {
        StaticArray<T, N> temp = *this;
        temp.bubbleSort();
        constexpr size_t half = N / 2;
        if constexpr(N % 2 != 0)
            return static_cast<double>(temp[half]);
        else
            return (static_cast<double>(temp[half - 1]) + static_cast<double>(temp[half])) / 2;
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
        for(size_t i = 0; i < N / 2; i++)
            swap(i, N - 1 - i);
    }

    void primes() requires UInt<T>
    {
        size_t i = 0;
        T num = 2;
        while(i < N)
        {            
            size_t counter = 2;
            for(T x = 2; x <= num / 2; x++)
                if(num % x == 0)
                    counter++;
            if(counter == 2)
            {
                (*this)[i] = num;
                i++;
            }
            if(num == std::numeric_limits<T>::max())
                throw std::overflow_error("Cannot represent further primes in this type");
            num++;
        }
    }

    //best O(n), avg O(n^2)
    void bubbleSort() requires AlphaNumericComplete<T>
    {
        for(size_t i = 0; i < N - 1; i++)
            for(size_t j = 0; j < N - 1 - i; j++)
                if((*this)[j] > (*this)[j + 1])
                    swap(j, j + 1);
    }

    //best O(n), avg O(n^2)
    void insertionSort() requires AlphaNumericComplete<T>
    {
        if(N > 1)
            for(size_t i = 1; i < N; i++)
            {
                size_t j = i;
                while(j > 0 && (*this)[j] < (*this)[j - 1])
                {
                    swap(j, j - 1);
                    j--;
                }
            }
    }

    //best O(n^2), avg O(n^2)
    void selectionSort() requires AlphaNumericComplete<T>
    {
        if(N > 1)
            for(size_t i = 0; i < N - 1; i++)
            {
                size_t min_index = i;
                for(size_t j = i + 1; j < N; j++)
                    if((*this)[j] < (*this)[min_index])
                        min_index = j;
                if(min_index != i)
                    swap(i, min_index);
            }
    }

    //best O(n^2), avg O(n^2)
    void exchangeSort() requires AlphaNumericComplete<T>
    {
        if(N > 1)
            for(size_t i = 0; i < N - 1; i++)
                for(size_t j = i + 1; j < N; j++)
                    if((*this)[j] < (*this)[i])
                        swap(i, j);
    }

    //best O(n^2), avg O(n^2)
    void cycleSort() requires AlphaNumericComplete<T>
    {
        if(N > 1)
            for(size_t i = 0; i < N - 1; i++)
            {
                T item = (*this)[i];
                size_t correct_index = i;

                for(size_t j = i + 1; j < N; j++)
                    if((*this)[j] < item)
                        correct_index++;

                if(correct_index == i)
                    continue;

                while(item == (*this)[correct_index])
                    correct_index++;
                
                while(correct_index != i)
                {
                    T temp = (*this)[correct_index];
                    (*this)[correct_index] = item;
                    item = temp;

                    correct_index = i;
                    for(size_t j = i + 1; j < N; j++)
                        if((*this)[j] < item)
                            correct_index++;
                    
                    while(item == (*this)[correct_index])
                        correct_index++;
                }
                
                (*this)[i] = item;
            }
    }
};

#endif