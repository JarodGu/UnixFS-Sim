/*
 * Jarod Guerrero and Antong Cheng
 * CSS 430 A
 * Final Project - Unix File System
 * 8/22/19
 *
 * Implementation file for the Inodes of the file system. The file system contains
 * an array of 1000 Inodes. Each Inode is linked to a record and has
 * details information about its UID, GID, disk blocks, type, access mode,
 * time created, and time modified. It has a vector of pointers pointing to
 * the exact blocks on disk its using. Blocks may also be added or removed
 * using the designated file system commands (MF and DB).
 */
#include "inode.h"

Inode::Inode() {

}

/*
 * Constructor for an inode.
 */
Inode::Inode(int blocks) {
    type = "File";
    accessMode = "-rwxr--r--";
    uid = "CSS430";
    gid = "CSS430";
    // block count is stored in directBlocks.size()

    timeCreated = std::time(0);
    timeModified = std::time(0);
}

// Destructor
Inode::~Inode() {
    // Remove all allocated blocks
    for(auto itr = directBlocks.begin(); itr != directBlocks.end(); ++itr)
    {
        // Set bitmap value to 0
        *itr = 0;
    }
    std::cout << "-=- Called inode destructor" << std::endl;
}

/*
 * Adds direct blocks to an existing inode. Appends onto the end of the
 * direct mapping
 */
void Inode::AddDirectBlocks(const std::vector<int *> &newBlocks) {
    directBlocks.insert(directBlocks.begin(), newBlocks.begin(), newBlocks.end());
}

/*
 * Getters and setters
 */
const std::string &Inode::getUid() const {
    return uid;
}

void Inode::setUid(const std::string &uid) {
    Inode::uid = uid;
}

const std::string &Inode::getType() const {
    return type;
}

void Inode::setType(const std::string &type) {
    Inode::type = type;
}

const std::string &Inode::getAccessMode() const {
    return accessMode;
}

void Inode::setAccessMode(const std::string &accessMode) {
    Inode::accessMode = accessMode;
}

const std::string &Inode::getGid() const {
    return gid;
}

void Inode::setGid(const std::string &gid) {
    Inode::gid = gid;
}

time_t Inode::getTimeCreated() const {
    return timeCreated;
}

void Inode::setTimeCreated(time_t timeCreated) {
    Inode::timeCreated = timeCreated;
}

time_t Inode::getTimeModified() const {
    return timeModified;
}

void Inode::setTimeModified(time_t timeModified) {
    Inode::timeModified = timeModified;
}

/*
 * Returns the number of bits the file is using up.
 * Assumes each block is 512K in size
 */
int Inode::getSize() const {
    return directBlocks.size() * 512;
}

/*
 * Returns the number of blocks used by the file
 */
int Inode::getBlockCount() const {
    return directBlocks.size();
}

std::vector<int *> &Inode::getDirectBlocks(){
    return directBlocks;
}

void Inode::setDirectBlocks(const std::vector<int *> &directBlocks) {
    Inode::directBlocks = directBlocks;
}
