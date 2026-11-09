                                        

#pragma once
#include "ConsoleFunctions.h"

class Hangman
{
    int stage;
    int x;
    int y;
    ConsoleFunctions cf;

public:
    Hangman();
    Hangman(int x, int y);
    ~Hangman();

    void drawNextStage();
    void resetStage();
    int getStage() const;
};