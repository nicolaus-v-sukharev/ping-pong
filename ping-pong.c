#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define X 40
#define Y 20
#define X_2 X / 2
#define Y_2 Y / 2
#define Y_LB 0 + 2
#define Y_HB Y - 3

unsigned char screen[X][Y];

unsigned char key;

short racket_left;
short racket_right;

short tmp;

float ball_x;
float ball_y;

float alt;

float ball_x_vector;
float ball_y_vector;

short score_left;
short score_right;

short counter;

short time_start;
short time_delta;

void setup()
{
    for (short y = 0; y < Y; y++)
    {
        for (short x = 0; x < X; x++)
        {
            if (x == X_2)
            {
                screen[x][y] = '|';
            }
            else
            {
                screen[x][y] = ' ';
            }
        }
    }
    key = 0;
    racket_left = Y_2;
    racket_right = Y_2;
    ball_x = X_2;
    ball_y = Y_2;
    alt = 0;
    ball_x_vector = 0.5;
    ball_y_vector = 0;
    score_left = 0;
    score_right = 0;
    counter = 0;
    time_start = 0;
    time_delta = 0;
}

void loop()
{
    counter++;
    key = 0;
    while (kbhit())
    {
        key = getch();
    }
    switch (key)
    {
    case 'W':
    case 'w':
        racket_left > Y_LB ? racket_left-- : 0;
        break;
    case 'S':
    case 's':
        racket_left < Y_HB ? racket_left++ : 0;
        break;
    }
    if (counter % 3 == 0)
    {
        if (racket_right <= ball_y)
        {
            racket_right < Y_HB ? racket_right++ : 0;
        }
        else if (racket_right >= ball_y)
        {
            racket_right > Y_LB ? racket_right-- : 0;
        }
    }
    if (floor(ball_x) <= 0)
    {
        alt = ball_y - racket_left;
        if (alt > -1.75 && alt < -0.5)
        {
            ball_x_vector *= -1.1;
            ball_y_vector = alt * 0.25;
        }
        else if (alt > -0.5 && alt < 0.5)
        {
            ball_x_vector *= -1.1;
        }
        else if (alt > 0.5 && alt < 1.75)
        {
            ball_x_vector *= -1.1;
            ball_y_vector = alt * 0.25;
        }
        else
        {
            ball_x = X_2;
            ball_y = Y_2;
            ball_x_vector = -0.5;
            ball_y_vector = 0;
            score_right++;
        }
    }
    if (ceil(ball_x) >= X)
    {
        alt = ball_y - racket_right;
        if (alt > -1.5 && alt < -0.5)
        {
            ball_x_vector *= -1.1;
            ball_y_vector = alt * 0.25;
        }
        else if (alt > -0.5 && alt < 0.5)
        {
            ball_x_vector *= -1.1;
        }
        else if (alt > 0.5 && alt < 1.5)
        {
            ball_x_vector *= -1.1;
            ball_y_vector = alt * 0.25;
        }
        else
        {
            ball_x = X_2;
            ball_y = Y_2;
            ball_x_vector = 0.5;
            ball_y_vector = 0;
            score_left++;
        }
    }
    ball_x += ball_x_vector;
    if (floor(ball_y) == 0 || ceil(ball_y) == Y)
    {
        ball_y_vector *= -1;
    }
    ball_y += ball_y_vector;
    if (1)
    {
        system("cls");
        for (short y = 0; y < Y; y++)
        {
            if (abs(y - racket_left) <= 1)
            {
                printf("|");
            }
            else
            {
                printf("%c", screen[0][y]);
            }
            for (short x = 1; x < X; x++)
            {
                if (rint(ball_x) == x && rint(ball_y) == y)
                {
                    printf("@");
                }
                else
                {
                    printf("%c", screen[x][y]);
                }
            }
            if (abs(y - racket_right) <= 1)
            {
                printf("|");
            }
            else
            {
                printf("%c", screen[X][y]);
            }
            printf("\n");
        }
        printf("s_left: %d\n", score_left);
        printf("s_right: %d\n", score_right);
    }
    time_delta = 42 + time_start - clock();
    Sleep(time_delta > 0 ? time_delta : 0);
    time_start = clock();
}

void main()
{
    setup();
    while (key != 27)
    {
        loop();
    }
}