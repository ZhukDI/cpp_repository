/*5.Создать класс Time для работы со временем в формате «часы:минуты:секунды».
Класс должен включать в себя не менее четырех конструкторов инициализации: числами,
строкой (например, «22:59:59»), секундами и временем. Перегрузить операции:
вычисление разницы между двумя моментами времени в секундах, сложение времени и заданного количества секунд,
вычитание из времени заданного количества секунд, сравнение моментов времени (==, !=, <, >), перевод в секунды,
перевод в минуты (с округлением до целой минуты).*/

#include <iostream> 
#include <clocale> 
#include <ctime>
#include <Windows.h>//для русского вывода char-ов 

using namespace std;

typedef unsigned int uint;

class Time{
private:
	uint hou;
	uint min;
	uint sec;
public:
	void ShowTime();
	int inSecond();
	int inMin();

	

	Time();
	Time(char *);
	Time(uint sec);
	Time(uint hou, uint min, uint sec);
	Time(const Time &t);

	Time operator - (const Time &); //вычисление разницы между двумя моментами времени в секундах
	void operator == (const Time &);
	void operator != (const Time &);
	void operator < (const Time &);
	void operator > (const Time &);
	Time &operator ++ (); //сложение времени и заданного количества секунд
	Time &operator -- (); //вычитание из времени заданного количества секунд
};

Time::Time() {
	hou = 0;
	min = 0;
	sec = 0;
}

Time::Time(char *time)
{
	hou = atoi(&time[0]);
	min = atoi(&time[3]);
	sec = atoi(&time[6]);
}

Time::Time(uint sec) {
	hou = sec / 3600;
	sec = sec - hou * 3600;
	min = sec/60;
	sec = sec - min * 60;
	this->sec = sec;
}

Time::Time(uint hou, uint min, uint sec) {
	this->hou = hou;
	this->min = min;
	this->sec = sec;
}

Time::Time(const Time &t){
	hou = t.hou;
	min = t.min; 
	sec = t.sec;
}

void Time::ShowTime()
{
	cout << hou << ":" << min << ":" << sec << endl;
}

int Time::inSecond()
{
	int t = hou * 3600 + min * 60 + sec;
	return t;
}

int Time::inMin()
{
	int t = hou * 3600 + min * 60 + sec;
	t = t / 60;
	return t;
}


Time Time::operator - (const Time &t){
	Time *result = new Time();
	int t1 = hou * 3600 + min * 60 + sec;
	int t2 = t.hou * 3600 + t.min * 60 + t.sec;
	t1 = t1 - t2;
	result->hou = t1 / 3600;
	t1 = t1 - result->hou * 3600;
	result->min = t1 / 60;
	t1 = t1 - result->min * 60;
	result->sec = t1;
	return *result;
}

void Time::operator == (const Time &t){
	int t1 = hou * 3600 + min * 60 + sec;
	int t2 = t.hou * 3600 + t.min * 60 + t.sec;
	if (t1 == t2)
		cout << "Равны" << endl;
	else
		cout << "Не равны" << endl;
	
}

void Time::operator != (const Time &t){
	int t1 = hou * 3600 + min * 60 + sec;
	int t2 = t.hou * 3600 + t.min * 60 + t.sec;
	if (t1 != t2)
		cout << "Не равны" << endl;
	else
		cout << "Равны" << endl;
}

void Time::operator < (const Time &t){
	int t1 = hou * 3600 + min * 60 + sec;
	int t2 = t.hou * 3600 + t.min * 60 + t.sec;
	if (t1 < t2)
		cout << "Первое время меньше" << endl;
	else if (t1 > t2)
		cout << "Первое время больше" << endl;
	else 
		cout << "Равны" << endl;
}

void Time::operator > (const Time &t){
	int t1 = hou * 3600 + min * 60 + sec;
	int t2 = t.hou * 3600 + t.min * 60 + t.sec;
	if (t1 < t2)
		cout << "Первое время меньше" << endl;
	else if (t1 > t2)
		cout << "Первое время больше" << endl;
	else
		cout << "Равны" << endl;
}

Time& Time::operator ++ ()
{
	uint s = 0;
	cout << "Введите количество секунд, которое хотите прибавить к времени: ";
	cin >> s;
	int t = hou * 3600 + min * 60 + sec;
	t += s;
	hou = t / 3600;
	t = t - hou * 3600;
	min = t / 60;
	t = t - min * 60;
	sec = t;
	return *this;
}

Time& Time::operator -- ()
{
	uint s = 0;
	cout << "Введите количество секунд, которое хотите отнять от времени: ";
	cin >> s;
	int t = hou * 3600 + min * 60 + sec;
	t -= s;
	hou = t / 3600;
	t = t - hou * 3600;
	min = t / 60;
	t = t - min * 60;
	sec = t;
	return *this;
}


int main()
{
	SetConsoleCP(1251);//для русского вывода char-ов 
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	Time t1;
	Time t2;
	Time t3;
	int pick;
	do{
		cout << "1. Инициализировать время\n";
		cout << "2. Вывести время\n";
		cout << "3. Вычесть из t2-а t1-ин\n";
		cout << "4. Прибавить к t1 заданное кол-во секунд:\n";
		cout << "5. Вычесть из t1 заданное кол-во секунд:\n"; 
		cout << "6. Сравнение моментов времени t1 и t2 (== , != , <, >):\n";
		cout << "7. Перевести t1 в секунды\n";
		cout << "8. Перевести t1 в минуты\n";
		cout << "0. Выход\n";
		cin >> pick;
		switch (pick){
		case 0: {return 1; }
		case 1: {
					cout << "Время t1: ";
					char time[9];
					cin >> time;
					t1 = *new Time(time);
					cout << "Время t2: ";
					cin >> time;
					t2 = *new Time(time);
					break;
		}
		case 2: {
					cout << "Время t1: "; t1.ShowTime();
					cout << "Время t2: "; t2.ShowTime();
					break;
		}
		case 3: {
					t3 = t2 - t1;
					t3.ShowTime();
					break;
		}
		case 4: {
					t1++;
					t1.ShowTime();
					break;
		}
		case 5: {
					t1--;
					t1.ShowTime();
					break;
		}
		case 6: {
					cout << "t1 == t2 ?  ";
					t1==t2;
					cout << "t1 != t2 ?  ";
					t1 != t2;
					cout << "t1 < t2 ?  ";
					t1 < t2;
					cout << "t1 > t2 ?  ";
					t1 > t2;
					break;
		}
		case 7: {
					cout << "Время t1 в секундах: " << t1.inSecond() << endl;
					break;
		}
		case 8: {
					cout << "Время t1 в минутах: " << t1.inMin() << endl;
					break;
		}
		
		default: {cout << "Ошибка! Попробуйте снова\n"; break; }
		}
	} while (pick != 0);
	cin.get();
	return 0;
}