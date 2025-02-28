#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
int isContinue = 1;
int year = 0, month = 0, day = 0;
int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool isLeapYear = false;
#define BUFFERSIZE 6
//**********************************************************************************************
bool ValidationNum(char* testNum, char string[BUFFERSIZE])
{
    bool notNum = false;
    if(string[4] != '\n' && string[4] != '\0')
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
int ScanYear(bool* _isLeapYear)
{
    *_isLeapYear = false;
    bool _isContinue = false;
    int _year = 0;
    do {
        _isContinue = false;
        printf("Enter the year of date(1000 - 9999):\n");
        _year = ScanNumsInt();
        if(_year < 1000 || _year > 9999)
        {
            printf("Incorrect year\n");
            _isContinue = true;
        }
        if ((_year % 100 != 0 && _year % 4 == 0) || (_year % 100 == 0 && _year % 400 == 0))
        {
            *_isLeapYear = true;
        }
    }
    while(_isContinue);
    return _year;
}
//**********************************************************************************************
int ScanMonth()
{
    int _month = 0;
    bool _isContinue = false;
    do
    {
        _isContinue = false;
        printf("Enter the month of date:\n");
        _month = ScanNumsInt();
        if (_month < 1 || _month > 12)
        {
            printf("Incorrect month\n");
            _isContinue = true;
        }
    }
    while(_isContinue);
    return _month;
}
//**********************************************************************************************
int ScanDay()
{
    bool _isContinue = false;
    int _day = 0;
    do
    {
        _isContinue = false;
        printf("Enter the day of date:\n");
        _day = ScanNumsInt();
        if(_day > 31 || _day < 1)
        {
            printf("Incorrect day\n");
            _isContinue = true;
        }
    }
    while (_isContinue);
        return _day;
}
//**********************************************************************************************
bool ValidationDay(int _day)
{
    bool correctDay = true;
    daysInMonth[1] = isLeapYear ? 29 : 28; // зміна значення, якщо високосний рік
    if(_day > daysInMonth[month-1] || _day < 1)
    {
        printf("Incorrect day\n");
        correctDay = false;
    }
    return correctDay;
}
//**********************************************************************************************
char* DayOfweek(int _year, int _month, int _day)
{
    char* dayOfWeek;
    int dayWeek = 0;
    int n = 0; // поправка
    if(month > 2)
    {
        n = 0;
    }
    else if(month <= 2 && isLeapYear)
    {
        n = 1;
    }
    else
    {
        n = 2;
    }
    dayWeek = ((int)(365.25*_year) + (int )(30.56*_month) + _day + n) % 7;
    switch (dayWeek)
    {
        case 0 :
            dayOfWeek = "Monday";
            break;
        case 1:
            dayOfWeek = "Tuesday";
            break;
        case 2:
            dayOfWeek = "Wednesday";
            break;
        case 3:
            dayOfWeek = "Thursday";
            break;
        case 4:
            dayOfWeek = "Friday";
            break;
        case 5:
            dayOfWeek = "Saturday";
            break;
        case 6:
            dayOfWeek = "Sunday";
            break;
        default:
            dayOfWeek = "What are you writing nigga?";
            break;
    }
    return dayOfWeek;
}
int main()
{
    do
    {
        isContinue = 1;
        day = ScanDay();
        month = ScanMonth();
        year = ScanYear(&isLeapYear);
        if(ValidationDay(day) == false)
        {
            continue;
        }
        printf("%s\n", DayOfweek(year, month, day));
        printf("if you want to continue press 1 or another key to exit\n");
        isContinue = ScanNumsInt();
    }
    while(isContinue == 1);
    return 0;
}
