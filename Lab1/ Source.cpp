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

	unsigned int b = 36; //Ðàçìåð â áàéòàõ çàâèñèò îò ñèñòåìû
	std::cout << binaryNotation(&b, sizeof(typeid(b).name())*8) << std::endl;

	system("pause");
	return 0;
}


template<class T> std::string binaryNotation(T* object, int countOfBytes) {
	int intPath = abs((int)*object); //Îòñå÷åíèå äðîáíîé ÷àñòè (åñëè èìååòñÿ)
	std::string result;
	char tmpChar[2];
	while (intPath) { //Ïåðåâîä öåëîé ÷àñòè â äâîè÷íóþ ñ.ñ.
		sprintf(tmpChar, "%d", intPath % 2); //Ìîæíî îáîáùèòü íà ëþáóþ ñ.ñ., åñëè îñòàòîê îò äåëåíèÿ îäíîçíà÷íîå ÷èñëî
		result += tmpChar[0]; 
		intPath /= 2;
	}
	std::reverse(result.begin(), result.end()); //Îáðàòíàÿ çàïèñü

	unsigned short expMantissa = (unsigned short) result.size() - 1; //Îïðåäåëåíèå èçìåíåíèÿ ïîðÿäêà ïðè íîðìàëèçàöèè ìàíòèññû
	std::string fracResult;
	if (typeid(T) == typeid(double) || typeid(T) == typeid(long double) || typeid(T) == typeid(float)) {  // Ïðîâåðêà óñëîâèÿ íà âîçìîæíîå íàëè÷èå äðîáíîé ÷àñòè ... Èëè ëó÷øå èñïîëüçîâàòü typeid(T).name()?
		T fracPath = fabs(*object - (int) *object);
		unsigned short countOfNumbers = 10; //Íà ñëó÷àé, åñëè áóäåò áåñêîíå÷íàÿ äðîáü
		while (fracPath && countOfNumbers) {
			fracPath *= 2;
			sprintf(tmpChar, "%d", (int)fracPath);
			fracResult += tmpChar[0];
			fracPath -= (int)fracPath;
			countOfNumbers--;
		}
		result += fracResult;
		expMantissa += 1023;
		doubleResult.precision = binaryNotation(&expMantissa, 11); //Îïðåäåëåííî ïîêà òîëüêî äëÿ double. Ïî èäåå ìîæíî îáîáùèòü
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
