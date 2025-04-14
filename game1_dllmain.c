#include <stdio.h>
#include "game1_dll.h"
#include <windows.h>

int lives = 3, level = 0, points = 0, selected = 0;
const int levels = 3;

const char *question[] = {
    "Quanto e a metade de 50?",
    "Quanto e 2 + 2?",
    "Qual a capital do Brasil?"};

const char *options[][4] = {
    {"10", "25", "30", "50"},
    {"22", "5", "4", "12"},
    {"Sao Paulo", "Salvador", "Amazonia", "Brasilia"}};

const int correct[] = {1, 2, 3};

DLLIMPORT void description()
{
    printf("** GAME 1 **\n\nAbsolute amazing game done by Teacher.\n\n");
}

DLLIMPORT void reset(void)
{
    lives = 3;
    level = 0;
    selected = 0;
    points = 0;
}

DLLIMPORT void update(void)
{
    if ((level >= levels) || (lives == 0))
    {
        printf("\n--- Fim do jogo ---\n");
    }
    else
    {
        printf("\nPLAYER 1: %d vidas    - %04d pontos\n\n", lives, points);
        printf("%s\n", question[level]);
        for (int i = 0; i < 4; i++)
        {
            printf("%c%d) %s\n", selected == i ? '*' : ' ', i + 1, options[level][i]);
        }
    }
}

DLLIMPORT void controller(int key, int button)
{
    switch (key)
    {
    case 1:
        selected = (selected == 0) ? 3 : selected - 1;
        break;
    case 2:
        selected = (selected == 3) ? 0 : selected + 1;
        break;
    }

    if (key == 0 && button)
    {
        if (selected == correct[level])
        {
            printf("ACERTOU!!!\n");
            level++;
            points += 100;
        }
        else
        {
            printf("ERROU!!!\n");
            lives--;
        }
        selected = 0;
    }
}

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
    return TRUE;
}
