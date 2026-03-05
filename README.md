///////////////////////////////////////////1 задание///////////////////////////////////////////


////header.h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <climits>

// Функции валидации данных 
bool IsWeightValid(int InWeight);
bool IsVolumeValid(int InVolume);
bool IsCountValid(int InCount);

// Основная функция решения задачи об археологе 
void BackRec4();


////source.cpp
#include "header.h"

// Реализация функций проверки
bool IsWeightValid(int InWeight)
{
    return InWeight >= 0;
}

bool IsVolumeValid(int InVolume)
{
    return InVolume >= 0;
}

bool IsCountValid(int InCount)
{
    return InCount > 0;
}

//FIX_ME: некорректное расположение скобок, названия переменных, отсутствие std::
//void BackRec4() {
//    ifstream f("f.txt");
//    if (!f.is_open()) cout << "Такого файла не существует";
void BackRec4()
{
    std::ifstream ArtifactInput("f.txt");

    // Проверка открытия файла
    if (!ArtifactInput.is_open())
    {
        std::cout << "Такого файла не существует";
        return;
    }

    //FIX_ME: некорректные имена переменных
    //int N, A, B;
    //f >> N >> A >> B;
    int NumArtifacts = 0;
    int MinWeightLimit = 0;
    int MaxWeightLimit = 0;

    if (!(ArtifactInput >> NumArtifacts >> MinWeightLimit >> MaxWeightLimit))
    {
        std::cout << "Ошибка чтения параметров N, A, B";
        return;
    }

    // Проверка валидности входных параметров через функции
    if (!IsCountValid(NumArtifacts) || MinWeightLimit < 0 || MaxWeightLimit < MinWeightLimit)
    {
        std::cout << "Некорректные входные данные в файле (N, A или B)";
        return;
    }

    //FIX_ME: некорректные имена векторов, отсутствие std::, расположение скобок
    //vector<int> c(N), d(N);
    //for (int i = 0; i < N; i++) {
    //    f >> c[i];
    //}
    std::vector<int> ArtifactWeights(NumArtifacts);
    std::vector<int> ArtifactVolumes(NumArtifacts);

    for (int i = 0; i < NumArtifacts; i++)
    {
        if (!(ArtifactInput >> ArtifactWeights[i]) || !IsWeightValid(ArtifactWeights[i]))
        {
            std::cout << "Ошибка в данных веса артефакта " << i + 1;
            return;
        }
    }

    for (int i = 0; i < NumArtifacts; i++)
    {
        if (!(ArtifactInput >> ArtifactVolumes[i]) || !IsVolumeValid(ArtifactVolumes[i]))
        {
            std::cout << "Ошибка в данных объема артефакта " << i + 1;
            return;
        }
    }

    ArtifactInput.close();

    //FIX_ME: некорректные имена переменных, отсутствие std::
    //vector<int> dp(B + 1, INT_MAX);
    //dp[0] = 0;
    std::vector<int> DPTable(MaxWeightLimit + 1, INT_MAX);
    DPTable[0] = 0;

    // Основной алгоритм динамического программирования
    //FIX_ME: некорректное расположение скобок, использование min без std::
    /*
    for (int i = 0; i < N; i++) {
        for (int w = B; w >= c[i]; w--) {
            if (dp[w - c[i]] != INT_MAX) {
                dp[w] = min(dp[w], dp[w - c[i]] + d[i]);
            }
        }
    }
    */
    for (int i = 0; i < NumArtifacts; i++)
    {
        for (int j = MaxWeightLimit; j >= ArtifactWeights[i]; j--)
        {
            if (DPTable[j - ArtifactWeights[i]] != INT_MAX)
            {
                int PotentialVolume = DPTable[j - ArtifactWeights[i]] + ArtifactVolumes[i];
                if (PotentialVolume < DPTable[j])
                {
                    DPTable[j] = PotentialVolume;
                }
            }
        }
    }

    //FIX_ME: некорректные имена переменных
    //int min_d = INT_MAX;
    //int C = 0;
    int MinTotalVolume = INT_MAX;
    int OptimalWeight = 0;

    for (int i = MinWeightLimit; i <= MaxWeightLimit; i++)
    {
        if (DPTable[i] < MinTotalVolume)
        {
            MinTotalVolume = DPTable[i];
            OptimalWeight = i;
        }
    }

    //FIX_ME: расположение скобок, использование and, отсутствие std::
    //if (min_d == INT_MAX) {
    //    cout << ":";
    //}
    if (MinTotalVolume == INT_MAX)
    {
        std::cout << "Решение не найдено в заданном диапазоне веса";
    }
    else
    {
        std::cout << "Минимальный объём: " << MinTotalVolume << std::endl;
        std::cout << "Вес: " << OptimalWeight << std::endl;
        std::cout << "Артефакты:" << std::endl;

        //FIX_ME: использование and вместо &&, отсутствие std::, имена переменных
        /*
        int w = C;
        for (int i = N - 1; i >= 0; i--) {
            if (w >= c[i] and dp[w] == dp[w - c[i]] + d[i]) {
                cout << i + 1 << ") Вес: " << c[i] << " Объём: " << d[i] << endl;
                w -= c[i];
            }
        }
        */
        int RemainingWeight = OptimalWeight;
        for (int i = NumArtifacts - 1; i >= 0; i--)
        {
            if (RemainingWeight >= ArtifactWeights[i] &&
                DPTable[RemainingWeight - ArtifactWeights[i]] != INT_MAX &&
                DPTable[RemainingWeight] == DPTable[RemainingWeight - ArtifactWeights[i]] + ArtifactVolumes[i])
            {
                std::cout << i + 1 << ") Вес: " << ArtifactWeights[i] << " Объём: " << ArtifactVolumes[i] << std::endl;
                RemainingWeight -= ArtifactWeights[i];
            }
        }
    }
}


