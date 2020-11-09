/*
 * Jarod Guerrero and Antong Cheng
 * CSS FourThreeZero A
 * Final Project - Unix File System
 * 8/22/19
 *
 * Header file for the records within a directory.
 * A directory is a list of Record objects. Each record has
 * a file name and points to an Inode that contains
 * more detailed information about the file.
 */

#ifndef UNIXFILESYSTEM_RECORD_H
#define UNIXFILESYSTEM_RECORD_H

#include "inode.h"
#include <ctime>
using std::ostream;

class Record
{
public:
    friend ostream& operator<<(ostream& os, const Record &r);
    Record(std::string fileName, Inode* &p);

    virtual ~Record();
    Inode *getFile() const;
    int getNumBlocks() const;
    const std::string &getFileName() const;
    void setFileName(const std::string &fileName);

private:
    Inode* file;
    std::string fileName;

};
#endif //UNIXFILESYSTEM_RECORD_H
