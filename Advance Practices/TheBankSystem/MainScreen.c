#include "Baccount.h"
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TEMPFILE "Temp.txt"


int mainscreen(char *user)
{
    int choice;
    printf("\t\t\t***____________Bank of the Enrique___________***\n");
    printf("\n\t\t\tWelcome, %s! What would you like to do?\n", user);
    printf("\n\t\t\t1. Check Balance.\n");
    printf("\n\t\t\t2. Withdraw.\n");
    printf("\n\t\t\t3. Deposit.\n");
    printf("\n\t\t\t4. Transfer.\n");
    printf("\n\t\t\t5. View Account Details.\n");
    printf("\n\t\t\t6. Change Password.\n");
    printf("\n\t\t\t7. Rules & Regulations.\n");
    printf("\n\t\t\t8. Logout.\n");
    printf("\n\t\t\t***___________________________________________***\n");
    printf("\t\t\t\t>");
    scanf("%d", &choice);
    getchar();
    
    return choice;
};

void mainscreenLogic(int *mainchoice, char *Baccount_Loggedin, bool *loggedin, bool *exitMainScreen){
    switch (*mainchoice)
            {
            case 1:
                system("cls");
                checkbalance(Baccount_Loggedin);
                getch();
                system("cls");
                break;

            case 2:
                system("cls");
                withdraw(Baccount_Loggedin);
                system("cls");
                break;

            case 3:
                system("cls");
                deposit(Baccount_Loggedin);
                system("cls");
                break;

            case 4:
                system("cls");
                bankTransfer(Baccount_Loggedin);
                system("cls");
                break;
            
            case 5:
                system("cls");
                viewAccountDetails(Baccount_Loggedin);
                getch();
                system("cls");
                break;
                
            case 6:
                system("cls");
                break;

            case 7:
                system("cls");
                showrules();
                getch();
                system("cls");
                break;

            case 8:
                if (validateConfirmationOfLogout(loggedin)) {
                    *exitMainScreen = true;
                }
                break;

            default:
                break;
            }
}

void checkbalance(char *user)
{
    FILE *Bfile = fopen(FILENAME, "r");
    struct Baccount info;
    int found = 0;

    if (Bfile == NULL)
    {
        failedtoOpenFile();
    }

    while (fread(&info, sizeof(struct Baccount), 1, Bfile))
    {
        if (strcmp(user, info.first_name) == 0)
        {
            found = 1;
            printf("\t\t\t***__________Bank of the Enrique_________***\n");
            printf("\n\t\t\tYour Balance: PHP %.2f\n", info.balance);
            printf("\n\t\t\tBank        : %s\n", info.bank_brand);
            printf("\n\t\t\t***___________________________________________***\n");
        };

        if (!found)
        {
            printf("\t\t\tNow Loading...");
            system("cls");
        };
    };
    fclose(Bfile);
};

//other 
void viewAccountDetails(char *user)
{
    FILE *Bfile = fopen(FILENAME, "r");
    struct Baccount info;
    int found = 0;

    if (Bfile == NULL)
    {
        failedtoOpenFile();
    }

    while (fread(&info, sizeof(struct Baccount), 1, Bfile))
    {
        if (strcmp(user, info.first_name) == 0)
        {
            found = 1;
            printf("\t\t\t***__________Bank of the Enrique_________***\n");
            printf("\n\t\t\tName         : %s %s\n", info.first_name, info.last_name);
            printf("\n\t\t\tDate of Birth: %s\n", info.date_of_birth);
            printf("\n\t\t\tEmail Address: %s\n", info.email_address);
            printf("\n\t\t\tAddress      : %s\n", info.address);
            printf("\n\t\t\tCitizenship  : %s\n", info.citizenship);
            printf("\n\t\t\tYour Balance : PHP %.2f\n", info.balance);
            printf("\n\t\t\tBank         : %s\n", info.bank_brand);
            printf("\n\t\t\tPassword     : %s\n", info.password);
            printf("\n\t\t\tPIN No.      : %s\n", info.pin);
            printf("\n\t\t\t***___________________________________________***\n");
        };

        if (!found)
        {
            printf("\t\t\tNow Loading...");
            system("cls");
        };
    };
    fclose(Bfile);
};