////main.cpp
#include "header.h"

int main()
{
    // Настройка локали для корректного отображения кириллицы
    setlocale(LC_ALL, "ru");

    //FIX_ME: отсутствие std::, несколько операторов на одной строке
    //BackRec4(); cout << endl << endl;

    BackRec4();

    std::cout << std::endl << std::endl;

    return 0;
}


///////////////////////////////////////////2 задание///////////////////////////////////////////


////header.h
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm> // для std::max
#include <windows.h>

// Функция для решения задачи о черепашке
void SolveTurtlePath();


////source.cpp
#include "header.h"

// Новая функция проверки размера
bool IsBoardSizeValid(int InSize)
{
    return InSize >= 1 && InSize <= 80;
}

// Новая функция проверки значения клетки
bool IsCellValueValid(int InValue)
{
    return InValue >= 0 && InValue <= 100;
}

void SolveTurtlePath()
{
    //FIX_ME: добавлены проверки открытия файлов и именование по PascalCase
    //ifstream f("21.txt");
    //ofstream m("22.txt");
    std::ifstream InputFile("21.txt");
    std::ofstream OutputFile("22.txt");

    if (!InputFile.is_open())
    {
        std::cout << "Ошибка: Не удалось открыть входной файл '21.txt'" << std::endl;
        return;
    }

    int BoardSize = 0;
    if (!(InputFile >> BoardSize))
    {
        std::cout << "Ошибка: Файл пуст или поврежден" << std::endl;
        return;
    }

    //FIX_ME: вынос проверки размера в отдельную функцию
    //if (n < 1 || n > 80)
    //{
    //    cout << "Ошибка, исправьте параметр n";
    //}
    if (!IsBoardSizeValid(BoardSize))
    {
        std::cout << "Ошибка: Неверный размер доски (должен быть 1-80)" << std::endl;
        return;
    }

    std::vector<std::vector<int>> ValueMatrix(BoardSize, std::vector<int>(BoardSize));
    std::vector<std::vector<int>> DPTable(BoardSize, std::vector<int>(BoardSize, 0));

    //FIX_ME: добавление проверки значений при чтении матрицы
    /*
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            f >> matr[i][j];
        }
    }
    */
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            if (!(InputFile >> ValueMatrix[i][j]))
            {
                std::cout << "Ошибка: Недостаточно данных в матрице" << std::endl;
                return;
            }

            if (!IsCellValueValid(ValueMatrix[i][j]))
            {
                std::cout << "Ошибка: Значение в клетке [" << i << "][" << j << "] вне диапазона 0-100" << std::endl;
                return;
            }
        }
    }

    //FIX_ME: реализация алгоритма с использованием (std::max) для обхода ошибки макроса Windows
    /*
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (i == 0 && j == n - 1) dosk[i][j] = matr[i][j];
            else if (i == 0) dosk[i][j] = dosk[i][j + 1] + matr[i][j];
            else if (j == n - 1) dosk[i][j] = dosk[i - 1][j] + matr[i][j];
            else dosk[i][j] = max(dosk[i - 1][j], dosk[i][j + 1]) + matr[i][j];
        }
    }
    */
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = BoardSize - 1; j >= 0; j--)
        {
            if (i == 0 && j == BoardSize - 1)
            {
                DPTable[i][j] = ValueMatrix[i][j];
            }
            else if (i == 0)
            {
                DPTable[i][j] = DPTable[i][j + 1] + ValueMatrix[i][j];
            }
            else if (j == BoardSize - 1)
            {
                DPTable[i][j] = DPTable[i - 1][j] + ValueMatrix[i][j];
            }
            else
            {
                // Используем (std::max) в скобках, чтобы Visual Studio не выдавала ошибку C2589
                DPTable[i][j] = (std::max)(DPTable[i - 1][j], DPTable[i][j + 1]) + ValueMatrix[i][j];
            }
        }
    }

    int MaxPathSum = DPTable[BoardSize - 1][0];

    if (OutputFile.is_open())
    {
        OutputFile << MaxPathSum;
        std::cout << "Результат успешно записан: " << MaxPathSum << std::endl;
    }

    InputFile.close();
    OutputFile.close();
}


