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
    char ch;

    char chsave;
    std::string profilname, content = "", profilpath = ".\\profil\\", line;

    std::cout << "[0] - New Backup\n[1] - Backup from profil\n[2] - Exit\n\n";

    do {
        std::cin >> ch;
    } while (ch != '0' && ch != '1' && ch != '2');

    std::cout << "\n\n";

    switch (ch) {
        case '0':
            do {
                std::cout << "Give the backup path: ";
                std::getline(std::cin, path);
            } while (stat(path.c_str(), &buffer) != 0 && path != "exit");

            if (stat(path.c_str(), &buffer) == 0) {
                if (path[path.size() - 1] == '\\') {
                    system(("mkdir " + path + "backup\\").c_str());
                    path += "backup\\";
                }
                else {
                    system(("mkdir " + path + "\\backup\\").c_str());
                    path += "\\backup\\";
                }
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
            
            std::cout << "\n\n";

            std::cout << "Do you want to save the profil? [y/n] ";
            
            std::cin >> chsave;

            if (chsave == 'y') {
                std::cout << "\nGive the profil name: ";
                std::getline(std::cin, profilname);

                for (int i = 0; i < repo.size(); i++) {
                    content += "git clone " + repo[i] + " " + path + "\n";
                }
                
                if (stat(profilpath.c_str(), &buffer) != 0)
                    system(("mkdir " + profilpath).c_str());

                std::ofstream outfile(".\\profil\\" + profilname);
                outfile << content;
                outfile.close();
            }
            break;
        case '1':
            do {
                std::cout << "\nGive the profil name: ";
                std::getline(std::cin, profilname);
            } while (stat(profilpath.c_str(), &buffer) != 0 && profilpath != "exit");
            
            if (stat(profilpath.c_str(), &buffer) == 0) {
                std::ifstream infile(".\\profil\\" + profilname);

                while (infile >> line) {
                    system(line.c_str());
                }

                infile.close();
            }
            break;
    }

    system("cls");
}
