
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
    cout << "y: ";
    y.print();


    Set<int> z = x.set_inter(y);
    cout << "z: ";
    z.print();

    Set<int> k = x.set_diff(y);
    cout << "k: ";
    k.print();

    return 0;

}
