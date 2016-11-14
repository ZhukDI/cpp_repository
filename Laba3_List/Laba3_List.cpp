/*
**	��������� ����� ��� ������ � ����������� �������. ������� ������ � �������������� �����.
**	������������ ������, ���������� ����������� ������������������ �����,
**	� ������������� ��� ���,����� ������������������ ���� ��������������.
**	��� ����� ���������� ��������� ��������� ������, �. �. ����� ������������� ���������� � ������,
**	��� ������� �������� ��� ������� ���� �� ������ � �������� �������.
*/
#include <iostream>
#include <clocale>
#include <Windows.h>//��� �������� ������ char-��

using namespace std;

struct listElement{
	double element;
	listElement *Next;
};

class List{
private:
	int listSize;
	listElement *Head;
public:
	List();
	~List();

	void addInBegining(double element);
	void addInEnd(double element);
	void addInPosition(int index, double element);
	void removeByIndex(int index);
	void reverseList();
	bool isEmpty();
	void showList();

	listElement *findByIndex(int index);

};

List::List()
{
	listSize = 0;
	Head = NULL;
}

List::~List()
{
	while (!isEmpty()){
		removeByIndex(1);
	}
}

bool List::isEmpty(){
	return bool(listSize == 0);
}

void List::removeByIndex(int index){
	listElement *temp;
	if ((index < 1) || (index > listSize)){
		cout << "�������� ������!\n";
	}
	else{
		listSize--;
		if (index == 1){
			temp = Head;
			Head = Head->Next;
		}
		else{
			listElement *prev = findByIndex(index - 1);
			temp = prev->Next;
			prev->Next = temp->Next;
		}
		temp->Next = NULL;
		delete temp;
		temp = NULL;
	}
}

listElement *List::findByIndex(int index){
	if ((index < 1) || (index > listSize)){
		return NULL;
	}
	else{
		listElement *temp = Head;
		for (int i = 1; i < index; i++){
			temp = temp->Next;
		}
		return temp;
	}
}

void List::addInBegining(double element){
	if (listSize != 0){
		while (element > Head->element){
			cout << "������� ������� ������� �� ������ ��� ";
			cout << Head->element << ": " << endl;
			cin >> element;
		}
	}
	listSize++;
	listElement *newElement = new listElement;
	newElement->element = element;
	newElement->Next = Head;
	Head = newElement;
}

void List::addInEnd(double element){
	if (listSize != 0){
		while (element < findByIndex(listSize)->element){
			cout << "������� ������� ������� �� ������ ��� ";
			cout << findByIndex(listSize)->element << ": " << endl;
			cin >> element;
		}
	}
	listElement *newElement = new listElement;
	newElement->element = element;
	if (listSize == 0){
		Head = newElement;
		newElement->Next = NULL;
	}
	else{
		listElement *prev = findByIndex(listSize);
		newElement->Next = NULL;
		prev->Next = newElement;
	}
	listSize++;
}

void List::addInPosition(int index, double element){
	if (listSize != 0){
		if (index == 0){
			while (element > Head->element){
				cout << "������� ������� ������� �� ������ ��� ";
				cout << Head->element << ": " << endl;
				cin >> element;
			}
		}
		if (index == listSize + 1){
			while (element < findByIndex(listSize)->element){
				cout << "������� ������� ������� �� ������ ��� ";
				cout << findByIndex(listSize)->element << ": " << endl;
				cin >> element;
			}
		}
		else{
			while (!(element <= findByIndex(index)->element && element >= findByIndex(index - 1)->element)){
				cout << "������� ������� ������� �� ������ " << findByIndex(index - 1)->element 
					<< " � �� ������ " << findByIndex(index)->element<<" ";
				cin >> element;
			}
		}
	}
	int newLength = listSize + 1;
	if ((index < 1) || (index > newLength)){
		cout << "�������� ������!\n";
	}
	else{
		listElement *newElement = new listElement;
		listSize = newLength;
		newElement->element = element;
		if (index == 1){
			newElement->Next = Head;
			Head = newElement;
		}
		else{
			listElement *prev = findByIndex(index - 1);
			newElement->Next = prev->Next;
			prev->Next = newElement;
		}
	}
}

void List::reverseList(){
	listElement *temp;
	listElement *tempHead = findByIndex(listSize);
	for (int i = 0; i < listSize-1; i++)
	{
		temp = findByIndex(listSize-i);
		temp->Next = findByIndex(listSize - i-1);
	}
	Head = tempHead;
	findByIndex(listSize)->Next = NULL;
}

void List::showList(){
	if (!listSize){
		cout << "������ ����\n";
	}
	else{
		cout << "�������� ������:\n";
		listElement *head = Head;
		while (head != NULL){
			cout << head->element << " ";
			head = head->Next;
		}
		cout << '\n';
	}
}

int main()
{
	SetConsoleCP(1251);//��� �������� ������ char-��
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	cout << "������ ���!" << endl;
	int index;
	double element;
	List l1;

	int pick;
	do{
		cout << "1. �������� ������� � ������\n";
		cout << "2. �������� ������� � �����\n";
		cout << "3. �������� ������� �� �������� �������\n";
		cout << "4. ������� ������\n";
		cout << "5. ������� ������� � �������� �������\n";
		cout << "6. ������������� � �������������� ������������������\n";
		cout << "0. �����\n";
		cin >> pick;
		switch (pick){
		case 0: {return 1; }
		case 1: {
					cout << "������� �������: ";
					cin >> element;
					l1.addInBegining(element);
					break;
		}
		case 2: {
					cout << "������� �������: ";
					cin >> element;
					l1.addInEnd(element);
					break;
		}
		case 3: {
					cout << "������� �������:\n";
					cin >> index;
					cout << "������� �������:\n";
					cin >> element;
					l1.addInPosition(index, element);
					l1.showList();
					break;
		}
		case 4: {				
					l1.showList();
					break;
		}
		case 5: {
					cout << "������� �������: ";
					cin >> index;
					l1.removeByIndex(index);
					l1.showList();
					break;
		}
		case 6: {
					cout << "��������������� ������: ";
					l1.reverseList();
					l1.showList();
					break;
		}
		default: {cout << "������! ���������� �����\n"; break; }
		}
	} while (pick != 0);

	cin.get();
	return 0;
}