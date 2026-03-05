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