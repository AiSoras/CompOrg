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

	unsigned int b = 36; //������ � ������ ������� �� �������
	std::cout << binaryNotation(&b, sizeof(typeid(b).name())*8) << std::endl;

	system("pause");
	return 0;
}


template<class T> std::string binaryNotation(T* object, int countOfBytes) {
	int intPath = abs((int)*object); //��������� ������� ����� (���� �������)
	std::string result;
	char tmpChar[2];
	while (intPath) { //������� ����� ����� � �������� �.�.
		sprintf(tmpChar, "%d", intPath % 2); //����� �������� �� ����� �.�., ���� ������� �� ������� ����������� �����
		result += tmpChar[0]; 
		intPath /= 2;
	}
	std::reverse(result.begin(), result.end()); //�������� ������

	unsigned short expMantissa = (unsigned short) result.size() - 1; //����������� ��������� ������� ��� ������������ ��������
	std::string fracResult;
	if (typeid(T) == typeid(double) || typeid(T) == typeid(long double) || typeid(T) == typeid(float)) {  // �������� ������� �� ��������� ������� ������� ����� ... ��� ����� ������������ typeid(T).name()?
		T fracPath = fabs(*object - (int) *object);
		unsigned short countOfNumbers = 10; //�� ������, ���� ����� ����������� �����
		while (fracPath && countOfNumbers) {
			fracPath *= 2;
			sprintf(tmpChar, "%d", (int)fracPath);
			fracResult += tmpChar[0];
			fracPath -= (int)fracPath;
			countOfNumbers--;
		}
		result += fracResult;
		expMantissa += 1023;
		doubleResult.precision = binaryNotation(&expMantissa, 11); //����������� ���� ������ ��� double. �� ���� ����� ��������
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