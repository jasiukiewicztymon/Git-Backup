#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>

int main() {
    std::cout << "   ____    __              _______________  __            __           \n"
        << "  / __/__ / /___ _____    / ___/  _/_  __/ / /  ___ _____/ /____ _____ \n"
        << " _\\ \\/ -_) __/ // / _ \\  / (_ // /  / /   / _ \\/ _ `/ __/  '_/ // / _ \\\n"
        << "/___/\\__/\\__/\\_,_/ .__/  \\___/___/ /_/   /_.__/\\_,_/\\__/_/\\_\\\\_,_/ .__/\n"
        << "                /_/                                             /_/    \n\nGithub: jasiukiewicztymon\n\n";

    std::string str, path;
    std::vector<std::string> repo;
    struct stat buffer;

    do {
        std::cout << "Give the backup path: ";
        std::getline(std::cin, path); 
    } while (stat(path.c_str(), &buffer) != 0);

    if (path[path.size() - 1] == '\\') {
        system(("mkdir " + path + "backup\\").c_str());
        path += "backup\\";
    }    
    else {
        system(("mkdir " + path + "\\backup\\").c_str());
        path += "\\backup\\";
    }  

    std::cout << "\n";

    while (1) {
        std::cout << "Give the git repo link: ";
        std::getline(std::cin, str);
        if (str.rfind("https://", 0) == 0 || str.rfind("http://", 0) == 0) {
            repo.emplace_back(str);
        }
        else { break; }
    }

    std::cout << "\n";

    for (int i = 0; i < repo.size(); i++) {
        system(("git clone " + repo[i] + " " + path).c_str());
        std::cout << "\n";
    }
}
