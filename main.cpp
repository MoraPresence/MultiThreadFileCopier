#include <iostream>
#include <thread>
#include <cstring>
#include "consumerFileCopier.h"
#include "producersFileCopier.h"

#define consumerCount 1
#define producerCount 2

#define argsWithoutMode 5
#define argsWithMode 7


/******************************************************************************/
//2. Многопоточность                                                          //
//        Напишите программу, которая принимает на вход два пути к директориям//
//        и копирует содержимое первой директории во вторую. Это должно       //
//        делаться в многопоточном режиме. Если в целевой директории уже      //
//        существует поддиректория как в исходной - нужно записывать в нее.   //
//        Если существует файл - нужно запрашивать подтверждение у            //
//        пользователя. Пользователь должен иметь возможность заранее указать //
//        какой-то флаг при запуске программы, давая таким образом            //
//        подтверждение перезаписи файлов заранее.                            //
/******************************************************************************/

namespace fs = std::filesystem;

/*
 * std::vector<std::thread> threads;
    threads.reserve(_threadCountDownload);
    for (size_t i = 0; i < _threadCountDownload; ++i) {
        threads.emplace_back(std::thread
        (&crawler::downloader, this, &currentList, &tmp));
    }
    for (auto &th : threads) {
        th.join();
    }
 */

int indexOfArg(int argc, char *argv[], const std::string &whatToFind) {
    for (int i = 0; i < argc; ++i) {
        if (whatToFind == std::string(argv[i]))
            return i;
    }
    return -1;
}

bool workWithArgs(int argc, char *argv[], std::string &srcPath, std::string &dstPath, std::string &mode) {
    int ind = 0;
    if (argc == argsWithoutMode) {
        if (((ind = indexOfArg(argc, argv, "--srcPath")) != -1) && (ind < argc - 1)) {
            srcPath = std::string(argv[ind + 1]);
        }
        if (((ind = indexOfArg(argc, argv, "--dstPath")) != -1) && (ind < argc - 1)) {
            dstPath = std::string(argv[ind + 1]);
        }
        return !(srcPath.empty() || dstPath.empty());
    } else if (argc == argsWithMode) {
        if (((ind = indexOfArg(argc, argv, "--srcPath")) != -1) && (ind < argc - 1)) {
            srcPath = std::string(argv[ind + 1]);
        }
        if (((ind = indexOfArg(argc, argv, "--dstPath")) != -1) && (ind < argc - 1)) {
            dstPath = std::string(argv[ind + 1]);
        }
        if (((ind = indexOfArg(argc, argv, "--mode")) != -1) && (ind < argc - 1)) {
            if (strcmp(argv[ind + 1], "overwrite") == 0) mode = std::string(argv[ind + 1]);
        }

        return !(srcPath.empty() || dstPath.empty() || mode.empty());
    } else {
        std::cout << "Error in args" << std::endl;
        std::cout << "ArgsWithoutMode: --srcPath /example/path --dstPath /examplePath" << std::endl;
        std::cout << "ArgsWithMode: --srcPath /example/path --dstPath /examplePath --mode overwrite" << std::endl;
        return false;
    }

}

int main(int argc, char *argv[]) {
    std::string srcPath, dstPath, mode;
    std::mutex mutexConnection;
    std::atomic<bool> atomicConnection = new std::atomic<bool>();
    auto *o_directoryInfo = new directoryInfo();
    std::vector<std::thread> threadsConsumer;
    std::vector<std::thread> threadsProdusers;

    workWithArgs(argc, argv, srcPath, dstPath, mode);
    atomicConnection = false;
    o_directoryInfo->pathDir = srcPath;


    consumerFileCopier consumer(o_directoryInfo, &mutexConnection, &atomicConnection);
    for (size_t i = 0; i < consumerCount; ++i) {
        threadsConsumer.emplace_back(std::thread
                                             (&consumerFileCopier::fillFilesQueue, &consumer, o_directoryInfo));
    }


    producersFileCopier produsers(dstPath, &mutexConnection, &atomicConnection);//delete dstPath
    for (size_t i = 0; i < producerCount; ++i) {
        threadsProdusers.emplace_back(std::thread
                                              (&producersFileCopier::copyFilesToAnotherDir, &produsers, o_directoryInfo, dstPath));
    }

    for (auto &th : threadsConsumer) {
        th.join();
    }

    for (auto &th : threadsProdusers) {
        th.join();
    }

    return 0;
}
