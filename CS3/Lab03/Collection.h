#pragma once

// Author: Matthew E. Miller

#ifndef COLLECTION_H_
#define COLLECTION_H_
//#include "pch.h"
#include "List.h"
#include <iostream>


// class prototype
template <typename T>
class Collection;

// equal function prototype
template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

// Class definition
template<typename T>
class Collection {
public:
	Collection() : listHead(nullptr) {}
	void addItem(const T& item);
	void removeItem(const T& item);
	T lastItem();
	void printCollection();
	friend bool equal<T>(const Collection<T>&, const Collection<T>&);
private:
	node<T> *listHead; // Always the head
};

template <typename T>
void Collection<T>::addItem(const T& item) {
	node<T> *tmp = new node<T>; // tmp node-pointer
	tmp->setData(item); // populate tmp node data
	tmp->setNext(listHead); // populate tmp node pointer
	listHead = tmp;
}

template <typename T>
void Collection<T>::removeItem(const T& item) {
	node<T> *next = nullptr;
	node<T> *prev = nullptr;
	node<T> *curr = listHead;

	while (curr != nullptr) {
		next = curr->getNext();
		if (curr->getData() == item) {
			// remove node procedure
			if (prev != nullptr) // if prev is nullptr, we are at head node
				prev->setNext(curr->getNext()); // manage soon-to-be missing link in node-list
			delete curr; // delete current node with data equal to item
		}
		// if current hasnt been deleted, save current as previous
		if (curr != nullptr)
			prev = curr;
		curr = next; // move to next node

	}
}

template <typename T>
T Collection<T>::lastItem() {
	return listHead->getData();  // Head is always last item inserted
}

template <typename T>
void Collection<T>::printCollection() {
	node<T> *curr = listHead;
	
	while (curr != nullptr) {
		std::cout << curr->getData() << " ";
		curr = curr->getNext();
	}
	std::cout << std::endl;
}

template <typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs) {
	node<T> *lptr = lhs.listHead;
	node<T> *rptr = rhs.listHead;

	// Test if both are empty
	if (lptr == nullptr && rptr == nullptr)
		return true;
	// Test if one is empty and other isnt
	else if (lptr == nullptr && rptr != nullptr)
		return false;
	// Test if one is empty and other isnt
	else if (lptr != nullptr & rptr == nullptr)
		return false;
	// Check all nodes for equality'
	else {
		// Traverse nodes
		while (lptr != nullptr && rptr != nullptr) {
			if (lptr->getData() != rptr->getData()) {
				//std::cout << lptr->getData() << " " << rptr->getData();
				return false;
			}
			lptr = lptr->getNext();
			rptr = rptr->getNext();
		}
		// Handle different sized collections
		if (lptr == nullptr && rptr != nullptr)
			return false;
		else if (lptr != nullptr && rptr == nullptr)
			return false;
	}
	
	// if program reaches here, lists have equal nodes and equal sizes
	return true;
}

#endif // Collection_H_