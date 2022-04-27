#include <iostream>
#include <experimental/filesystem>
#include "consumerFileCopier.h"
#include "producersFileCopier.h"
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

namespace fs = std::experimental::filesystem;


void demo_status(const fs::path &p, fs::file_status s) {
    std::cout << p;
    // alternative: switch(s.type()) { case fs::file_type::regular: ...}
    if (fs::is_regular_file(s)) std::cout << " is a regular file\n";
    if (fs::is_directory(s)) std::cout << " is a directory\n";
    if (fs::is_block_file(s)) std::cout << " is a block device\n";
    if (fs::is_character_file(s)) std::cout << " is a character device\n";
    if (fs::is_fifo(s)) std::cout << " is a named IPC pipe\n";
    if (fs::is_socket(s)) std::cout << " is a named IPC socket\n";
    if (fs::is_symlink(s)) std::cout << " is a symlink\n";
    if (!fs::exists(s)) std::cout << " does not exist\n";
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    /*std::string src = "C:\\Users\\od341\\CLionProject\\multiThreadFileCopier\\DirToTest1";
    std::string dst = "C:\\Users\\od341\\CLionProject\\multiThreadFileCopier\\DirToTest2";
    std::mutex mutexConnection;
    std::atomic<bool> atomicConnection = new std::atomic<bool>();
    atomicConnection = false;
    std::queue<std::string> queue;
    consumerFileCopier a(&queue, &mutexConnection, &atomicConnection);
    a.fillFilesQueue(src);
    producersFileCopier b(dst, &queue, &mutexConnection, &atomicConnection);
    b.copyFilesToAnotherDir();*/

    fs::copy_file("C:\\Users\\od341\\CLionProject\\multiThreadFileCopier\\DirToTest1\\IamTest\\9.txt",
                  "C:\\Users\\od341\\CLionProject\\multiThreadFileCopier\\DirToTest2",
                  fs::copy_options::overwrite_existing | fs::copy_options::recursive);
    return 0;
}
