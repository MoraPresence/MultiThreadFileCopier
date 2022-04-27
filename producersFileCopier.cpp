//
// Created by mora on 26.04.2022.
//

#include "producersFileCopier.h"

int producersFileCopier::copyFilesToAnotherDir() {
    std::string q_element;
    bool result;
    do {
        while (!_filesQueue->empty()) {
            _mutexConnection->lock();
            q_element = _filesQueue->front();
            _filesQueue->pop();
            _mutexConnection->unlock();
        }
        if (_overwrite == overwriteUserFlag)
            fs::copy_file(q_element, _dstDir, fs::copy_options::overwrite_existing);
        else {
            _mutexProducers.lock();
            getUserOverWriteAnswer(result, q_element);
            _mutexProducers.unlock();
            if (result) {
                fs::copy_file(q_element, _dstDir, fs::copy_options::overwrite_existing);
            }
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
