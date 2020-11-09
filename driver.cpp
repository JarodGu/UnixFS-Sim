/*
 * Jarod Guerrero and Antong Cheng
 * CSS FourThreeZero A
 * Final Project - Unix File System
 * 8/22/19
 *
 * Driver file for the Unix File System implementation.
 * Creates a File System object and runs commands from a
 * file named "commands.txt"
 * The supported commands are:
 *      NF - New File
 *      MF - Modify File
 *      DF - Delete File
 *      DB - Delete Blocks
 */
#include <iostream>
#include "filesystem.h"
using std::cout;
using std::endl;

int main() {
    FileSystem UnixFileSystem;
    UnixFileSystem.ReadCommands();
    cout << "Done executing commands. Goodbye!" << endl;
    return 0;
}
