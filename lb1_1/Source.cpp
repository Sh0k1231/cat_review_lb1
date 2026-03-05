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