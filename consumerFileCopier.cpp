//
// Created by mora on 26.04.2022.
//

#include "consumerFileCopier.h"


/*int consumerFileCopier::fillFilesQueue(std::string pathToDir) {
    if (fs::exists(pathToDir)) {
        if (!fs::is_directory(pathToDir)) return -1;
    } else return -1;
    std::cout << "ok" << std::endl;
    for (const auto &file : fs::recursive_directory_iterator(pathToDir)) {
        //if (!fs::is_regular_file(file.path())) continue;
        std::cout << file.path() << std::endl;
        _mutexConnection->lock();
        _filesQueue->push(file.path().string());
        _mutexConnection->unlock();
    }
    *_atomicConnection = true;
    return 0;
}*/

int consumerFileCopier::fillFilesQueue(struct directoryInfo * dir) {
    if (fs::exists(dir->pathDir)) {
        if (!fs::is_directory(dir->pathDir)) return -1;
    } else return -1;
    //std::cout << "ok" << std::endl;
    for (const auto &file : fs::directory_iterator(dir->pathDir)) {
        if (fs::is_regular_file(file.path())){
            //std::cout << file.path() << std::endl;
            _mutexConnection->lock();
            dir->files.push_back(file.path());
            _mutexConnection->unlock();
        }else if(fs::is_directory(file.path())){
            //std::cout << file.path() << std::endl;
            auto* nextDir = new directoryInfo();
            nextDir->pathDir = file.path();
            _mutexConnection->lock();
            dir->directories.push_back(nextDir);
            _mutexConnection->unlock();
            fillFilesQueue(nextDir);
        } else continue;

    }
    *_atomicConnection = true;
    return 0;
}


int consumerFileCopier::setConsumerCount(int value) {
    _consumerCount = value;
    return 0;
}
