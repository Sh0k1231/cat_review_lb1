#pragma once

#include <iostream>
#include <windows.h>

/** Функции для проверки корректности входных данных */
bool IsBaseValid(int InBase);
bool IsDigitsCountValid(int InDigits, int InBase);

/** Функция для решения задачи о K-ичных числах */
void SolveNumberSystemTask();
