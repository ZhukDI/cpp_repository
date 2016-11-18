/*
**	Построить класс для работы с односвязным списком. Элемент списка – действительное число.
**	Сформировать список, содержащий неубывающую последовательность чисел,
**	и преобразовать его так,чтобы последовательность была невозрастающей.
**	Для этого необходимо совершить переворот списка, т. е. такую переустановку указателей в списке,
**	при которой элементы его следуют друг за другом в обратном порядке.
*/
#include <iostream>
#include <clocale>
#include <Windows.h>//для русского вывода char-ов

using namespace std;

template <class Type>
struct listElement{
	Type element;
	listElement *Next;
};

template <class Type>
class List{
private:
	int listSize;
	listElement<Type> *Head;
public:
	List();
	~List();

	void addInBegining();
	void addInEnd();
	void addInPosition(int index);
	void removeByIndex(int index);
	void reverseList();
	bool isEmpty();
	void showList();

	listElement<Type> *findByIndex(int index);

};

template <class Type>
List<Type>::List()
{
	listSize = 0;
	Head = NULL;
}

template <class Type>
List<Type>::~List()
{
	while (!isEmpty()){
		removeByIndex(1);
	}
}

template <class Type>
bool List<Type>::isEmpty(){
	return bool(listSize == 0);
}

template <class Type>
void List<Type>::removeByIndex(int index){
	listElement<Type> *temp;
	if ((index < 1) || (index > listSize)){
		cout << "Неверный индекс!\n";
	}
	else{
		listSize--;
		if (index == 1){
			temp = Head;
			Head = Head->Next;
		}
		else{
			listElement<Type> *prev = findByIndex(index - 1);
			temp = prev->Next;
			prev->Next = temp->Next;
		}
		temp->Next = NULL;
		delete temp;
		temp = NULL;
	}
}

template <class Type>
listElement<Type> *List<Type>::findByIndex(int index){
	if ((index < 1) || (index > listSize)){
		return NULL;
	}
	else{
		listElement<Type> *temp = Head;
		for (int i = 1; i < index; i++){
			temp = temp->Next;
		}
		return temp;
	}
}

template <class Type>
void List<Type>::addInBegining(){
	Type element;
	cout << "Введите элемент: ";
	cin >> element;
	if (listSize != 0){
		while (element > Head->element){
			cout << "Введите элемент который не больше чем ";
			cout << Head->element << ": " << endl;
			cin >> element;
		}
	}
	listSize++;
	listElement<Type> *newElement = new listElement<Type>;
	newElement->element = element;
	newElement->Next = Head;
	Head = newElement;
}

template <class Type>
void List<Type>::addInEnd(){
	Type element;
	cout << "Введите элемент: ";
	cin >> element;
	if (listSize != 0){
		while (element < findByIndex(listSize)->element){
			cout << "Введите элемент который не меньше чем ";
			cout << findByIndex(listSize)->element << ": " << endl;
			cin >> element;
		}
	}
	listElement<Type> *newElement = new listElement<Type>;
	newElement->element = element;
	if (listSize == 0){
		Head = newElement;
		newElement->Next = NULL;
	}
	else{
		listElement<Type> *prev = findByIndex(listSize);
		newElement->Next = NULL;
		prev->Next = newElement;
	}
	listSize++;
}

template <class Type>
void List<Type>::addInPosition(int index){
	Type element;
	cout << "Введите элемент: ";
	cin >> element;
	if (listSize != 0){
		if (index == 0){
			while (element > Head->element){
				cout << "Введите элемент который не больше чем ";
				cout << Head->element << ": " << endl;
				cin >> element;
			}
		}
		if (index == listSize + 1){
			while (element < findByIndex(listSize)->element){
				cout << "Введите элемент который не меньше чем ";
				cout << findByIndex(listSize)->element << ": " << endl;
				cin >> element;
			}
		}
		else{
			while (!(element <= findByIndex(index)->element && element >= findByIndex(index - 1)->element)){
				cout << "Введите элемент который не меньше " << findByIndex(index - 1)->element
					<< " и не больше " << findByIndex(index)->element << " ";
				cin >> element;
			}
		}
	}
	int newLength = listSize + 1;
	if ((index < 1) || (index > newLength)){
		cout << "Неверный индекс!\n";
	}
	else{
		listElement<Type> *newElement = new listElement<Type>;
		listSize = newLength;
		newElement->element = element;
		if (index == 1){
			newElement->Next = Head;
			Head = newElement;
		}
		else{
			listElement<Type> *prev = findByIndex(index - 1);
			newElement->Next = prev->Next;
			prev->Next = newElement;
		}
	}
}

template <class Type>
void List<Type>::reverseList(){
	listElement<Type> *temp;
	listElement<Type> *tempHead = findByIndex(listSize);
	for (int i = 0; i < listSize - 1; i++)
	{
		temp = findByIndex(listSize - i);
		temp->Next = findByIndex(listSize - i - 1);
	}
	Head = tempHead;
	findByIndex(listSize)->Next = NULL;
}

template <class Type>
void List<Type>::showList(){
	if (!listSize){
		cout << "Список пуст\n";
	}
	else{
		cout << "Элементы списка:\n";
		listElement<Type> *head = Head;
		while (head != NULL){
			cout << head->element << " ";
			head = head->Next;
		}
		cout << '\n';
	}
}

int main()
{
	SetConsoleCP(1251);//для русского вывода char-ов
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	int index;

	List<double> l1;

	int pick;
	do{
		cout << "1. Добавить элемент в начало\n";
		cout << "2. Добавить элемент в конец\n";
		cout << "3. Добавить элемент на заданную позицию\n";
		cout << "4. Вывести список\n";
		cout << "5. Удалить элемент с заданной позиции\n";
		cout << "6. Преобразовать в невозрастающую последовательность\n";
		cout << "0. Выход\n";
		cin >> pick;
		switch (pick){
		case 0: {return 1; }
		case 1: {
					l1.addInBegining();
					break;
		}
		case 2: {
					l1.addInEnd();
					break;
		}
		case 3: {
					cout << "Введите позицию:\n";
					cin >> index;
					l1.addInPosition(index);
					l1.showList();
					break;
		}
		case 4: {
					l1.showList();
					break;
		}
		case 5: {
					cout << "Введите позицию: ";
					cin >> index;
					l1.removeByIndex(index);
					l1.showList();
					break;
		}
		case 6: {
					cout << "Преобразованный список: ";
					l1.reverseList();
					l1.showList();
					break;
		}
		default: {cout << "Ошибка! Попробуйте снова\n"; break; }
		}
	} while (pick != 0);

	cin.get();
	return 0;
}