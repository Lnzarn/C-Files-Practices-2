#include <stdio.h>

struct student
{
    char name[80];
    int grades;
};

void Displayrecord()
{
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        printf("\nNo records found or error opening file.\n");
        return;
    }

    struct student std1;
    printf("\nStudent Record\n");
    printf("--------------\n");

    while (fscanf(fp, "%79s %d", std1.name, &std1.grades) == 2)
    {
        printf("Student name: %s\n", std1.name);
        printf("Grades: %d\n\n", std1.grades);
    }

    fclose(fp);
}

void Writerecord()
{
    FILE *fp = fopen("student.txt", "a"); // Changed to "a" to append rather than overwrite
    if (fp == NULL)
    {
        printf("\nError opening file for writing.\n");
        return;
    }

    struct student std1;
    int exit = 0;

    do
    {
        printf("Enter name: ");
        scanf("%79s", std1.name);
        printf("Enter grades: ");
        scanf("%d", &std1.grades);
        fprintf(fp, "%s %d\n", std1.name, std1.grades);

        printf("Enter 1 to exit or 0 to continue: ");
        scanf("%d", &exit);
    } while (exit != 1);

    fclose(fp);
}

int main()
{
    int choice = 0;

    do
    {
        printf("\n1. Display record");
        printf("\n2. Write record");
        printf("\n3. Exit");
        printf("\n_______________\n> ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (choice > 3 || choice < 1)
        {
            printf("Please choose the appropriate number (1-3).\n");
        }
        else if (choice != 3)
        {
            switch (choice)
            {
            case 1:
                Displayrecord();
                break;
            case 2:
                Writerecord();
                break;
            default:
                break;
            }
        }
    } while (choice != 3);

    printf("Exiting program.\n");
    return 0;
}