void withdraw(char *user){
    FILE *Bfile, *Bfile1;
    Bfile = fopen(FILENAME, "r");
    Bfile1 = fopen(TEMPFILE, "w");

    if (Bfile == NULL)
    {
        failedtoOpenFile();
    }

    struct Baccount info;

    int found = 0;
    bool balanceFlag = false;
    float balanceBuffer;
    float withdrawal;
    float result;

    while (fread(&info, sizeof(struct Baccount), 1, Bfile))
    {
        if (strcmp(user, info.first_name) == 0)
        {
            while (balanceFlag == false)
            { 
                found = 1;
                withdrawal = inputMoneyforProcedure("Withdrawed");

                if (withdrawal <= 0)
                {
                    balanceFlag = asktoCancelProcedure("Withdrawal");
                }
                else
                {
                    balanceBuffer = info.balance;
                    result = balanceBuffer - withdrawal;

                    if (result < 0)
                    {
                            system("cls");
                            printf("\t\t\t***__________Bank of the Enrique_________***\n");
                            printf("\t\t\tYou have insufficient balance to proceed with the withdrawal.\n");
                            balanceFlag = asktoCancelProcedure("Withdrawal");
                    }
                    else
                    {
                        balanceFlag = true;
                        info.balance = result;
                        displaySuccessfulProcedure("Withdrawing");
                    };
                };
            };
        };

        if (!found)
        {
            printf("\t\t\tNow Loading...");
            system("cls");
        };

        fwrite(&info, sizeof(struct Baccount), 1, Bfile1);
    };
    fclose(Bfile);
    fclose(Bfile1);


    if (found)
    {
        implementChangesinFile(Bfile, Bfile1);
    };
};

void deposit(char *user)
{
    FILE *Bfile, *Bfile1;
    Bfile = fopen(FILENAME, "r");
    Bfile1 = fopen(TEMPFILE, "w");
    if (Bfile == NULL)
    {
        failedtoOpenFile();
    }

    struct Baccount info;
    int found = 0;
    bool balanceFlag = false;
    float balancebuff;
    float deposit;
    float result;

    while (fread(&info, sizeof(struct Baccount), 1, Bfile))
    {
        if (strcmp(user, info.first_name) == 0)
        {
            while (balanceFlag == false)
            {
                found = 1;
                deposit = inputMoneyforProcedure("Deposited");
                if (deposit <= 0)
                {
                    balanceFlag = asktoCancelProcedure("Deposit");
                }
                else
                {
                    balancebuff = info.balance;
                    result = balancebuff + deposit;

                    if (result < 0)
                    {
                        system("cls");
                        printf("\t\t\t***__________Bank of the Enrique_________***\n");
                        printf("\t\t\tDeposit Failed.\n");
                        balanceFlag = asktoCancelProcedure("Deposit");
                        getch();
                        system("cls");
                    }
                    else
                    {
                        balanceFlag = true;
                        info.balance = result;
                        displaySuccessfulProcedure("Depositing");
                    };
                };
            };
        };

        if (!found)
        {
            printf("\t\t\tNow Loading...");
            system("cls");
        };

        fwrite(&info, sizeof(struct Baccount), 1, Bfile1);
    };
    fclose(Bfile);
    fclose(Bfile1);

    if (found)
    {
        implementChangesinFile(Bfile, Bfile1);
    };
};

void bankTransfer(char *user) {
    FILE *Bfile = fopen(FILENAME, "r+");
    if (Bfile == NULL) {
        failedtoOpenFile();
        return;
    }

    struct Baccount info;
    int senderFound = 0, receiverFound = 0;
    char userReceiver[20];
    float fundstobeTransferred;

    printf("\t\t\t***__________Bank of the Enrique_________***\n");
    printf("\t\t\tWho would you like to transfer funds to? (Enter the First Name)\n");
    printf("\t\t\t>");
    fgets(userReceiver, 20, stdin);
    getchar();

    printf("\t\t\t***__________Bank of the Enrique_________***\n");
    printf("\t\t\tHow much would you like to transfer?\n");
    printf("\t\t\t>");
    scanf("%f", &fundstobeTransferred);
    getchar();

    if (fundstobeTransferred <= 0) {
        printf("\t\t\tInvalid amount. Transfer failed.\n");
        fclose(Bfile);
        return;
    }

    while (fread(&info, sizeof(struct Baccount), 1, Bfile)) {
        if (strcmp(user, info.first_name) == 0) {
            senderFound = 1;
            if (fundstobeTransferred > info.balance) {
                printf("\t\t\tInsufficient balance. Transfer failed.\n");
                fclose(Bfile);
                return;
            }
            info.balance -= fundstobeTransferred;
            fseek(Bfile, -(long)sizeof(struct Baccount), SEEK_CUR);  // Move back to update the record
            fwrite(&info, sizeof(struct Baccount), 1, Bfile);
            break;
        }
    }

    if (!senderFound) {
        printf("\t\t\tSender not found. Transfer failed.\n");
        fclose(Bfile);
        return;
    }

    rewind(Bfile);

    while (fread(&info, sizeof(struct Baccount), 1, Bfile)) {
        if (strcmp(userReceiver, info.first_name) == 0) {
            receiverFound = 1;
            info.balance += fundstobeTransferred;
            fseek(Bfile, -(long)sizeof(struct Baccount), SEEK_CUR); // Move back to update the record
            fwrite(&info, sizeof(struct Baccount), 1, Bfile);
            break;
        }
    }

    if (!receiverFound) {
        printf("\t\t\tReceiver not found. Transfer failed.\n");
        fclose(Bfile);
        return;
    }

    displaySuccessfulProcedure("Transferring");

    fclose(Bfile);
}

