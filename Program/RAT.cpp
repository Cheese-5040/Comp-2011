#include <iostream>
using namespace std;

int main()
{
    cout << "input size of RAT: " << endl;
    int size; //height means width + size
    cin >> size;

    for (int width = 1; width <= size; width++) //iterations means height
    {
        // drawing one row of RAT
        for (int j = 0; j < 2 * width - 1; j++) //width of a row
        {
            cout << "*";
        }
        cout << endl;
    }

    cout << "A hollow RAT" << endl;
    for (int width = 1; width <= size; width++) //iterations means height
    {
        // drawing one row of RAT
        for (int j = 0; j < width; j++) //width of a row
        {
            cout << ((j == 0 || j == width - 1 || width == size) ? "*" : " ");
        }
        cout << endl;
    }

    cout << "an upside down rat" << endl;
    for (int width = size; width >= 1; width--)
    {
        for (int j = 0; j < width; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}