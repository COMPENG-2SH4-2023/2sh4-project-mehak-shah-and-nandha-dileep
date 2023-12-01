#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input; // Holds the most recent input collected via MacUILib_getChar()
        bool exitFlag;
        bool loseFlag;
        /*  - Records whether the player has lost the game (Snake eating into itself). 
            - Flag should not be set to true if the player presses the exit key to terminate the game. 
            - Use this flag to determine what messages to display at the end of the game.*/
        int score; // Holds the current score of the player
        
        int boardSizeX;
        int boardSizeY;

    public:
        // Default Constructors
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();
        
        // Getters
        bool getExitFlagStatus();
        bool getLoseFlagStatus();
        char getInput();
        int getBoardSizeX();
        int getBoardSizeY();
        int getScore();
        
        // Setters
        void setExitTrue();
        void setLoseFlag();
        void setInput(char this_input);
        
        // Additional Setter Functions
        void clearInput();
        void incrementScore();
      

};

#endif