#include "Baccount.h"
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//problem if similar first name, it asks for the two passwords.

int main()
{
    char startChoice;
    bool loggedin = false;
    char Baccount_Loggedin[20];

    while (1) {
        do
        {
            startChoice = '\0';
            startingScreen(&startChoice);
        } while (startChoice != 'Y');

        loginscreen(loggedin);

        strcpy(Baccount_Loggedin, checkpassword());

        int mainchoice;
        bool exitMainScreen = false;
        
        do
        {
            mainchoice = mainscreen(Baccount_Loggedin);
            mainscreenLogic(&mainchoice, Baccount_Loggedin, &loggedin, &exitMainScreen);
        } while (!exitMainScreen);
        
        loggedin = false;
    }
        

    return 0;
}



