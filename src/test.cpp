#include "StaticArray.h"

int main() 
{
    StaticArray<float, 4> x = {9.6, 4.6, -2.3, 5.2};
    StaticArray<float, 5> y = {2.3, 4.1, -3.7, 3.6, 10.5};
    x.print();
    std::cout << x.mean() << " " << x.median() << '\n';
    y.print();
    std::cout << y.mean() << " " << y.median() << '\n';
    std::cin.get();
    return 0;
}