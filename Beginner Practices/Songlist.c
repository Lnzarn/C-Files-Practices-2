#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void songList();
void songAdd();

struct songF
{
    char songName[50];
    char songArtist[50];
    int songNo;
};

void main()
{
    int choice;

    while (choice != 5)
    {
        printf("\t________________________________________________\n");
        printf("\t\tWelcome to the Idiotic Song List\n\n");
        printf("\t\tPlease choose an action\n\n");
        printf("\t\t1. Open the list of songs.\n");
        printf("\t\t2. Add a new song.\n");
        printf("\t\t5. Exit.\n");
        printf("\t________________________________________________\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            songList();
            getch();
            system("cls");
            break;

        case 2:
            system("cls");
            songAdd();
            system("cls");
            break;

        default:
            break;
        }
    }
}

void songList()
{
    FILE *fpsong;
    struct songF info;
    fpsong = fopen("songlist", "r");

    if (fpsong == NULL)
    {
        fprintf(stderr, "\t\tCan't open file");
    }
    else
    {
        printf("\t\t\t----Song List----\n");
        printf("\t\t_______________________________\n\n");
    };

    while (fread(&info, sizeof(struct songF), 1, fpsong))
    {
        printf("\t\tSong Name    : %s\n", info.songName);
        printf("\t\tArtist       : %s\n", info.songArtist);
        printf("\t\tSong Number  : %d\n", info.songNo);
        printf("\n\t\t______________________________\n");
    };
    fclose(fpsong);
    getch();
}

void songAdd()
{
    char another;
    FILE *fpsong;
    struct songF info;

    do
    {
        system("cls");
        fpsong = fopen("songlist", "a");
        printf("What is the song's name?:");
        scanf("%s", &info.songName);
        printf("Who made the song?:");
        scanf("%s", &info.songArtist);
        printf("When was the song published?: ");
        scanf("%d", &info.songNo);

        if (fpsong == NULL)
        {
            fprintf(stderr, "\t\tCan't open file");
        }
        else
        {
            printf("\t\tRecord stored succesfully.");
        };

        fwrite(&info, sizeof(struct songF), 1, fpsong);
        fclose(fpsong);

        printf("Do you want to add another song? (y/n):");
        scanf("%s", &another);
        another = toupper(another);

    } while (another == 'Y');
}