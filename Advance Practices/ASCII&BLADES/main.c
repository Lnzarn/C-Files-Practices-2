#include "headers.h"
#include "data.c"
int firstPageScreen();
void firstpageMenuLogic(int choice);
void createNewGame();
void loadExistingGame();
void loadWelcomescreen();
void combatscreen();
void randomEnemy();
int checkforHealth();
void checkforLevelUp();
void saveCurrentFile();
struct Character
{
    char name[80];
    int class;
    int level;
};
int characterexist = 0;
char constantplayername[80];
int constantclass;
int constantlevel;
int constanthp;
int constantenemyhp;
int accumulatedEXP;

int main()
{
    do
    {
        system("cls");
        int firstpagechoice = firstPageScreen();
        firstpageMenuLogic(firstpagechoice);
    } while (characterexist != 1);
    combatscreen();

    return 0;
}
void combatscreen()
{
    int combatchoice;
    int attackchoice;
    int runaway = 0;
    constanthp = statclass[constantclass].hp;
    do
    {
        system("cls");
        randomEnemy();
        printf("\n===============================\n");
        printf("A Wild %s has Appeared!\n", currentEnemy.enemyname);
        printf("\n===============================\n");
        getchar();
        do
        {
            system("cls");
            printf("%s        Lvl.%d Swordsman\n", constantplayername, constantlevel);
            printf("===============================\n");
            printf("You\tHP:  %d/%d\n", constanthp, statclass[constantclass].hp);
            printf("Enemy\tHP:  %d/%d\n", constantenemyhp, currentEnemy.hp);
            printf("Enemy Name: %s\n", currentEnemy.enemyname);
            printf("-------------------------------\n");
            printf("Choose your action:\n");
            printf("[1] Attack\n[2] Defend\n[3] Use Item\n[4] Run\n");
            printf(">");
            scanf("%d", &combatchoice);
            switch (combatchoice)
            {
            case 1:
                int characterdmg = 0;
                printf("[1] %s [2] %s\n>", statclass[constantclass].attacks[0].attackname,
                       statclass[constantclass].attacks[1].attackname);
                scanf("%d", &attackchoice);
                characterdmg = statclass[constantclass].atk * statclass[constantclass].attacks[attackchoice - 1].multiplier;
                if (statclass[constantclass].speed >= currentEnemy.speed)
                {
                    constantenemyhp = constantenemyhp - characterdmg;
                    printf("\nYour %s did %d damage to %s\n", statclass[constantclass].attacks[combatchoice].attackname, characterdmg, currentEnemy.enemyname);
                    if (checkforHealth() == 1)
                    {
                        break;
                    }
                    constanthp = constanthp - currentEnemy.atk;
                    printf("\n%s has Attacked You!\nHealth - %d\n", currentEnemy.enemyname, currentEnemy.atk);
                }
                else
                {
                    constanthp = constanthp - currentEnemy.atk;
                    printf("\n%s has Attacked You!\nHealth - %d\n", currentEnemy.enemyname, currentEnemy.atk);
                    if (checkforHealth() == 0)
                    {
                        break;
                    }
                    constantenemyhp = constantenemyhp - characterdmg;
                    printf("\nYour %s did %d damage to %s\n", statclass[constantclass].attacks[combatchoice].attackname, characterdmg, currentEnemy.enemyname);
                }
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                printf("\nYou ran away!");
                runaway = 1;
                break;
            default:
                break;
            }
            getchar();
            while (getchar() != '\n')
                ;
        } while (constantenemyhp != 0 && constantenemyhp > 0 && constanthp > 0 && runaway != 1);
    } while (constanthp > 0 && runaway != 1);
    saveCurrentFile();
}

