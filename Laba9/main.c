#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

#define ERROR (-1)
#define SUCCESS 0
#define BUFFERSIZE 18

#define ADD 0
#define READ 1
#define REMOVE 2
#define EDIT 3
#define SORT 4
#define INSERT 5
#define DELETE 6
#define RENAME 7
#define NEXT_FILE 8

#define SORT_BY_NAME 0
#define SORT_BY_XP 1
#define SORT_BYM_MANA 2
#define SORT_BY_DAMAGE 3

typedef struct
{
    char name[BUFFERSIZE];
    int xp;
    int mana;
    double damage;
} dotaHero;
typedef struct
{
    dotaHero* dotaHero;
    int numsOfHeroes;
}HeroMass;
typedef  struct
{
    int position;
    int value;
}IntAndPos;

bool ValidationNum(const char* testNum,const char string[BUFFERSIZE]);
int ScanNumsInt();
double ScanNumsDouble();
void PrintListOfCommands();
bool CheckFileExist(char* Filename);
HeroMass ScanHeroesFromFile(char * _fileName);
void PrintHeroes(HeroMass heroMass);
char* ScanFileName();
int CreateFile(char*);
int DeleteFile(char*);
int CheckNumOfHeroesInFile(char* );
HeroMass ScanHeroesFromUser();
int AddHeroesToFile(HeroMass heroMass, char*);
int EditHeroesInFile(HeroMass heroMass, char*);
int DeleteHeroesFromFile(char*);
bool SortLinesAsc(int i, int j, HeroMass heroMass);
bool SortLinesDesc(int i, int j, HeroMass heroMass);
void removeEnter(char *str);
bool SortIntValuesAsc(int i, int j,IntAndPos* massOfInts);
bool SortIntValuesDesc(int i, int j,IntAndPos* massOfInts);
bool (*IntSort) (int, int, IntAndPos*);
HeroMass SortIntValues(HeroMass heroMass, bool isXp, bool isAsc);
bool SortDoubleAsc(int i, int j, HeroMass heroMass);
bool SortDoubleDesc(int i, int j, HeroMass heroMass);
int Sort(char* _fileName);
int main(void)
{
    bool isContinue = true;
    bool isReturntoFileName;
    char* FileName;
    char* NewFileName;
    int Operation;
    printf("This program can make files where will store dota heroes\n");
    PrintListOfCommands();
    do {
        FileName = ScanFileName();
        if(CheckFileExist(FileName) == false)
        {
            printf("This file doesn't exist. Do you want to create it?(y,n)\n");
            if(getchar() == 'y')
            {
                CreateFile(FileName);
                fflush(stdin);
            }
            else
            {
                isContinue = true;
                fflush(stdin);
                continue;
            }
        }

        do
        {
            isReturntoFileName = false;
            Operation = ScanNumsInt();
            switch (Operation)
            {
                case ADD:
                    if(AddHeroesToFile(ScanHeroesFromUser(), FileName) == ERROR)
                    {
                        printf("Error in adding heroes\n");
                    }
                    break;
                case READ:
                    PrintHeroes(ScanHeroesFromFile(FileName));
                    break;
                case REMOVE:
                    if(DeleteHeroesFromFile(FileName) == ERROR)
                    {
                        printf("Error in removing heroes\n");
                    }
                    break;
                case EDIT:
                    if(EditHeroesInFile(ScanHeroesFromUser(), FileName)== ERROR)
                    {
                        printf("Error in editing heroes\n");
                    }
                    break;
                case SORT:
                    if(Sort(FileName) == ERROR)
                    {
                        printf("Error in sorting heroes\n");
                    }
                    break;
                case INSERT:
                    if(AddHeroesToFile(ScanHeroesFromUser(), FileName) == ERROR)
                    {
                        printf("Error in adding heroes in insert\n");
                    }
                    if(Sort(FileName) == ERROR)
                    {
                        printf("Error in sorting heroes in insert\n");
                    }
                    break;
                case DELETE:
                    DeleteFile(FileName);
                    isReturntoFileName = true;
                    break;
                case RENAME:
                    NewFileName = ScanFileName();
                    if(rename(FileName, NewFileName) == -1)
                    {
                        printf("Error in renaming file\n");
                    }
                    else
                    {
                        printf("File has been successfully renamed\n");
                        FileName = NewFileName;
                    }
                    break;
                case NEXT_FILE:
                    isReturntoFileName = true;
                    break;
                default:
                    printf("Incorrect command\n");
                    PrintListOfCommands();
            }
        } while (isReturntoFileName == false);
        printf("do you want to quit the program(y,n)?\n");
        if(getchar() == 'y')
        {
            isContinue = false;
        }
        fflush(stdin);
    }while(isContinue); // exit from program
    return 0;
}
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
int ScanNumsInt()
{
    bool _isNum = true;
    int num = 0;
    char *testNum;
    char string[BUFFERSIZE] = {'\0'};
    do
    {
        _isNum = true;
        fflush(stdin);
        fgets(string, BUFFERSIZE, stdin);
        num = strtol(string, &testNum, 10);
        fflush(stdin);
        if (string[0] == '\n')
        {
            _isNum = false;
            printf("Incorrect input\n");
            continue;
        }
        if (ValidationNum(testNum, string))
        {
            _isNum = false;
            printf("Incorrect input\n");
            continue;
        }
        if(num < 0 || num > 10000)
        {
            _isNum = false;
            printf("Value is must be in diapason from 0 to 10000\n");
            continue;
        }
    } while (_isNum == false);
    return num;
}
double ScanNumsDouble()
{
    bool _isNum = true;
    double num = 0;
    char* testNum;
    char string[BUFFERSIZE] = "\0";
    do {
        _isNum = true;
        fgets(string, sizeof(string), stdin);
        if (string[0] == '\n')
        {
            _isNum = false;
            printf("Incorrect input\n");
            continue;
        }
        num = strtod(string, &testNum);
        fflush(stdin);
        if (ValidationNum(testNum, string))
        {
            _isNum = false;
            printf("Incorrect input\n");
            continue;
        }
        if(num < 0.0 || num > 10000.)
        {
            _isNum = false;
            printf("Value is must be in diapason from 0 to 10000\n");
            continue;
        }
    } while (_isNum == false);
    return num;
}
bool ScanBool()
{
    int isAscInt;
    bool returnValue;
    bool isContinue;

    do {
        isContinue = false;
        isAscInt = ScanNumsInt();
        if (isAscInt == 0) {
            returnValue = true;
        } else if (isAscInt == 1) {
            returnValue = false;
        } else {
            printf("Incorrect Input\n");
            isContinue = true;
        }
    } while (isContinue);

    return returnValue;
}
void PrintListOfCommands()
{
    printf("List of commands:\n"
           "Add Heroes to file : 0\n"
           "Read heroes from file : 1\n"
           "Remove heroes from file : 2\n"
           "Edit file : 3\n"
           "Sort file : 4\n"
           "Insert in sorted file : 5\n"
           "Delete file : 6\n"
           "Rename file : 7\n"
           "Choose next file(or if you want to exit): 8\n");
}
void removeEnter(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '\n') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Завершення нового рядка
}
bool CheckFileExist(char* Filename)
{
    bool returnValue;
    FILE* fp;
    fp = fopen(Filename, "rb");
    if(fp == NULL)
    {
        returnValue = false;
    }
    else
    {
        returnValue = true;
    }
    fclose(fp);
    return returnValue;
}
HeroMass ScanHeroesFromFile(char * _fileName)
{
    int numsOfHeroes = CheckNumOfHeroesInFile(_fileName);
    HeroMass heromass;
    heromass.dotaHero = (dotaHero*) calloc(numsOfHeroes, sizeof(dotaHero));
    if(heromass.dotaHero == NULL)
    {
        heromass.numsOfHeroes = -1;
        return heromass;
    }
    FILE* fp = fopen(_fileName, "rb");
    if(fp == NULL)
    {
        printf("Error scanning\n");
        heromass.numsOfHeroes = -1; // error return
    }
    else
    {
        fread(heromass.dotaHero, sizeof(dotaHero), numsOfHeroes, fp);
        fclose(fp);
        heromass.numsOfHeroes = numsOfHeroes;
    }
    return heromass;
}
void PrintHeroes(HeroMass heroMass)
{
    if(heroMass.numsOfHeroes == 0)
    {
        printf("File is empty\n");
    }
    for (int i = 0; i < heroMass.numsOfHeroes; ++i)
    {
        printf("Hero%d  name: \"%s\" \t xp : %d \t mana : %d \t damage : %.1f",i+1, heroMass.dotaHero[i].name, heroMass.dotaHero[i].xp, heroMass.dotaHero[i].mana, heroMass.dotaHero[i].damage);
        printf("\n");
    }
}
char* ScanFileName()
{
    bool isCorrectName;
    int NumofDots;
    int lettersInName;
    char fileName[BUFFERSIZE] = {'\0'} ;
    do {
        lettersInName = 0;
        NumofDots = 0;
        isCorrectName = false;
        printf("Write file name (name.dat)(16 letters with.dat)\n");
        fgets(fileName, BUFFERSIZE, stdin);
        fflush(stdin);
        if(fileName[BUFFERSIZE -2] != '\n' && fileName[BUFFERSIZE -2] != '\0')
        {
            printf("Incorrect file name\n");
            continue;
        }
        for (int i = 0; i < BUFFERSIZE; ++i)
        {
            if (fileName[i] == '.')
            {
                NumofDots++;
                if(fileName[i + 1] == 'd' && fileName[i + 2] == 'a' && fileName[i + 3] == 't' &&   fileName[i+4] == '\n')
                {
                    isCorrectName = true;
                }
            }
            if(fileName[i] != '\n')
            {
                lettersInName++;
            }
        }
        if(isCorrectName == false)
        {
            printf("Incorrect file name\n");
            continue;
        }
        if(NumofDots > 1)
        {
            isCorrectName = false;
            printf("Incorrect file name\n");
            continue;
        }
    }while(isCorrectName == false);
    removeEnter(fileName);
    char* returnValue = (char*) calloc(lettersInName, sizeof(char));
    for (int i = 0; i < lettersInName; ++i)
    {
     returnValue[i] = fileName[i];
    }
    printf("File name has been read\n");
    return returnValue;
}
int CreateFile(char* _fIleName)
{
    FILE* _fp;
    if((_fp = fopen(_fIleName, "wb")) == NULL)
    {
        perror("File hasn't been created\n");
        return ERROR;
    }
    else
    {
        fclose(_fp);
        printf("File \"%s\" successfully has been created\n", _fIleName);
        return SUCCESS;
    }
}
int DeleteFile(char* _fileName)
{
    if(remove(_fileName) == 0)
    {
        printf("File \"%s\" successfully has been deleted\n", _fileName);
        return SUCCESS;
    }
    else
    {
        printf("File \"%s\" hasn't been deleted\n", _fileName);
        return ERROR;
    }
}
int CheckNumOfHeroesInFile(char* _fileName)
{
    dotaHero CheckHeroes;
    int numOfHeroesInFile;
    FILE* fp = fopen(_fileName, "r+b");
    if(fp == NULL)
    {
        return ERROR;
    }
    for(numOfHeroesInFile = 0; fread(&CheckHeroes, sizeof (dotaHero), 1,fp) == 1; numOfHeroesInFile++);
    fclose(fp);
    return numOfHeroesInFile;
}
int EditHeroesInFile(HeroMass heroMass, char* fileName)
{
    if(heroMass.numsOfHeroes == -1)
    {
        return ERROR;
    }
    FILE* fp;
    int numsOfHeroesInFile;
    int checkAdd;
    int setPos;
    if((fp = fopen(fileName, "r+b")) == NULL)
    {
        printf("File doesn't exist\n");
        return ERROR;
    }
    if((numsOfHeroesInFile = CheckNumOfHeroesInFile(fileName)) == ERROR)
    {
        printf("Trouble in calculating the number of heroes in FILE\n");
        return  ERROR;
    }
    if(numsOfHeroesInFile == 0)
    {
        printf("File doesn't have heroes to change\n");
        return ERROR;
    }
    else {
        printf("On which position you want to edit(change)heroes(1 - %d)\n", numsOfHeroesInFile);
        bool _isContinue = false;
        do {
             _isContinue = false;
            setPos = ScanNumsInt() - 1;// відразу віднімаємо 1 для подальшого коректного використання
            if((setPos + heroMass.numsOfHeroes) > numsOfHeroesInFile)
            {
                printf("Editing heroes are out of range\n");
                _isContinue = true;
                continue;
            }
            if (setPos > (numsOfHeroesInFile-1) || setPos < 0)
            {
                printf("position is out of range\n");
                _isContinue = true;
                continue;
            }
        } while (_isContinue);
        fseek(fp, (setPos * sizeof(dotaHero)), SEEK_SET);
        checkAdd = (int) fwrite(heroMass.dotaHero, sizeof(dotaHero), heroMass.numsOfHeroes, fp);
        free(heroMass.dotaHero);
    }
    if(checkAdd == heroMass.numsOfHeroes)
    {
        printf("Heroes has been successfully added\n");
        fclose(fp);
        return SUCCESS;
    }
    else
    {
        printf("Error in adding heroes to file\n");
        fclose(fp);
        return ERROR;
    }
}
int AddHeroesToFile(HeroMass heroMass, char* fileName)
{
    if(heroMass.numsOfHeroes == -1)
    {
        return ERROR;
    }
    FILE* fp;
    int checkAdd;
    if((fp = fopen(fileName, "r+b")) == NULL)
    {
        printf("File doesn't exist\n");
        return ERROR;
    }
    fseek(fp, 0, SEEK_END);
    checkAdd = (int) fwrite(heroMass.dotaHero, sizeof(dotaHero), heroMass.numsOfHeroes, fp);
    free(heroMass.dotaHero);
    if(checkAdd == heroMass.numsOfHeroes)
    {
        printf("Heroes has been successfully added\n");
        fclose(fp);
        return SUCCESS;
    }
    else
    {
        printf("Error in adding heroes to file\n");
        fclose(fp);
        return ERROR;
    }
}
int DeleteHeroesFromFile(char* fileName)
{
    HeroMass heroMass1;
    HeroMass heroMass2;
    FILE *fp;
    FILE * fp1;
    int NumsToDelete;
    int numsOfHeroesInFile;
    int checkAdd;
    int setPos;
    fp = fopen(fileName, "r+b");
    if(fp == NULL)
    {
        printf("File doesn't exist\n");
        return ERROR;
    }
    if ((numsOfHeroesInFile = CheckNumOfHeroesInFile(fileName)) == ERROR)
    {
        printf("Trouble in calculating the number of heroes in FILE\n");
        return ERROR;
    }
    if (numsOfHeroesInFile == 0) {
        printf("File doesn't have heroes to delete\n");
        return ERROR;
    }
    fclose(fp);
    bool _isContinue = false;
    do {
        _isContinue = false;
        printf("On which position you want to  start delete heroes(1 - %d)?\n", numsOfHeroesInFile);
        setPos = ScanNumsInt() - 1;// відразу віднімаємо 1 для подальшого коректного використання
        if (setPos > (numsOfHeroesInFile - 1) || setPos < 0)
        {
            printf("position is out of range\n");
            _isContinue = true;
            continue;
        }
        printf("How many heroes you want to delete?\n");
        NumsToDelete = ScanNumsInt();
        if (NumsToDelete > (numsOfHeroesInFile) || NumsToDelete <= 0)
        {
            printf("value is out of range\n");
            _isContinue = true;
            continue;
        }
        if ((setPos + NumsToDelete) > numsOfHeroesInFile) {
            printf("Deleting heroes are out of range\n");
            _isContinue = true;
            continue;
        }
    } while (_isContinue);
    fp1 = fopen(fileName, "r+b");
    if (fp1 != NULL)
    {
        fseek(fp1, 0, SEEK_SET);
        if (setPos != 0)
        {
            heroMass1.dotaHero = (dotaHero*) calloc(setPos*sizeof(dotaHero), sizeof(dotaHero));
            checkAdd = fread(heroMass1.dotaHero, sizeof(dotaHero), setPos, fp1);
            heroMass1.numsOfHeroes = setPos;
            if (checkAdd != setPos)
            {
                printf("Error in reading file\n");
            }
            heroMass1.numsOfHeroes = setPos;
        }
        else
        {
            heroMass1.dotaHero = NULL;
        }
        if ((setPos + NumsToDelete) != numsOfHeroesInFile)
        {
            heroMass2.dotaHero = (dotaHero *) calloc((numsOfHeroesInFile  - setPos - NumsToDelete), sizeof(dotaHero));
            fseek(fp1, sizeof(dotaHero)*(setPos + NumsToDelete), SEEK_SET);
            checkAdd = fread(heroMass2.dotaHero, sizeof(dotaHero), (numsOfHeroesInFile - setPos - NumsToDelete), fp);
            heroMass2.numsOfHeroes = numsOfHeroesInFile - setPos - NumsToDelete;
            if (checkAdd != numsOfHeroesInFile - setPos - NumsToDelete)
            {
                printf("Error in reading file\n");
            }
            heroMass2.numsOfHeroes = numsOfHeroesInFile - setPos - NumsToDelete;
        } else
        {
            heroMass2.dotaHero = NULL;
        }
        fclose(fp1);
    }
    else
    {
        return ERROR;
    }
    fp = fopen(fileName, "wb");
    if (fp == NULL) {
        printf("Error in opening file\n");
        return ERROR;
    }
    if (heroMass1.dotaHero != NULL)
    {
        fwrite(heroMass1.dotaHero, sizeof(dotaHero), heroMass1.numsOfHeroes, fp);
    }
    if (heroMass2.dotaHero != NULL) {
        fwrite(heroMass2.dotaHero, sizeof(dotaHero), heroMass2.numsOfHeroes, fp);
    }
    free(heroMass1.dotaHero);
    free(heroMass2.dotaHero);
    printf("Heroes has been deleted\n");
    fclose(fp);
    return SUCCESS;
}
bool SortLinesAsc(int i, int j, HeroMass heroMass)
{
    return (strcmp(heroMass.dotaHero[i].name, heroMass.dotaHero[j].name) > 0);
}
bool SortLinesDesc(int i, int j, HeroMass heroMass)
{
    return (strcmp(heroMass.dotaHero[i].name, heroMass.dotaHero[j].name) < 0);
}
bool SortIntValuesAsc(int i, int j,IntAndPos* massOfInts)
{
    return massOfInts[i].value > massOfInts[j].value;
}
bool SortIntValuesDesc(int i, int j,IntAndPos* massOfInts)
{
    return massOfInts[i].value < massOfInts[j].value;
}
bool (*IntSort) (int, int, IntAndPos*);
HeroMass SortIntValues(HeroMass heroMass, bool isXp, bool isAsc)
{
    IntAndPos* massOfInts = (IntAndPos*) calloc(heroMass.numsOfHeroes, sizeof( IntAndPos));
    if(isXp)
    {
        for (int i = 0; i < heroMass.numsOfHeroes; ++i)
        {
            massOfInts[i].position = i;
            massOfInts[i].value = heroMass.dotaHero[i].xp;
        }
    }
    else
    {
        for (int i = 0; i < heroMass.numsOfHeroes; ++i)
        {
            massOfInts[i].position = i;
            massOfInts[i].value = heroMass.dotaHero[i].mana;
        }
    }
    if(isAsc)
    {
        IntSort = SortIntValuesAsc;
    }
    else
    {
        IntSort = SortIntValuesDesc;
    }
    for (int i = 0; i < heroMass.numsOfHeroes - 1; i++)
    {
        for (int j = i + 1; j < heroMass.numsOfHeroes; j++)
        {
            if (IntSort(i,j,massOfInts))
            {
                IntAndPos changeValue = massOfInts[i];
                massOfInts[i] = massOfInts[j];
                massOfInts[j] = changeValue;
            }
        }
    }
    HeroMass helpChangeValue;
    helpChangeValue.dotaHero = (dotaHero*) calloc(heroMass.numsOfHeroes, sizeof(dotaHero));
    for (int i = 0; i < heroMass.numsOfHeroes; ++i)
    {
        helpChangeValue.dotaHero[i] = heroMass.dotaHero[i];
    }
    for (int i = 0; i < heroMass.numsOfHeroes; ++i)
    {
        heroMass.dotaHero[i] = helpChangeValue.dotaHero[massOfInts[i].position];
    }
    free(massOfInts);
    free(helpChangeValue.dotaHero);
    return heroMass;
}
bool SortDoubleAsc(int i, int j, HeroMass heroMass)
{
    return heroMass.dotaHero[i].damage > heroMass.dotaHero[j].damage;
}
bool SortDoubleDesc(int i, int j, HeroMass heroMass)
{
    return heroMass.dotaHero[i].damage < heroMass.dotaHero[j].damage;
}
bool (*SortPointer)(int, int, HeroMass heroMass);
int Sort(char* fileName)
{
    HeroMass heroMass = ScanHeroesFromFile(fileName);
    if(heroMass.numsOfHeroes == -1 || heroMass.numsOfHeroes == 0)
    {
        printf("Error in scanning heroes form file\n");
        return ERROR;
    }

    int byValueSorting;
    bool isAsc;
    printf("By which value you want to sort heroes:(name(0), xp(1), mana(2), damage(3)?)\n");
    do{
        byValueSorting = ScanNumsInt();
        if(byValueSorting > 3)
        {
            printf("Incorrect input\n");
        }
    }while(byValueSorting > 3);
    printf("Asc(0) or desc(1)\n");
    isAsc = ScanBool();
    if(byValueSorting == SORT_BY_XP)
    {
        heroMass = SortIntValues(heroMass, true, isAsc);
    }
    else if (byValueSorting == SORT_BYM_MANA)
    {
        heroMass = SortIntValues(heroMass, false, isAsc);
    }
    else {
        if (isAsc) {
            switch (byValueSorting) {
                case SORT_BY_NAME:
                    SortPointer = SortLinesAsc;
                    break;
                case SORT_BY_DAMAGE:
                    SortPointer = SortDoubleAsc;
                    break;
                default:
                    printf("Incorrect input\n");
                    break;
            }

        } else {
            switch (byValueSorting) {
                case SORT_BY_NAME:
                    SortPointer = SortLinesDesc;
                    break;
                case SORT_BY_DAMAGE:
                    SortPointer = SortDoubleDesc;
                    break;
                default:
                    printf("Incorrect input\n");
                    break;
            }
        }
        for (int i = 0; i < heroMass.numsOfHeroes - 1; i++)
        {
            for (int j = i + 1; j < heroMass.numsOfHeroes; j++)
            {
                if (SortPointer(i, j, heroMass))
                {
                    dotaHero ptr;
                    ptr = heroMass.dotaHero[i];
                    heroMass.dotaHero[i] = heroMass.dotaHero[j];
                    heroMass.dotaHero[j] = ptr;
                }
            }
        }
    }
    PrintHeroes(heroMass);
    printf("Do you want to save them into file(y, n)\n");
    if(getchar() == 'y')
    {
        FILE* fp = fopen(fileName, "wb");
        if(fp != NULL)
        {
            fwrite(heroMass.dotaHero, sizeof(dotaHero), heroMass.numsOfHeroes, fp);
            fclose(fp);
            printf("File successfully has been edited\n");
            return SUCCESS;
        }
        else
        {
            printf("Error editing file");
            return ERROR;
        }
    }
    free(heroMass.dotaHero);
    return SUCCESS;
}
HeroMass ScanHeroesFromUser() // return struct with mass and number of elements in this mass
{
    dotaHero* massOfHeroes;
    HeroMass heroMass;
    int numsOfHeroes;
    do {
        printf("How many heroes you want to add(1-10)?\n");
        numsOfHeroes = ScanNumsInt();
        if (numsOfHeroes > 10 || numsOfHeroes < 1)
        {
            printf("Number of heroes must be in diapason from 1 to 10\n");
            continue;
        }
    }while(numsOfHeroes > 10 || numsOfHeroes < 1);
    massOfHeroes = (dotaHero*) calloc(numsOfHeroes, sizeof(dotaHero));
    if(massOfHeroes == NULL)
    {
        perror("Memory hasn't been allocated for mass of heroes\n");
        heroMass.numsOfHeroes = -1;
        return heroMass;
    }
    for (int i = 0; i < numsOfHeroes; ++i)
    {
        printf("Write %d hero's name\n", i+1);
        fgets(massOfHeroes[i].name, sizeof(massOfHeroes->name), stdin);// можливо +2 додати
        removeEnter(massOfHeroes[i].name);
        printf("Write %d hero's xp\n", i+1);
        massOfHeroes[i].xp = ScanNumsInt();
        printf("Write %d hero's mana\n", i+1);
        massOfHeroes[i].mana = ScanNumsInt();
        printf("Write %d hero's damage\n", i+1);
        massOfHeroes[i].damage = ScanNumsDouble();
    }
    heroMass.dotaHero = massOfHeroes;
    heroMass.numsOfHeroes = numsOfHeroes;
    return heroMass;
}