#include <iostream>
#include <Windows.h>

using namespace std;

typedef unsigned int uint;

struct Node
{
	int data;
	Node* next;
	Node* prev;

	Node() : data(0), next(NULL), prev(NULL) {}
	Node(int value) : data(value), next(NULL), prev(NULL) {}
};


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

DoublyLinkedList::DoublyLinkedList() : size(0), head(NULL), tail(NULL) {}

DoublyLinkedList::~DoublyLinkedList()
{
	deleteAll();
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList &otherList){
	head = tail = NULL;
	size = 0;

	Node* tmpNode = otherList.head;
	while (tmpNode != NULL){
		insertBack(tmpNode->data);
		tmpNode = tmpNode->next;
	}
}

bool DoublyLinkedList::isEmpty(){
	return bool(size == 0);
}

void DoublyLinkedList::insertFront(int value){
	Node* tmpNode = new Node(value);
	if (head == NULL)
		head = tail = tmpNode;
	else{
		head->prev = tmpNode;
		tmpNode->next = head;
		head = tmpNode;
	}
	size++;
}

void DoublyLinkedList::insertBack(int value){
	Node* tmpNode = new Node(value);
	if (head == NULL)
		head = tail = tmpNode;
	else{
		tail->next = tmpNode;
		tmpNode->prev = tail;
		tail = tmpNode;
	}
	size++;
}

void DoublyLinkedList::deleteFront(){
	if (!isEmpty()){
		Node* tmpNode = head;
		head = head->next;
		//head->prev = NULL;
		delete tmpNode;
		size--;
	}
}

void DoublyLinkedList::deleteBack(){
	if (!isEmpty()){
		Node* tmpNode = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete tmpNode;
		size--;
	}
}

void DoublyLinkedList::deleteNode(int index){
	if (!isEmpty()){
		//Node* tmpNode = head;
		Node* delNode = findByIndex(index);
		Node* prevDel = delNode->prev;
		Node* nextDel = delNode->next;
		if (prevDel != NULL && size != 1)
			prevDel->next = nextDel;
		if (nextDel != NULL && size != 1)
			nextDel->prev = prevDel;
		if (index == 1)
			head = nextDel;
		if (index == size)
			tail = prevDel;
		delete delNode;
		size--;
	}
	else
		cout << "Неверный индекс!" << endl;

}

void DoublyLinkedList::deleteAll()
{
	// Пока остаются элементы, удаляем по одному с головы
	while (size != 0){
		deleteNode(1);
		//cout << "Удалил узел!\n";
	}
}

void DoublyLinkedList::show(){
	if (!size){
		cout << "Список пуст\n";
	}
	else{
		cout << "Элементы списка:\n";
		Node *tmpNode = head;
		while (tmpNode != NULL){
			cout << tmpNode->data << " -> ";
			tmpNode = tmpNode->next;
		}
		cout << "NULL\n";
	}
}

Node *DoublyLinkedList::findByIndex(int index){
	if ((index < 1) || (index > size)){
		return NULL;
	}
	else{
		Node *tmpNode = head;
		for (int i = 1; i < index; i++){
			tmpNode = tmpNode->next;
		}
		return tmpNode;
	}
}

DoublyLinkedList & DoublyLinkedList::operator = (const DoublyLinkedList & otherList)
{
	// Проверка присваивания элемента "самому себе"
	if (this == &otherList)
		return *this;
	// удаление старого списка
	this->deleteAll(); 

	Node * tmpNode = otherList.head;

	// Копируем элементы
	while (tmpNode != NULL)
	{
		insertBack(tmpNode->data);
		tmpNode = tmpNode->next;
	}

	return *this;
}

DoublyLinkedList DoublyLinkedList::operator + (const DoublyLinkedList & otherList){
	DoublyLinkedList result = *this;
	Node *tmpNode = otherList.head;

	while (tmpNode != NULL){
		result.insertBack(tmpNode->data);
		tmpNode = tmpNode->next;
	}
	return result;
}

void DoublyLinkedList::operator == (const DoublyLinkedList & otherList){
	if (size == otherList.size){
		Node *tmpNode = head;
		Node *otherTmpNode = otherList.head;
		while (tmpNode != NULL){
			if (tmpNode->data != otherTmpNode->data)
				break;
			tmpNode = tmpNode->next;
			otherTmpNode = otherTmpNode->next;
		}
		if (tmpNode == NULL)
			cout << "Равны\n";
		else
			cout << "Не равны\n";
	}
	else
		cout << "Не равны\n";
}

void DoublyLinkedList::operator != (const DoublyLinkedList & otherList){
	if (size == otherList.size){
		Node *tmpNode = head;
		Node *otherTmpNode = otherList.head;
		while (tmpNode != NULL){
			if (tmpNode->data != otherTmpNode->data)
				break;
			tmpNode = tmpNode->next;
			otherTmpNode = otherTmpNode->next;
		}
		if (tmpNode == NULL)
			cout << "Равны\n";
		else
			cout << "Не равны\n";
	}
	else
		cout << "Не равны\n";
}

ostream& operator<<(ostream & os, const DoublyLinkedList & list){
	if (!list.size){
		os << "Список пуст\n";
	}
	else{
		os << "Элементы списка:\n";
		Node *tmpNode = list.head;
		while (tmpNode != NULL){
			os << tmpNode->data << " -> ";
			tmpNode = tmpNode->next;
		}
		os << "NULL\n";
	}
	return os;
}

istream& operator>> (istream & is, DoublyLinkedList & list)
{
	cout << "Количество элементов списка: ";
	int i, tmp;
	cin >> i;
	while (i > 0){
		cout << "Введите элемент: ";
		cin >> tmp;
		list.insertBack(tmp);
		i--;
	}
	return is;
}

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