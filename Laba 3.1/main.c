#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
float x = 0, e = 0; // введені дані користувачем
int k = 0; // введені дані користувачем
float result = 1.0; // результат
int isContinue = 1;
#define BUFFERSIZE 12
//**********************************************************************************************
bool ValidationNum(char* testNum, char string[BUFFERSIZE])
{
    bool notNum = false;
    if(string[10] != '\n' && string[10] != '\0')
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
float ScanNumsFloat(bool* _isNum)
{
    *_isNum = true;
    float num = 0;
    char* testNum;
    char string[BUFFERSIZE];
    fgets(string, sizeof(string), stdin);
    if(string[0] == '\n')
    {
        *_isNum = false;
    }
    num = strtof(string, &testNum);
    fflush(stdin);
    if(ValidationNum(testNum, string))
    {
        *_isNum = false;
        num = 0;
    }
    return num;
}
//**********************************************************************************************
int ScanNumsInt(bool* _isNum)
{
    *_isNum = true;
    int num = 0;
    char* testNum;
    char string[BUFFERSIZE];
    fgets(string, sizeof(string), stdin);
    if(string[0] == '\n')
    {
        *_isNum = false;
    }
    num = strtol(string, &testNum, 10);
    fflush(stdin);
    if(ValidationNum(testNum,string))
    {
        *_isNum = false;
        num = 0;
    }

    return num;
}
//**********************************************************************************************
float ScanXvalue()
{
    bool isNum = true;
    float _x = 0;
    do
    {
        isNum = true;
        printf("Enter the x - the number from which you want to find root (float)(read only 10 digits)\n");
        _x = ScanNumsFloat(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num\n");
        }
    }
    while(isNum == false);
        return _x;
}
//**********************************************************************************************
float ScanEvalue()
{

    bool isNum = true;
    float _e = 0;
    do
    {
        isNum = true;
        printf("Enter the e - calculation accuracy (float)(read only 10 digits and must be positive)\n");
        _e = ScanNumsFloat(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        if(_e <= 0)
        {
            printf("e must be positive\n");
        }
        if(_e < 0.0000001)
        {
            printf("e must be bigger than 0.0000001 \n");
            isNum = false;
        }
    }
    while(isNum == false || _e <= 0);
    return _e;
}
//**********************************************************************************************
int ScanKvalue()
{
    bool isNum = true;
    int _k = 0;
    do
    {
        isNum = true;
        printf("Enter the k - value of nth root from -100 to 100 (int)(read only 10 digits)\n");
        _k = ScanNumsInt(&isNum);
        if(_k < -100 || _k > 100)
        {
         isNum = false;
        }
        if(isNum == false)
        {
            printf("Incorrect num\n");
        }
    }
    while(isNum == false);
    return _k;
}
//**********************************************************************************************
float NthRoot(float _x, float _e, int _k)
{
    float _result = 1.0;
    float delta = 1.0;
    do
    {
        delta = 1.0 / _k * (_x / powf(_result, _k - 1) - _result);
        if (fabsf(delta) >= _e)
        {
            _result += delta;
        }
    }
    while (fabsf(delta) >= _e);
    return _result;
}
//**********************************************************************************************
bool ValidationXandK(float _x, int _k)
{
    bool validation = true;
    if(_k == 0)
    {
        printf("k must be not 0\n");
        validation =false;
    }
    if(_k > 0)
    {
        if(_k % 2 == 0)
        {
            if(_x < 0)
            {
                printf("x must be positive or 0 if k is even number\n");
                validation = false;
            }
        }
    }
    else
    {
        if(_k % 2 == 0)
        {
            if (_x <= 0)
            {
                printf("x must be positive if k is negative even number\n");
                validation = false;
            }
        }
        else
        {
            if(_x == 0)
            {
                printf("x must be positive if k is negative number\n");
                validation = false;
            }
        }
    }
    return validation;
}
//**********************************************************************************************
int main()
{
    int l = 0;
    bool toContinue;
    do
    {
        l = 0;
        isContinue = 1;
        x = ScanXvalue();
        e = ScanEvalue();
        for(float _e = e; _e <= 0.2; l++) // обчислення кількості знаків після коми
        {
            _e = _e*10;
        }
        k = ScanKvalue();
        if(ValidationXandK(x, k) == false)
        {
            continue;
        }
        if (k > 0)
        {
            result = NthRoot(x, e, k);
            printf("result: %.*f\n",l, result);
        }
        else
        {
            k = abs(k);
            result = 1 / NthRoot(x, e, k);
            printf("result: %.*f\n",l, result);
        }
        printf("if you want to continue press 1 or another key to exit\n");
        isContinue = ScanNumsInt(&toContinue);
    }
    while(isContinue == 1);
    return 0;
}