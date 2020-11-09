/*
 * Jarod Guerrero and Antong Cheng
 * CSS FourThreeZero A
 * Final Project - Unix File System
 * 8/22/19
 *
 * Header file for the Inodes of the file system. The file system contains
 * an array of 1000 Inodes. Each Inode is linked to a record and has
 * details information about its UID, GID, disk blocks, type, access mode,
 * time created, and time modified. It has a vector of pointers pointing to
 * the exact blocks on disk its using. Blocks may also be added or removed
 * using the designated file system commands (MF and DB).
 */

#ifndef UNIXFILESYSTEM_INODE_H
#define UNIXFILESYSTEM_INODE_H

#include <iostream>
#include <vector>
#include <time.h>
#include <iterator>
#include <ctime>

class Inode
{
public:
    Inode();
    Inode(int);
    virtual ~Inode();

    void AddDirectBlocks(const std::vector<int*> &directBlocks);

    const std::string &getUid() const;
    void setUid(const std::string &uid);
    const std::string &getGid() const;
    void setGid(const std::string &gid);
    int getSize() const;
    int getBlockCount() const;
    std::vector<int *> &getDirectBlocks();
    void setDirectBlocks(const std::vector<int *> &directBlocks);
    const std::string &getType() const;
    void setType(const std::string &type);
    const std::string &getAccessMode() const;
    void setAccessMode(const std::string &accessMode);
    time_t getTimeCreated() const;
    void setTimeCreated(time_t timeCreated);
    time_t getTimeModified() const;
    void setTimeModified(time_t timeModified);

private:
    std::string type;
    std::string accessMode;
    std::string uid;
    std::string gid;

    time_t timeCreated;
    time_t timeModified;

    // block count is also stored in directBlocks.size()
    std::vector<int*> directBlocks;
};

#endif //UNIXFILESYSTEM_INODE_H