////main.cpp
#include "header.h"

int main()
{
    // Настройка локали для работы с русским языком в консоли VS
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //FIX_ME: вызов функции без использования using namespace std
    //BackRec4(); cout << endl << endl;
    SolveTurtlePath();

    std::cout << std::endl << "Нажмите любую клавишу для выхода..." << std::endl;
    system("pause"); // Чтобы консоль не закрывалась сразу

    return 0;
}


///////////////////////////////////////////3 задание///////////////////////////////////////////


////header.h
#pragma once

#include <iostream>
#include <windows.h>

/** Функции для проверки корректности входных данных */
bool IsBaseValid(int InBase);
bool IsDigitsCountValid(int InDigits, int InBase);

/** Функция для решения задачи о K-ичных числах */
void SolveNumberSystemTask();


////source.cpp
#include "header.h"

// Реализация функций проверки
bool IsBaseValid(int InBase)
{
    return InBase >= 2 && InBase <= 10;
}

// Исправлено: имя параметра теперь соответствует использованию в теле функции
bool IsDigitsCountValid(int InDigits, int InBase)
{
    // FIX_ME: идентификатор "InValue" не определен
    // return InDigits > 1 && InDigits < 20 && (InDigits + InBase) < 26;
    return InDigits > 1 && InDigits < 20 && (InDigits + InBase) < 26;
}

