#include "StaticArray.h"

int main() 
{
    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int x4 = 4;
    StaticArray<int*, 4> ptrs = {&x1, &x2, &x3, &x4};
    ptrs.print();
    ptrs.reverse();
    ptrs.print();
    std::cout << ptrs.min() << " at " << ptrs.argmin() << '\n';
    std::cout << ptrs.max() << " at " << ptrs.argmax() << '\n';
    std::cin.get();
    return 0;
}