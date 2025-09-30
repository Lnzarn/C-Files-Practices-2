#include "Baccount.h"
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
bool lookforBankNoRepeats(FILE *Bfile, int buffer[]){
    struct Baccount info;
    size_t i;

    while (fread(&info, sizeof(struct Baccount), 1, Bfile))
    {
        if (*buffer == info.bank_No)
        {
            for (i = 0; i < 10 - 1; i++) 
            {
            size_t j = i + rand() / (RAND_MAX / (10 - i) + 1);
            int t = buffer[j];
            buffer[j] = buffer[i];
            buffer[i] = t;
            }
            
        } else return false;
    }
}
void getbankNo(int buffer[]){
    srand(time(NULL));
    int temp;
    for (int i = 0; i < 10; i++) {
        temp = rand() % 9;
        buffer[i] = abs(temp);
    }
}
void startingScreen(char *startChoice) {
    printf("\t\t\t***___________________________________________________***\n");
    printf("\t\t\tHello, User! Would you like to open a Bank account? (y/n)\n");
    printf("\t\t\t>");

    validateCharacterInput(startChoice);
    *startChoice = toupper(*startChoice);

    if (*startChoice == 'N') {
        exitProgram();
    }
}

void loginscreen(bool loggedin)
{
    int choice;
    bool checkloggedin = false;

    while (loggedin == false && checkloggedin == false && choice != 3)
    {
        while (checkloggedin == false && choice != 3)
        {
            displayLoginMenu(&checkloggedin, &choice);
        };
    };
};

bool loginaccount()
{
    FILE *Bfile = fopen(FILENAME, "r");
    
    if (Bfile == NULL)
    {
        fprintf(stderr, "\t\t\tThere is no accounts.");
        getch();
        exit(0);
    }

    displayBankAccounts(Bfile);
    fclose(Bfile);
    return true;
};

void makeaccount()
{
    FILE *Bfile = fopen(FILENAME, "a+");
    if (Bfile == NULL)
    {
        fprintf(stderr, "\t\t\tCan't open file");
        getch();
        exit(0);
    }
    struct Baccount info;
    int buffer[10];
    bool repeat = true;

    getAccountDetails(&info);
    getBankSubscription(&info);
    getbankNo(buffer);
    
    while(repeat) {
        repeat = lookforBankNoRepeats(Bfile, buffer);
    }
    info.balance = 0;
    fwrite(&info, sizeof(struct Baccount), 1, Bfile);
    fclose(Bfile);

    printf("\t\t\tYou have now made a new bank account!\n\t\t\t");
};

char *checkpassword()
{
    FILE *Bfile = fopen(FILENAME, "r");
    struct Baccount info;
    char accountSearch[50];
    int found = 0;
    char passwordcheck[20];
    int check = 0;
    char *firstname_buffer;
    firstname_buffer = (char *)malloc(20 * sizeof(char));

    while (found != 1)
    {
        rewind(Bfile);
        printf("\t\t\t***__________Bank of the Enrique_________***\n");
        printf("\t\t\tWhich account would you like to login?\n\t\t\t (Please enter the First Name.)\n");
        printf("\t\t\t>");
        fgets(accountSearch, 50, stdin);
        accountSearch[strcspn(accountSearch, "\n")] = '\0';
        system("cls");
        while (fread(&info, sizeof(struct Baccount), 1, Bfile))
        {
            if (strcmp(accountSearch, info.first_name) == 0)
            {
                do
                {
                    found = 1;
                    printf("\t\t\t***__________Bank of the Enrique_________***\n");
                    printf("\t\t\tName:       %s %s\n", info.first_name, info.last_name);
                    printf("\t\t\tPassword:   ");
                    scanf("%s", passwordcheck);
                    if (strcmp(passwordcheck, info.password) == 0)
                    {
                        check = 1;
                        system("cls");
                        printf("\t\t\t***__________Bank of the Enrique_________***\n");
                        printf("\n\t\t\tNow entering! Hello %s!\n", info.first_name);
                        printf("\n\t\t\t***_______________________________________***\n");
                        strcpy(firstname_buffer, info.first_name);
                        getch();
                        system("cls");
                    }
                    else
                    {
                        system("cls");
                        printf("\t\t\tThat was the wrong password! Please try again.");
                        getch();
                        system("cls");
                    };

                } while (check == 0);
            };

            if (!found)
            {
                printf("\t\t\tNow Loading...");
                system("cls");
            };
        };
    };
    fclose(Bfile);

    return firstname_buffer;
};


//////////
//Broken Down Functions
//////////


void exitProgram() {
    system("cls");
    printf("\t\t\t***__________Bank of the Enrique_________***\n");
    printf("\t\t\t You have chosen to Exit the program...\n");
    printf("\t\t\t Closing the program. :)");
    printf("\n\t\t\t***___________________________________________***\n");
    getch();
    exit(0);
}

void displayLoginMenu(bool *checkloggedin, int *choice) {
    
    system("cls");
    printf("\t\t\t***__________Bank of the Enrique_________***\n");
    printf("\t\t\t\tWhat would you like to do?\n");
    printf("\n\t\t\t\t1. Login an Existing Account\n");
    printf("\n\t\t\t\t2. Make a new Account\n");
    printf("\n\t\t\t\t3. Exit\n");
    printf("\t\t\t***_______________________________________***\n");
    printf("\t\t\t\t>");
    scanf("%d", choice);
    getchar();

    switch (*choice)
            {
            case 1:
                system("cls");
                *checkloggedin = loginaccount();
                getch();
                system("cls");
                break;

            case 2:
                system("cls");
                makeaccount();
                getch();
                system("cls");
                break;
               
            case 3:
                exitProgram();

            default:
                system("cls");
                break;
            }

}

