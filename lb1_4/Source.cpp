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