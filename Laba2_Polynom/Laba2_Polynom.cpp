/*
Разработать класс «Многочлен» – Polynom степени n. Написать несколько конструкторов, 
в том числе конструктор копирования. Реализовать методы для вычисления значения полинома;
сложения, вычитания и умножения полиномов. Перегрузить операции сложения, вычитания, умножения,
инкремента, декремента, индексирования, присваивания. Создать массив объектов класса. 
Передать его в функцию, вычисляющую сумму полиномов массива и возвращающую полином-результат, 
который выводится на экран в головной программе.

Многочлен имеет вид: Kn*X^n + K(n-1)*X^(n-1) + ... + K1*X^1 + K0;
*/
#include <iostream>
#include <clocale>
#include <Windows.h>//для русского вывода char-ов

using namespace std;

class Polynom{
private:
	unsigned int deg; //степень полинома (многочлена)
	double *koef; //указатель на массив коэффициентов полинома

	void CorrectDeg(); // функция корректировки степени полинома

public:
	Polynom(); //конструктор без параметров
	Polynom(unsigned int); //полином с одним параметром                      
	Polynom(unsigned int, double*); //конструктор с параметрами
	Polynom(const Polynom &); //контсруктор копирования 
	Polynom::~Polynom(); //деструктор                                        

	void showPolynom();   //функция вывода полинома      getPolinom();
	unsigned int GetDeg(); //функция получения степени полинома
	double* GetKoef(); //функция получения коэффициента при i-й степени       
	void valueCalculation(); //вычисление значения при заданном x
	Polynom operator + (const Polynom &);   //оператор сложения двух полиномов           
	Polynom operator - (const Polynom &);	//оператор разности двух полиномов
	Polynom operator * (const Polynom &);   //оператор сложения двух полиномов 
	Polynom operator = (const Polynom &);   //оператор присваивания 

	Polynom &operator ++ ();  //Инкремент
	Polynom &operator -- ();  //Декремент
	double &operator[] (int); //перегрузка индексирования[]     
	
};

// конструктор без параметров: создается полином нулевой степени
// с коэффициентом при нулевой степени равным нулю
Polynom::Polynom(){
	deg = 0;
	koef = new double[deg + 1];
	koef[0] = 0.0;
}

// конструктор с одним параметром
Polynom::Polynom(unsigned int new_deg){
	deg = new_deg;
	koef = new double[deg + 1];
	for (int i = 0; i<deg; i++){
		cout << "K" << i << " = ";
		cin >> koef[i];
	}
	do{
		cout << "K" << deg << " = ";
		cin >> koef[deg];
		if (koef[deg] == 0)
			cout << "K" << deg << " must not be zero!\n";
	} while (!koef[deg]);
}

// конструктор с двумя параметрами
Polynom::Polynom(unsigned int new_deg, double *new_koef){
	deg = 0;
	for (int i = 0; i <= new_deg; i++)
		if (new_koef[i] != 0) 
			deg = i;   //инициализация переменной степени
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = new_koef[i]; //инициализация массива коэффициентов
}

//копирующий конструктор
Polynom::Polynom(const Polynom &f){
	deg = f.deg;
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = f.koef[i];
}

//деструктор
Polynom::~Polynom(){
	//cout << "Деструктор!" << endl;
	delete[] koef;
}

unsigned int Polynom::GetDeg()
{
	return deg;
}

//функция вывода полинома
void Polynom::showPolynom(){
	if (koef[deg] == 1)
		cout << "X^" << deg;
	else if (koef[deg] == -1)
		cout << "-X^" << deg;
	else
		cout << koef[deg] << "X^" << deg;
	for (int i = deg - 1; i>0; i--){
		if (koef[i]>0){
			if (koef[i] == 1)
				cout << " + " << "X^" << i;
			else
				cout << " + " << koef[i] << "X^" << i;
		}
		else if (koef[i]<0)
		if (koef[i] == -1)
			cout << " - " << "X^" << i;
		else
			cout << " - " << (-1)*koef[i] << "X^" << i;
	}

	if (koef[0]>0)
		cout << " + " << koef[0] << "\n";
	else if (koef[0]<0)
		cout << " - " << (-1)*koef[0] << "\n";
}

void Polynom::valueCalculation(){
	double x;
	cout << "Введите значение x: ";
	cin >> x;

	double res = 0;
	for (int i = GetDeg(); i > 0; i--){
		res += pow(x, i)*koef[i];
	}
	res += koef[0];

	cout << "Многочлен при x = " << x << " равен: " << res << endl;
}

double* Polynom::GetKoef(){
	return koef;
}




Polynom Polynom::operator + (const Polynom &t){
	int i;
	Polynom *result;

	if (deg >= t.deg){ //если степень первого полинома больше степени второго
		result = new Polynom(deg, koef);
		for (i = 0; i <= t.deg; i++)
			result->koef[i] = result->koef[i] + t.koef[i];
	}
	else{                   //если степень второго полинома больше степень первого
		result = new Polynom(t.deg, t.koef);
		for (i = 0; i <= deg; i++)
			result->koef[i] = result->koef[i] + koef[i];
	}
	result->CorrectDeg();
	return *result;
}

