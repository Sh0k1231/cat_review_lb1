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