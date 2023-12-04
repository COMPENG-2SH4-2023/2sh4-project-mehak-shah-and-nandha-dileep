#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP}; 

        Player(GameMechs* thisGMRef, Food* thisFood);
        ~Player();

        objPosArrayList* getPlayerPos(); 
        void updatePlayerDir();
        void movePlayer();

        bool checkFoodComsumption(); 
        void increasePlayerLength(); 
        bool checkSelfCollision();

    private:
        objPosArrayList *playerPosList;     
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        // Need a reference to Food Object
        Food* foodRef;
};

#endif