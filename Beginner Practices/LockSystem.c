#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char password[50];
    char input[50];
    int check = 1;

    printf("\t*************************************\n");
    printf("\tWelcome to a simple Lock System!\n");
    printf("\n\tPlease put a password.\n");
    printf("\t_________________________________\n");
    printf("\t>");
    scanf("\t%s", &password);

    system("cls");

    printf("\tYou have now made a password!");
    getch();
    system("cls");

    do
    {
        printf("\t*************************************\n");
        printf("\tNow, what was the password?\n");
        printf("\t_________________________________\n");
        printf("\t>");
        scanf("%s", &input);
        if (strcmp(password, input) == 0)
        {
            printf("You got the correct password!");
            check = 0;
        }
        else
        {
            printf("That was the wrong password!");
            getch();
            system("cls");
        }
    } while (check == 1);
}
