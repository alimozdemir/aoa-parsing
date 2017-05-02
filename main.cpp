//@author   Alim Ozdemir 150140807
//@date     23.04.2017
//@desc
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <fstream>
#include "Parser.h"

Parser p;

int main(int argc, char*argv[]) {
	if (argc != 2)
	{
		std::cout << "Wrong command line." << std::endl;
		return -1;
	}

	//init the rules, words etc..
	init();

	//read input file
	std::string output;
	std::ifstream file(argv[1]);
	std::vector<std::string> sentences;
	while (std::getline(file, output))
	{
		sentences.push_back(output);
	}
	file.close();

	auto it = sentences.begin();

	std::ofstream outputFile("output.txt");
	for (; it != sentences.end(); it++) {
		std::string result = p.extractParseTree(*it);

		std::cout << "[SENTENCE] " << *it << std::endl;
		std::cout << "[RESULT] " << result << std::endl;
		outputFile << result << std::endl;
	}
	outputFile.close();

	return 0;
}
