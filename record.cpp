/*
 * Jarod Guerrero and Antong Cheng
 * CSS 430 A
 * Final Project - Unix File System
 * 8/22/19
 *
 * Implementation file for the records within a directory.
 * A directory is a list of Record objects. Each record has
 * a file name and points to an Inode that contains
 * more detailed information about the file.
 */
#include "record.h"

Record::Record(std::string fileName, Inode* &p) {
    this->fileName = fileName;
    file = p;
}

// Destructor
Record::~Record() {

}

/*
 * Cout overload to print information about a record in the directory
 */
ostream &operator<<(ostream &os, const Record &r) {
    Inode* f = r.getFile();
    // Code to print the time modified
    time_t t = f->getTimeModified();
    tm* now = std::localtime(&t);

    os << "RecAdr: " << &r << " " << f->getAccessMode() << " UID:" << f->getUid() << " GID:" << f->getGid()
        << " Blocks:" << f->getBlockCount() << " " << (now->tm_year + 1900) << '-' << (now->tm_mon + 1)
        << '-' <<  now->tm_mday << " " << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec
        <<  " " << r.getFileName() << " Size:" << (r.getNumBlocks() * 512) << "K";
    return os;
}

/*
 * Returns a pointer to the record's Inode
 */
Inode *Record::getFile() const {
    return file;
}

/*
 * Returns the number of blocks used by the record
 */
int Record::getNumBlocks() const {
    return file->getBlockCount();
}

/*
 * Returns the name of the file.
 */
const std::string &Record::getFileName() const {
    return fileName;
}

/*
 * Function that allows one to rename a file. Not
 * currently used.
 */
void Record::setFileName(const std::string &fileName) {
    Record::fileName = fileName;
}
