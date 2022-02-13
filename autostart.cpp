#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <time.h>   
#include <windows.h>
#include <Lmcons.h>
#include <iostream>
#include <Windows.h>

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

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    while (1) {
        std::time_t rawtime;
        std::tm* timeinfo;
        char buffer2[80];

        std::time(&rawtime);
        timeinfo = std::localtime(&rawtime);

        std::strftime(buffer2, 80, "%Y-%m-%d", timeinfo);

        std::string date = buffer2, wdate, line, content, newcontent;

        std::vector<std::string> Dir;
        struct dirent* d;
        DIR* dr;
        dr = opendir(".\\Scripts\\");

        if (dr != NULL)
        {
            for (d = readdir(dr); d != NULL; d = readdir(dr)) { Dir.push_back(d->d_name); }
            closedir(dr);
        }

        std::fstream file, f;

        for (int i = 0; i < Dir.size(); i++) {
            if (Dir[i] != "." && Dir[i] != ".." && Dir[i] != ".git") {
                file.open(".\\Scripts\\" + Dir[i] + "\\" + Dir[i]);

                file >> wdate;
                file.close();
                if (wdate != date) {
                    f.open(".\\Scripts\\" + Dir[i] + "\\" + Dir[i]);
                    f << date;
                    f.close();
                    f.open(".\\Scripts\\" + Dir[i] + "\\" + Dir[i] + ".bat");
                    while (getline(f, line)) {
                        content += line + "\n";
                    }

                    int start = 0;
                    int end = content.find(wdate);
                    while (end != -1) {
                        newcontent += content.substr(start, end - start) + date;
                        start = end + wdate.size();
                        end = content.find(wdate, start);
                    }
                    newcontent += content.substr(start, end - start);
                    f.close();
                    f.open(".\\Scripts\\" + Dir[i] + "\\" + Dir[i] + ".bat");
                    f << newcontent;
                    f.close();
                    newcontent = "";

                    system(("start .\\Scripts\\" + Dir[i] + "\\" + Dir[i] + ".bat").c_str());
                }
            }
        }
        Sleep(10000);
    }
}
