#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void addStudent();
void studentRecord();
void searchStudent();
void deleteStudent();

struct student
{
    char first_name[20];
    char last_name[20];
    int student_no;
    char section[10];
    char address[20];
    float average;
};

void main()
{
    int choice;

    while (choice != 5)
    {
        printf("\t\t---Welcome to the Student Database---");
        printf("\n\n\t\tPlease choose your actions.\n\n");
        printf("\t\t 1. Add a New Student Record\n");
        printf("\t\t 2. Check the Student Records\n");
        printf("\t\t 3. Search for a Student Record\n");
        printf("\t\t 4. Delete an Existing Record\n");
        printf("\t\t 5. Exit\n");
        printf("\t\t _______________________________\n");
        printf("\t\t");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            addStudent();
            system("cls");
            break;

        case 2:
            system("cls");
            studentRecord();
            printf("\t\tPress any key to exit.\n");
            getch();
            system("cls");
            break;

        case 3:
            system("cls");
            searchStudent();
            printf("\t\tPress any key to exit.\n");
            getch();
            system("cls");
            break;

        default:
            break;
        }
    }
}

void addStudent()
{
    char another;
    FILE *fp;
    struct student info;

    do
    {
        system("cls");
        printf("\t\t---Add New Student Record---");
        fp = fopen("Records", "a");
        printf("\n\t\tEnter first name:");
        scanf("%s", &info.first_name);
        printf("\n\t\tEnter last name:");
        scanf("%s", &info.last_name);
        printf("\n\t\tEnter student no.:");
        scanf("%d", &info.student_no);
        printf("\n\t\tEnter section:");
        scanf("%s", &info.section);
        printf("\n\t\tEnter address:");
        scanf("%s", &info.address);
        printf("\n\t\tEnter average grades:");
        scanf("%f", &info.average);
        printf("\n\t\t_______________________________\n");

        if (fp == NULL)
        {
            fprintf(stderr, "\t\tCan't open file");
        }
        else
        {
            printf("\t\tRecord stored succesfully.");
        };

        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);

        printf("\n\t\tDo you want to continue adding student records? Y/N");
        scanf("%s", &another);
        another = toupper(another);

    } while (another == 'Y');
}

void studentRecord()
{
    FILE *fp;
    struct student info;
    fp = fopen("Records", "r");

    printf("\t\t---Student Records---\n\n");

    if (fp == NULL)
    {
        fprintf(stderr, "\t\tCan't open file");
    }
    else
    {
        printf("\t\tRecords\n");
        printf("\t\t_______________________________\n\n");
    };

    while (fread(&info, sizeof(struct student), 1, fp))
    {
        printf("\n\t\tStudent's name      : %s %s", info.first_name, info.last_name);
        printf("\n\t\tStudent no.         : %d", info.student_no);
        printf("\n\t\tStudent's section   : %s", info.section);
        printf("\n\t\tStudent's address   : %s", info.address);
        printf("\n\t\tStudent's grades    : %.2f", info.average);
        printf("\n\t\t__________________________________\n");
    };
    fclose(fp);
    getch();
}

void searchStudent()
{
    FILE *fp;
    struct student info;
    fp = fopen("Records", "r");
    int searchNo;
    int found = 0;

    printf("\t\t---Student Records---\n\n");
    printf("\t\tPlease enter the Student No.\n");
    printf("\t\t>");
    scanf("%d", &searchNo);

    while (fread(&info, sizeof(struct student), 1, fp))
    {
        if (info.student_no == searchNo)
        {
            found = 1;
            printf("\n\t\tStudent's name      : %s %s", info.first_name, info.last_name);
            printf("\n\t\tStudent no.         : %d", info.student_no);
            printf("\n\t\tStudent's section   : %s", info.section);
            printf("\n\t\tStudent's address   : %s", info.address);
            printf("\n\t\tStudent's grades    : %.2f", info.average);
            printf("\n\t\t__________________________________\n");
        }
    };

    if (!found)
    {
        printf("Record not found.");
    }
    fclose(fp);
    getch();
}