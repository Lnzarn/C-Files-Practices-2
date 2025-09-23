#include <stdio.h>

int main()
{
    int ipa, user;

    printf("\nPlease enter your age:");
    scanf("%d", &user);

    ipa = user / 2 + 7;

    printf("\nYour ideal partner's age is %d", ipa);
    return 0;
}