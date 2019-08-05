#ifndef CS2_STACK_HPP_
#define CS2_STACK_HPP_
////////////////////////////////////////////////////////////////////////////
//
// File: stack.hpp
//
// Programmer:
// Updated:    3/2019
//
//
//
//

#include <new>
#include <cassert>

////////////////////////////////////////////////////////////////////////////
//           
template<typename T> 
class Node {
	public:
		Node() : data(), next(nullptr) {};
		Node(const T &item) : data(item), next(nullptr) {};
		Node<T>* getNext() { return next; };
		T getNodeData() { return data; };
		void setNodeData(T anItem) { data = anItem; };
		void setNext(Node<T>* aNext) { next = aNext; };
	private:
		T data;
		Node<T> *next;
};


////////////////////////////////////////////////////////////////////////////
// CLASS INV:
//
//    
template <typename T>
class stack {
	public:
		stack();
		stack(const stack<T>&);
		~stack();
		void swap(stack<T>&);
		stack<T>& operator= (stack<T>);
		bool empty() const { return tos == nullptr; };
		bool full() const;
		T top() const { if (height != 0) return tos->getNodeData(); };
		T pop();
		void push(const T&);
		int getHeight() const { return height; };

		bool operator == (const stack<T>&) const;
		bool operator != (const stack<T>& rhs) const { return !(*this == rhs); };
	private:
		Node<T>   *tos;
		int height;
};

template <typename T> stack<T>::stack() {
	tos = nullptr;
	height = 0;
}
template<typename T> stack<T>::stack(const stack<T>&actual) {
	Node<T> *bot, *tmptop, *tmpNode;
	tmptop = actual.tos;
	tos = nullptr;
	height = actual.height;
	while (tmptop != nullptr) {
		tmpNode = new Node<T>(tmptop->getNodeData());
		if (tos == nullptr) {
			tos = tmpNode;
		} else {
			bot->setNext(tmpNode);
		}

		bot = tmpNode;
		tmptop = tmptop->getNext();
	}
}
template<typename T> stack<T>::~stack() {
	while (tos != nullptr) {
		Node<T> *tmp = tos;
		tos = tos->getNext();
		delete tmp;
	}
	height = 0;
}
template<typename T> void stack<T>::swap(stack<T>&rhs) {
	Node<T> *tmp = tos;
	int tmpHeight = height;

	tos = rhs.tos;
	height = rhs.height;

	rhs.tos = tmp;
	rhs.height = tmpHeight;
}
template <typename T> stack<T>&stack<T>::operator=(stack<T> rhs) {
	swap(rhs);
	return *this;
}
template<typename T> bool stack<T>::full() const {
	Node<T> *tmp = new(std::nothrow) Node<T>();

	if (tmp == nullptr) {
		return 1;
	}
	delete tmp;
	return 0;
}
template<typename T> T stack<T>::pop() {
	assert(tos != nullptr);

	Node<T> *tmp = tos;
	
	T result = tos->getNodeData();
	
	tos = tos->getNext();
	height--;

	delete tmp;
	return result;
}
template<typename T> void stack<T>::push(const T& item) {
	assert(!full());

	Node<T> *tmp = new Node<T>(item);

	tmp->setNext(tos);

	tos = tmp;
	height++;
}
template<typename T> bool stack<T>::operator == (const stack<T>& rhs) const {
	if (height != rhs.height) {
		return 0;
	}

	stack<T> left(*this), right(rhs);

	while (!left.empty() && !right.empty()) {
		if (left.pop() != right.pop()) {
			return 0;
		}
	}

	return 1;
}
#endif

