
                                         
#pragma once
#include "ConsoleFunctions.h"
#include "Hangman.h"

class Game
{
    Hangman hangman;
    char* wordList[50];
    char* secretWord;
    bool* secretWordCheck;
    char letters[26];
    bool lettersCheck[26];

    char wrongLetters[7];
    int wrongCount;

    int wordCount;
    int wordLength;
    int totalGuesses;
    int remainingGuesses;

    ConsoleFunctions cf;

public:
    Game();
    ~Game();

    void loadWordList();
    void pickSecretWord();
    char getGuess();
    bool isLetterUsed(char guess);
    void checkGuess(char guess);
    void updateHangman();
    bool hasWon();
    bool hasLost();
    void reset();
    void display();
    void play();
};