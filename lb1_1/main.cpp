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