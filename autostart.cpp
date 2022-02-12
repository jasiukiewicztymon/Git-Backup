#include "dirent.h"
#include <vector>
#include <string>
#include <chrono>
#include <ctime>  
#include <fstream>
#include <sstream>

int main() {
    std::vector<std::string> Dir;
    struct dirent* d;
    DIR* dr;
    dr = opendir(".\\Scripts\\");

    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr)) { Dir.push_back(d->d_name); }
        closedir(dr);
    }

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::string timer = std::ctime(&end_time);
    std::string timestr = timer.substr(0, 2) + timer.substr(4, 6) + timer.substr(timer.size() - 4, timer.size());

    std::string confStr, batContent, line;
    std::vector<std::string> Vconf, Vbat;

    for (int i = 0; i < Dir.size(); i++) {
        if (Dir[i].find('.') != std::string::npos) {
            std::ifstream conf(Dir[i]);
            conf >> confStr;
            conf.close();

            std::stringstream sc(confStr);
            while (sc >> line) {
                Vconf.emplace_back(line);
            }

            if (timestr != Vconf[0] && Vconf.size() >= 3 && (Vconf[1].rfind("https://", 0) == 0 || Vconf[1].rfind("http://", 0) == 0)) {
                std::string  content = "@echo off\n";
                for (int i = 2; i < Vconf.size() - 1; i++) {
                    content += "cd " + Vconf[i] + "\n";
                    content += "git init\ngit add .\ngit commit -m \"" + timestr + "\"\n";
                    if (i == 0)
                        content += "git branch \"" + timestr + "\"\n";
                    content += "git checkout \"" + timestr + "\"\n";
                    content += "git remote add origin " + Vconf[1] + "\n";
                    content += "git push -u origin \"" + timestr + "\"\n";
                }

                std::ofstream fw(".\\Scripts\\" + Dir[i] + ".bat");
                fw << content;
                fw.close();
            }
            else {

            }

            system(("start .\\Scripts\\" + Dir[i] + ".bat").c_str());
        }
    }
}
