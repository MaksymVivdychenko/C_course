#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFFERSIZE 12
double a = 0, b = 0, c = 0; // коефіцієнти

//**********************************************************************************************
bool ValidationNum(char* testNum, char string[BUFFERSIZE])
{
    bool notNum = false;
    if(string[BUFFERSIZE - 2] != '\n' && string[BUFFERSIZE - 2] != '\0')
    {
        return notNum = true;
    }
    for (int i = 0; i < strlen(testNum); i++)
    {
        if(testNum[i] != ' ' && testNum[i] != '\n')
        {
            notNum = true;
            break;
        }
    }
    return  notNum;
}
//**********************************************************************************************
int ScanNumsInt()
{
    int num = 0;
    char *testNum;
    char string[BUFFERSIZE];
    fgets(string, sizeof(string), stdin);
    num = strtol(string, &testNum, 10);
    fflush(stdin);
    if (ValidationNum(testNum, string))
    {
        num = 0;
    }
    return num;
}
//**********************************************************************************************
double ScanNumsDouble(bool* _isNum)
{
    *_isNum = true;
    double num = 0;
    char *testNum;
    char string[BUFFERSIZE];
    fgets(string, sizeof(string), stdin);
    if (string[0] == '\n') {
        *_isNum = false;
    }
    num = strtod(string, &testNum);
    fflush(stdin);
    if (ValidationNum(testNum, string)) {
        *_isNum = false;
        num = 0;
    }
    return num;
}
//**********************************************************************************************
double ScanCoefficient(char numOfCoefficient)
{
    bool isNum = true;
    double _x = 0;
    do
    {
        isNum = true;
        printf("Enter the %c coefficient of equation x^3 + ax^2 + bx +c (read only 10 digits)\n", numOfCoefficient);
        _x = ScanNumsDouble(&isNum);
        if(isNum == false)
        {
            printf("Incorrect Num\n");
        }
    }
    while(isNum == false);
    return _x;
}
//**********************************************************************************************
void RootOfTheEquation(double _a, double _b, double _c)
{
    double _result1 = 0, _result2 = 0, _result3 = 0;
    double _p = 0, _q = 0; // спрощені коефіцієнти
    double _d = 0;
    _p = _b - _a * _a / 3; // ЗРОБИТИ ПЕРЕВІРКУ НА НУЛЬ
    _q = 2 * _a * _a * _a / 27 - _a * _b / 3 + _c;// ЗРОБИТИ ПЕРЕВІРКУ НА НУЛЬ
    if (a != b || a != 3)
    {
        _d = _p * _p * _p / 27 + _q * _q / 4;
        if (_d > 0)
        {
            double _result2Complex = 0, _result3Complex;
            double _u = 0, _v = 0;
            double _y = -_q / 2 + sqrt(_d);
            double _z = -_q / 2 - sqrt(_d);
            _u = (_y > 0) ? (pow(_y, 1 / 3.)) : (pow(fabs(_y), 1 / 3.) * -1);
            _v = (_z > 0) ? (pow(_z, 1 / 3.)) : (pow(fabs(_z), 1 / 3.) * -1);
            _result1 = (_u + _v) - _a / 3;
            _result2 = _result3 = -(_u + _v) / 2 - a / 3;
            _result2Complex = _result3Complex = sqrt(3.0) * (_u - _v) / 2;
            printf("root of the equation I = %f;\nroot of the equation II = %f +i*%f;\nroot of the equation III = %f -i*%f;\n",
                   _result1, _result2, _result2Complex, _result3, _result3Complex);

        }
        else if (_d == 0)
        {
            _result1 = (3 * _q) / _p - a / 3;
            _result2 = _result3 = -3 * _q / (2 * _p) - a / 3;
            printf("root of the equation I = %f;\nroot of the equation II = %f;\nroot of the equation IIІ = %f;\n",
                   _result1, _result2, _result3);
        }
        else
        {
            double _k = 0, _r = 0;
            _r = sqrt(-_p * _p * _p / 27.);// ЧИ ТРЕБА РОБИТИ ПЕРЕВІРКУ???
            _k = acos(-_q / (2. * _r));
            _result1 = 2. * fabs(pow(_r, 1 / 3.0)) * cos(_k / 3.) - _a / 3.;
            _result2 = 2. * fabs(pow(_r, 1 / 3.0)) * cos(((_k + 2. * M_PI) / 3.)) - _a / 3.;
            _result3 = 2. * fabs(pow(_r, 1 / 3.0)) * cos((_k + 4. * M_PI) / 3.) - _a / 3.;
            printf("root of the equation I = %f;\nroot of the equation II = %f;\nroot of the equation III = %f;\n",
                   _result1, _result2, _result3);
        }
    }
    else
    {
        printf("Program cant find solution when a = b = 3\n");
    }
}
int main()
{
    int isContinue = 1;
    do
    {
        a = ScanCoefficient('a');
        b = ScanCoefficient('b');
        c = ScanCoefficient('c');
        if(a == 0 && b == 0)
        {
            printf("Program can't find solution when a = b = 0\n");
            continue;
        }
        RootOfTheEquation(a, b, c);
        printf("if you want to continue press 1 or another key to exit\n");
        isContinue = ScanNumsInt();
    }
    while(isContinue == 1);
    return 0;
}
