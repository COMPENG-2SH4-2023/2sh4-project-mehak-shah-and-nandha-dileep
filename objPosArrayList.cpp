#include "objPosArrayList.h"


objPosArrayList::objPosArrayList()
{
    sizeList = 0; // Points to the next position in the array and holds the number of items in the array
    sizeArray = ARRAY_MAX_CAP; // Holds the total size of the array, currently sizeArray = 200
    aList = new objPos[ARRAY_MAX_CAP]; // Array
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Create new (larger) array if the current array is full. 
    if(sizeList >= sizeArray)
    {
        // Allocate memory for a new list
        objPos* newList = new objPos[sizeArray + ARRAY_INCREASE_AMOUNT];

        // Copy old list items into new list
        for (int i = 0; i < sizeList; i++)
        {
            newList[i] = aList[i];
        }

        // Deallocate the memory of the old array
        delete[] aList;

        // Update the pointer to point to the new array 
        aList = newList;

        sizeArray = sizeArray + ARRAY_INCREASE_AMOUNT; // Updates list size
    }

    // Shits all elements towards the tail to create space at the head
    for (int i = sizeList; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]);
    }

    // Inserts the new element at the head, index: 0
    aList[0].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Create new (larger) array if the current array is full. 
    if(sizeList >= sizeArray)
    {
        // Allocate memory for a new list
        objPos* newList = new objPos[sizeArray + ARRAY_INCREASE_AMOUNT];

        // Copy old list items into new list
        for (int i = 0; i < sizeList; i++)
        {
            newList[i] = aList[i];
        }

        // Deallocate the memory of the old array
        delete[] aList;

        // Update the pointer to point to the new array 
        aList = newList;

        sizeArray = sizeArray + ARRAY_INCREASE_AMOUNT; // Updates list size
    }

    // Inserts the new element at the tail, index: sizeList
    aList[sizeList].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::removeHead()
{
    // Can't remove elements if sizeList is negative or contains no elements
    if(sizeList <= 0)
    {
        return;
    }   

    // Shifts all the elements to the left to remove head element
    for(int i = 0; i < sizeList - 1; i++)
    {
        aList[i].setObjPos(aList[i+1]);
    }
    sizeList--;
}

void objPosArrayList::removeTail()
{
    // Can't remove elements if sizeList is negative or if the array contains no elements
    if(sizeList <= 0)
    {
        return;
    }   
    sizeList--;
}

// Pass-by-value GETTERS
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    // If the index is out-of-bounds, do not return any value
    if (index < 0 || index >= sizeList)
    {
        return;
    }
    
    returnPos.setObjPos(aList[index]);
}