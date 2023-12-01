#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList; // Heap data member
                       // Points to the start of an objPos array list
        int sizeList;  // Number of elements currently in list
                       // NOTE: Points to the next position in the array
        int sizeArray; // Total number of available array elements: (200) 

    public:
        objPosArrayList(); // Default Constructor
        ~objPosArrayList(); // Destructor

        int getSize(); // Returns sizeList
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        // Other getters (pass-by-reference)
        void getHeadElement(objPos &returnPos);
        void getTailElement(objPos &returnPos);
        void getElement(objPos &returnPos, int index);
};

#endif