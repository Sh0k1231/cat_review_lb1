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