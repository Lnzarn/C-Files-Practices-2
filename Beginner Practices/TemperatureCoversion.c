#include <stdio.h>
#include <ctype.h>

int main()
{
    float input, result;
    char another;
    int choice;

    do
    {
        printf("Please choose the conversion you require.\n");
        printf("1. Celcius -> Fahrenheit\n");
        printf("2. Fahrenheit -> Celcius\n");
        printf("The chosen conversion is:");
        scanf("%d", &choice);
        printf("Are you sure?");
        scanf("%s", &another);
        another = toupper(another);
    } while (another != 'Y');

    switch (choice)
    {
    case 1:
        printf("Input the celsius:");
        scanf("%f", &input);
        result = (input * 1.8) + 32;
        printf("The celsius inputted is %.2f C.\n", input);
        printf("The fahrenheit is %.2f F.", result);
        break;

    case 2:
        printf("Input the fahrenheit:");
        scanf("%f", &input);
        result = (input - 32) * 5 / 9;
        printf("The fahrenheit inputted is %.2f F.\n", input);
        printf("The celcius is %.2f C.", result);
        break;

    default:
        printf("Chosen conversion invalid.");
        break;
    }

    return 0;
}