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