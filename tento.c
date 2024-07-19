#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

enum colors{Red=1,Green=11,Blue=21,Yellow=31,Cyan=41,Magenta=51};
//consts
#define WIDTH 120  
#define HEIGHT 35  
#define M_PI 3.14159265358979323846
#define TRUE 1
#define SLEEPTIME 20
#define ANGLE 0.06
#define COLORSPEED 2


/*
clears the screen for next frame
input: none
output: none
*/
void clearScreen() 
{
    system("cls");
}
/*
Changes the color of the word 
input: number of color the hConsole to change color
output: none
*/
void changeColor(int* number, HANDLE hConsole)
{
    int colorNumber = *number;
    //changing the color by the number of the color which is set by the enum
    switch (colorNumber)
    {
        case Red:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            break;
        case Green:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            break;
        case Blue:
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            break;
        case Yellow:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case Cyan:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case Magenta:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
            break;
        default:
            break;
    }
}
/*
moves the cursor to the location said
input: x, y location of the mouse
output: none
*/
void moveCursorTo(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}


/*
handles the math and puts each char in its place and redners the word each time
input: the centerx and y(where is the center) the angle and wordiself and height and width
*/
void renderWord(int centerX, int centerY, float angle, char** bigWord, int width, int height) 
{
    int xp = 0;
    int yp = 0;
    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width; ++j)
        {
            if (bigWord[i][j] != ' ') {
                xp = (int)(centerX + (j - width / 2) * cos(angle) - (i - height / 2) * sin(angle));
                yp = (int)(centerY + (j - width / 2) * sin(angle) + (i - height / 2) * cos(angle));

                // ensure the coordinates are within bounds with padding
                if (xp >= 0 && xp < WIDTH && yp >= 0 && yp < HEIGHT)
                {
                    moveCursorTo(xp, yp);
                    putchar(bigWord[i][j]);
                }
            }
        }
    }
}

int main() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int width = 108;
    int height = 16;  
    int color = 1;
    float angle = 0.0;
    //mallocing size
    char** bigWord = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; ++i) 
    {
        bigWord[i] = (char*)malloc(width + 1);
    }
    //defining asci art
    strcpy(bigWord[0], "         tttt                              NNNNNNNNN        NNNNNNN         tttt                           ");
    strcpy(bigWord[1], "      ttt:::t                              N:::::::N       N::::::N      ttt:::t                           ");
    strcpy(bigWord[2], "      t:::::t                              N:::::::N      N:::::::N      t:::::t                           ");
    strcpy(bigWord[3], "      t:::::t                              N:::::::N     N::::::::N      t:::::t                           ");
    strcpy(bigWord[4], "ttttttt:::::ttttttt        eeeeeeeeeeee    N:::::::N    N:::::::::Nttttttt:::::ttttttt       ooooooooooo   ");
    strcpy(bigWord[5], "t:::::::::::::::::t      ee::::::::::::ee  N:::::::N   N::::::::::Nt:::::::::::::::::t     oo:::::::::::oo ");
    strcpy(bigWord[6], "t:::::::::::::::::t     e::::::eeeee:::::eeN:::::::N  N:::::::::::Nt:::::::::::::::::t    o:::::::::::::::o");
    strcpy(bigWord[7], "tttttt:::::::tttttt    e::::::e     e:::::eN:::::::N N::::N:::::::Ntttttt:::::::tttttt    o:::::ooooo:::::o");
    strcpy(bigWord[8], "      t:::::t          e:::::::eeeee::::::eN::::::::N::::N N::::::N      t:::::t          o::::o     o::::o");
    strcpy(bigWord[9], "      t:::::t          e:::::::::::::::::e N::::::::::::N  N::::::N      t:::::t          o::::o     o::::o");
    strcpy(bigWord[10], "      t:::::t          e::::::eeeeeeeeeee N:::::::::::N   N::::::N      t:::::t          o::::o     o::::o");
    strcpy(bigWord[11], "      t:::::t    tttttte:::::::e          N::::::::::N    N::::::N      t:::::t    tttttto::::o     o::::o");
    strcpy(bigWord[12], "      t::::::tttt:::::te::::::::e         N:::::::::N     N::::::N      t::::::tttt:::::to:::::ooooo:::::o");
    strcpy(bigWord[13], "      tt::::::::::::::t e::::::::eeeeeeee N::::::::N      N::::::N      tt::::::::::::::to:::::::::::::::o");
    strcpy(bigWord[14], "        tt:::::::::::tt  ee:::::::::::::e N::::::N        N::::::N        tt:::::::::::tt oo:::::::::::oo ");
    strcpy(bigWord[15], "          ttttttttttt      eeeeeeeeeeeeee NNNNNNN         NNNNNNNN          ttttttttttt     ooooooooooo   ");
    //rendering each frame which is loaded at 20ms
    while (TRUE) 
    {
        clearScreen();
        renderWord(WIDTH / 2, HEIGHT / 2, angle, bigWord, width, height);
        Sleep(SLEEPTIME);
        angle += ANGLE;
        changeColor(&color, hConsole);
        color += COLORSPEED;
        if (color > Magenta)
        {
            color = Red;
            angle += ANGLE * COLORSPEED;
        }

    }
    //freeing everything
    for (int i = 0; i < height; ++i) 
    {
        free(bigWord[i]);
    }
    free(bigWord);

    return 0;
}

