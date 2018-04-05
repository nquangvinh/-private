#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkNum(const char *string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if ( (string[i] < '0' ) || (string[i])> '9' )
        {
            printf("ERR(not interger)\n");
            return 0;
        }
        i++;
    }
    return 1;
}

int lengthGen(const char *stringNum1, const char *stringNum2)
{
    int length;
    if(strlen(stringNum2) > strlen(stringNum1))
    {
        length = strlen(stringNum2);
    }
    else length = strlen(stringNum1);
    return length;
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("ERR(argv)\n");
        return 0;
    }

    int i;
    for (i=1; i<argc; i++)
    {
        if(!checkNum(argv[i]))
        {
            return 0;
        }
    }

    char *num1 = NULL;
    char *num2 = NULL;
    if(strlen(argv[2]) > strlen(argv[1]))
    {
        num1 = (char*)malloc(strlen(argv[2])*sizeof(char));
        num2 = (char*)malloc(strlen(argv[2])*sizeof(char));
        char *tmpZero = (char*)malloc((strlen(argv[2])-strlen(argv[1]))*sizeof(char));
        int i;
        for (i = 0; i <(strlen(argv[2]) - strlen(argv[1])); i++)
        {
            *(tmpZero +i) = '0';
        }
        strcpy(num2, tmpZero);
        strcat(num2, argv[1]);
        strcpy(num1, argv[2]);
    }
    else
    {
        num1 = (char*)malloc(strlen(argv[1])*sizeof(char));
        num2 = (char*)malloc(strlen(argv[1])*sizeof(char));
        char *tmpZero = (char*)malloc((strlen(argv[1])-strlen(argv[2]))*sizeof(char));
        int i;
        for (i = 0; i <(strlen(argv[1]) - strlen(argv[2])); i++)
        {
            *(tmpZero +i) = '0';
        }
        strcpy(num1, argv[1]);
        strcpy(num2, tmpZero);
        strcat(num2, argv[2]);
    }

    char *ToTalSum = (char *)malloc(strlen(num1)*sizeof(char)+1); //now strlen(num1) = strlen(num2) and num1 "MAYBE" > num2
    int len = strlen(num1);;

    int tmpNum1 = 0, tmpNum2 = 0, tmpSum = 0, tmpSumExcess = 0;
    for (i = len -1; i >= 0 ; i--)
    {
        tmpNum1 = num1[i] - '0';
        tmpNum2 = num2[i] - '0';
        tmpSum = tmpNum1 + tmpNum2 + tmpSumExcess;
        if (tmpSum >= 10)
        {
            tmpSum = tmpSum - 10;
            tmpSumExcess = 1;
        }
        else
        {
            tmpSumExcess = 0;
        }

        *(ToTalSum + i +1) = tmpSum + '0';

        if ((i == 0) && (tmpSumExcess == 1))
        {
            *(ToTalSum + 0) = tmpSumExcess + '0';
        }
        else
        {
            *(ToTalSum + 0) = ' ';
        }
    }
    printf("   ptrNum1:\t%s\n", num1);
    printf(" + ptrNum2:\t%s\n", num2);
    printf("---------------------------------------------------------------\n");
    printf("   TOTAL: \t%s\n", ToTalSum);

    return 0;
}