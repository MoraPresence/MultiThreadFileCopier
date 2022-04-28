//
// Created by mora on 26.04.2022.
//


#include "producersFileCopier.h"
#include "consumerFileCopier.h"

/*int producersFileCopier::copyFilesToAnotherDir() {
    std::string q_element;
    bool result;
    do {
        while (!_filesQueue->empty()) {
            _mutexConnection->lock();
            q_element = _filesQueue->front();
            _filesQueue->pop();
            _mutexConnection->unlock();

            if (_overwrite == overwriteUserFlag)
                fs::copy(q_element, _dstDir, fs::copy_options::overwrite_existing);
            else {
                _mutexProducers.lock();
                getUserOverWriteAnswer(result, q_element);
                _mutexProducers.unlock();
                if (result) {
                    fs::copy(q_element, _dstDir, fs::copy_options::overwrite_existing);
                }
            }
        }
    } while (*_atomicConnection != true);
    return 0;
}*/

int producersFileCopier::copyFilesToAnotherDir(struct directoryInfo *dir, std::string dstDir) {
    std::string q_element;
    struct directoryInfo *d_element;
    bool result;
    do {
        while (!dir->files.empty()) {
            _mutexConnection->lock();
            q_element = dir->files.back();
            dir->files.pop_back();
            _mutexConnection->unlock();
            std::string tmp = dstDir + "/" + (q_element.substr(q_element.find_last_of("/\\") + 1));
            if (_overwrite == overwriteUserFlag)
                fs::copy(q_element, dstDir, fs::copy_options::overwrite_existing);
            else {
                _mutexProducers.lock();
                if (fs::exists(tmp)) getUserOverWriteAnswer(result, q_element);//here
                else result = true;
                _mutexProducers.unlock();
                if (result) {
                    fs::copy(q_element, dstDir, fs::copy_options::overwrite_existing);
                }
            }
        }
        while (!dir->directories.empty()) {
            _mutexConnection->lock();
            d_element = dir->directories.back();
            dir->directories.pop_back();
            _mutexConnection->unlock();
            std::string tmp = dstDir + ((d_element->pathDir).substr(d_element->pathDir.find_last_of("/\\")));
            if (!fs::exists(tmp)) fs::create_directory(tmp);

            copyFilesToAnotherDir(d_element, tmp);
        }
    } while (*_atomicConnection != true);
    return 0;
}

int producersFileCopier::getUserOverWriteAnswer(bool &answer_valid, std::string &file) {
    answer_valid = false;
    std::string answer;

    std::cout << "Overwrite this file?" << file << "[Y/n]:";
    std::cin >> answer;

    std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

    answer_valid =
            (answer == "y") ||
            (answer == "n") ||
            (answer == "yes") ||
            (answer == "no");

    return 0;
}
