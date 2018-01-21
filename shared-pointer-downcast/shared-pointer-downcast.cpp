/*
A shared pointer downcasting example.

Copyright (C) 2018, Adrian Raul Mos

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
#include <iostream>
#include <mutex>

using namespace std;

class Interface {
public:
	virtual void foo() = 0;
};


class MyClass : public Interface {
public:
	MyClass() {
		cout << " MyClass object created" << std::endl;
	}
	void foo() {
		cout << " foo() called" << std::endl;
	}
	void bar() {
		cout << " bar() called" << std::endl;
	}
};


int main()
{ 
	// SITUATION #1

	// an object and a shared pointer (of type Interface) is created
	std::shared_ptr<Interface> pointerToClassThroughInterface = std::make_shared<MyClass>();

	// by using the shared pointer we can access everything defined by the interface 
	pointerToClassThroughInterface->foo();

	// but we can not access other functions defined in MyClass
	//pointerToClassThroughInterface->bar(); // not possible

	// we must downcast the shared pointer (of type Interface) to a shared pointer of type MyClass
	std::shared_ptr<MyClass> pointerToClass;
	pointerToClass = std::static_pointer_cast<MyClass>(pointerToClassThroughInterface);

	// now, we can access everything
	pointerToClass->foo();
	pointerToClass->bar();


	// SITUATION #2

	// first the object is created using a shared pointer of type (MyClass)
	// then, it is used for creating a shared pointer (of type Interface) 
	std::shared_ptr<MyClass> pointerToClass2 = std::make_shared<MyClass>();
	std::shared_ptr<Interface> pointerToClassThroughInterface2 = pointerToClass2;

	// by using the proper pointers, we can access everything
	pointerToClassThroughInterface2->foo();
	pointerToClass2->foo();
	pointerToClass2->bar();

	std::getchar();
}

