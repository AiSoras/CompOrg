#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <math.h>
#include <string>
#include <windows.h>
#include <conio.h>

COORD m = { 0, 0 };
COORD c = { 0, 1 };
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

union doubleStructure{
	double number;
	unsigned long long binary;
	//__int8 binary[sizeof(double)];
};
static doubleStructure doubleResult;


//union doubleStructure{
//	double number;
//	struct {
//		unsigned int sign : 1;
//		unsigned int exponent : 11;
//		unsigned long long mantissa : 52;
//	} parts;
//} doubleNumber;


template<class T> std::string binaryNotation(T* object, int countOfBytes);
//template<class T> bool signDefine(T* object, int countOfBytes);

std::string replaceBytes(std::string result);

void menu();
//void keyPressed();
int Point();


int main()
{
//	doubleNumber.number = 15.375;
//	std::cout << doubleNumber.parts.sign << " " << doubleNumber.parts.exponent << " " << doubleNumber.parts.mantissa << std::endl;
//	system("pause");

	menu();
	return 0;
}


template<class T> std::string binaryNotation(T* object, int countOfBytes) {
	std::string result;
	bool mask = 1;
	unsigned long long obj = (unsigned long long)*object; //unsigned long long = unsigned __int64 - 8 бай
	for (int i = 0; i < countOfBytes; i++) {
		result += std::to_string(mask & obj);
		obj >>= 1;
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
		std::string result;
		switch (menuPoint)
		{
		case 1:
			unsigned int uint;
			std::cout << "Unsigned int\n>>>";
			std::cin >> uint;
			result = binaryNotation(&uint, sizeof(unsigned int) * 8);
			std::cout << result;
			//std::cin.clear();
			std::cout << "\n\nChange bytes? Y(1)/N(0)\n";
			std::cin >> tmp;
			if (tmp) {
				result = replaceBytes(result);
				uint = std::stoul(result, 0, 2); //В 64-битной long и unsigned int эквивалентны
				std::cout << uint << std::endl;
			}
			std::cout << "Repeat? Y(1)/N(0)\n";
			std::cin >> tmp;
			if (!tmp) {
				menu();
			}
			break;
		case 2:
			std::cout << "Double\n>>>";
			std::cin >> doubleResult.number;
			result = binaryNotation(&doubleResult.binary, sizeof(unsigned long long) * 8);
			std::cout << result;
			//std::cin.clear();
			std::cout << "\n\nChange bytes? Y(1)/N(0)\n";
			std::cin >> tmp;
			if (tmp) {
				result = replaceBytes(result);
				doubleResult.binary = std::stoull(result, 0, 2);
				std::cout << doubleResult.number << std::endl;
			}
			std::cout << "Repeat? Y(1)/N(0)\n";
			std::cin >> tmp;
			if (!tmp) {
				menu();
			}
			break;
		}
	}
}


std::string replaceBytes(std::string result) {

	std::string replacementBytes;
	short byteNumer;

	std::cout << "Byte No\n";
	std::cin >> byteNumer;
	std::cout << "Bytes \n";
	std::cin >> replacementBytes;

	std::reverse(result.begin(), result.end()); //В обратном порядке
	result.replace(byteNumer, replacementBytes.size(), replacementBytes);
	std::reverse(result.begin(), result.end());

	std::cout << "Result:\n" << result << std::endl;

	return result;
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
