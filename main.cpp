
#include <iostream>
#include "Search_Tree/Tree.cpp"

using namespace std;

int main() {

    Set<int> x;
    x.insert(5);
    x.insert(-4);
    x.insert(6);

    Set<int> y;
    y.insert(-4);
    y.insert(6);
    y.insert(70);

    cout << "x: ";
    x.print();
    std::cout << "y: ";
    y.print();

    
    return 0;

}
