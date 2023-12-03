#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>  
#include <time.h> 

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPos blockOff); // Upgrade this to objPosArrayList
        //Need to accept the player body array list 
        // Go through each array list element to make sure they are all blocked off from random food generation

        void getFoodPos(objPos &returnPos); // This too

    private:
        objPos foodPos;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif