#include <iostream>
#include <Windows.h>

using namespace std;

typedef unsigned int uint;

template <class Type>
struct Node
{
	Type data;
	Node* next;
	Node* prev;

	Node() : data(0), next(NULL), prev(NULL) {}
	Node(Type value) : data(value), next(NULL), prev(NULL) {}
};

template <class Type>
class DoublyLinkedList
{
private:
	uint size;
	Node<Type> *head;
	Node<Type> *tail;

public:
	DoublyLinkedList();
	~DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList &);

	void insertFront(Type);
	void insertBack(Type);
	void deleteFront();
	void deleteBack();
	void deleteNode(int);//удаление по индексу
	void deleteAll();
	bool isEmpty();
	void show();
	Node<Type> *findByIndex(int);

	DoublyLinkedList & operator = (const DoublyLinkedList &);
	DoublyLinkedList operator + (const DoublyLinkedList &);//слияние двух списков
	void operator == (const DoublyLinkedList &);
	void operator != (const DoublyLinkedList &);
	friend ostream& operator << <Type>(ostream & os, const DoublyLinkedList &);
	friend istream& operator >> <Type>(istream & is, DoublyLinkedList<Type> &);
};

template <class Type>
DoublyLinkedList<Type>::DoublyLinkedList() : size(0), head(NULL), tail(NULL) {}

template <class Type>
DoublyLinkedList<Type>::~DoublyLinkedList()
{
	deleteAll();
}

template <class Type>
DoublyLinkedList<Type>::DoublyLinkedList(const DoublyLinkedList &otherList){
	head = tail = NULL;
	size = 0;

	Node<Type>* tmpNode = otherList.head;
	while (tmpNode != NULL){
		insertBack(tmpNode->data);
		tmpNode = tmpNode->next;
	}
}

template <class Type>
bool DoublyLinkedList<Type>::isEmpty(){
	return bool(size == 0);
}

template <class Type>
void DoublyLinkedList<Type>::insertFront(Type value){
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

template <class Type>
void DoublyLinkedList<Type>::insertBack(Type value){
	Node<Type>* tmpNode = new Node<Type>(value);
	if (head == NULL)
		head = tail = tmpNode;
	else{
		tail->next = tmpNode;
		tmpNode->prev = tail;
		tail = tmpNode;
	}
	size++;
}

template <class Type>
void DoublyLinkedList<Type>::deleteFront(){
	if (!isEmpty()){
		Node* tmpNode = head;
		head = head->next;
		//head->prev = NULL;
		delete tmpNode;
		size--;
	}
}

template <class Type>
void DoublyLinkedList<Type>::deleteBack(){
	if (!isEmpty()){
		Node* tmpNode = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete tmpNode;
		size--;
	}
}

template <class Type>
void DoublyLinkedList<Type>::deleteNode(int index){
	if (!isEmpty()){
		//Node* tmpNode = head;
		Node<Type>* delNode = findByIndex(index);
		Node<Type>* prevDel = delNode->prev;
		Node<Type>* nextDel = delNode->next;
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

template <class Type>
void DoublyLinkedList<Type>::deleteAll()
{
	// Пока остаются элементы, удаляем по одному с головы
	while (size != 0){
		deleteNode(1);
		//cout << "Удалил узел!\n";
	}
}

template <class Type>
void DoublyLinkedList<Type>::show(){
	if (!size){
		cout << "Список пуст\n";
	}
	else{
		cout << "Элементы списка:\n";
		Node<Type> *tmpNode = head;
		while (tmpNode != NULL){
			cout << tmpNode->data << " -> ";
			tmpNode = tmpNode->next;
		}
		cout << "NULL\n";
	}
}

template <class Type>
Node<Type> *DoublyLinkedList<Type>::findByIndex(int index){
	if ((index < 1) || (index > size)){
		return NULL;
	}
	else{
		Node<Type> *tmpNode = head;
		for (int i = 1; i < index; i++){
			tmpNode = tmpNode->next;
		}
		return tmpNode;
	}
}

template <class Type>
DoublyLinkedList<Type> & DoublyLinkedList<Type>::operator = (const DoublyLinkedList<Type> & otherList)
{
	// Проверка присваивания элемента "самому себе"
	if (this == &otherList)
		return *this;
	// удаление старого списка
	this->deleteAll();

	Node<Type> * tmpNode = otherList.head;

	// Копируем элементы
	while (tmpNode != NULL)
	{
		insertBack(tmpNode->data);
		tmpNode = tmpNode->next;
	}

	return *this;
}

template <class Type>
DoublyLinkedList<Type> DoublyLinkedList<Type>::operator + (const DoublyLinkedList<Type> & otherList){
	DoublyLinkedList result = *this;
	Node<Type> *tmpNode = otherList.head;

	while (tmpNode != NULL){
		result.insertBack(tmpNode->data);
		tmpNode = tmpNode->next;
	}
	return result;
}

template <class Type>
void DoublyLinkedList<Type>::operator == (const DoublyLinkedList<Type> & otherList){
	if (size == otherList.size){
		Node<Type> *tmpNode = head;
		Node<Type> *otherTmpNode = otherList.head;
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

template <class Type>
void DoublyLinkedList<Type>::operator != (const DoublyLinkedList<Type> & otherList){
	if (size == otherList.size){
		Node<Type> *tmpNode = head;
		Node<Type> *otherTmpNode = otherList.head;
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

template <class Type>
ostream& operator<<(ostream & os, const DoublyLinkedList<Type> & list){
	if (!list.size){
		os << "Список пуст\n";
	}
	else{
		os << "Элементы списка:\n";
		Node<Type> *tmpNode = list.head;
		while (tmpNode != NULL){
			os << tmpNode->data << " -> ";
			tmpNode = tmpNode->next;
		}
		os << "NULL\n";
	}
	return os;
}

template <class Type>
istream& operator>> (istream & is, DoublyLinkedList<Type> & list)
{
	cout << "Количество элементов списка: ";
	int i;
	Type tmp;
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

	DoublyLinkedList<double> l1;
	l1.insertBack(1);
	l1.insertBack(3);
	l1.insertBack(5);
	l1.show();
	DoublyLinkedList<double> l2;
	l2.insertBack(8);
	l2.insertBack(38);
	l2.insertBack(58);
	l2.show();
	l2.deleteNode(2);
	l2.show();
	DoublyLinkedList<double> l3;
	l3 = l1 + l2;
	l3.show();

	DoublyLinkedList<double> l4;
	l4.insertBack(0);
	l4.insertBack(3);
	l4.insertBack(5);
	cout << "l1 == l2 ?  ";
	l1 == l4;
	cout << "l1 != l2 ?  ";
	l1 != l4;
	cout << l1;

	DoublyLinkedList<double> l5;
	cin >> l5;
	cout << l5;
	//cin.get();
	return 0;
}