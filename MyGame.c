#include <stdio.h>
#include <windows.h>

enum key
{
    knone,
    kup,
    kdown,
    kleft,
    kright
};
enum button
{
    bnone = 0,
    ba = 1,
    bb = 2
};

typedef void (*PTRDESCRIPTION)();
typedef void (*PTRRESET)();
typedef void (*PTRUPDATE)();
typedef void (*PTRCONTROLLER)(int key, int button);

struct my_game
{
    HMODULE impl;
    PTRDESCRIPTION description;
    PTRRESET reset;
    PTRUPDATE update;
    PTRCONTROLLER controller;
};

void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void load_game(const char *game_library, struct my_game *game)
{
    game->impl = LoadLibraryA(game_library);
    game->description = (PTRDESCRIPTION)GetProcAddress(game->impl, "description");
    game->reset = (PTRRESET)GetProcAddress(game->impl, "reset");
    game->update = (PTRUPDATE)GetProcAddress(game->impl, "update");
    game->controller = (PTRCONTROLLER)GetProcAddress(game->impl, "controller");
}

int main(int argc, char *argv[])
{
    struct my_game game;
    load_game(argv[1], &game);
    game.description();
    game.reset();

    do
    {
        game.update();
        char x = getchar();
        flush();
        switch (x)
        {
        case 'w':
        case 'W':
            game.controller(kup, bnone);
            break;
        case 's':
        case 'S':
            game.controller(kdown, bnone);
            break;
        case 'a':
        case 'A':
            game.controller(kleft, bnone);
            break;
        case 'd':
        case 'D':
            game.controller(kright, bnone);
            break;
        case 'n':
        case 'N':
            game.controller(knone, ba);
            break;
        case 'm':
        case 'M':
            game.controller(knone, bb);
            break;
        case 'r':
        case 'R':
            game.reset();
            break;
        }
    } while (1);

    return 0;
}
