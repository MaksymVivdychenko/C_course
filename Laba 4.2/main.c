#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define BUFFERSIZE 12
int n = 0;
struct Nums
{
    double dblNumber;
    int digitsAfterComma;
};
struct Nums* ptr;
//******************************************************************
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
//******************************************************************
double ScanNumsDouble(bool* _isNum, int* _digitsAfterComma)
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
    if(*_isNum == true)
    {
        for (int i = 0; i < sizeof(string) ; i++)
        {
            if(string[i] == '\n')
            {
                break;
            }
            if(string[i] == '.')
            {
                i++;
                while(string[i] != '\n')
                {
                    (*_digitsAfterComma)++;
                    i++;
                }
            }

        }
    }
    return num;
}
//******************************************************************
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
//******************************************************************
int ScanN()
{
    bool isNum = true;
    int _n = 0;
    do
    {
        isNum = true;
        printf("Enter the length of array(from 1 to 100):\n");
        _n = ScanNumsInt(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        if(_n <= 0 || _n > 100)
        {
            printf("The length of array must be in diapason from 1 to 100\n");
            isNum = false;
        }
    } while(isNum == false);
    return _n;
}
//******************************************************************
void ScanArray(int _n, struct Nums* _ptr)
{
    int _digitsAfterComma = 0;
    bool isNum = true;
    for(int i = 0; i < _n; i++)
    {
        _digitsAfterComma = 0;
        isNum = true;
        printf("Enter %d element of array:\n", i+1);
        (_ptr + i)->dblNumber  = ScanNumsDouble(&isNum, &_digitsAfterComma);
        (_ptr + i)->digitsAfterComma = _digitsAfterComma;
        if(isNum == false)
        {
            printf("Incorrect num\n");
            i--;
            continue;
        }
    }
}

int main()
{
    bool toContinue;
    int isContinue;
    do {
        isContinue = 1;
        n = ScanN();
        ptr = (struct Nums*) calloc(n, sizeof(struct Nums));
        ScanArray(n, ptr);
        if (ptr != NULL)
        {
            for (int i = 0; i < n - 1; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if ((ptr+i)->dblNumber > (ptr+j)->dblNumber)
                    {
                        struct Nums t = ptr[i];
                        ptr[i] = ptr[j];
                        ptr[j] = t;
                    }
                }
            }
            printf("Sorted array:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%.*f  ",ptr[i].digitsAfterComma, ptr[i].dblNumber);
            }
        }
        else
        {
            printf("Memory hasn't been allocated\n");
        }
        free(ptr);
        printf("\nif you want to continue press 1 or another key to exit\n");
        isContinue = ScanNumsInt(&toContinue);
    } while (isContinue == 1);
    return 0;
}