void SolveNumberSystemTask()
{
    // FIX_ME: некорректные имена переменных, отсутствие std::
    /*
    int k, n;
    cout << "Введите систему счисления: ";
    cin >> k;
    cout << "количество разрядов: ";
    cin >> n;
    */
    int Base;
    int DigitsCount;

    std::cout << "Введите систему счисления: ";
    std::cin >> Base;
    std::cout << "Количество разрядов: ";
    std::cin >> DigitsCount;

    // FIX_ME: расположение скобок, использование функций проверки
    /*
    if (k < 2 || k > 10 || n <= 1 || n >= 20 || (n + k) >= 26) {
        cout << "Некорректные данные, повторите ввод";
    }
    */
    if (!IsBaseValid(Base) || !IsDigitsCountValid(DigitsCount, Base))
    {
        std::cout << "Некорректные данные, повторите ввод" << std::endl;
        return;
    }

    // FIX_ME: некорректные и непонятные имена переменных, объявление в одну строку
    /*
    float nz, oz, tz, thz, i, _nz, _oz, _tz, _thz, foz, _foz;
    nz = k - 1;
    oz = 1;
    tz = 0;
    thz = 0;
    foz = 0;
    */
    float NoZeros;           // Числа без нулей на конце
    float OneZero;           // Один ноль на конце
    float TwoZeros;          // Два нуля на конце
    float ThreeZeros;        // Три нуля на конце
    float FourOrMoreZeros;   // Более трех нулей (целевое состояние)

    float PrevNoZeros;
    float PrevOneZero;
    float PrevTwoZeros;
    float PrevThreeZeros;
    float PrevFourOrMoreZeros;

    // Инициализация для первого разряда
    NoZeros = (float)Base - 1;
    OneZero = 0;
    TwoZeros = 0;
    ThreeZeros = 0;
    FourOrMoreZeros = 0;

    // FIX_ME: расположение скобок, использование префиксного инкремента, логика переходов
    /*
    for (i = 2; i <= n; i++) {
        _nz = nz;
        _oz = oz;
        _tz = tz;
        _thz = thz;
        _foz = foz;
        nz = _nz * (k - 1) + _oz * (k - 1) + _thz * (k - 1) + _tz * (k - 1) + _foz * (k - 1);
        oz = _nz;
        tz = _oz;
        thz = _tz;
        foz = _thz + _foz * k;
    }
    */
    for (int i = 2; i <= DigitsCount; ++i)
    {
        PrevNoZeros = NoZeros;
        PrevOneZero = OneZero;
        PrevTwoZeros = TwoZeros;
        PrevThreeZeros = ThreeZeros;
        PrevFourOrMoreZeros = FourOrMoreZeros;

        // Любое число, если к нему приписать не нуль, попадает в категорию NoZeros
        NoZeros = (PrevNoZeros + PrevOneZero + PrevTwoZeros + PrevThreeZeros + PrevFourOrMoreZeros) * (Base - 1);

        // Распределение при приписывании нуля
        OneZero = PrevNoZeros;
        TwoZeros = PrevOneZero;
        ThreeZeros = PrevTwoZeros;

        // Новое состояние "более 3 нулей": если было 3 и добавили 0, или если уже было более 3 (тогда любая цифра сохраняет свойство)
        FourOrMoreZeros = PrevThreeZeros + (PrevFourOrMoreZeros * Base);
    }

    // FIX_ME: отсутствие std::
    // cout << "Количество чисел, содержащих более трёх идущих нулей: " << foz;
    std::cout << "Количество чисел, содержащих более трех идущих нулей: " << FourOrMoreZeros << std::endl;
}


////main.cpp
#include "header.h"

int main()
{
    // FIX_ME: использование сокращенной строки локали
    // setlocale(LC_ALL, "ru");
    setlocale(LC_ALL, "Russian");

    // Выполнение логики программы
    SolveNumberSystemTask();

    // FIX_ME: отсутствие std:: и лишние операторы на одной строке
    // cout << endl << endl;
    std::cout << std::endl << std::endl;

    return 0;
}


///////////////////////////////////////////4 задание///////////////////////////////////////////


////header.h
#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

// Функции проверки 
bool IsStringValid(const std::string& InExpression);

// Основная рекурсивная функция вычисления выражения 
bool EvaluateExpression(const std::string& InS, int& OutIndex);

// Запуск задачи 
void SolveLogicTask();


