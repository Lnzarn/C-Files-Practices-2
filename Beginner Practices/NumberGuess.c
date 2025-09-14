#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    const int MIN = 1;
    const int MAX = 100;
    int guess;
    int guesses;
    int answer;

    srand(time(0));

    answer = (rand() % MAX) + MIN;

    do
    {
        printf("Guess the answer!:");
        scanf("%d", &guess);

        if (guess > answer)
        {

            printf("Too High!\n");
        }
        else if (guess < answer)
        {

            printf("Too Low!\n");
        }
        else
        {

            printf("Correct!\n");
        }

        guesses++;
    } while (guess != answer);

    printf("******************************\n");
    printf("The answer was:%d\n", answer);
    printf("Your final Guess was:%d\n", guess);
    printf("Total guesses:%d\n", guesses);
    printf("******************************");

    return 0;
}