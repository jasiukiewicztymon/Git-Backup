#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

int main() {
	struct stat buffer;
	std::string config = ".\config", line, line2, timer;
	std::vector<std::vector<std::string>> content;
	std::vector<std::string> temp;

	if (stat(config.c_str(), &buffer) == 0) {
		std::ifstream infile(config);

		while (infile >> line) {
			if (stat(line.c_str(), &buffer) == 0) {
				std::ifstream infile2(line);

				while (infile2 >> line2) {
					temp.push_back(line2);
				}

				infile.close();
			}
			content.emplace_back(temp);
			temp.clear();
		}
		infile.close();

		while (1) {
			
		}
	}
}
