#include <iostream>
#include <Windows.h>

#include "globals.h"
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "rus");

	DoublyLinkedList l1;
	l1.insertBack(1);
	l1.insertBack(3);
	l1.insertBack(5);
	l1.show();
	DoublyLinkedList l2;
	l2.insertBack(8);
	l2.insertBack(38);
	l2.insertBack(58);
	l2.show();
	l2.deleteNode(2);
	l2.show();
	DoublyLinkedList l3;
	l3 = l1 + l2;
	l3.show();

	DoublyLinkedList l4;
	l4.insertBack(0);
	l4.insertBack(3);
	l4.insertBack(5);
	cout << "l1 == l2 ?  ";
	l1 == l4;
	cout << "l1 != l2 ?  ";
	l1 != l4;
	cout << l1;

	DoublyLinkedList l5;
	cin >> l5;
	cout << l5;
	//cin.get();
	return 0;
}