#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <math.h>
#include <string>
#include <windows.h>
#include <conio.h>

COORD m = { 0, 0 };
COORD c = { 0, 1 };
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

struct doubleStructure{
public:
	bool sign;
	std::string mantissa;
	std::string precision;
};
static doubleStructure doubleResult;


template<class T> std::string binaryNotation(T* object, int countOfBytes);
//template<class T> bool signDefine(T* object, int countOfBytes);

void menu();
//void keyPressed();
int Point();


int main()
{
	menu();
	return 0;
}


template<class T> std::string binaryNotation(T* object, int countOfBytes) { //Работает норм пока для целых. Скоро залью версию для плавающей запятой
	std::string result;
	bool mask = 1;
	char tmpChar[2];
	for (int i = 0; i < countOfBytes; i++) {
		sprintf(tmpChar, "%d", mask & (unsigned long long)*object>>i); //unsigned long long = unsigned __int64 - 8 байт
		result += tmpChar[0];
	}
	std::reverse(result.begin(), result.end());
	return result;
}

void menu() {
	int menuPoint;
	system("cls");
	SetConsoleCursorPosition(h, m);
	std::cout << "____Menu____"
		<< "\n   Unsigned int"
		<< "\n   Double"
		<< "\n\n\n!Press Esc for exit";
	menuPoint = Point();
	while (1) {
		system("cls");
		bool tmp;
		switch (menuPoint)
		{
		case 1:
			unsigned int uint;
			std::cout << "Unsigned int\n>>>";
			std::cin >> uint;
			std::cout << binaryNotation(&uint, sizeof(typeid(uint).name()) * 8);
			std::cout << "\nRepeat? Y(1)/N(0)\n";
			std::cin >> tmp;
			if (!tmp) {
				menu();
			}
			break;
		case 2:
			double dbl;
			std::cout << "Double\n>>>";
			std::cin >> dbl;
			std::cout << binaryNotation(&dbl, sizeof(typeid(dbl).name()) * 8);
			std::cout << "\nRepeat? Y(1)/N(0)\n";
			std::cin >> tmp;
			if (!tmp) {
				menu();
			}
			break;
		}
	}
}


int Point()
{
	char point[] = "->";
	short stop = 2;
	c.Y = 1;
	int menu = 1;
	COORD temp = { 0, 0 };
	while (1)
	{
		SetConsoleCursorPosition(h, c);
		std::cout << "  ";
		SetConsoleCursorPosition(h, c);
		std::cout << point;
		temp.Y = c.Y;
		int key = _getch();
		if (key == 0 || key == 224)
			key = _getch();
		switch (key)
		{
		case 72: 
			if (c.Y != 1)
			{
				c.Y--;
				menu--;
			}
			break;
		case 75:
			if (c.Y != 1)
			{
				c.Y--;
				menu--;
			}
			break;
		case 77:
			if (c.Y != stop)
			{
				c.Y++;
				menu++;
			}
			break;
		case 80:
			if (c.Y != stop)
			{
				c.Y++;
				menu++;
			}
			break;
		case 27:
			exit(1);
		case 13:
			return menu;
		default: break;
		}
		SetConsoleCursorPosition(h, temp);
		std::cout << "  ";
		SetConsoleCursorPosition(h, c);
		std::cout << point;
	}
};


//void keyPressed() {
//	int key = _getch();
//	if (key == 0 || key == 224)
//		key = _getch();
//	if (key == 27)
//		exit(1);
//}


//template<class T> bool signDefine(T* object, int countOfBytes) {
//	bool mask = 1;
//	return mask & (__int64) *object>>(countOfBytes-1);
//}


//template<class T> std::string binaryNotation(T* object, int countOfBytes) {
//	int intPath = abs((int)*object); //Отсечение дробной части (если имеется)
//	std::string result;
//	char tmpChar[2];
//	while (intPath) { //Перевод целой части в двоичную с.с.
//		sprintf(tmpChar, "%d", intPath % 2); //Можно обобщить на любую с.с., если остаток от деления однозначное число
//		result += tmpChar[0]; 
//		intPath /= 2;
//	}
//	std::reverse(result.begin(), result.end()); //Обратная запись
//
//	unsigned short expMantissa = (unsigned short) result.size() - 1; //Определение изменения порядка при нормализации мантиссы
//	std::string fracResult;
//	if (typeid(T) == typeid(double) || typeid(T) == typeid(long double) || typeid(T) == typeid(float)) {  // Проверка условия на возможное наличие дробной части ... Или лучше использовать typeid(T).name()?
//		T fracPath = (T) fabs(*object - (int) *object);
//		unsigned short countOfNumbers = countOfBytes - (unsigned short) result.size(); //На случай, если будет бесконечная дробь
//		while (fracPath && countOfNumbers) {
//			fracPath *= 2;
//			sprintf(tmpChar, "%d", (int)fracPath);
//			fracResult += tmpChar[0];
//			fracPath -= (int)fracPath;
//			countOfNumbers--;
//		}
//		result += fracResult;
//		expMantissa += 1023;
//		doubleResult.precision = binaryNotation(&expMantissa, 11); //Определенно пока только для double. По идее можно обобщить
//	}	
//	result += std::string(countOfBytes - result.size(), '0');
//	return result;
//}
