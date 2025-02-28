#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define BUFFERSIZE 12

wchar_t** list;
int numOfLines = 0, lengthOfLine = 0;
//**************************************************************************************
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
int Random(int minValue, int maxValue)
{
    int randomValue = (minValue + rand()%(maxValue - minValue));
    return randomValue;
}
//**************************************************************************************
int ScanNumsInt(bool *_isNum)
{
    *_isNum = true;
    int _num = 0;
    char *testNum;
    char string[BUFFERSIZE];
    fgets(string, sizeof(string), stdin);
    _num = strtol(string, &testNum, 10);
    fflush(stdin);
    if(string[0] == '\n')
    {
        *_isNum = false;
    }
    if (ValidationNum(testNum, string))
    {
        _num = 0;
        *_isNum = false;
    }
    return _num;
}
//**************************************************************************************
int ScanNum(char* _string)
{
    bool isNum = true;
    int _n = 0;
    do
    {
        isNum = true;
        printf("%s", _string);
        _n = ScanNumsInt(&isNum);
        if(isNum == false)
        {
            printf("Incorrect num\n");
            continue;
        }
        if(_n <= 1 || _n > 100)
        {
            printf("input must be in diapason from 2 to 100\n");
            isNum = false;
        }
    } while(isNum == false);
    return _n;
}
//**************************************************************************************
void ReadingLines(wchar_t** _list, int _numOfLines, int _lengthOfLine)
{
    for(int i = 0; i < _numOfLines; i++)
    {
        printf("Write %d line\n", i+1);
        fgetws(_list[i], _lengthOfLine, stdin);
        fflush(stdin);
        if(_list[i][_lengthOfLine-2] != '\n')
        {
            printf("Incorrect line \n");
            i--;
        }
    }
}
//**************************************************************************************
void SortLines(wchar_t** _list, int _numOfLines)
{
    for(int i = 0; i < _numOfLines -1; i++)
    {
        for(int j = i + 1; j < _numOfLines; j++)
        {
            if(wcscmp(_list[i], _list[j]) > 0)
            {
                wchar_t *ptr = _list[i];
                _list[i] = _list[j];
                _list[j] = ptr;
            }
        }
    }
}
//**************************************************************************************
wchar_t GenerateChar()
{
    wchar_t _ch;
    bool isWchar = false;
    int bannedChars[] = {218, 219, 221, 250, 251, 253};
    struct NeededDiapasones
    {
        int startOfDiapason;
        int eneOfDiapason;
    };
    struct NeededDiapasones neededdiapasons[] = {{64, 91},{96, 123}, {187, 256}};
    do
    {
        _ch =(wchar_t)Random(65, 256);
        if(((_ch > neededdiapasons[0].startOfDiapason && _ch < neededdiapasons[0].eneOfDiapason) || (_ch > neededdiapasons[1].startOfDiapason && _ch < neededdiapasons[1].eneOfDiapason)))
        {
            isWchar = true;
        }
        else if(_ch > neededdiapasons[2].startOfDiapason && _ch < neededdiapasons[2].eneOfDiapason)
        {
            isWchar = true;
            for(int k = 0; k < (sizeof(bannedChars)/sizeof(bannedChars[0])); k++)
            {
                if (_ch == bannedChars[k])
                {
                    isWchar = false;
                }
            }
        }
    }
    while(isWchar == false);
    return _ch;
}
//**************************************************************************************
void AutoCompleteLines(wchar_t** _list, int _numOfLines, int _lengthOfLine)
{
    wchar_t ch;
    for(int i = 0; i < _numOfLines; i++)
    {
        for(int j =0; j < _lengthOfLine - 2; j++) // останні дві комірки заповняться \n та \0
        {
                ch = GenerateChar();
                _list[i][j] = ch;
        }
    }
    for(int i = 0; i < _numOfLines; i++)
    {
        _list[i][_lengthOfLine -2] = '\n';
        _list[i][_lengthOfLine -1] = '\0';
    }
}
void PrintLines(wchar_t** _list, int _numOfLines)
{
    for(int i = 0;i < _numOfLines; i++)
    {
        wprintf(L"%d-> %ls",i+1, _list[i]);
    }
}
//**************************************************************************************
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int isContinue = 1;
    bool toContinue;
    do {
        numOfLines = ScanNum("Write the number of line(2 - 100)(later you can choose between generated lines or self-written)\n");
        lengthOfLine = ScanNum("Write the length of line(2 - 100)\n") + 2; // додавання комірок в масив для \n та \0
        list = (wchar_t **) calloc(numOfLines, sizeof(wchar_t *));
        for (int i = 0; i < numOfLines; i++)
        {
            list[i] = (wchar_t *) calloc(lengthOfLine, sizeof(wchar_t));
        }
        if(list != NULL)
        {
            wprintf(L"If you want to write lines by yourself press 1 or another key to generate them\n");
            if (ScanNumsInt(&toContinue) == 1) {
                ReadingLines(list, numOfLines, lengthOfLine);
                SortLines(list, numOfLines);
                wprintf(L"Sorted Lines:\n");
                PrintLines(list, numOfLines);
            } else {
                srand(time(NULL));
                AutoCompleteLines(list, numOfLines, lengthOfLine);
                wprintf(L"Lines for sorting:\n");
                PrintLines(list, numOfLines);
                SortLines(list, numOfLines);
                wprintf(L"Sorted lines:\n");
                PrintLines(list, numOfLines);
            }
            for (int i = 0; i < numOfLines; ++i) {
                free(list[i]);
            }
            free(list);
            wprintf(L"if you want continue press 1 or another key to exit\n");
            isContinue = ScanNumsInt(&toContinue);
        }
        else
        {
            printf("Memory hasn't been allocated\n");
            isContinue = 1;
            continue;
        }

    }
    while(isContinue == 1);
    return 0;
}