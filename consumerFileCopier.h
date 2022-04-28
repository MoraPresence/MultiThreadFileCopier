//
// Created by mora on 26.04.2022.
//

#ifndef MULTITHREADFILECOPIER_CONSUMERFILECOPIER_H
#define MULTITHREADFILECOPIER_CONSUMERFILECOPIER_H

#include <queue>
#include <string>
#include <mutex>
#include <filesystem>
#include <iostream>
#include <atomic>
#include <thread>

namespace fs = std::filesystem;

struct directoryInfo {
    std::vector<std::string> files;
    std::vector<struct directoryInfo *> directories;
    std::string pathDir;
};


class consumerFileCopier {
public:
    /*explicit consumerFileCopier(std::queue<std::string> *filesQueue, std::mutex *mutexConnection,
                                std::atomic<bool> *atomicConnection) : _filesQueue(filesQueue),
                                                                       _mutexConnection(mutexConnection),
                                                                       _atomicConnection(atomicConnection) {};*/

    explicit consumerFileCopier(struct directoryInfo *directoryInfo,
                                std::mutex *mutexConnection,
                                std::atomic<bool> *atomicConnection) :
            _directoryInfo(directoryInfo),
            _mutexConnection(mutexConnection),
            _atomicConnection(atomicConnection) {};


    int setConsumerCount(int value);


    int fillFilesQueue(struct directoryInfo *);

private:


    struct directoryInfo *_directoryInfo;
    std::mutex *_mutexConnection;
    std::atomic<bool> *_atomicConnection;
    int _consumerCount = 1;
};


#endif //MULTITHREADFILECOPIER_CONSUMERFILECOPIER_H
