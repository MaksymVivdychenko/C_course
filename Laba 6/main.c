#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#define BUFFERSIZE 12

double** slr; // matrix
int matrixSize = 0;
double* results, *valuesAfterEqual;
double e = 0.;
int numsAfterComma = 0;
//**********************************************************************************************
bool ValidationNum(const char* testNum,const char string[BUFFERSIZE])
{
    bool notNum = false;
    if(string[BUFFERSIZE - 2] != '\n' && string[BUFFERSIZE - 2] != '\0')
    {
        return notNum = true;
    }
    if(testNum[0] != '\n')
    {
        notNum = true;
    }
    return  notNum;
}
//**********************************************************************************************
int ScanNumsInt(bool *_isNum)
{
    *_isNum = true;
    int num = 0;
    char *testNum;
    char string[BUFFERSIZE];
    fgets(string, sizeof(string), stdin);
    num = strtol(string, &testNum, 10);
    fflush(stdin);
    if(string[0] == '\n')
    {
        *_isNum = false;
    }
    if (ValidationNum(testNum, string))
    {
        num = 0;
        *_isNum = false;
    }
    return num;
}
//**********************************************************************************************
double ScanNumsDouble(bool* _isNum)
{
    *_isNum = true;
    double num = 0;
    char* testNum;
    char string[BUFFERSIZE];
    fgets(string, sizeof(string), stdin);
    if(string[0] == '\n')
    {
        *_isNum = false;
    }
    num = strtod(string, &testNum);
    fflush(stdin);
    if(ValidationNum(testNum, string))
    {
        *_isNum = false;
        num = 0;
    }
    return num;
}
//**********************************************************************************************
double RandomDouble()
{
    return pow(-1., rand()%2)*(rand()%1000) + (rand()%1000)/1000.;
}
//**********************************************************************************************
double MaxValueOfArray(double* array,int _sizeOfArray)
{
    double maxValue = array[0];
    for(int i = 0; i < _sizeOfArray; i++)
    {
        if(maxValue < array[i])
        {
            maxValue = array[i];
        }
    }
    return maxValue;
}
//**********************************************************************************************
double GetDoubleForMatrix()
{
    bool isNum = true;
    double _value = 0;
    do
    {
        isNum = true;
        _value = ScanNumsDouble(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num, write again NORMAL number\n");
            continue;
        }
        if(_value <= -1000 || _value >= 1000)
        {
            printf("Matrix element must be in diapason from -1000 to 1000 \n");
            isNum = false;
        }

    }
    while(isNum == false);
    return _value;
}
//**********************************************************************************************
double GetEvalue(int* _numsAfterComma)
{
    bool isNum = true;
    double _e = 0;
    do
    {
        isNum = true;
        printf("Enter the e - calculation accuracy (double)(read only 10 digits and must be positive)\n");
        _e = ScanNumsDouble(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        if(_e <= 0)
        {
            printf("e must be positive\n");
            isNum = false;
            continue;
        }
        if(_e < 0.0000001 || _e >= 1)
        {
            printf("e must be bigger than 0.0000001 and smaller than 1 \n");
            isNum = false;
        }
        for(double l = _e; l <= 0.2; (*_numsAfterComma)++) // обчислення кількості знаків після коми
        {
            l = l*10;
        }
    }
    while(isNum == false);
    return _e;
}
//**********************************************************************************************
int GetMatrixSize()
{
    int _matrixSize = 0;
    bool isNum = true;
    do
    {
        printf("Write the size of matrix(2 - 6)\n");
        _matrixSize = ScanNumsInt(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num\n");
        }
        if(_matrixSize < 2 || _matrixSize > 6)
        {
            printf("Size of matrix must be in diapason from 2 to 6\n");
            isNum = false;
        }
    }while(isNum == false);
    return _matrixSize;
}
//**********************************************************************************************
bool IsCorrectSlr(const double** _slr,const int _matrixSize)
{
bool _isCorrectSlr = false;
for(int i = 0; i < _matrixSize; i++)
{
    double sumOfLine = 0;
    for(int k = 0; k < _matrixSize; k++)
    {
        if (k != i)
        {
            sumOfLine += fabs(_slr[i][k]);
        }
    }
    _isCorrectSlr = fabs(_slr[i][i])  > sumOfLine;
    if(_isCorrectSlr == false)
    {
        return _isCorrectSlr;
    }
}
    return _isCorrectSlr;
}
//**********************************************************************************************
void ScanSLR(double** _slr, double* _valuesAfterEqual,const int _matrixSize)
{
    for(int i = 0; i < _matrixSize; i++)
    {
        for(int j = 0; j < _matrixSize; j++)
        {
            printf("Write A%d%d element of matrix(-1000 to 1000)(diagonal abs(el) must be bigger then sum of abs(other el from line))\n", i+1, j+1);
            _slr[i][j] = GetDoubleForMatrix();
        }
    }
    for(int i = 0; i < _matrixSize; i++)
    {
        printf("Write B%d element of matrix\n", i+1);
        _valuesAfterEqual[i] = GetDoubleForMatrix();
    }
}
//**********************************************************************************************
void FindingResults( const double** _slr, double* _results,const double* _valuesAfterEqual,const int _matrixSize, const double _e)
{
    double *xp = (double *) calloc(_matrixSize, sizeof(double *));
    double *delta = (double *) calloc(_matrixSize, sizeof(double *));
    double maxDelta = 0;
    double SumOfElementsDividedByXp = 0;
    for(int i = 0; i < _matrixSize; i++)
    {
        xp[i] = _valuesAfterEqual[i]/_slr[i][i];
    }
    do
    {
        maxDelta = 0;
        for (int i = 0; i < _matrixSize; i++)
        {
            SumOfElementsDividedByXp = 0;
            for (int j = 0; j < _matrixSize; j++)
            {
                if (j != i)
                {
                    SumOfElementsDividedByXp += (_slr[i][j] * xp[j]);
                }
            }
            _results[i] = (_valuesAfterEqual[i] - SumOfElementsDividedByXp) / _slr[i][i];
            delta[i] = fabs(_results[i] - xp[i]);
        }
        maxDelta = MaxValueOfArray(delta, _matrixSize);
        for(int i = 0; i < _matrixSize; i++)
        {
            xp[i] = _results[i];
        }
    }
    while(maxDelta >= _e/10);
}
//**********************************************************************************************
void PrintResults(const double* _results,const int _matrixSize, const int _numsAfterComma)
{
    printf("\nresults:");
    for(int i = 0; i < _matrixSize; i++)
    {
        printf(" x%d = %.*f  ", i+1,_numsAfterComma, _results[i]);
    }
}
//**********************************************************************************************
void PrintSLR(const double** _slr, const int _matrixSize, const double* _valuesAfterEqual, const int _numsAfterComma)
{
    printf("\n\tinput matrix:\n");
    for(int i = 0; i < _matrixSize; i++)
    {
        for(int j = 0; j < _matrixSize-1; j++)
        {
            printf("%.*fx%d + ",_numsAfterComma,_slr[i][j] , j+1);
        }
        printf("%.*fx%d  = %.*f\n",_numsAfterComma, _slr[i][_matrixSize-1], _matrixSize,_numsAfterComma ,_valuesAfterEqual[i]);
    }
}
//**********************************************************************************************
void AutoCompleteMatrix(double** _slr,const int _matrixSize, double* _valuesAfterEqual)
{
    double* randomLine = (double*) calloc(_matrixSize, sizeof(double));
    double sumOfDoubles = 0;// сума елементів рядку, окрім діагонального
    do
    {
        for (int i = 0; i < _matrixSize; i++)
        {
            sumOfDoubles = 0;
            for (int k = 0; k < _matrixSize - 1; k++)
            {
                randomLine[k] = RandomDouble();
                sumOfDoubles += fabs(randomLine[k]);
            }
            randomLine[_matrixSize - 1] = pow(-1, rand() % 2) * (sumOfDoubles + rand() %100) + (rand() %1000)/1000.; // в останній комірці зберігається діагональний елемент
            for (int j = 0; j < _matrixSize - 1; j++)
            {
                if (j == i)
                {
                    _slr[i][j] = randomLine[_matrixSize - 1];
                }
                else
                {
                    _slr[i][j] = randomLine[j];
                }
            }
            _slr[i][_matrixSize-1] = randomLine[i];
        }
    } while (IsCorrectSlr(_slr, _matrixSize) == false);
    for (int i = 0; i < _matrixSize; ++i)
    {
        _valuesAfterEqual[i] = RandomDouble();
    }
}
//**********************************************************************************************
int main()
{
    srand(time(NULL));
    int isContinue = 1;
    bool isCorrectSLR = true;
    bool toContinue;
    do {
        numsAfterComma = 0;
        printf("\t matrix form:\n"
               "A11x1 + A12x2 + ... + A1nXn = B1\n"
               "A21x1 + A22x2 + ... + A2nXn = B2\n"
               "An1x1 + An2x2 + ... + AnnXn = B1\n\n");
        matrixSize = GetMatrixSize();
        e = GetEvalue(&numsAfterComma);
        slr = (double **) calloc(matrixSize, sizeof(double *));
        for (int i = 0; i < matrixSize; i++)
        {
            slr[i] = (double *) calloc(matrixSize, sizeof(double)); // виділення пам'яті для кожного рядку матриці
        }
        results = (double *) calloc(matrixSize, sizeof(double));
        valuesAfterEqual = (double *) calloc(matrixSize, sizeof(double));
        printf("If you want to write matrix by yourself press 1 or another key to generate them\n");
        if (ScanNumsInt(&toContinue) == 1)
        {
            do {
                isCorrectSLR = true;
                ScanSLR(slr, valuesAfterEqual, matrixSize);
                if (IsCorrectSlr(slr, matrixSize) == false)
                {
                    printf("Diagonal abs(el) must be bigger then sum of abs(other el from line)\n");
                    isCorrectSLR = false;
                    continue;
                }
                PrintSLR(slr, matrixSize, valuesAfterEqual, numsAfterComma);
                FindingResults(slr, results, valuesAfterEqual, matrixSize, e);
                PrintResults(results, matrixSize, numsAfterComma);
            } while (isCorrectSLR == false);
        }
        else
        {
            AutoCompleteMatrix(slr, matrixSize, valuesAfterEqual);
            PrintSLR(slr, matrixSize, valuesAfterEqual, numsAfterComma);
            FindingResults(slr, results, valuesAfterEqual, matrixSize, e);
            PrintResults(results, matrixSize, numsAfterComma);
        }
        printf("\nif you want to continue press 1 or another key to exit\n");
        isContinue = ScanNumsInt(&toContinue);
        free(slr);
        free(results);
        free(valuesAfterEqual);
    }while(isContinue == 1);
    return 0;
}