////source.cpp
#include "header.h"

// Реализация проверки
bool IsExpressionEmpty(const std::string& InExpression)
{
    return InExpression.length() == 0;
}

// Рекурсивный разбор выражения
// FIX_ME: Использование цикла while (запрещено), некорректные имена, отсутствие std::
/*
bool F(const string& s, int& i)
{
    bool l, r;
    while (i < s.length() && s[i] == ' ')
    {
        i++;
    }
    if (i == s.length())
        return false;
    if (s[i] == 'T')
    {
        i++;
        return true;
    }
    if (s[i] == 'F')
    {
        i++;
        return false;
    }
    if (s.substr(i, 4) == "And(")
    {
        i += 4;
        l = F(s, i);
        i++; //пропускаем запятую
        r = F(s, i);
        i++; //пропуск скобки
        return l && r;
    }
    if (s.substr(i, 3) == "Or(")
    {
        i += 3;
        l = F(s, i);
        i++;
        r = F(s, i);
        i++;
        return l || r;
    }
    return false;
}
*/
bool EvaluateLogicalExpression(const std::string& InS, int& OutIndex)
{
    // Проверка на конец строки
    if (OutIndex >= (int)InS.length())
    {
        return false;
    }

    // Обработка константы True
    if (InS[OutIndex] == 'T')
    {
        OutIndex++;
        return true;
    }

    // Обработка константы False
    if (InS[OutIndex] == 'F')
    {
        OutIndex++;
        return false;
    }

    // Обработка функции And(x, y)
    // Используем сравнение строк без создания подстрок substr для оптимизации
    if (OutIndex + 4 <= (int)InS.length() && InS.compare(OutIndex, 4, "And(") == 0)
    {
        OutIndex += 4; // Пропускаем "And("

        bool bLeftValue = EvaluateLogicalExpression(InS, OutIndex);

        // Пропускаем запятую (без цикла)
        if (OutIndex < (int)InS.length() && InS[OutIndex] == ',')
        {
            OutIndex++;
        }

        bool bRightValue = EvaluateLogicalExpression(InS, OutIndex);

        // Пропускаем закрывающую скобку
        if (OutIndex < (int)InS.length() && InS[OutIndex] == ')')
        {
            OutIndex++;
        }

        return bLeftValue && bRightValue;
    }

    // Обработка функции Or(x, y)
    if (OutIndex + 3 <= (int)InS.length() && InS.compare(OutIndex, 3, "Or(") == 0)
    {
        OutIndex += 3; // Пропускаем "Or("

        bool bLeftValue = EvaluateLogicalExpression(InS, OutIndex);

        // Пропускаем запятую
        if (OutIndex < (int)InS.length() && InS[OutIndex] == ',')
        {
            OutIndex++;
        }

        bool bRightValue = EvaluateLogicalExpression(InS, OutIndex);

        // Пропускаем закрывающую скобку
        if (OutIndex < (int)InS.length() && InS[OutIndex] == ')')
        {
            OutIndex++;
        }

        return bLeftValue || bRightValue;
    }

    return false;
}

void SolveLogicTask()
{
    std::string InputString;
    std::cout << "Введите логическое выражение: ";
    std::getline(std::cin, InputString);

    if (IsExpressionEmpty(InputString))
    {
        std::cout << "Ошибка: введена пустая строка." << std::endl;
        return;
    }

    int CurrentIndex = 0;
    bool bFinalResult = EvaluateLogicalExpression(InputString, CurrentIndex);

    // FIX_ME: Некорректное расположение скобок, отсутствие std::
    /*
    if (res == true)
    {
        cout << "Значение логического выражения - T";
    }
    else
    {
        cout << "Значение логического выражения - F";
    }
    */
    if (bFinalResult)
    {
        std::cout << "Значение логического выражения - T" << std::endl;
    }
    else
    {
        std::cout << "Значение логического выражения - F" << std::endl;
    }
}


////main.cpp
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
