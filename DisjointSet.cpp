// DisjointSet implementation using union by size and path compression
// By Mary Elaine Califf and Drew Huniak

#include "DisjointSet.h"
#include <iostream>

DisjointSet::DisjointSet(int numObjects)
{
    theArray.assign(numObjects, -1);
    this->numValues = numObjects;
}

//recursive method to find the item -- does path compression on the way out of the recursion
int DisjointSet::find(int objectIndex)
{
    if(theArray[objectIndex] < 0)
    {
        return objectIndex;
    }
    else
    {
        return theArray[objectIndex] = find(theArray[objectIndex]);
    }
    
}

bool DisjointSet::doUnion(int objIndex1, int objIndex2)
{
    objIndex2 = find(objIndex2);
    objIndex1 = find(objIndex1);
    
   
    if(theArray[objIndex1] > theArray[objIndex2]) 
    {
        theArray[objIndex2] = theArray[objIndex2] + theArray[objIndex1];
        theArray[objIndex1] = objIndex2;
    }
    else
    {
        theArray[objIndex1] = theArray[objIndex2] + theArray[objIndex1]; 
        theArray[objIndex2] = objIndex1;
    }
    

    if((theArray[objIndex1]*-1) == numValues || theArray[objIndex2] *-1 == numValues)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DisjointSet::printArrayValues(std::ostream &outputStream)
{
    for (int i = 0; i < numValues; i++)
    {
        outputStream << theArray[i] << " ";
    }
    outputStream << std::endl;
}