Polynom Polynom::operator - (const Polynom &t){
	int i;
	Polynom *result;

	if (deg >= t.deg){ //если степень первого полинома больше степени второго
		result = new Polynom(deg, koef);
		for (i = 0; i <= t.deg; i++)
			result->koef[i] = result->koef[i] - t.koef[i];
	}
	else{                   //если степень второго полинома больше степень первого
		result = new Polynom(t.deg, t.koef);
		for (i = 0; i <= deg; i++)
			result->koef[i] = koef[i] - result->koef[i];
		result->koef[i] = -result->koef[i];
	}
	result->CorrectDeg();
	return *result;
}

Polynom Polynom::operator * (const Polynom &t){
	
	Polynom *result;
	double *K = new double[deg+t.deg];
	result = new Polynom(deg + t.deg, K);
	for (int i = 0; i <= (deg + t.deg); i++)
	{
		result->koef[i] = 0;
	}
	double kk = 0, tk = 0;
	for (int i = 0; i <= deg + t.deg; i++)
	{
		for (int g = 0; g <= i; g++)
		{
			kk = koef[g];
			tk = t.koef[i - g];
			if (g >= deg + 1)
			{
				kk = 0;
			}
			if (i-g >= t.deg + 1)
			{
				tk = 0;
			}
			result->koef[i] = result->koef[i] + kk * tk;
		}
	}	
	result->CorrectDeg();
	return *result;
}

//оператор присваивания
Polynom Polynom::operator = (const Polynom &t){
	deg = t.deg;
	delete[] koef;
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = t.koef[i];
	return *this;
}

Polynom& Polynom::operator ++ ()
{
	double n = 0;
	cout << "Введите число, которое хотите прибавить к многочлену: ";
	cin >> n;
	koef[0] += n;
	return *this;
}

Polynom& Polynom::operator -- ()
{
	double n = 0;
	cout << "Введите число, которое хотите отнять от многочлена: ";
	cin >> n;
	koef[0] -= n;
	return *this;
}

double &Polynom::operator[] (int n)
{
	return koef[n];
}

// функция корректировки степени полинома: коэффициент 
// при максимальной степени должен быть ненулевым
void Polynom::CorrectDeg(){
	if (koef[deg] == 0){
		do{
			deg--;
		} while (deg && koef[deg] == 0);
	}
}


int main()
{
	SetConsoleCP(1251);//для русского вывода char-ов
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	//double K[6] = { 1.0, 3.2, 0.0, 4.1, 0.0, 1.1 }; //{ K0, K1, K2, K3, K4, K5}
	//Polynom p2(n, K);
	cout << "\nМногочлен имеет вид: Kn*X^n + K(n-1)*X^(n-1) + ... + K1*X^1 + K0;\n" << endl;

	Polynom *polynom_spis;
	int n = 6;
	int k = 0; // кол-во созданных многочленов -1
	int deg = 0, tmp;
	polynom_spis = new Polynom[n];

	
	int pick;
	do{
		cout << "1. Создать два многочлена вручную\n";
		cout << "2. Вывести все многочлены на экран\n";
		cout << "3. Сложить два первых многочлена\n";
		cout << "4. Разность первых двух многочленов\n";
		cout << "5. Инкрементировать первый многочлен\n";
		cout << "6. Декрементировать первых многочлен\n";
		cout << "7. Узнать коэффициент перед i-ой степенью первого многочлена\n";
		cout << "8. Прировнять (скопировать) первый многочлен в k-ый\n";
		cout << "9. Подставить x в первый многочлен\n";
		cout << "10.Перемножить первые два многочлена\n";
		cout << "0. Выход\n";
		cin >> pick;
		switch (pick){
		case 0: {return 1; }
		case 1: {
					while (k != 2)
					{
						cout << "Введите размер многочлена: ";
						cin >> deg;
						polynom_spis[k] = *new Polynom(deg);
						k++;
					}
					k = 0;
					break;
		}
		case 2: {
					for (int i = 0; i < n; i++)// i<k
					{
						cout << "Polynom[" << i << "] = ";
						polynom_spis[i].showPolynom();
						cout << endl;
					}
					break;
		}
		case 3: {
					polynom_spis[2] = polynom_spis[0] + polynom_spis[1];
					cout << "Сумма равна: ";
					polynom_spis[2].showPolynom();
					cout << endl;
					break;
		}
		case 4: {
					polynom_spis[3] = polynom_spis[0] - polynom_spis[1];
					cout << "Разность равна: ";
					polynom_spis[3].showPolynom();
					cout << endl;
					break;
		}
		case 5: {
					polynom_spis[0]++;
					polynom_spis[0].showPolynom();
					break;
		}
		case 6: {
					polynom_spis[0]--;
					polynom_spis[0].showPolynom();
					break;
		}
		case 7: {
					cout << "Введите степь, коэффициент перед которой хотите узнать: ";
					cin >> tmp;
					if (0<=tmp && tmp <= polynom_spis[0].GetDeg())
						cout << "Коэффициент: " << polynom_spis[0].operator[](tmp) << endl;
					else
						cout << "Такого коеффициента не существует" << endl;
					break;
		}
		case 8: {
					polynom_spis[4] = polynom_spis[0];
					break;
		}
		case 9: {
					polynom_spis[0].valueCalculation();
					break;
		}
		case 10: {
					polynom_spis[5] = polynom_spis[0] * polynom_spis[1];
					cout << "Произведение равно: ";
					polynom_spis[5].showPolynom();
					cout << endl;
					break;
		}
		default: {cout << "Ошибка! Попробуйте снова\n"; break; }
		}
	} while (pick != 0);
	
	cin.get();
	return 0;
}