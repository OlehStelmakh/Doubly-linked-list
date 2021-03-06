#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
class List2 {
public:

	int GetSize() { return Size; } //returns the size of the list
	void clear(); //removes all elements from the list
	void push_front(T data); //inserts an element as the first one
	void push_back(T data); //inserts an element as the last one
	void pop_front(); //delete the first element
	void pop_back(); //delete the last element
	void insert(T data, int index); //insert element by index
	void removeAt(int index); //delete element by index
	T & operator [] (const int index); // overloaded operator []
	void PrintFromHead(); //print from the beginning of the list
	void PrintFromTail(); // print from the end of the list

	List2 <T>();
	~List2 <T>();

private:

	template <typename T>
	class Node {
	public:
		Node(T data = T(), Node *pNext = nullptr, Node *pPrev = nullptr) {
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}

		T data;
		Node *pNext;
		Node *pPrev;
	};

	Node <T> *head;
	Node <T> *tail;
	int Size;
};

template <typename T> List2 <T>::List2() {
	head = nullptr;
	tail = nullptr;
	Size = 0;
}

template <typename T> List2 <T>::~List2() {
	clear();
}

template<typename T>
void List2<T>::clear() {
	while (Size) {
		pop_front();
	}
}

template <typename T>
void List2 <T>::push_front(T data) {
	if (Size > 1) {
		Node <T> *temp = head;
		head = new Node <T>(data, head);
		temp->pPrev = head;
	}
	else if (Size == 1) {
		head = new Node <T>(data, head);
		tail->pPrev = this->head;
	}
	else {
		head = tail = new Node <T>(data, head, tail);
	}
	Size++;
}

template <typename T>
void List2 <T>::push_back(T data) {
	if (Size > 1) {
		Node <T> *temp = tail;
		tail = new Node <T>(data, nullptr, tail);
		temp->pNext = tail;
	}
	else if (Size == 1) {
		tail = new Node <T>(data, nullptr, tail);
		head->pNext = this->tail;
	}
	else {
		head = tail = new Node <T>(data, head, tail);
	}
	Size++;
}

template <typename T>
void List2 <T>::pop_front() {
	if (Size > 1) {
		Node <T> *temp = head;
		head = head->pNext;
		delete temp;
	}
	else if (Size == 1) {
		Node <T> *temp = head;
		tail = head = head->pNext;
		delete temp;
	}
	Size--;
}

template <typename T>
void List2<T>::pop_back() {
	if (Size > 1) {
		Node <T> *temp = tail;
		tail = tail->pPrev;
		delete temp;
	}
	else if (Size == 1) {
		Node <T> *temp = tail;
		tail = head = tail->pPrev;
		delete temp;
	}

	Size--;
}

template <typename T>
void List2 <T>::insert(T data, int index) {
	if (index == 0) push_front(data);

	else if (index == Size || index > Size) {
		push_back(data);
	}

	else if (index <= Size / 2) {
		Node<T> *previous = this->head;
		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;
		}

		Node<T> *newNode = new Node<T>(data, previous->pNext, previous);

		previous->pNext = newNode;
		Node<T> *next = newNode->pNext;
		next->pPrev = newNode;

		Size++;
	}

	else if (index > Size / 2) {
		Node<T> *next = this->tail;
		for (int i = Size - 1; index < i; i--) {
			next = next->pPrev;
		}

		Node<T> *newNode = new Node<T>(data, next, next->pPrev);

		next->pPrev = newNode;
		Node<T> *previous = newNode->pPrev;
		previous->pNext = newNode;

		Size++;
	}
}

template <typename T>
void List2 <T>::removeAt(int index) {
	if (index == 0) {
		pop_front();
	}
	else if (index == Size || index > Size) {
		pop_back();
	}

	else if (index <= Size / 2) {
		Node<T> *previous = this->head;
		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;
		}

		Node<T> *toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		Node<T> *next = toDelete->pNext;
		delete toDelete;
		next->pPrev = previous;

		Size--;
	}

	else if (index > Size / 2) {
		Node<T> *next = this->tail;
		for (int i = Size - 1; index < i; i--) {
			next = next->pPrev;
		}

		Node<T> *toDelete = next->pPrev;
		next->pPrev = toDelete->pPrev;
		Node<T> *previous = toDelete->pPrev;
		delete toDelete;
		previous->pNext = next;

		Size--;
	}
}

template <typename T>
T & List2 <T>::operator[] (const int index) {
	if (index <= Size / 2) {
		int counter = 0;
		Node <T> *current = this->head;

		while (current != nullptr) {
			if (counter == index) {
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}
	else {
		int counter = Size - 1;
		Node <T> *current = this->tail;

		while (current != nullptr) {
			if (counter == index) {
				return current->data;
			}
			current = current->pPrev;
			counter--;
		}
	}
}

template <typename T>
void List2 <T>::PrintFromHead() {
	cout << "\nList (from head):\n[ ";
	Node <T> *print = head;
	while (print) {
		cout << print->data << " ";
		print = print->pNext;
	}
	cout << "]" << endl;
}

template <typename T>
void List2 <T>::PrintFromTail() {
	cout << "\nList (from tail):\n[ ";
	Node <T> *print = tail;
	while (print) {
		cout << print->data << " ";
		print = print->pPrev;
	}
	cout << "]" << endl;
}

int main() {
	List2 <int> lst;

	int sizeOfList;
	cout << "Input a quantity of numbers: ";
	cin >> sizeOfList;

	srand(time(0));
	for (int i = 0; i < sizeOfList; i++) {
		lst.push_back(rand() % 10);
	}

	lst.PrintFromHead();
	lst.PrintFromTail();

	system("pause");
	return 0;
}