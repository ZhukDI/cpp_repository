#include <iostream>
#include <clocale>
#include <Windows.h>//для русского вывода char-ов

using namespace std;

class Stroka{
protected:
	char *str;
	int len;

public:
	Stroka();
	Stroka(char*);
	Stroka(int);
	Stroka(const Stroka &);
	~Stroka();

	virtual void showStroka();
	int getLength();
	void cleaningStr();
};

Stroka::Stroka()
{
	str = NULL;
	len = 0;
}

Stroka::Stroka(char* s)
{
	len = strlen(s);
	str = new char[len+1];
	strcpy_s(str, len+1, s);
}

Stroka::Stroka(int len)
{
	str = new char[len+1];
	cout << "Введите строку" << endl;
	cin.getline(str, len + 1);
	str[len] = '\0';
}

//конструктор копирования
Stroka::Stroka(const Stroka &f){
	len = f.len;
	str = new char[len + 1];
	strcpy_s(str, len + 1, f.str);
}

//дуструктор
Stroka::~Stroka(){
	//cout << "Деструктор!" << endl;
	delete[] str;
}

//вывод строки
void Stroka::showStroka()
{
	if (str != NULL)
		cout << str << endl;
	else
		cout << "Строка пустая" << endl;
}

//получение днилы строки
int Stroka::getLength()
{
	return len;
}

//очистка строки 
void Stroka::cleaningStr()
{
	str = NULL;
	len = 0;
}


class Bit_Stroka : public Stroka
{
public:
	Bit_Stroka();
	Bit_Stroka(char*);
	Bit_Stroka(const Bit_Stroka &);
	~Bit_Stroka();

	void showStroka();
	void invert();
	void convertToAddCode();

	Bit_Stroka operator = (const Bit_Stroka &);   //оператор присваивания 
	void operator == (const Bit_Stroka &); //оперратор равенства
};

//конструктор без параметров
Bit_Stroka::Bit_Stroka()
{
	str = NULL;
	len = 0;
}

Bit_Stroka::Bit_Stroka(char* s)
{
	len = strlen(s);
	str = new char[len + 1];
	for (int i = 0; i < len; i++){
		if (s[i] == '1' || s[i] == '0')
			str[i] = s[i];
		else{
			str = NULL;
			len = 0;
		}
	}
	if (str != NULL)
		str[len] = '\0';
}

//конструктор копирования
Bit_Stroka::Bit_Stroka(const Bit_Stroka &f){
	len = f.len;
	str = new char[len+1];

	strcpy_s(str, len + 1, f.str);

	//for (int i = 0; i < len; i++)
	//{
	//	str[i] = f.str[i];
	//}
	//str[len] = '\0';
	
}

Bit_Stroka::~Bit_Stroka()
{
	//cout << str;
	//cout << "Деструктор!" << endl;
	//delete[] str;
}

void Bit_Stroka::showStroka()
{
	if (str != NULL)
		cout << str << endl;
	else
		cout << "Битовая строка пустая" << endl;
}

void Bit_Stroka::invert()
{
	for (int i = 1; i < len; i++)
	{
		if (str[i] == '0')
			str[i] = '1';
		else
			str[i] = '0';
	}
}

void Bit_Stroka::convertToAddCode()
{
	if (str[0] == '1')
	{
		this->invert();
		//this->showStroka();
		for (int i = len - 1; i > 0; i--)
		{
			if (str[i] == '0'){
				str[i] = '1';
				break;
			}
			else{
				str[i] = '0';
				if (str[i - 1] == '0' & str[i - 1] == '0'){
					str[i - 1] = '1';
					break;
				}
			}

		}
		//this->showStroka();
	}
}

Bit_Stroka Bit_Stroka::operator = (const Bit_Stroka &t){
	len = t.len;
	//delete[] str;
	str = new char[len + 1];
	//for (int i = 0; i < len; i++)
		//str[i] = t.str[i];
	strcpy_s(str, len + 1, t.str);
	//this->showStroka();
	//str[len] = '\0';
	return *this;
}

void  Bit_Stroka::operator == (const  Bit_Stroka &t){
	for (int i = 0; i < len; i++){
		if (str[i] != t.str[i] || len != t.len){
			cout << "Не равны" << endl;
			break;
		}
		if (i==len-1)
			cout << "Равны" << endl;
	}
}

int main()
{
	SetConsoleCP(1251);//для русского вывода char-ов
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	//Stroka str1(10);
	//str1.showStroka();

	//Stroka str2("qw er ty");
	//str2.showStroka();
	Stroka str;
	str.showStroka();

	Bit_Stroka bstr("11t1");
	bstr.showStroka();

	Bit_Stroka bstr1("1101");
	cout << "bstr1: ";
	bstr1.showStroka();

	cout << "Конвертирование в дополнительный код" << endl;
	bstr1.convertToAddCode();//1101 - 1011; 1000-1000;
	cout << "bstr1: ";
	bstr1.showStroka();

	Bit_Stroka bstr2("1000");
	cout << "bstr2: ";
	bstr2.showStroka();
	cout << "Сравнение" << endl;
	bstr1 == bstr2;

	cout << "Присваивание" << endl;
	bstr1 = bstr2;
	bstr1.showStroka();

	bstr1 == bstr2;

	cin.get();
return 0;
}