#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define cols 25 
#define rows 25
#define foods 50

char board[cols * rows];

int isGameOver = 0;

void fill_board()
{
    int x, y;

    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < cols; x++)
        {
            if (x == 0 || y == 0 || x == cols - 1 || y == rows - 1)
            {
                board[y * cols + x] = '#';
            }
            else
            {
                board[y * cols + x] = ' ';
            }
        }
    }
}

void clear_screen()
{
    system("cls");
}

void print_board()
{
    int x, y;

    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < cols; x++)
        {
            putch(board[y * cols + x]);
        }
        putch('\n');
    }
}

#define SNAKE_MAX_LEN 256

struct snakePart
{
    int x, y;
};

struct snake
{
    int length;
    struct snakePart bodyPart[SNAKE_MAX_LEN];
};
struct snake snakes;

struct Food
{
    int x, y;
    int consumed;
};

struct Food food[foods];

void draw_snake()
{
    int i;

    for (i = snakes.length - 1; i > 0; i--)
    {
        board[snakes.bodyPart[i].y * cols + snakes.bodyPart[i].x] = '*';
    }
    board[snakes.bodyPart[0].y * cols + snakes.bodyPart[0].x] = '@';
}

void move_snake(int deltaX, int deltaY)
{
    int i;
    for (i = snakes.length - 1; i > 0; i--)
    {
        snakes.bodyPart[i] = snakes.bodyPart[i - 1];
    }

    snakes.bodyPart[0].x += deltaX;
    snakes.bodyPart[0].y += deltaY;
}

void read_keyboard()
{
    int ch = getch();

    switch (ch)
    {
    case 'w':
        move_snake(0, -1);
        break;

    case 's':
        move_snake(0, 1);
        break;

    case 'a':
        move_snake(-1, 0);
        break;

    case 'd':
        move_snake(1, 0);
        break;
    case '\e':
    }
}

void draw_food()
{
    int i;

    for (i = 0; i < foods; i++)
    {
        if (!food[i].consumed)
        {
            board[food[i].y * cols + food[i].x] = '+';
        }
    }
}

void setup_food()
{
    int i;

    for (i = 0; i < foods; i++)
    {
        food[i].x = 1 + rand() % (cols - 2);
        food[i].y = 1 + rand() % (rows - 2);
        food[i].consumed = 0;
    }
}

void setup_snake()
{
    snakes.length = 1;
    snakes.bodyPart[0].x = 1 + rand() % (cols - 2);
    snakes.bodyPart[0].y = 1 + rand() % (rows - 2);
}

void game_rules()
{
    int i;

    for (i = 0; i < foods; i++)
    {
        if (!food[i].consumed)
        {
            if (food[i].x == snakes.bodyPart[0].x &&
                food[i].y == snakes.bodyPart[0].y)
            {
                food[i].consumed = 1;
                snakes.length++;
            }
        }
    }

    if (snakes.bodyPart[0].x == 0 || snakes.bodyPart[0].x == cols - 1 || snakes.bodyPart[0].y == 0 || snakes.bodyPart[0].y == rows - 1)
    {
        isGameOver = 1;
    }

    for (i = 1; i < snakes.length; i++)
    {
        if (snakes.bodyPart[0].x == snakes.bodyPart[i].x && snakes.bodyPart[0].y == snakes.bodyPart[i].y)
        {
            isGameOver = 1;
        }
    }
}
int main(int argc, char **argv)
{
    srand(time(0));

    setup_snake();
    setup_food();

    while (!isGameOver)
    {
        fill_board();
        draw_food();
        draw_snake();
        game_rules();
        clear_screen();
        print_board();
        printf("Score: %d\n", snakes.length * 100);
        if (!isGameOver)
            read_keyboard();
    }

    printf("Game Over, Final Score: %d\n", snakes.length * 100);

    while (1)
        getch();
    return 0;
};