#include <stdio.h>
#include <string.h>
struct filevalue
{
    char name[80];
    int grades;
};

void Writefile()
{
    FILE *fp;
    char filename[80];
    printf("\nEnter a file name: ");
    scanf("%s", filename);
    strcat(filename, ".txt");
    fp = fopen(filename, "w");
    int buffercontinue = 0;
    char temp[80];
    struct filevalue file;
    do
    {
        printf("\nEnter a name: ");
        scanf("%s", file.name);
        printf("\nEnter grades: ");
        scanf("%d", &file.grades);

        fprintf(fp, "%s\t %d\n", file.name, file.grades);
        printf("Continue? press 0\n>");
        scanf("%d", &buffercontinue);
    } while (buffercontinue != 1);
}

int main()
{
    int choice = 0;

    do
    {
        printf("\n1. Write a file");
        printf("\n2. Append to an existing file");
        printf("\n3. Display a file");
        printf("\n4. Delete a file");
        printf("\n5. Exit");
        printf("\n________________");
        printf("\n>");
        scanf("%d", &choice);
        if (choice > 5 || choice < 1)
        {
            printf("Please enter the appropriate number.");
        }

        switch (choice)
        {
        case 1:
            Writefile();
            break;
        case 2:
            // Appendfile();
            break;
        case 3:
            // Displayfile();
            break;
        case 4:
            // Deletefile();
            break;
        default:
            break;
        }
    } while (choice != 5);

    return 0;
}