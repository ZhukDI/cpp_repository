#pragma once

#include <iostream>
#include "globals.h"
#include "Node.h"

using namespace std;

class DoublyLinkedList
{
private:
	uint size;
	Node *head;
	Node *tail;

public:
	DoublyLinkedList();
	~DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList &);

	void insertFront(int);
	void insertBack(int);
	void deleteFront();
	void deleteBack();
	void deleteNode(int);//удаление по индексу
	void deleteAll();
	bool isEmpty();
	void show();
	Node *findByIndex(int);

	DoublyLinkedList & operator = (const DoublyLinkedList &);
	DoublyLinkedList operator + (const DoublyLinkedList &);//слияние двух списков
	void operator == (const DoublyLinkedList &);
	void operator != (const DoublyLinkedList &);
	friend ostream& operator<<(ostream & os, const DoublyLinkedList &);
	friend istream& operator>> (istream & is, DoublyLinkedList &);
};