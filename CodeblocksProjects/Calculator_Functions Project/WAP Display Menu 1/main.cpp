#include <iostream>

using namespace std;

void displayMenu();

int main()
{
    displayMenu();
    return 0;
}

void displayMenu ()
{
    cout << ">- What shape would you like?" << endl;
    cout << endl;
    cout << "Please enter an integer between 1 and 8 to select a shape" << endl;
    cout << "(Integer is a non decimal number)" << endl;
    cout << endl;
    cout << ">- 1. Rectangle" << endl;
    cout << ">- 2-6. Triangle" << endl;
    cout << ">- 7. Diamond" << endl;
    cout << ">- 8. Tree" << endl;
}
