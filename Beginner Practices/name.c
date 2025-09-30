#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    fp = fopen("name.txt", "w");
    fclose(fp);
    fp = fopen("name.txt", "a");

    int exit = 0;

    printf("\nEnter the names\n");
    do
    {
        char temp[80];
        printf(">");
        scanf("%79s", temp);
        temp[0] = toupper(temp[0]);
        if (strcmp(temp, "Exit") == 0)
        {
            exit = 1;
        }
        else
        {
            fprintf(fp, "%s\n", temp);
        }
    } while (exit != 1);

    fclose(fp);
    fp = fopen("name.txt", "r");

    char values[80];
    printf("\n\nNow showing the names:\n");
    while (fgets(values, sizeof(values), fp) != NULL)
    {
        printf("%s", values);
    };

    fclose(fp);
}