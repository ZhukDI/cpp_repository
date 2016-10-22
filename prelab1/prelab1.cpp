/*Создать класс Vector размерности  . Перегрузить операции ввода/вывода. 
Объявить массив из   объектов. Каждую из пар векторов передать в функцию, определяющую,
будут эти векторы коллинеарными или ортогональными. Вывести коллинеарные или ортогональные векторы.*/

#include <iostream> 
#include <clocale> 
#include <ctime>
#include <Windows.h>//для русского вывода char-ов 

using namespace std;

class Vector {
private:
	unsigned int n; //размерность
	int *arr; //массив координат
	 
public:
	Vector();
	Vector(unsigned int); 
	Vector(unsigned int, int *);
	Vector(const Vector &);
	~Vector();

	void ShowVector();

	friend ostream& operator<<(ostream& os, const Vector& vc);
	friend istream& operator>> (istream& is, Vector& vc);
	friend void isCollinear(Vector v1, Vector v2);
	friend void isOrthogonal(Vector v1, Vector v2);	
};

Vector::Vector() {
	n = 2;
	arr = new int[n];
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 5;
	}
}

Vector::Vector(unsigned int n)
{
	this->n = n;
	cout << "Заполнение вектора элементами:" << endl;
	arr = new int[n];
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 5;
	}
}
Vector::Vector(unsigned int n, int*s_arr)
{
	this->n = n;
	arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = s_arr[i];
	}
}

Vector::Vector(const Vector &v)
{
	n = v.n;
	arr = new int[n];
	for (int i = 0; i <= n; i++)
		arr[i] = v.arr[i];
}
void Vector::ShowVector()
{
	cout << "Вектор с координатами: (";
	for (int i = 0; i < n-1; i++) {
		cout << arr[i] << ", ";
	}
	cout << arr[n-1];
	cout << ")" << endl;
}

Vector::~Vector()
{
	delete[] arr;
}

ostream& operator<<(ostream& os, const Vector& vc)
{
	os << "(";
	for (int i = 0; i < vc.n-1; i++)
	{
		os << vc.arr[i] << ", ";
	}
	os << vc.arr[vc.n - 1]<<")";
	return os;
}

istream& operator>> (istream& is, Vector& vc)
{
	cout << "Размерность вектора: ";
	is>> vc.n;
	vc.arr = new int[vc.n];
	cout << "Введите координаты вектора" << endl;
	for (int i = 0; i < vc.n; i++)
	{
		cout << "a" << i << ":  ";
		is >> vc.arr[i];
	}
	return is;
}

void isCollinear(Vector v1, Vector v2)
{
	bool  coll = true;
	if (v1.n != v2.n){
		cout << "Векторы разной размерности"<<endl;
		coll = false;
	}
	int n = v1.n;//размерность векторов;
	for (int i = 0, k = 0; i < n-1 && coll; i++)
	{
		if (v1.arr[i] * v2.arr[i + 1] == v1.arr[i + 1] * v2.arr[i]){
			k++;
		}
		else{
			coll = false;
		}
		if (k == n - 1)
		{
			coll = true;
		}
	}
	if (coll == true){
		cout << "Векторы " << v1 << " и " << v2 << " коллинеарны" << endl;
	}
	//else
	//	cout << "Векторы неколлинеарны" << endl;

}

void isOrthogonal(Vector v1, Vector v2)
{
	bool  ort = true;
	if (v1.n != v2.n){
		cout << "Векторы разной размерности" << endl;
		ort = false;
	}
	int n = v1.n;
	int sum = 0;
	for (int i = 0; i < n && ort; i++)
	{
		sum += v1.arr[i] * v2.arr[i];
	}
	if (ort == true && sum == 0){
		cout << "Векторы " << v1 << " и " << v2 << " ортогональны" << endl;
	}
	//else
	//	cout << "Векторы неортогональны" << endl;
}

int main()
{
	SetConsoleCP(1251);//для русского вывода char-ов 
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	Vector *vector_spis;
	vector_spis = new Vector[0];
	int n;
	int pick;
	do{
		cout << "1. Инициализировать векторы\n";
		cout << "2. Вывести векторы\n";
		cout << "3. Вывести пары коллинеарных векторов\n";
		cout << "4. Вывести пары ортогональных векторов\n";
		cout << "0. Выход\n";
		cin >> pick;
		switch (pick){
		case 0: {return 1; }
		case 1: {
					cout << "Инициализация векторов" << endl;
					cout << "Введите количество векторов: ";
					cin >> n;
					vector_spis = new Vector[n];
					for (int i = 0; i < n; i++)
					{
						cin >> vector_spis[i];
					}
					break;
		}
		case 2: {
					cout << "Вывод векторов" << endl;
					for (int i = 0; i < n; i++)
					{
						cout << i << ") " << vector_spis[i] << endl;
					}
					break;
		}
		case 3: {
					for (int i = 0; i < n - 1; i++){
						for (int j = i; j < n - 1; j++){
							isCollinear(vector_spis[i], vector_spis[j + 1]);
						}
					}
					break;
		}
		case 4: {
					for (int i = 0; i < n - 1; i++){
						for (int j = i; j < n - 1; j++){
							isOrthogonal(vector_spis[i], vector_spis[j + 1]);
						}
					}
					break;
		}
		default: {cout << "Ошибка! Попробуйте снова\n"; break; }
		}
	} while (pick != 0);
	return 0;
}