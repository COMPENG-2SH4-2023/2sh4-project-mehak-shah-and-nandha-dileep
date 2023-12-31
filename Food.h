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
        //~Food();

        void generateFood(objPosArrayList &playerPosList);
        void getFoodPos(objPos &returnPos); 

    private:
        objPos foodPos;
        // Need a reference to the Main Game Mechanisms to access board dimensions
        GameMechs* mainGameMechsRef;
};

#endif