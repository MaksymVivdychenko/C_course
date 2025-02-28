#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define BUFFERSIZE 12
int lastXValue = 0, firstXValue = 0, dx = 0;
double e = 0;
int l = 0;
//**********************************************************************************************
bool ValidationNum(char* testNum, char string[BUFFERSIZE])
{
    bool notNum = false;
    if(string[BUFFERSIZE-2] != '\n' && string[BUFFERSIZE-2] != '\0')
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
double ScanEvalue()
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
    }
    while(isNum == false);
    return _e;
}
//**********************************************************************************************
int ScanXValue(char* string)
{
    bool isNum = true;
    int _x = 0;
    do
    {
        isNum = true;
        printf("%s\n", string);
        _x = ScanNumsInt(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        if(_x > 1000 || _x < -1000)
        {
            printf("x must be in diapason from -1000 to 1000\n");
            isNum = false;
        }
    }
    while(isNum == false);
    return _x;
}
//**********************************************************************************************
int ScanDxValue()
{
    bool isNum = true;
    int _dx = 0;
    do
    {
        isNum = true;
        printf("Enter the dx - distinct between next and previous x\n");
        _dx = ScanNumsInt(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        if(_dx <= 0)
        {
            printf("dx must be positive\n");
            isNum = false;
        }
    }
    while(isNum == false);
    return _dx;
}
//**********************************************************************************************
void GetSinTaylor(int _firstXValue, double _e)
{
    int n = 1;
    double radianX = (_firstXValue * M_PI) / 180;
    double _sinXvalue0 = radianX;
    double _sinXvalue1 = -radianX * radianX * radianX / ((n + 1) * (n + 2));
    double PreviousValue = _sinXvalue1;
    _sinXvalue1 = _sinXvalue0 + _sinXvalue1;
    n += 2;
    while (fabs(_sinXvalue0 - _sinXvalue1) >= _e/10)
    {
        _sinXvalue0 = _sinXvalue1;
        _sinXvalue1 = PreviousValue * ((-radianX * radianX) / ((n + 1) * (n + 2)));
        PreviousValue = _sinXvalue1;
        _sinXvalue1 = _sinXvalue1 + _sinXvalue0;
        n += 2;
    }
    printf("---x---   ---sin(x)--- \t---sin(Taylor)--- \t---sin(x)-sin(Taylor)---\n");
    printf("%d \t   %7.*f \t %7.*f \t\t\t %e\n",_firstXValue,l, sin(radianX),l, _sinXvalue1, sin(radianX) - _sinXvalue1);
}
//**********************************************************************************************
void GetSin(int _firstXValue, int _lastXValue,int _dx, double _e)
{
    if(_firstXValue > _lastXValue)
    {
        _dx = -_dx;
        while(_firstXValue >= _lastXValue)
        {
            GetSinTaylor(_firstXValue, _e);
            _firstXValue += _dx;
        }
    }
    else
    {
        while(_firstXValue <= _lastXValue)
        {
            GetSinTaylor(_firstXValue, _e);
            _firstXValue += _dx;
        }
    }
}
int main()
{
    bool toContinue;
    int isContinue = 0;
    do
    {
        l = 0;
        isContinue = 1;
        firstXValue = ScanXValue("Enter the x - first value of finding sin(x)(in degrees)(from -1000 to 1000)");
        lastXValue = ScanXValue("Enter the x - last value of finding sin(x)(in degrees)(the last value should not be greater than the first value by more than 360)(from -1000 to 1000)");
        if(abs(firstXValue - lastXValue) > 360)
        {
            printf("The last value should not be greater than the first value by more than 360\n");
            continue;
        }
        dx = ScanDxValue();
        e = ScanEvalue();
        for(double _e = e; _e <= 0.2; l++) // обчислення кількості знаків після коми
        {
            _e = _e*10;
        }
        GetSin(firstXValue, lastXValue,dx, e);
        printf("if you want to continue press 1 or another key to exit\n");
        isContinue = ScanNumsInt(&toContinue);
    } while (isContinue == 1);
    return 0;
}
