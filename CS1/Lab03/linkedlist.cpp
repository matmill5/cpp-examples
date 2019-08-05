// CS1_Lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

// Class Definition
class Node {
public:
	Node(std::string nameData, int ageData, Node* nextLoc = nullptr);
	
	Node* getNextNode();
	std::string getName();
	int getAge();

	void setName(std::string);
	void setAge(int);

	void insertAfter(Node*);
	void printNodeData();
private:
	std::string nameValue;
	int ageValue;
	Node* nextNodePtr;
};

void bubbleSort(Node* headObj);
void swap(Node* a, Node* b);
void printEntireList(Node* headObj);

// Constructor
Node::Node(std::string nameData, int ageData, Node* nextLoc) {

	this->nameValue = nameData;
	this->ageValue = ageData;
	this->nextNodePtr = nextLoc;

	return;
}

//Get next Node
Node* Node::getNextNode() {
	return this->nextNodePtr;
}

std::string Node::getName() {
	return this->nameValue;
}

int Node::getAge() {
	return this->ageValue;
}

void Node::setName(std::string a) {
	this->nameValue = a;
}

void Node::setAge(int i) {
	this->ageValue = i;
}

//Insert next node
void Node::insertAfter(Node* nodeLoc) {

	Node* tmpNext = nullptr;

	tmpNext = this->nextNodePtr;
	this->nextNodePtr = nodeLoc;
	nodeLoc->nextNodePtr = tmpNext;

	return;
}

// Print Node values
void Node::printNodeData() {

	std::cout << this->nameValue << " " << this->ageValue << std::endl;

	return;
}

void printEntireList(Node* headObj) {
	Node* currObj = nullptr;
	currObj = headObj;
	while (currObj != nullptr) {
		currObj->printNodeData();
		currObj = currObj->getNextNode();
	}
}

//Bubble sort the given linked list
void bubbleSort(Node* headObj){
	int swapped;
	Node* ptr1;
	Node* lptr = nullptr;

	if (headObj->getNextNode() == nullptr)
		return;

	do
	{
		swapped = 0;
		ptr1 = headObj;

		while (ptr1->getNextNode() != lptr)
		{
			if (ptr1->getName() > ptr1->getNextNode()->getName())
			{
				swap(ptr1, ptr1->getNextNode());
				swapped = 1;
			}
			ptr1 = ptr1->getNextNode();
		}
		lptr = ptr1;
	} while (swapped);
}

//Swap data of two nodes a and b
void swap(Node* a, Node* b){
	std::string name_temp = a->getName();
	int age_temp = a->getAge();
	a->setAge(b->getAge());
	a->setName(b->getName());
	b->setAge(age_temp);
	b->setName(name_temp);
}

int main() {
	char Name[256];
	char Age[256];

	Node* headObj = nullptr; // Create Node objects pointers
	Node* nodeObj1 = nullptr;
	Node* nodeObj2 = nullptr;
	Node* nodeObj3 = nullptr;
	Node* tmp = nullptr;

	std::ifstream input_file("inputfile.txt");

	if (!input_file.is_open()) { //Checks if input file opened successfully.
		std::cout << "Input file not opened";
	}
	else {
		if (!input_file.eof()) {

			//Front of nodes list
			input_file.getline(Name, 256, ' ');
			input_file.getline(Age, 256, '\n');
			headObj = new Node(Name, atoi(Age));

			//Insert some nodes
			input_file.getline(Name, 256, ' ');
			input_file.getline(Age, 256, '\n');
			nodeObj1 = new Node(Name, atoi(Age));
			headObj->insertAfter(nodeObj1);

			input_file.getline(Name, 256, ' ');
			input_file.getline(Age, 256, '\n');
			nodeObj2 = new Node(Name, atoi(Age));
			nodeObj1->insertAfter(nodeObj2);

			input_file.getline(Name, 256, ' ');
			input_file.getline(Age, 256, '\n');
			nodeObj3 = new Node(Name, atoi(Age));
			nodeObj2->insertAfter(nodeObj3);
		}
		bubbleSort(headObj);
	}
	//Print the data in the linked list
	printEntireList(headObj);
	input_file.close();
	return 0;
}