#include <stdio.h>
#include <ctype.h>

int main()
{
    char questions[][100] = {"1. What is my favorite Dish?:\n",
                             "2. How old am I?:\n",
                             "3. What is the name of my Dog?:\n",
                             "4. What is my mother tongue?:\n"};
    char options[][100] = {"A. Adobo", "B. Tilapia", "C. Fried Rice", "D. Siomai",
                           "A. 18", "B. 16", "C. 17", "D. 19",
                           "A. Oreo", "B. Yumi", "C. Whitey", "D. Charles",
                           "A. English", "B. Sanskrit", "C. Tagalog", "D. Hangul"};
    char answers[4] = {'C', 'A', 'B', 'C'};
    int numberOfQuestions = sizeof(questions) / sizeof(questions[0]);

    char guess;
    int score;

    printf("QUIZ GAME: Lanz Version!\n");

    for (int i = 0; i < numberOfQuestions; i++)
    {
        printf("**********************\n");
        printf("%s\n", questions[i]);
        printf("**********************\n");

        for (int j = (i * 4); j < (i * 4) + 4; j++)
        {
            printf("%s\n", options[j]);
        }

        printf("Input your guess:");
        scanf("%c", &guess);
        scanf("%c");
        scanf("%c");
        guess = toupper(guess);

        if (guess == answers[i])
        {
            printf("CORRECT!\n");
            score++;
        }
        else
        {
            printf("WRONG!\n");
        }
    }

    printf("**********************\n");
    printf("FINAL SCORE: %d/%d\n", score, numberOfQuestions);
    printf("**********************\n");

    return 0;
}