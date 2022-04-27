//
// Created by mora on 26.04.2022.
//

#ifndef MULTITHREADFILECOPIER_CONSUMERFILECOPIER_H
#define MULTITHREADFILECOPIER_CONSUMERFILECOPIER_H

#include <queue>
#include <string>
#include <mutex>
#include <experimental/filesystem>
#include <iostream>
#include <atomic>

namespace fs = std::experimental::filesystem;

class consumerFileCopier {
public:
    explicit consumerFileCopier(std::queue<std::string> *filesQueue, std::mutex *mutexConnection,
                                std::atomic<bool> *atomicConnection) : _filesQueue(filesQueue),
                                                                       _mutexConnection(mutexConnection),
                                                                       _atomicConnection(atomicConnection) {};

    int fillFilesQueue(std::string &);

private:
    std::queue<std::string> *_filesQueue;
    std::mutex *_mutexConnection;
    std::atomic<bool> *_atomicConnection;
};


#endif //MULTITHREADFILECOPIER_CONSUMERFILECOPIER_H
