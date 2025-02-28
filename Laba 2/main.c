#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
double a = 0,b = 0,c = 0; // сторони трикутника
double hA = 0, hB = 0, hC = 0; // висоти до сторін
double mA = 0, mB = 0, mC = 0; // медіани до сторін
double bA = 0, bB = 0, bC = 0; // бісектриси до сторін
double p = 0, s = 0; //  периметр, площа
double halfP = 0;
#define BUFFERSIZE 12

double HalfPerimeter(double a, double b, double c)
{
    return (a+b+c)/2;
}

double Square(double a, double b, double c, double p)
{
    return  sqrt(p*(p-a)*(p-b)*(p-c));
}

double Height(double a, double b, double c, double p) //перший елемент визначає до якої сторони
{
    return 2*sqrt(p*(p-a)*(p-b)*(p-c))/a;
}

double Median(double a, double b, double c) // перший елемент визначає до якої сторони
{
    return 0.5*(sqrt(2*b*b + 2*c*c - a*a));
}

double Bisector(double a, double b, double c, double p) // перший елемент визначає до якої сторони
{
    return 2/(b+c)*sqrt(b*c*p*(p-a));
}

bool ValidationNum(char* testNum, char string[BUFFERSIZE])
{
    bool notNum  = false;
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
double ScanSide(char chSide)
{
    bool _isNum = true;
    double side = 0;
    do
    {
        _isNum = true;
        printf("Enter the %c side length(read only 10 digits) \n", chSide);
        side = ScanNumsDouble(&_isNum);

        if (_isNum == false)
        {
            printf("Incorrect side\n");
            continue;
        }
        if(side <= 0)
        {
            printf("Side must be positive\n");
            _isNum = false;
        }
        else if (side <= 0.0001)
        {
            printf("Side must be bigger than 0.0001\n");
            _isNum = false;
        }

    } while(_isNum == false);
    return side;
}
double FindBiggestSide(double _a,double  _b, double _c)
{
    return  (_a > _b) ? (_a > _c ? _a : _c) : (_b > _c ? _b : _c);
}
int main()
{
    int isContinue = 0;
    bool toContinue = false;
    double BiggestSide = 0;
    do {
        a = ScanSide('A');
        b = ScanSide('B');
        c = ScanSide('C');
        BiggestSide = FindBiggestSide( a, b, c);
        if(BiggestSide/a <= powf(10, 4) && BiggestSide/b <= powf(10, 4) && BiggestSide/c <= powf(10, 4)) // як різниця між сторонами більша ніж в 4 рази, то розрахунки стають некоректними
        {
            if (a + b > c && a + c > b && b + c > a)
            {
                halfP = HalfPerimeter(a, b, c);
                s = Square(a, b, c, halfP);
                p = halfP * 2; // знаходження переметру
                hA = Height(a, b, c, halfP);
                hB = Height(b, a, c, halfP);
                hC = Height(c, a, b, halfP);
                mA = Median(a, b, c);
                mB = Median(b, a, c);
                mC = Median(c, a, b);
                bA = Bisector(a, b, c, halfP);
                bB = Bisector(b, a, c, halfP);
                bC = Bisector(c, a, b, halfP);
                printf("Square: %18.18f  \n", s);
                printf("Perimeter: %10.11f \n", p);
                printf("Height to a: %10.11f, height to b: %10.11f, height to c: %10.11f \n", hA, hB, hC);
                printf("Bisector to a: %10.11f, Bisector to b: %10.11f, Bisector to c: %10.11f \n", bA, bB, bC);
                printf("Median to a: %10.11f, Median to b: %10.11f, Median to c: %10.11f \n", mA, mB, mC);
            } else {
                printf("This triangle is not exist\n");
            }
        }
        else
        {
            printf("The biggest side must not be bigger than the smallest side more than 10^4 times\n");
        }
        printf("if you want to continue press 1 or another key to exit\n");
        isContinue = ScanNumsInt(&toContinue);
    } while (isContinue == 1);
    return 0;
}
