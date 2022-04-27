//
// Created by mora on 26.04.2022.
//

#ifndef MULTITHREADFILECOPIER_PRODUCERSFILECOPIER_H
#define MULTITHREADFILECOPIER_PRODUCERSFILECOPIER_H

#include <queue>
#include <string>
#include <mutex>
#include <experimental/filesystem>
#include <iostream>
#include <atomic>

#define overwriteUserFlag 1
#define askOverwriteUserFlag 0

namespace fs = std::experimental::filesystem;

class producersFileCopier {
public:
    explicit producersFileCopier(std::string &dstDir, std::queue<std::string> *filesQueue, std::mutex *mutexConnection,
                                 std::atomic<bool> *atomicConnection)
            : _dstDir(dstDir),
              _filesQueue(filesQueue),
              _overwrite(askOverwriteUserFlag),
              _mutexConnection(mutexConnection),
              _atomicConnection(atomicConnection) {};

    producersFileCopier(std::string &dstDir, std::queue<std::string> *filesQueue, bool overwriteFlag,
                        std::mutex *mutexConnection, std::atomic<bool> *atomicConnection)
            : _dstDir(dstDir),
              _filesQueue(filesQueue),
              _overwrite(overwriteFlag),
              _mutexConnection(mutexConnection),
              _atomicConnection(atomicConnection) {};

    int copyFilesToAnotherDir();


private:
    static int getUserOverWriteAnswer(bool &, std::string &);

    std::string _dstDir;
    std::queue<std::string> *_filesQueue;
    std::mutex *_mutexConnection;
    std::mutex _mutexProducers;
    bool _overwrite;
    std::atomic<bool> *_atomicConnection;
};


#endif //MULTITHREADFILECOPIER_PRODUCERSFILECOPIER_H
