#ifndef BACCOUNT_H
#define BACCOUNT_H

#include <stdio.h>
#include <stdbool.h>

//The File Name of the Storage
#define FILENAME "Trial.txt"

//Struct Bank Account
struct Baccount
{
    char first_name[20];
    char last_name[20];
    float balance;
    char bank_brand[50];
    char date_of_birth[11];
    char email_address[80];
    char address[150];
    char citizenship[30];
    int bank_No;
    char password[20];
    char pin[7];
};

//The Functions
void startingScreen(char *startChoice);
void loginscreen(bool);
void displayLoginMenu(bool *checkloggedin, int *choice);
void displayBankAccounts(FILE *Bfile);
void viewAccountDetails(char *user);
void makeaccount();
void getAccountDetails(struct Baccount *info);
void getBankSubscription(struct Baccount *info);
bool loginaccount();
char *checkpassword();
int mainscreen(char *);
void mainscreenLogic(int *mainchoice, char *Baccount_Loggedin, bool *loggedin, bool *exitMainScreen);
float inputMoneyforProcedure(char *procedure);
bool asktoCancelProcedure(char *procedure);
void displaySuccessfulProcedure(char *procedure);
void implementChangesinFile(FILE *Bfile, FILE *Bfile1);
void checkbalance(char *);
void withdraw(char *);
void deposit(char *);
void bankTransfer(char *user);
void showrules();

void exitProgram();

//Errorhandler Functions
void validateStringInput(char *prompt, char *buffer, int maxLength);
void validateStringInputNoNumber(char *prompt, char *buffer, int maxLength);
void validateStringInputOnlyNumber(char *prompt, char *buffer, int maxLength);
void validateStringInputforEmail(char *prompt, char *buffer, int maxLength);
void validateCharacterInput(char *input);
bool validateConfirmationOfLogout(bool *loggedin);
void failedtoOpenFile();


#endif
