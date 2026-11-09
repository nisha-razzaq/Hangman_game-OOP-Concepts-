
                                 
#include "Hangman.h"
#include <iostream>
#include <string>

using namespace std;

Hangman::Hangman()
{
    stage = 0;
    x = 55;
    y = 5;
}

Hangman::Hangman(int x, int y)
{
    stage = 0;
    this->x = x;
    this->y = y;
}

Hangman::~Hangman()
{
}

void Hangman::drawNextStage()
{
    if (stage < 7)
    {
        stage++;
    }

    string r[7];

    for (int i = 0; i < 7; i++)
    {
        r[i] = string(13, ' ');
    }

    if (stage >= 1)
    {
        r[6] = "  =======    ";
    }

    if (stage >= 2)
    {
        for (int i = 1; i <= 5; i++)
            r[i][3] = '|';
    }

    if (stage >= 3)
    {
        r[0] = "   +-----+   ";
        r[1][9] = '|';
    }

    if (stage >= 4)
    {
        r[2][9] = 'O';
    }

    if (stage >= 5)
    {
        r[3][9] = '|';
        r[4][9] = '|';
    }

    if (stage >= 6)
    {
        r[3][8] = '/';
        r[3][10] = '\\';
    }

    if (stage >= 7)
    {
        r[5][8] = '/';
        r[5][10] = '\\';
    }

    for (int i = 0; i < 7; i++)
    {
        cf.SetCursorAt(x, y + i);
        cout << r[i];
    }
}

void Hangman::resetStage()
{
    stage = 0;
}

int Hangman::getStage() const
{
    return stage;
}