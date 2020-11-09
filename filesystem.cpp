/*
 * Jarod Guerrero and Antong Cheng
 * CSS FourThreeZero A
 * Final Project - Unix File System
 * 8/22/19
 *
 * Implementation for the file system object. File system contains
 * a single directory, disk, and array of 1000 inodes.
 * Supports four commands read in from a file named "commands.txt"
 *      NF - New File
 *      MF - Modify File
 *      DF - Delete File
 *      DB - Delete Blocks
 */

#include "filesystem.h"

/*
 * Constructor initializes the inode array with 1000 null inodes
 */
FileSystem::FileSystem() {
    inodeArray = vector<Inode *>(1000, nullptr);
}

// Destructor
FileSystem::~FileSystem() {
}

/*
 * Parses and runs commands based on a commands
 * file input. File must be named newCommands.txt and located
 * in the same directory.
 */
int FileSystem::ReadCommands() {
    ifstream infile("commands.txt");
    if (!infile) {
        cout << "commands.txt not found." << endl;
        return 1;
    }
    string info;
    getline(infile, info); // Check if first line is FM
    if (info[info.size() - 1] == '\r') // trim \r from string
        info.resize(info.size() - 1);

    if (info != "FM") {
        cout << "File System not Formatted" << endl;
        return 1;
    }

    while (!infile.eof()) {
        vector<string> tokens;
        getline(infile, info);

        if (info[info.size() - 1] == '\r') // trim \r from string
            info.resize(info.size() - 1);

        std::istringstream ss(info);
        string token;

        // Tokenize input
        while (getline(ss, token, ' ')) {
            // token.erase(0, 1); // erase extra space at start
            tokens.push_back(token);
        }

        // Read NF command
        if (tokens[0] == "NF") {
            cout << info << endl;
            NewFile(tokens[1], stoi(tokens[2]));
            PrintDirectory();
        }
            // Read MF command
        else if (tokens[0] == "MF") {
            cout << info << endl;
            ModifyFile(tokens[1], stoi(tokens[2]));
            PrintDirectory();
        }
            // Read DF
        else if (tokens[0] == "DF") {
            cout << info << endl;
            DeleteFile(tokens[1]);
            PrintDirectory();
        }
            // Read DB
        else if (tokens[0] == "DB") {
            cout << info << endl;
            DeleteBlocks(tokens[1], stoi(tokens[2]));
            PrintDirectory();
        } else {
            cout << "Error: " << tokens[0] << " is an unknown command." << endl;
        }
    }
    return 0;
}

/*
 * Prints info about each record in the directory and
 * the total number of blocks on disk being utilized.
 */
void FileSystem::PrintDirectory(){
    for(auto itr = directory.begin(); itr != directory.end(); ++itr)
    {
        cout << *itr << endl;
    }
    cout << "Blocks Used/Free: " << disk.GetNumUsedBlocks() << "/" << 1000 << endl;
    cout << endl;
}

/*
 * Creates a new file within the main directory. A new record is added
 * to the end of the directory list. This record has a corresponding
 * inode which contains info about the file and any allocated disk blocks
 */
int FileSystem::NewFile(std::string fileName, int size) {
    for (int i = 0; i < 1000; i++) {
        if (inodeArray[i] == nullptr) {
            // Create Inode and record
            Inode *pInode = new Inode(size);
            // Allocate blocks from disk
            pInode->setDirectBlocks(disk.TakeBlock(size));

            Record temp = Record(fileName, pInode);
            directory.push_back(temp);
            // Create new inode, set inode[i] to point
            inodeArray[i] = pInode;
            cout << "Allocated new Inode at index " << i << endl;
            return 1;
        }
    }
    cout << "Failed to find inode slot" << endl;
    return 0;
}

/*
 * Modify file function used to add blocks to an existing file. Additional
 * blocks are added on to the end.
 */
int FileSystem::ModifyFile(std::string fileName, int size)
{
    for(auto itr = directory.begin(); itr != directory.end(); ++itr)
    {
        // Find file in directory
        if(itr->getFileName() == fileName)
        {
            // Add blocks to the direct mapping
            itr->getFile()->AddDirectBlocks(disk.TakeBlock(size));
            // Update time
            itr->getFile()->setTimeModified(time(0));
            cout << "Mapped " << size << " extra blocks." << endl;
            return 1;
        }
    }
    cout << "Error: File not found" << endl;
    return 0;
}

/*
 * Deletes a file and all its allocated blocks from the disk. All its blocks are free'd
 * for other files to use and the file is erased from the list.
 * Its inode is also deleted and free'd in the inode array.
 */
int FileSystem::DeleteFile(std::string fileName) {
    // To delete a file, we need to delete its record and inode entry
    auto itr = directory.begin();
    while (itr->getFileName() != fileName) {
        ++itr;
    }
    cout << fileName << " found and ready for deletion." << endl;

    // Set inode array entry to nullptr, then delete record
    for (int i = 0; i < 1000; i++) {
        if (inodeArray[i] != nullptr) {
            if (inodeArray[i] == itr->getFile()) {
                inodeArray[i] = nullptr;
                std::cout << "Set Inode array at index " << i << " to nullptr" << endl;
                directory.erase(itr);
                return 1;
            }
        }
    }
    cout << "Error deleting file" << endl;
    return 0;
}

/*
 * Deletes blocks from an existing file. File will still exist as an
 * empty file if all blocks are deleted and must be deleted through
 * the delete file command.
 * Blocks are deallocated starting with the newest ones
 */
int FileSystem::DeleteBlocks(std::string fileName, int size) {
    for(auto itr = directory.begin(); itr != directory.end(); ++itr)
    {
        // Find file in directory
        if(itr->getFileName() == fileName)
        {
            disk.FreeBlock(itr->getFile()->getDirectBlocks(), size);
            return 1;
        }
    }
    cout << "Error: File not found" << endl;
    return 0;
}
