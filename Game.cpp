
                                      

#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

Game::Game() : hangman(55, 5)
{
    srand((unsigned)time(0));

    secretWord = nullptr;
    secretWordCheck = nullptr;
    wordCount = 0;
    wordLength = 0;
    wrongCount = 0;
    totalGuesses = 7;
    remainingGuesses = 7;

    for (int i = 0; i < 50; i++)
    {
        wordList[i] = nullptr;
    }

    for (int i = 0; i < 26; i++)
    {
        letters[i] = 'A' + i;
        lettersCheck[i] = false;
    }

    loadWordList();
    pickSecretWord();
}

Game::~Game()
{
    for (int i = 0; i < wordCount; i++)
    {
        delete[] wordList[i];
    }

    delete[] secretWordCheck;
}

void Game::loadWordList()
{
    ifstream f("Words.txt");

    if (!f.is_open())
    {
        cout << "There are errors while opening file!" << endl;
        return;
    }

    string line;

    while (wordCount < 50 && getline(f, line))
    {
        int count = 0;
        while (line[count] != '\0')
        {
            count++;
        }

        wordList[wordCount] = new char[count + 1];

        for (int i = 0; i < count; i++)
        {
            wordList[wordCount][i] = line[i];
        }

        wordList[wordCount][count] = '\0';
        wordCount++;
    }

    f.close();
}

void Game::pickSecretWord()
{
    if (wordCount == 0)
        return;

    delete[] secretWordCheck;

    secretWord = wordList[rand() % wordCount];

    wordLength = 0;
    while (secretWord[wordLength] != '\0')
    {
        wordLength++;
    }

    secretWordCheck = new bool[wordLength];

    for (int i = 0; i < wordLength; i++)
    {
        secretWordCheck[i] = false;
    }
}

bool Game::isLetterUsed(char guess)
{
    return lettersCheck[guess - 'A'];
}

char Game::getGuess()
{
    char guess;

    while (true)
    {
        cf.SetCursorAt(0, 14);
        cout << string(40, ' ');
        cf.SetCursorAt(0, 14);

        cout << "Next guess please? ";
        cin >> guess;

        if (guess >= 'a' && guess <= 'z')
        {
            guess = guess - 32;
        }

        if (guess < 'A' || guess > 'Z')
        {
            continue;
        }

        if (isLetterUsed(guess))
        {
            continue;
        }

        return guess;
    }
}

void Game::checkGuess(char guess)
{
    lettersCheck[guess - 'A'] = true;

    bool found = false;

    for (int i = 0; i < wordLength; i++)
    {
        char wordChar = secretWord[i];

        if (wordChar >= 'a' && wordChar <= 'z')
        {
            wordChar = wordChar - 32;
        }

        if (wordChar == guess)
        {
            secretWordCheck[i] = true;
            found = true;
        }
    }

    if (!found)
    {
        wrongLetters[wrongCount] = guess;
        wrongCount++;
        remainingGuesses--;
        updateHangman();
    }
}

void Game::updateHangman()
{
    hangman.drawNextStage();
}

bool Game::hasWon()
{
    for (int i = 0; i < wordLength; i++)
    {
        if (!secretWordCheck[i])
        {
            return false;
        }
    }

    return true;
}

bool Game::hasLost()
{
    return remainingGuesses <= 0;
}

void Game::reset()
{
    for (int i = 0; i < 26; i++)
    {
        lettersCheck[i] = false;
    }

    wrongCount = 0;
    remainingGuesses = totalGuesses;
    hangman.resetStage();
    pickSecretWord();
}

void Game::display()
{
    cf.SetColor(white, black);

    cf.SetCursorAt(0, 0);
    cout << "The Hangman Game";

    cf.SetCursorAt(0, 2);
    cout << "Welcome to Hangman! I have selected a secret word, and your goal is to guess it";
    cf.SetCursorAt(0, 3);
    cout << "letter by letter before you run out of lives.";

    cf.SetCursorAt(0, 5);
    for (int i = 0; i < 13; i++)
    {
        if (lettersCheck[i])
            cf.SetColor(red, black);
        else
            cf.SetColor(white, black);

        cout << letters[i] << " ";
    }

    cf.SetCursorAt(0, 6);
    for (int i = 13; i < 26; i++)
    {
        if (lettersCheck[i])
            cf.SetColor(red, black);
        else
            cf.SetColor(white, black);

        cout << letters[i] << " ";
    }

    cf.SetColor(white, black);

    cf.SetCursorAt(0, 8);
    cout << "Secret Word:";

    cf.SetCursorAt(0, 9);
    for (int i = 0; i < wordLength; i++)
    {
        if (secretWordCheck[i])
            cout << secretWord[i] << " ";
        else
            cout << "_ ";
    }
    cout << " (" << wordLength << " letters)";

    cf.SetCursorAt(0, 11);
    cout << "Incorrect Guesses: ";
    if (wrongCount == 0)
    {
        cout << "None";
    }
    else
    {
        for (int i = 0; i < wrongCount; i++)
        {
            cout << wrongLetters[i] << " ";
        }
    }
    cout << "          ";

    cf.SetCursorAt(0, 12);
    cout << "Lives Left: " << remainingGuesses << " ";
}

void Game::play()
{
    if (wordCount == 0)
    {
        cout << "No words loaded. Check Words.txt!" << endl;
        return;
    }

    char again;

    do
    {
        system("cls");

        while (true)
        {
            display();

            if (hasWon() || hasLost())
            {
                break;
            }

            char guess = getGuess();
            checkGuess(guess);
        }

        cf.SetCursorAt(0, 16);

        if (hasWon())
        {
            cout << "YOU WON!";
        }
        else
        {
            cout << "YOU LOST!";
            cout << "\nCorrect Word : " << secretWord;
        }

        cout << "\n\nPlay again? (y/n) : ";
        cin >> again;

        if (again == 'y' || again == 'Y')
        {
            reset();
        }

    } while (again == 'y' || again == 'Y');
}