void saveCurrentFile()
{
    FILE *fp, *temp;
    struct Character charac;
    fp = fopen("Saves.bin", "rb");
    temp = fopen("Savestemp.bin", "wb");
    while (fread(&charac, sizeof(struct Character), 1, fp))
    {
        if (strcmp(constantplayername, charac.name) == 0 && constantclass + 1 == charac.class)
        {
            charac.level = constantlevel;
        }
        fwrite(&charac, sizeof(struct Character), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    fp = fopen("Saves.bin", "wb");
    temp = fopen("Savestemp.bin", "rb");
    while (fread(&charac, sizeof(struct Character), 1, temp))
    {
        fwrite(&charac, sizeof(struct Character), 1, fp);
    }
    fclose(fp);
    fclose(temp);
    remove("./Savestemp.bin");
    printf("\nProgress has been saved.");
}
void checkforLevelUp()
{
    if (accumulatedEXP > 99)
    {
        accumulatedEXP -= 100;
        constantlevel += 1;
        printf("\nYou have leveled up! You are now lvl.%d", constantlevel);
    }
}
int checkforHealth()
{
    if (constantenemyhp < 0 || constantenemyhp == 0)
    {
        printf("\n%s has died!", currentEnemy.enemyname);
        accumulatedEXP += currentEnemy.expdrop;
        checkforLevelUp();
        getchar();
        return 1;
    }
    else if (constanthp < 0 || constanthp == 0)
    {
        printf("\nYou have died!");
        getchar();
        return 0;
    }
}
void randomEnemy()
{
    srand(time(NULL));
    int roll = rand() % 100 + 1;

    if (roll <= 50)
    {
        int i = rand() % 3;
        currentEnemy = LowEnemy[i];
        constantenemyhp = currentEnemy.hp;
    }
    else if (roll <= 85)
    {
        int i = rand() % 3;
        currentEnemy = MidEnemy[i];
        constantenemyhp = currentEnemy.hp;
    }
    else if (roll <= 95)
    {
        int i = rand() % 7;
        currentEnemy = HighEnemy[i];
        constantenemyhp = currentEnemy.hp;
    }
    else
    {
        int i = rand() % 2;
        currentEnemy = BossEnemy[i];
        constantenemyhp = currentEnemy.hp;
    }
}
void createNewGame()
{
    FILE *fp;
    fp = fopen("Saves.bin", "ab");
    struct Character charac;
    printf("\n====================================\n");
    printf("\t Character Creation\n");
    printf("____________________________________\n");
    printf("Name of your Character: ");
    scanf("%s", charac.name);
    printf("\n\t Possible Classes\n");
    printf("     [1] Swordsman [2] Archer\n");
    printf("     [3] Assassin  [4] Wizard\n");
    printf("====================================\n");
    printf("\t > ");
    scanf("%d", &charac.class);
    charac.level = 0;
    fwrite(&charac, sizeof(struct Character), 1, fp);
    fclose(fp);
    strcpy(constantplayername, charac.name);
    constantclass = charac.class - 1;
    constantlevel = charac.level;
    system("cls");
    loadWelcomescreen();
    characterexist = 1;
    system("cls");
}

void loadExistingGame()
{
    FILE *fp;
    fp = fopen("Saves.bin", "rb");
    if (!fp)
    {
        printf("File doesn't Exist");
    }
    struct Character charac;
    printf("\nExisting characters\n");
    int listno = 1;
    char buffername[80];
    int bufferclass;
    while (fread(&charac, sizeof(struct Character), 1, fp))
    {
        printf("%d. Name: %s, Class: %s, Lvl. %d\n", listno, charac.name, classes[charac.class - 1], charac.level);
        listno += 1;
    }
    printf("Please enter the name: ");
    scanf("%s", buffername);
    printf("Please enter the class:\n");
    printf("\t[1] Swordsman [2] Archer\n");
    printf("\t[3] Assassin  [4] Wizard\n");
    printf(">");
    scanf("%d", &bufferclass);
    fseek(fp, 0, SEEK_SET);
    int found = 0;
    while (fread(&charac, sizeof(struct Character), 1, fp))
    {
        if (strcmp(buffername, charac.name) == 0 && bufferclass == charac.class)
        {
            strcpy(constantplayername, charac.name);
            constantclass = charac.class - 1;
            constantlevel = charac.level;
            system("cls");
            loadWelcomescreen();
            found = 1;
            characterexist = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\n\nCharacter doesn't exist.");
        while (getchar() != '\n')
            ;
        getchar();
        characterexist = 0;
    }
    fclose(fp);
}
void firstpageMenuLogic(int choice)
{
    char temp[80];
    switch (choice)
    {
    case 1:
        createNewGame();
        break;
    case 2:
        system("cls");
        loadExistingGame();
        break;
    case 3:
        printf("\n\n 3 Chosen");
        break;
    case 4:
        printf("\n\n 4 Chosen");
        break;
    default:
        break;
    }
}

int firstPageScreen()
{
    int firstpagechoice;
    do
    {
        printf("\n====================================\n");
        printf("\t     A  &  B\n");
        printf("\t  ASCII & BLADES\n");
        printf("____________________________________\n");
        printf("\t  [1] New Game\n");
        printf("\t  [2] Load Game\n");
        printf("\t  [3] About\n");
        printf("\t  [4] Exit\n");
        printf("====================================\n");
        printf("\t > ");
        scanf("%d", &firstpagechoice);
        if (firstpagechoice > 4 || firstpagechoice < 1)
        {
            printf("\nPlease enter the appropriate number for your desired action.");
        }
        else if (firstpagechoice != 4)
        {
            return firstpagechoice;
        }
    } while (firstpagechoice != 4);
}

void loadWelcomescreen()
{
    while (getchar() != '\n')
        ;
    printf("\n====================================\n");
    printf("   Welcome to the ASCII & BLADES!\n\n Dear, %s.\n ", constantplayername);
    printf("Start your journey as a %s.\n Good Luck!\n\t\t-A&B\n", classes[constantclass]);
    printf("====================================\n");
    getchar();
}