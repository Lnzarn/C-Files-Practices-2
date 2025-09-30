#include "Baccount.h"
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void validateStringInput(char *prompt, char *buffer, int maxLength)
{
    while(1) {
        printf("%s (up to %d characters): ", prompt, maxLength - 1);
        if (fgets(buffer, 100, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';

            if (strlen(buffer) >= maxLength) {
                printf("Error: Input must be less than %d characters. \n", maxLength);
            } else {
                break;
            }
        }
    }
};

void validateStringInputforEmail(char *prompt, char *buffer, int maxLength)
{
    while(1) {
        printf("%s (up to %d characters): ", prompt, maxLength - 1);
        if (fgets(buffer, 100, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';

            if (strlen(buffer) >= maxLength) {
                printf("Error: Input must be less than %d characters. \n", maxLength);
            } else if (strpbrk(buffer, "@") == NULL){
                printf("Error: Input must be an email");
            } else {
                break;
            }
        }
    }
};

void validateStringInputNoNumber(char *prompt, char *buffer, int maxLength)
{
    while(1) {
        printf("%s (up to %d characters): ", prompt, maxLength - 1);
        if (fgets(buffer, 100, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';

            if (strlen(buffer) >= maxLength) {
                printf("Error: Input must be less than %d characters. \n", maxLength);
            } else if (isalpha(*buffer) == 0) {
                printf("\t\t\tError, You must input the approriate characters.");
            } else {
                break;
            }
        }
    }
};

void validateStringInputOnlyNumber(char *prompt, char *buffer, int maxLength)
{
    while(1) {
        printf("%s (up to %d characters): ", prompt, maxLength - 1);
        if (fgets(buffer, 100, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';

            if (strlen(buffer) >= maxLength) {
                printf("Error: Input must be less than %d characters. \n", maxLength);
            } else if (isdigit(*buffer) == 0) {
                printf("\t\t\tError, You must input the approriate numbers.");
            } else {
                break;
            }
        }
    }
};

void validateCharacterInput(char *input) {
    char temp;
    while(1) {
        if (scanf("%c", &temp) != 1 || isalpha(temp) == 0 || getchar() != '\n' ) {
            printf("\t\t\tError, You must input the approriate characters.");
            while(getchar() != '\n');
            printf("\n\t\t\t>");
        } else {
            *input = temp;
            break;
        }
    }
}



bool validateConfirmationOfLogout(bool *loggedin) {
    while (1) {
        char exitconfirm;
        printf("\t\t\tAre you sure you would like to logout?\n\t\t\t (Y/N)\n");
                printf("\t\t\t>");
                scanf(" %c", &exitconfirm);
                exitconfirm = toupper(exitconfirm);

        if (exitconfirm == 'N')
        {
            system("cls");
            return false;
        }
        else if (exitconfirm == 'Y')
        {
            system("cls");
            printf("\t\t\t***__________Bank of the Enrique_________***\n");
            printf("\t\t\t You have chosen to Logout...\n");
            printf("\t\t\t Logging out. :)\n");
            getch();
            system("cls"); 
            getchar();
            return true;
        }
        else
        {
            system("cls");
            printf("\t\t\tNot a valid answer.\n");
            getch();
            exitconfirm = '\0';
        };
    }
}

void failedtoOpenFile() {
    fprintf(stderr, "\t\t\tCan't open file");
    getch();
    exit(0);
}
