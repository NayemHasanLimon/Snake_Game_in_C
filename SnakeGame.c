#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int height = 20;
int width = 40;
int FPS = 5;
int x, y;
int gameOver = 0;
int dir;
int foodX, foodY;
int score = 0;
int body[799][2];

void setup()
{
    x = (width / 2);
    y = (height / 2);
    foodX = (rand() % width) + 1;
    foodY = (rand() % height) + 1;
}

void draw()
{
    system("cls");
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (i == 0 || i == height || j == 0 || j == width)
            {
                printf("#");
            }
            else if (i == y && j == x)
            {
                printf("O");
            }
            else if (j == foodX && i == foodY)
            {
                printf("o");
            }
            else
            {
                int isBody = 0;
                for (int k = 1; k <= score; k++)
                {
                    if (i == body[k][1] && j == body[k][0])
                    {
                        isBody = 1;
                        printf("O"); 
                        break;
                    }
                }
                if (!isBody)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d", score);
}

void gameOverScreen()
{
    system("cls");
    for (int i = 0; i <= height; i++)
    {
        if (i == 10)
        {
            printf("#                Game Over              #\n");
            continue;
        }
        for (int j = 0; j <= width; j++)
        {
            if (i == 0 || i == height || j == 0 || j == width)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d", score);
}

void input()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == 'a' && !(dir == 'R'))
        {
            dir = 'L';
        }
        else if (key == 'd' && !(dir == 'L'))
        {
            dir = 'R';
        }
        else if (key == 'w' && !(dir == 'D'))
        {
            dir = 'U';
        }
        else if (key == 's' && !(dir == 'U'))
        {
            dir = 'D';
        }
    }
}

void logic()
{
    switch (dir)
    {
    case 'L':
        x--;
        break;
    case 'R':
        x++;
        break;
    case 'U':
        y--;
        break;
    case 'D':
        y++;
        break;
    default:
        break;
    }

    if (x == 0 || x == width || y == 0 || y == height)
    {
        gameOver = 1;
    }
    for (int i = 0; i < score; i++)
    {
        if (x == body[i][0] && y == body[i][1])
        {
            gameOver = 1;
        }
    }

    if (x == foodX && y == foodY)
    {
        foodX = (rand() % width - 2) + 1;
        foodY = (rand() % height - 2) + 1;
        score++;
    }

    for (int i = score; i > 0; i--)
    {
        body[i][0] = body[i - 1][0];
        body[i][1] = body[i - 1][1];
    }
    body[0][0] = x;
    body[0][1] = y;
}

int main()
{
    srand(time(0));
    setup();
    while (!gameOver)
    {
        input();
        logic();
        draw();
        Sleep(1000 / FPS);
    }
    if (gameOver)
    {
        gameOverScreen();
    }

    return 0;
}