#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define BUFFERSIZE 12
#
#define SECOND_CIRCUIT 2
#define THIRD_CIRCUIT 3
#define FORTH_CIRCUIT 4
#define CASE_FOR_FIRST_AND_SEC_CIRCUIT 1
#define CASE_FOR_THIRD_AND_FORTH_CIRCUIT 2
#define FIRST_CIRCUIT 1
#define CASE_FOR_SEC_THIRD_AND_FORTH_CIRCUIT 2
typedef struct complex
{
    double Re;
    double Im;
} Resistance;

double L = 0,C = 0, R1 = 0, R2 = 0, Fmin = 0, Fmax = 0, Fstep = 0, F0 = 0;
int circuit = 0;
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
double ScanDoubleValues(char*string)
{
    bool _isNum = false;
    double value = 0;
    do
    {
        printf("%s", string);
        value = ScanNumsDouble(&_isNum);
        if(_isNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        if(value <= 0 || value >= 10000)
        {
            printf("Value must be in diapason from 1 to 10000\n");
            _isNum = false;
            continue;
        }
    }while(_isNum == false);
    return value;
}
int ScanCircuit()
{
    bool _isNum = false;
    int value = 0;
    do {
        printf("Select the circuit {1 ,2 ,3 ,4}\n");
        value = ScanNumsInt(&_isNum);
        if(_isNum == false)
        {
            printf("Incorrect num\n");
            _isNum = false;
            continue;
        }
        if(value <= 0 || value > 4 )
        {
            printf("Incorrect circuit\n");
            _isNum = false;
            continue;
        }
    }while(_isNum == false);
    return value;
}
//**********************************************************************************************
double ScanF(char* string)
{
    double F = 0;
    bool _isCorrectNum = false;
    do {
        printf("%s",string);
        F = ScanNumsDouble(&_isCorrectNum);
        if(_isCorrectNum  == false)
        {
            printf("Incorrect F\n");
            _isCorrectNum =false;
        }
        if(F <= 0 || F > 10000.)
        {
            printf("F must be in diapason from 1 to 10000\n");
            _isCorrectNum = false;
        }
    } while (_isCorrectNum == false);
    return F;
}
//**********************************************************************************************
void CheckAndScanF(double *_Fmin, double* _Fmax)
{
    bool _isCorrectF = true;
    do {
        _isCorrectF = true;
        *_Fmin = ScanF("Enter F min == ");
        *_Fmax = ScanF("Enter F max(F max must be bigger than F min) == ");
        if(*_Fmax <= *_Fmin)
        {
            printf("F max must be bigger than F min\n");
            _isCorrectF = false;
        }
        }while(_isCorrectF == false);
}
//**********************************************************************************************
void FindAndPrintResult(double _a, double _b, double _c, double _d,double _Fmin,int _circuit) // підфункція для функції FindResistance
{
    double k;
    double l;
    Resistance result;
    if(_circuit > 1 && _circuit < 5)
    {
        _circuit = CASE_FOR_SEC_THIRD_AND_FORTH_CIRCUIT;
    }
    switch (_circuit)
    {
        case FIRST_CIRCUIT:
            k = (_a*_c - _b*_d);
            l = (_c*_c + _d*_d);
            result.Re = (_a*_c - _b*_d)/(pow(_c,2)+ pow(_d,2));
            k = _b*_c + _a*_d;
            l = (_c*_c + _d*_d);
            result.Im = (_b*_c + _a*_d)/(pow(_c,2)+ pow(_d,2));
            if(result.Im < 0)
            {
                printf("\nf = %f \tz = %e + i* %e", _Fmin, result.Re, fabs(result.Im));
            }
            else
            {
                printf("\nf = %f \tz = %e - i* %e", _Fmin, result.Re, fabs(result.Im));
            }
            break;
        case CASE_FOR_SEC_THIRD_AND_FORTH_CIRCUIT:
            k = _a*_c + _b*_d;
            l = pow(_c,2)+ pow(_d,2);
            result.Re = (_a*_c + _b*_d)/(pow(_c,2)+ pow(_d,2));
            k = _b*_c - _a*_d;
            l = pow(_c,2)+ pow(_d,2);
            result.Im = (_b*_c - _a*_d)/(pow(_c,2)+ pow(_d,2));
            if(result.Im < 0)
            {
                printf("\nf = %f \tz = %e - i* %e", _Fmin, result.Re, fabs(result.Im));
            }
            else
            {
                printf("\nf = %f \tz = %e + i* %e", _Fmin, result.Re, fabs(result.Im));
            }
            break;
        default:
            printf("Unpredictable input");
            break;
    }
}
//**********************************************************************************************
 void FindResistance(double _L, double _C,double _Fmin, double _Fmax,double _Fstep, double  _R1, double  _R2, int _circuit)
{
    int _circuitForCase = _circuit;
    if(_circuit == SECOND_CIRCUIT) // ще одне групування
    {
        _circuitForCase = CASE_FOR_FIRST_AND_SEC_CIRCUIT;
    }
    double a,b,c,d;
    double _w = 0;
    if(_circuit)
    switch (_circuitForCase)
    {
        case CASE_FOR_FIRST_AND_SEC_CIRCUIT :
            while(_Fmin <= _Fmax)
            {
                _w = 2 * M_PI * _Fmin;
                a = _L/_C;
                b = _R1/(_w * _C);
                c = _R1;
                d = _w*_L - 1/(_w * _C);
                FindAndPrintResult(a,b,c,d,_Fmin, _circuit);
                _Fmin += _Fstep;
            }
            break;
        case THIRD_CIRCUIT :
            while(_Fmin <= _Fmax)
            {
                _w = 2*M_PI*_Fmin;
                a = _R1 * _R2;
                b = (_w * _L - 1 / (_w * _C))*_R1;
                c = _R1 + _R2;
                d = _w * _L - 1 / (_w * _C);
                FindAndPrintResult(a,b,c,d,_Fmin, _circuit);
                _Fmin += _Fstep;
            }
            break;
        case FORTH_CIRCUIT :
            while (_Fmin <= _Fmax)
            {
                _w = 2.*M_PI*_Fmin;
                a = _R1*_R2 + _L/_C;
                b = _w*_L*_R1 - _R2/(_w*_C);
                c = _R1 + _R2;
                d = _w*_L - 1/(_w*_C);
                FindAndPrintResult(a,b,c,d,_Fmin, _circuit);
                _Fmin += _Fstep;
            }
            break;
        default:
            printf("Unpredictable input");
            break;
    }
}
//**********************************************************************************************
int main()
{
    bool toContinue; // потрібне для функції ScanNumsInt
    do {
        circuit = ScanCircuit();
        int circuitInput = circuit;
        L = ScanDoubleValues("Enter L ==");
        C = ScanDoubleValues("Enter C ==");
        if (circuit == SECOND_CIRCUIT) // зведення для switch
        {
            circuitInput = CASE_FOR_FIRST_AND_SEC_CIRCUIT;
        }
        else if (circuit == FORTH_CIRCUIT || circuit == THIRD_CIRCUIT) // зведення для switch
        {
            circuitInput = CASE_FOR_THIRD_AND_FORTH_CIRCUIT;
        }
        switch (circuitInput)
        {
            case CASE_FOR_FIRST_AND_SEC_CIRCUIT:
                R1 = ScanDoubleValues("Enter R ==");
                CheckAndScanF(&Fmin, &Fmax);
                Fstep = ScanDoubleValues("Enter F step ==");
                break;
            case CASE_FOR_THIRD_AND_FORTH_CIRCUIT:
                R1 = ScanDoubleValues("Enter R1 ==");
                R2 = ScanDoubleValues("Enter R2 ==");
                CheckAndScanF(&Fmin, &Fmax);
                Fstep = ScanDoubleValues("Enter F step ==");
                break;
            default:
                printf("Unpredictable input\n");
                break;
        }
        F0 = 1. / (2 * M_PI * sqrt(L * C));
        printf("\nResonant frequency = %f", F0);
        FindResistance(L, C, Fmin, Fmax, Fstep, R1, R2, circuit);
        printf("\nif you want to continue press 1 or another key to exit\n");
    }while(ScanNumsInt(&toContinue) == 1);
    return 0;
}
