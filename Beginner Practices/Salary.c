#include <stdio.h>

int main()
{
    char name[80];
    float hours = 0;
    float gross_pay = 0;
    float withholding = 0;
    float net_pay = 0;

    printf("Please enter your name and how many hours you've worked for:\n>");
    scanf("%s", &name);
    scanf("%f", &hours);

    gross_pay = hours * 281;
    withholding = gross_pay * 0.21;
    net_pay = gross_pay - withholding;

    printf("\nHello, %s!\n\n", name);
    printf("Hourly rate:  281.00\n");
    printf("Hours worked: %.2f\n", hours);
    printf("Gross Pay:    %.2f\n", gross_pay);
    printf("Withholding:  %.2f\n", withholding);
    printf("Net pay:      %.2f\n", net_pay);

    return 0;
}