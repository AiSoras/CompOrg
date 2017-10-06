#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <math.h>
#include <string>

struct doubleStructure{
public:
	bool sign;
	std::string mantissa;
	std::string precision;
};
static doubleStructure doubleResult;


template<class T> std::string binaryNotation(T* object, int countOfBytes);
template<class T> bool signDefine(T* object);

int main()
{
	double a = -15.375;
	doubleResult.sign = signDefine(&a);
	doubleResult.mantissa = binaryNotation(&a, 52);
	std::cout << doubleResult.sign << " " << doubleResult.precision << " " << doubleResult.mantissa << std::endl;

	unsigned int b = 36; //Размер в байтах зависит от системы
	std::cout << binaryNotation(&b, sizeof(typeid(b).name())*8) << std::endl;

	system("pause");
	return 0;
}


template<class T> std::string binaryNotation(T* object, int countOfBytes) {
	int intPath = abs((int)*object); //Отсечение дробной части (если имеется)
	std::string result;
	char tmpChar[2];
	while (intPath) { //Перевод целой части в двоичную с.с.
		sprintf(tmpChar, "%d", intPath % 2); //Можно обобщить на любую с.с., если остаток от деления однозначное число
		result += tmpChar[0]; 
		intPath /= 2;
	}
	std::reverse(result.begin(), result.end()); //Обратная запись

	unsigned short expMantissa = (unsigned short) result.size() - 1; //Определение изменения порядка при нормализации мантиссы
	std::string fracResult;
	if (typeid(T) == typeid(double) || typeid(T) == typeid(long double) || typeid(T) == typeid(float)) {  // Проверка условия на возможное наличие дробной части ... Или лучше использовать typeid(T).name()?
		T fracPath = fabs(*object - (int) *object);
		unsigned short countOfNumbers = 10; //На случай, если будет бесконечная дробь
		while (fracPath && countOfNumbers) {
			fracPath *= 2;
			sprintf(tmpChar, "%d", (int)fracPath);
			fracResult += tmpChar[0];
			fracPath -= (int)fracPath;
			countOfNumbers--;
		}
		result += fracResult;
		expMantissa += 1023;
		doubleResult.precision = binaryNotation(&expMantissa, 11); //Определенно пока только для double. По идее можно обобщить
	}	
	result += std::string(countOfBytes - result.size(), '0');
	return result;
}


template<class T> bool signDefine(T* object) {
	if (*object > 0)
		return 0;
	else
		return 1;
}