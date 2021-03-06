/*
This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.*/

#include "stdafx.h"
#include <algorithm>
#include <stdio.h>
#include <iostream>

using namespace std;

int incrementFunction(int x) { return (x + 1); }

// Functor
//   you can mimmic a function by using a class
//   and you get the bonus of encapsulation ...
class IncrementFunctor {
private:
    int incrementUnit;
public:
    IncrementFunctor(int n) : incrementUnit(n) { }

    // overload () operator
    // this function is called when the functor is "called"
    int operator () (int x) const {
        return incrementUnit + x;
    }
};


void displayArray(int *arr, int length) {
    for (int i = 0; i<length; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
    int length = sizeof(arr) / sizeof(arr[0]);
    
    // No functor
    transform(arr, arr + length, arr, incrementFunction);
    displayArray(arr, length);

    // Functor
    transform(arr, arr + length, arr, IncrementFunctor(10));
    displayArray(arr, length);

    std::cin.get();
    return 0;
}



