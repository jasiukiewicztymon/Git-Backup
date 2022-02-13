#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <time.h>   
#include <windows.h>
#include <Lmcons.h>


#ifndef _UNISTD_H
#define _UNISTD_H    1

#include <stdlib.h>
#include <io.h>
#include <process.h> 
#include <direct.h> 

#define srandom srand
#define random rand

#define R_OK    4       
#define W_OK    2       
#define F_OK    0   

#define access _access
#define dup2 _dup2
#define execve _execve
#define ftruncate _chsize
#define unlink _unlink
#define fileno _fileno
#define getcwd _getcwd
#define chdir _chdir
#define isatty _isatty
#define lseek _lseek

#ifdef _WIN64
#define ssize_t __int64
#else
#define ssize_t long
#endif

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#endif

#include <chrono>
#include <ctime>  

#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")
#pragma comment( lib, "advapi32" )  

#include "dirent.h"

/*
    gitPath: C:/Users/Jasiu/.git/
*/

std::string user_name()
{
    char buffer[UNLEN + 1]{};
    DWORD len = UNLEN + 1;
    if (::GetUserNameA(buffer, &len)) return buffer;
    else return {}; // or: return "" ;
}

int main() {
    system("");
    struct stat buffer;
    std::string name = user_name();
    const std::string gitPath = "C:/Users/" + name + "/GitBackup/";
    if (stat(".\\Scripts\\", &buffer) != 0) {
        system("mkdir .\\Scripts\\");
    }

    std::string n;
    std::vector<std::string> Dir;

    std::cout << "   ____    __              _______________  __            __           \n"
        << "  / __/__ / /___ _____    / ___/  _/_  __/ / /  ___ _____/ /____ _____ \n"
        << " _\\ \\/ -_) __/ // / _ \\  / (_ // /  / /   / _ \\/ _ `/ __/  '_/ // / _ \\\n"
        << "/___/\\__/\\__/\\_,_/ .__/  \\___/___/ /_/   /_.__/\\_,_/\\__/_/\\_\\\\_,_/ .__/\n"
        << "                /_/                                             /_/    \n\nGithub: jasiukiewicztymon\n\n";

    int choice;

    std::ifstream f((gitPath + "config").c_str());
    if (!f) {
        std::ofstream fw((gitPath + "config").c_str());
        fw << "";
        fw.close();
    }
    f.close();

    std::string content, outname;
    std::ofstream fw;

    char backer0 = 0;
    std::string path0, repo0, filename0 = "";
    std::vector<std::string> Path0;

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::string timer = std::ctime(&end_time);
    std::string timestr = timer.substr(0, 3) + timer.substr(4, 3) + timer.substr(timer.size() - 5, 4);

    do {
        // get option
        std::cout << "[0] - Upload from local a backup\n[1] - Download to local a backup\n[2] - Manage backups\n[3] - Exit\n\n";
        do {
            std::cout << "> ";
            std::cin >> choice;
        } while (choice < 0 || choice > 4);
        std::cout << "\n";

        std::cin.ignore();

        // switch option to scripts
        switch (choice) {
            case 0:
                // select folder to upload
                while (1) {
                    std::cout << "Give a path to backup: ";
                    std::getline(std::cin, path0);
                    if (path0.size() < 5)
                        break;
                    else
                        Path0.emplace_back(path0);
                } 
                
                std::cout << "\n";
       
                // select a repository
                do {
                    std::cout << "Give the repository url: ";
                    std::cin >> repo0;
                    if (repo0.rfind("https://", 0) == 0 || repo0.rfind("http://", 0) == 0 || repo0.rfind("git@", 0) == 0)
                        break;
                } while (1);

                std::cout << "\n";

                /*
                Config file:

                date ~ [date]
                repo ~ [link]
                file ~ [dir]
                */

                std::cout << "\nName the bat file: ";
                std::cin >> outname;
                n = ".\\Scripts\\" + outname + "\\";

                if (stat(n.c_str(), &buffer) != 0) {
                    system(("mkdir " + n).c_str());
                }

                for (int i = 0; i < Path0.size(); i++)
                    system(("copy /Z \"" + Path0[i] + "\" .\\Scripts\\" + outname + "\\").c_str());

                fw.open(".\\Scripts\\" + outname + "\\" + outname + ".bat");
                fw << "@echo off\n";
                fw << "git.exe init\n";
                fw << "git.exe add --all\n";
                fw << "git.exe commit -m " + timestr + "\n";
                fw << "git.exe branch -M " + timestr + "\n";
                fw << "git.exe remote set-url origin " + repo0 + "\n";
                fw << "git.exe push --all --repo=" + repo0 + "\n";
                fw << "exit";
                fw.close();

                fw.open(".\\Scripts\\" + outname + "\\" + outname);
                fw << timestr << "\n" << repo0 << "\n";
                fw.close();

                std::cout << "\nThe opertation ended successfuly!\n\n";

                system(("start .\\Scripts\\" + outname + "\\" + outname + ".bat").c_str());

                Path0.clear();
                break;
            case 1:
                break;
            case 2:
                break;
        }
    } while (choice != 3);
}
