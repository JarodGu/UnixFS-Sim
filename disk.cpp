/*
 * Jarod Guerrero and Antong Cheng
 * CSS FourThreeZero A
 * Final Project - Unix File System
 * 8/22/19
 *
 * Header file for the disk. This disk contains 1000 blocks
 * of 512Kb represented by a bitmap. When a block in the bitmap
 * is being used, its corresponding value it set to 1. If not being
 * used, it's set to 0.
 *
 * The disk is only accessed and modified through the FileSystem object
 */
#include "disk.h"

Disk::Disk() {
    bitMap = std::vector<int>(1000, 0);
}

// Destructor
Disk::~Disk() {

}

// Returns the number of blocks currently occupied
int Disk::GetNumUsedBlocks() {
    int count = 0;
    for(int i=0; i< bitMap.size(); i++)
    {
        if(bitMap[i] == 1)
            ++count;
    }
    return count;
}

/*
 * Finds available blocks from the disk and returns an array of
 * pointers to each available block. Does not check for errors
 * if the number of blocks requested is greater than what is available.
 */
std::vector<int*> Disk::TakeBlock(int numAdd)
{
    std::vector<int*> retVal;
    for(int i = 0; i < 1000 && numAdd > 0; i++)
    {
        if(bitMap[i] == 0)
        {
            bitMap[i] = 1;
            retVal.push_back(&bitMap[i]);
            numAdd--;
        }
    }
    return retVal;
}

/*
 * Deallocates each block from an array of pointers
 * to disk.
 */
void Disk::FreeBlock(std::vector<int *>& directBlocks, int numFree) {

    std::vector<int*>::iterator it1, it2;
    it1 = directBlocks.begin();
    it2 = directBlocks.begin() + numFree;

    std::cout << "Old size: " << directBlocks.size() << std::endl;
    for(int i = 0; i < numFree; i++){
        //std::cout << "Block was " << *directBlocks[i] << std::endl;
        *directBlocks[i] = 0;
        //std::cout << "Block is now " << *directBlocks[i] << std::endl;
    }
    directBlocks.erase(it1, it2);
    std::cout << "New size: " << directBlocks.size() << std::endl;

}
