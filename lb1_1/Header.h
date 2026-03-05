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