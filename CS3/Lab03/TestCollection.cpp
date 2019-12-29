// testing the implementation of templated list collection
// Mikhail Nesterenko
// 9/10/2015

//#include "pch.h"
#include "Collection.h" // template definition
#include <iostream>
#include <string>

using std::cout; using std::endl;
using std::string;

int main() {

	// manipulating integers
	Collection<int> cone;
	cout << "Integer collection: ";
	cone.addItem(1); cone.addItem(2); cone.addItem(3);
	cone.printCollection();

	cone.removeItem(2);
	cone.printCollection();

	if (equal(cone, cone))
		cout << "cone is equal to itself" << endl;


	// uncomment when you debug the code above


	// manipulating strings
	string sa[] = {"yellow", "orange", "green", "blue"};
	Collection<string> ctwo;

	for(auto s : sa)
	   ctwo.addItem(s);

	cout << "String collection: ";
	ctwo.printCollection();


	// manipulating character collections

	// individal collections
	Collection<char> a2g, h2n, o2u;
	for(char c='a'; c <='g'; ++c) a2g.addItem(c);
	for(char c='h'; c <='n'; ++c) h2n.addItem(c);
	for(char c='o'; c <='u'; ++c) o2u.addItem(c);
	
	//Debuging
	//a2g.printCollection();
	//h2n.printCollection();
	//o2u.printCollection();

	if(!equal(a2g, h2n))
	   cout << "a2g is not equal to h2n" << endl;

	// collection of collections
	Collection<Collection<char>> cpile;

	// adding individual collections
	cpile.addItem(a2g);
	cpile.addItem(h2n);
	cpile.addItem(o2u);

	// printing characters from last collection added
	cout << "Last added character collection: ";
	cpile.lastItem().printCollection();

	
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
