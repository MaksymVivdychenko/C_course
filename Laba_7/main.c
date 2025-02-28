#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define BUFFERSIZE 12
#define LN_EQUATION 1
#define HALFDIVIDING 1
#define NEWTONS_METHOD 2

double firstLimit = 0, secondLimit = 0, result = 0, e = 1e-15;
int t = 0, equation = 0, method = 0;
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
    char string[BUFFERSIZE] = "\0";
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
void ScanDiapasons(double *_firstLimit, double *_secondLimit, int _equation)
{
    bool isCorrectNum = false;
    do
    {
        printf("Write first limit(-100 to 100(but not 0))\n");
        *_firstLimit = ScanNumsDouble(&isCorrectNum);
        if(isCorrectNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        printf("Write second limit(-100 to 100(but not 0))\n");
        *_secondLimit = ScanNumsDouble(&isCorrectNum);
        if(isCorrectNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        if(*_firstLimit == 0 || *_secondLimit == 0)
        {
            printf("limit can't be 0\n");
            isCorrectNum = false;
            continue;
        }
        if(((*_firstLimit) < -100 || (*_firstLimit) > 100) || ((*_secondLimit < -100) || (*_secondLimit) > 100))
        {
            printf("limits must be in diapason from -100 to 100\n");
            isCorrectNum = false;
            continue;
        }
        if(_equation == LN_EQUATION && *_firstLimit <= 0)
        {
            printf("first limit must be bigger than 0\n");
            isCorrectNum = false;
            continue;
        }
        if(*_secondLimit <= *_firstLimit)
        {
            printf("The second limit must be bigger than the first one\n");
            isCorrectNum = false;
            continue;
        }
    }while(isCorrectNum == false);
}
int ScanBinary(char* string)
{
    int _equation = 0;
    bool isCorrectNum = false;
    do
    {
        printf("%s", string);
        _equation = ScanNumsInt(&isCorrectNum);
        if(_equation != 1 && _equation != 2)
        {
            printf("incorrect num\n");
            isCorrectNum = false;
        }
    }while(isCorrectNum == false);
    return  _equation;
}
int ScanT()
{
    int _t = 0;
    bool isCorrectNum = false;
    do {
        printf("write t value(-10 to 10)(int):\n");
        _t = ScanNumsInt(&isCorrectNum);
        if(isCorrectNum == false)
        {
            printf("t must be integer!!!\n");
        }
        if(_t > 10 || _t < -10)
        {
            printf("t must be in diapason from -10 to 10)\n");
            isCorrectNum = false;
        }
    }while(isCorrectNum == false);
    return  _t;
}
double SinCosEquationValue(double _x,int _t)
{
    return cos(_t/_x) - 2*sin(1/_x) + 1/_x;
}
double LnEquationValue(double _x,int _t)
{
    return sin(log(_x)) - cos(log(_x)) + _t*log(_x);
}
double (*functions[2]) (double, int) = {SinCosEquationValue, LnEquationValue

};
double BisektionsMethod(double _firstLimit, double _secondLimit,const int _equation,const int _t)
{
    int i = 0; // лічильник кількості ітерацій
    double x = 0;
        do
        {
            x = (_firstLimit + _secondLimit)/2.;
            if(functions[_equation](x, _t) * functions[_equation](_firstLimit, _t) > 0) //
            {
                _firstLimit = x;
            }
            else
            {
                _secondLimit = x;
            }
            if(i == 2 && (functions[_equation](_firstLimit, _t) > 0 ^ functions[_equation](_secondLimit, _t) < 0))
            {
                x = 0; // такий корінь програма порахувати не може, буде перевірка при виводі результатів
                break;
            }
            i++;
        }while (fabs(_secondLimit - _firstLimit) > e);
    return x;
}
double NewtonsMethod( double _secondLimit,const int _equation,const int _t)
{
    double delta = 0;
    double x = _secondLimit;
    delta = functions[_equation](x, _t)/((functions[_equation](x + e, _t) - functions[_equation](x, _t))/e);
    while(fabs(delta) > e)
    {
        x -= delta;
        delta = functions[_equation](x, _t)/((functions[_equation](x + e, _t) - functions[_equation](x, _t))/e);
    }
    return x;
}
int main()
{
    bool toContinue;
    printf("1.cos(t/x) -2sin(1/x) + 1/x = 0\n"
           "2.sin(lnx) - cos(lnx) + t*lnx = 0\n");
    do
    {
        equation = ScanBinary("choose equation:\n") -1; // функції записані у масив, щоб їх коректно викликати віднімаю 1
        t = ScanT();
        ScanDiapasons(&firstLimit, &secondLimit, equation);
        method = ScanBinary("write 1 if you want to find roots by half dividing method or 2 to find roots by Newton's method\n");
        switch (method)
        {
            case HALFDIVIDING:
                result = BisektionsMethod(firstLimit, secondLimit, equation, t);
                if(result != 0)
                {
                    printf("result = %.15f\n", result);
                }
                else
                {
                    printf("Program can't find solution on this diapason by bisection's method\n");
                }
                break;
            case NEWTONS_METHOD :
                result = NewtonsMethod(secondLimit, equation, t);
                if(result > secondLimit || result < firstLimit)
                {
                    printf("Program can't find solution on this diapason by Newton's method\n");
                }
                else
                {
                    printf("result = %.15f\n", result);
                }
                break;
            default:
                printf("Incorrect input\n");
        }
        printf("if you want to continue press 1 or another key to exit\n");
    } while (ScanNumsInt(&toContinue) == 1);
    return 0;
}