void displayBankAccounts(FILE *Bfile) {
    struct Baccount info;
    int accountNo = 1;

    printf("\t\t\tExisting Bank Accounts:\n");
    printf("\t\t\t***__________Bank of the Enrique_________***\n");

    while (fread(&info, sizeof(struct Baccount), 1, Bfile))
    {
        printf("\n\t\t\tAccount No. %d\n", accountNo);
        printf("\t\t\tName:     %s %s\n", info.first_name, info.last_name);
        printf("\t\t\tBank:     %s\n", info.bank_brand);
        printf("\t\t\tBank No.: %d\n", info.bank_No);
        printf("\t\t\t***_______________________________________***\n");
        accountNo += 1;
    }

    printf("\n\t\t\tPress Any Key to continue.\n\t\t\t");
}

void getAccountDetails(struct Baccount *info) {
    char buffer[100];
    char longerbuffer[150];
    printf("\t\t\t***__________Bank of the Enrique_________***\n");
    printf("\t\t\tYou are now currently making a new account.\n");

    //First Name
    validateStringInputNoNumber("\n\t\t\tEnter First Name:", buffer, 20);
    strncpy(info->first_name, buffer, 19);
    info->first_name[19] = '\0';
        
    //Last Name
    validateStringInputNoNumber("\n\t\t\tEnter Last Name:", buffer, 20);
    strncpy(info->last_name, buffer, 19);
    info->last_name[19] = '\0';

    //Password
    validateStringInput("\n\t\t\tEnter Password:", buffer, 20);
    strncpy(info->password, buffer, 19);
    info->password[19] = '\0';

    //PIN
    validateStringInput("\n\t\t\tEnter PIN:", buffer, 7);
    strncpy(info->pin, buffer, 6);
    info->pin[6] = '\0';

    //Birthday
    longerbuffer[0] = '\0';
    printf("\n\t\t\t*_Enter your Birthday (YYYY-MM-DD)_*\n\n");
    validateStringInputOnlyNumber("\n\t\t\tEnter Year of Birth:", buffer, 5);
    strncat(longerbuffer, buffer, 4);
    strcat(longerbuffer, "-");
    validateStringInputOnlyNumber("\n\t\t\tEnter Month of Birth:", buffer, 3);
    strncat(longerbuffer, buffer, 2);
    strcat(longerbuffer, "-");
    validateStringInputOnlyNumber("\n\t\t\tEnter Day of Birth:", buffer, 3);
    strncat(longerbuffer, buffer, 2);
    strncpy(info->date_of_birth, longerbuffer, 11);
    info->date_of_birth[10] = '\0';

    //Email
    validateStringInputforEmail("\n\t\t\tEnter Email Address:", buffer, 80);
    strncpy(info->email_address, buffer, 79);
    info->email_address[79] = '\0';

    //Address
    longerbuffer[0] = '\0';
    printf("\n\t\t\t*_Enter your Address_*\n\n");
    validateStringInput("\n\t\t\tEnter StreetNo./BuildingNo.:", buffer, 50);
    strncat(longerbuffer, buffer, 49);
    strcat(longerbuffer, ", ");
    validateStringInput("\n\t\t\tEnter Barangay:", buffer, 50);
    strncat(longerbuffer, buffer, 49);
    strcat(longerbuffer, ", ");
    validateStringInput("\n\t\t\tEnter Municipality:", buffer, 50);
    strncat(longerbuffer, buffer, 49);
    strncpy(info->address, longerbuffer, 149);
    info->address[149] = '\0';

    //Citizen
    validateStringInputNoNumber("\n\t\t\tEnter Citizenship(e.g. Filipino):", buffer, 30);
    strncpy(info->citizenship, buffer, 29);
    info->citizenship[29] = '\0';
}

void getBankSubscription(struct Baccount *info) {
    int choice;
    system("cls");
    printf("\t\t\t***____________Available Banks____________***\n");
    printf("\t\t\tWhich Bank would you like to subscribe to?\n\n");
    printf("\t\t\t\t1. Bank of the Enrique\n");
    printf("\t\t\t\t2. Metrobank\n");
    printf("\t\t\t\t3. Philippine National Bank\n");
    printf("\t\t\t\t4. BDO\n");
    printf("\t\t\t\t5. United Enrique Bank\n");
    printf("\t\t\t\t6. Golden Bank\n");
    printf("\n\t\t\t***_______________________________________***\n");
    printf("\t\t\t\t>");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        strncpy(info->bank_brand, "Bank of the Enrique", 50);
        break;

    case 2:
        strncpy(info->bank_brand, "Metrobank", 50);
        break;

    case 3:
        strncpy(info->bank_brand, "Philippine National Bank", 50);
        break;

    case 4:
        strncpy(info->bank_brand, "BDO", 50);
        break;

    case 5:
        strncpy(info->bank_brand, "United Enrique Bank", 50);
        break;

    case 6:
        strncpy(info->bank_brand, "Golden Bank", 50);
        break;
    default:
        printf("\t\t\tNot a supported bank, now assigning the standard bank.\n");
        strncpy(info->bank_brand, "Bank of the Enrique", 50);
        break;
    };
}