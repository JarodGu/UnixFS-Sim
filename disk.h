/*
 * Jarod Guerrero and Antong Cheng
 * CSS 430 A
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

#ifndef UNIXFILESYSTEM_DISK_H
#define UNIXFILESYSTEM_DISK_H

#include <vector>
#include <iostream>

class Disk
{
public:
    Disk();
    ~Disk();
    std::vector<int*> TakeBlock(int);
    void FreeBlock(std::vector<int*>&, int);

    int GetNumUsedBlocks();
private:
    // 0 is open, 1 is used
    std::vector<int> bitMap;
};
#endif //UNIXFILESYSTEM_DISK_H
