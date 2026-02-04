#include "static_linked_list.h"

int main() 
{
    int x[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    StaticLinkedList<int, 10> link(x);
    link.print();
    link.reverse();
    link.print();
    std::cin.get();
    return 0;
}