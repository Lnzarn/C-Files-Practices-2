#include <stdio.h>
#include <ctype.h>

int main()
{
    float firstNum;
    float secondNum;
    float result;
    char another;
    int choice;

    printf("\nPlease enter the first number:");
    scanf("%f", &firstNum);

    printf("Please enter the second number:");
    scanf("%f", &secondNum);

    do
    {
        printf("Please choose an operation:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Divition\n");
        printf("Your chosen operation is:");
        scanf("%d", &choice);
        printf("\nAre you sure?(Y/N)");
        scanf("%s", &another);
        another = toupper(another);

    } while (another == 'N');

    switch (choice)
    {
    case 1:
        result = firstNum + secondNum;
        printf("The result of %.0f + %.0f is %.0f.\n", firstNum, secondNum, result);
        break;

    case 2:
        result = firstNum - secondNum;
        printf("The result of %.0f - %.0f is %.0f.\n", firstNum, secondNum, result);
        break;

    case 3:
        result = firstNum * secondNum;
        printf("The result of %.0f * %.0f is %.0f.\n", firstNum, secondNum, result);
        break;

    case 4:
        if (secondNum != 0)
        {
            result = firstNum / secondNum;
            printf("The result of %.0f / %.0f is %.0f.\n", firstNum, secondNum, result);
        }
        else
        {
            printf("Undefined\n");
        };
        break;

    default:
        printf("Invalid Choice\n");
        break;
    }

    return 0;
};