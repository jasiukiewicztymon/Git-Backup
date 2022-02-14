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

int main() {
    system("");
    struct stat buffer;
    char buffer3[UNLEN + 1];
    DWORD len = UNLEN + 1;
    std::string name;
    if (::GetUserNameA(buffer3, &len))
        name = buffer3;
    const std::string gitPath = "C:/Users/" + name + "/GitBackup/";
    if (stat(".\\Scripts\\", &buffer) != 0) {
        system("mkdir .\\Scripts\\");
    }

    struct dirent* d;
    int pathtodel;

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

    std::string path1, repo1;
    std::vector<std::string> Repo1;

    do {
        // version name
        std::time_t rawtime;
        std::tm* timeinfo;
        char buffer2[80];

        std::time(&rawtime);
        timeinfo = std::localtime(&rawtime);

        std::strftime(buffer2, 80, "%Y-%m-%d", timeinfo);

        std::string date = buffer2;

        // get option
        std::cout << "[0] - Generate backup script from local to Git\n[1] - Generate backup script from Git to local\n[2] - Delete backups\n[3] - Exit\n\n";
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
                system(("xcopy /S /E /-Y /Y \"" + Path0[i] + "\" .\\Scripts\\" + outname + "\\").c_str());

            fw.open(".\\Scripts\\" + outname + "\\" + outname + ".bat");
            fw << "@echo off\n";
            for (int i = 0; i < Path0.size(); i++)
                fw << "xcopy /S /E /-Y /Y \"" + Path0[i] + "\" .\\Scripts\\" + outname + "\\\n";
            fw << "git.exe init\n";
            fw << "git.exe add --all\n";
            fw << "git.exe add .\n";
            fw << "git.exe add *\n";
            fw << "git.exe commit -m " + date + "\n";
            fw << "git.exe branch -M " + date + "\n";
            fw << "git.exe remote set-url origin " + repo0 + "\n";
            fw << "git.exe push --all --repo=" + repo0 + "\n";
            fw << "exit";
            fw.close();

            fw.open(".\\Scripts\\" + outname + "\\" + outname);
            fw << date << "\n";
            fw.close();

            std::cout << "\nThe opertation ended successfuly!\n\n";

            Path0.clear();
            break;
        case 1:
            // select a repository
            do {
                std::cout << "Give the repository url: ";
                getline(std::cin, repo1);
                if (repo1.rfind("https://", 0) == 0 || repo1.rfind("http://", 0) == 0 || repo1.rfind("git@", 0) == 0)
                    Repo1.emplace_back(repo1);
                else
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

            fw.open(".\\Scripts\\" + outname + "\\" + outname + ".bat");
            fw << "@echo off\n";
            fw << "cd " << n << "\n";
            for (int i = 0; i < Repo1.size(); i++) {
                fw << "git clone " << Repo1[i] << " .\\Scripts\\" << outname << "\\" << date << "\\\n";
            }
            fw << "exit";
            fw.close();

            fw.open(".\\Scripts\\" + outname + "\\" + outname);
            fw << date << "\n";
            fw.close();

            std::cout << "\nThe opertation ended successfuly!\n\n";

            Repo1.clear();
            break;
        case 2:
            DIR * dr;
            dr = opendir(".\\Scripts");

            if (dr != NULL)
            {
                for (d = readdir(dr); d != NULL; d = readdir(dr)) { Dir.push_back(d->d_name); }
                closedir(dr);
            }

            for (int i = 0; i < Dir.size(); i++) {
                std::cout << i << ": " << Dir[i] << "\n";
            }

            std::cout << "\n";

            std::cout << "Write a path index to delete: ";
            std::cin >> pathtodel;
            if (pathtodel < Dir.size() && pathtodel >= 0) {
                system(("rmdir .\\Scripts\\" + Dir[pathtodel]).c_str());
            }

            break;
        }
    } while (choice != 3);
}
