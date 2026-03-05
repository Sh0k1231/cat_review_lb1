#include "header.h"

// FIX_ME: отсутствие std::, использование нескольких операторов на одной строке, некорректное расположение скобок, лишние переменные в теле main
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	string s;
//	cout << "Введите логическое выражение, заданное в виде строки s: ";
//	getline(cin, s);
//	int i = 0;
//	bool res = F(s, i);
//	if (res == true)
//	{
//		cout << "Значение логического выражения - T";
//	}
//	else
//	{
//		cout << "Значение логического выражения - F";
//	}
//	return 0;
//}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	SolveLogicTask();

	std::cout << std::endl;
	system("pause");

	return 0;
}