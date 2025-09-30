#include <stdio.h>

int main()
{
    FILE *fp;
    fp = fopen("message.txt", "w");
    char message[100];
    printf("\nEnter a message: ");
    scanf("%s", &message);
    fprintf(fp, "%s\n", message);

    printf("\nOpening the file...");
    fclose(fp);

    fp = fopen("message.txt", "r");
    char buffer[100];
    fscanf(fp, "%s\n", buffer);
    printf("\n\nYour message is: %s", buffer);

    fclose(fp);
    return 0;
}