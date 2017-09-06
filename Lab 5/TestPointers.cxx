#include "MyClass.cxx"


// Pass by value
void fun1(MyClass a)
{
	a.setX(1);
}


// Pass by reference
void fun2(MyClass& a)
{
	a.setX(2);
}



// Pass by pointer
void fun3(MyClass* a)
{
	a->setX(3);
}


// Using double pointers! Coz why stop at single pointers? :)
void fun4(MyClass** a)
{
	(*a)->setX(4);
}



int main() 
{
	MyClass a;
	MyClass* b;
	MyClass** c;
	
	cout << endl << "----Calling fun1----" << endl;
	
	fun1(a); 
	a.printX(); // Explaining output (1 point)	
	//This will print out the value of a originally which is 0 but since it is a pass by value you can't change
	//the variable value.


	cout << endl << "----Calling fun2----" << endl;	
	
	fun2(a); 
	a.printX(); // Explaining output (1 point)
	// Since this is a pass by reference it will print the changed variable of a which in this case is 2.

	
	cout << endl << "----Calling fun3----" << endl;
	
	b = &a;     // Fixing compile error (1 point)
	fun3(b);   
	a.printX(); // Explaining output (1 point)
	// b is initialized and given the value of a which was changed in fun2 to 2 and then b is a pointer 2 a in
	// memory address and changed to the value of 3.


	cout << endl << "----Calling fun4----" << endl;
	
	c = &b;    // Fixing compile error (1 point)
	fun4(c);    
	a.printX(); // Explaining output (1 point)
	// c is initialized and given the value of the new value of a from pointer b to 3 then since c is pointing to b and 
	// b is pointing to then the value of a is changed to 4.
	
	//Dereferencing using single pointer
	cout << "\n\nTwo ways of dereferencing, \n1. Using '.' operator\n2. Using '->' operator\n\n";
	
	
	(*b).printX();          // Fixing compile error (1 point)
	(b)->printX();      // Fixing compile error (1 point) 
	
	// add a statement here!
	// The first print statement and the second print statement achieve the same thing and will print 
	// the value of b which is pointing to a and thus the value of a which was changed in fun4 and the
	// value was changed to 4.

	cout << "\n\n----Understanding arrays as pointers----" << endl;
	MyClass arr[5];
	
	arr[0].setX(10);
	arr[1].setX(20);
	arr[2].setX(30);
	arr[3].setX(40);
	arr[4].setX(50);
	
	cout << "----Running for loop for array variable 'arr' with 5 slots----" << endl << endl;
	
	//Explaining for loop (2 points)
	// This array contains 5 slots and will run through each slot and identify which
	// memory address that integer value is located in and gives two different ways of
	// printing the memory address.
	for (unsigned int i=0; i<5; i++)
	{
		cout << "i = " << i << endl;
		cout << "memory location (arr + i) = " << arr+i << endl;
		cout << "  (*(arr + i)).printX() prints ";
		(*(arr+i)).printX();
		cout << "        arr[i].printX() prints ";
		arr[i].printX();
		cout << endl;
	}
	
	
	
	return 0;


}

