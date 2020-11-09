/*
 * Jarod Guerrero and Antong Cheng
 * CSS 430 A
 * Final Project - Unix File System
 * 8/22/19
 *
 * Header file for the file system object. File system contains
 * a single directory, disk, and array of 1000 inodes.
 * Supports four commands read in from a file named "commands.txt"
 *      NF - New File
 *      MF - Modify File
 *      DF - Delete File
 *      DB - Delete Blocks
 */
#ifndef UNIXFILESYSTEM_FILESYSTEM_H
#define UNIXFILESYSTEM_FILESYSTEM_H

#include "disk.h"
#include "record.h"
#include "inode.h"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
#include <list>
#include <iterator>

using std::stoi;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::list;

class FileSystem {
public:
    FileSystem();
    ~FileSystem();

    int ReadCommands();
    void PrintDirectory();

    int NewFile(std::string fileName, int size);
    int ModifyFile(std::string fileName, int size);
    int DeleteFile(std::string fileName);
    int DeleteBlocks(std::string fileName, int size);

private:
    // linked list for directory records
    list<Record> directory;
    Disk disk;
    vector<Inode*> inodeArray;

};


#endif //UNIXFILESYSTEM_FILESYSTEM_H
