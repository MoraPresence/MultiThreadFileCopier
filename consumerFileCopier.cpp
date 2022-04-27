//
// Created by mora on 26.04.2022.
//

#include "consumerFileCopier.h"

int consumerFileCopier::fillFilesQueue(std::string &pathToDir) {
    if(fs::exists(pathToDir)){
        if (!fs::is_directory(pathToDir)) return -1;
    } else return -1;
    std::cout << "ok" << std::endl;
    for (const auto &file : fs::recursive_directory_iterator(pathToDir)) {
        if (!fs::is_regular_file(file.path())) continue;
        _mutexConnection->lock();
        _filesQueue->push(file.path().string());
        _mutexConnection->unlock();
    }
    *_atomicConnection = true;
    return 0;
}
