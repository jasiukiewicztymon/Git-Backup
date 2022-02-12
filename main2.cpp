#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <time.h>   

/*
    gitPath: C:/Users/Jasiu/.git/
*/

int main() {
    std::cout << "   ____    __              _______________  __            __           \n"
        << "  / __/__ / /___ _____    / ___/  _/_  __/ / /  ___ _____/ /____ _____ \n"
        << " _\\ \\/ -_) __/ // / _ \\  / (_ // /  / /   / _ \\/ _ `/ __/  '_/ // / _ \\\n"
        << "/___/\\__/\\__/\\_,_/ .__/  \\___/___/ /_/   /_.__/\\_,_/\\__/_/\\_\\\\_,_/ .__/\n"
        << "                /_/                                             /_/    \n\nGithub: jasiukiewicztymon\n\n";

    const std::string gitPath = "C:/Users/Jasiu/.git/";

    int choice;
    struct stat buffer;

    std::string path0;
    std::vector<std::string> Path0;

    do {
        // get option
        std::cout << "[0] - Upload from local a backup\n[1] - Download to local a backup\n[2] - Exit\n\n";
        do {
            std::cout << "> ";
            std::cin >> choice;
        } while (choice < 0 || choice > 3);
        std::cout << "\n";

        // switch option to scripts
        switch (choice) {
            case 0:
                // select folder to upload
                do {
                    std::cout << "Give a path to backup: ";
                    std::cin >> path0;

                    if (stat(path0.c_str(), &buffer) == 0)
                        Path0.emplace_back(path0);
                    else
                        std::cout << "Invalid path!\n";
                } while (path0[0] == '.' || path0.rfind(":\\", 1) == 0 || path0.rfind(":/", 1) == 0);

                // select a repository
                break;
            case 1:
                break;
        }
        std::cout << "\n";
    } while (choice != 2);
}