void showrules() {
    printf("\t\t\t***_____________Rules & Regulation____________***\n");
    printf("\n\t\t\t1. Account Security:\n");
    printf("\t\t\t   - You are responsible for maintaining the confidentiality of your account\n");
    printf("\t\t\t     credentials (username, password, and PIN).\n");
    printf("\t\t\t   - Notify the bank immediately if you suspect unauthorized access.\n");

    printf("\n\t\t\t2. Transactions:\n");
    printf("\t\t\t   - All transactions are final once processed.\n");
    printf("\t\t\t   - Ensure sufficient funds before initiating withdrawals or transfers.\n");

    printf("\n\t\t\t3. Fees and Charges:\n");
    printf("\t\t\t   - Fees may apply for certain transactions, such as overdrafts or\n");
    printf("\t\t\t     international transfers. Refer to the fee schedule for details.\n");

    printf("\n\t\t\t4. Privacy Policy:\n");
    printf("\t\t\t   - Your personal and financial information is protected under our\n");
    printf("\t\t\t     Privacy Policy. We do not share your data with third parties\n");
    printf("\t\t\t     without your consent.\n");

    printf("\n\t\t\t5. Liability:\n");
    printf("\t\t\t   - The bank is not liable for losses due to unauthorized transactions\n");
    printf("\t\t\t     if you fail to secure your account credentials.\n");

    printf("\n\t\t\t6. Dispute Resolution:\n");
    printf("\t\t\t   - Report any discrepancies in your account statement within 30 days.\n");
    printf("\t\t\t   - The bank will investigate and resolve disputes promptly.\n");

    printf("\n\t\t\t***___________________________________________***\n");
}


//////////
//Broken Down Functions
//////////


float inputMoneyforProcedure(char *procedure) {
    system("cls");
    float money;
    printf("\t\t\t***__________Bank of the Enrique_________***\n");
    printf("\t\t\tPlease Input Amount of money to be %s", procedure);
    printf("\n\t\t\t>");
    scanf("%f", &money);
    getchar();
    
    return money;
}

bool asktoCancelProcedure(char *procedure){
    bool cancelation;
    char cancel;
    system("cls");
    printf("%s Failed.\n", procedure);
    printf("\t\t\tWould you like to cancel %s? (y/n) \n\t\t\t>", procedure);
    scanf("%c", &cancel);
    cancel = toupper(cancel);

    if (cancel == 'Y')
    {
        cancelation = true;
    }
    else
    {
        cancelation = false;
    }

    return cancelation;
}

void displaySuccessfulProcedure(char *procedure){
    system("cls");
    printf("\t\t\t***__________Bank of the Enrique_________***\n");
    printf("\t\t\t%s.", procedure);
    printf("\n\t\t\t***______________________________________***\n");
    getch();
    system("cls");
}

void implementChangesinFile(FILE *Bfile, FILE *Bfile1) {
    struct Baccount info;
    Bfile1 = fopen(TEMPFILE, "r");
    Bfile = fopen(FILENAME, "w");

    while (fread(&info, sizeof(struct Baccount), 1, Bfile1))
    {
        fwrite(&info, sizeof(struct Baccount), 1, Bfile);
    }
    fclose(Bfile);
    fclose(Bfile1);
}