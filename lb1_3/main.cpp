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