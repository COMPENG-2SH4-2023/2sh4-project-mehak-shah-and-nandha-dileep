#ifndef FOOD_H
#define FOOD_H_H

#include <cstdlib>  //not sure if i need this library
#include <time.h> //not sure if i neeed this library

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{

    public:
        Food();
        ~Player();

        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);

    private:
        objPos foodPos;
};

#endif