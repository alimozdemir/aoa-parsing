//@author   Alim Ozdemir 150140807
//@date     23.04.2017
//@desc
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "word.h"

class Parser {
private:
	std::string solve(std::vector<word> window, int current);
public:
	std::string extractParseTree(std::string sentence);
};

std::string error("SYNTAX ERROR");

bool isThisError(std::string result) {
	return result.compare(error) == 0;
}

std::string Parser::solve(std::vector<word> window, int current)
{
	int size = window.size();

	//if there left 1 item and it's rule S, then we found it.
	if (size == 1)
	{
		if (window[0].type == RULES::S) {
			return window[0].text;
		}
	}

	//right most pair
	if (current > 1) {
		RULES r1 = window[current - 1].type; //current item
		RULES r2 = window[current - 2].type; //current -1 item
		RULES result = find_rule(r2, r1); //check if there exists any rule with combination of those rules.

		if (result != RULES::NONE) 
		{
			//create a temp vector
			std::vector<word> temp;
			auto windowit = window.begin();
			//seek it to current - 1
			std::advance(windowit, current - 2);

			//Take begining of the first vector to temp vector
			temp.insert(temp.begin(), window.begin(), windowit);

			//create new data
			word wStar(window[current - 2].text + " " + window[current - 1].text, result);
			
			//insert it to back
			temp.push_back(wStar);

			//if there exists any data behind, then add them too.
			if (window.size() > current)
			{
				windowit = window.begin();
				std::advance(windowit, current);

				temp.insert(temp.end(), windowit, window.end());
			}

			//recrusive call that, decreases the vector and it is size
			std::string output = solve(temp, temp.size());
			if (!isThisError(output))
				return output;
		}
		//left shift, if there is no rule for those, then shift left and seek for new.
		std::string output2 = solve(window, current - 1); //current -1 means shift.
		if (!isThisError(output2))
			return output2;
	}

	return error; //if there is no probability left, then return error.
}

std::string Parser::extractParseTree(std::string sentence)
{
	std::stringstream ss(sentence);
	std::vector<std::string> words;
	std::vector<word> text;
	std::string output;

	//read each word
	while (ss >> output)
	{
		words.push_back(output);
	}

	auto it = words.begin();
	for (; it != words.end(); it++)
	{
		std::string temp(*it); //carry the word to temp string
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //make all characters to lowercase
		if (wordMap.find(temp) == wordMap.end())
		{
			return "Not found:" + *it; //in any case.
		}
		else
		{
			RULES rule = wordMap[temp];
			word w(*it, rule);
			text.push_back(w);
		}
	}

	std::string rest = solve(text, text.size());

	if (isThisError(rest))
		return error;
	else
		return rest;
}
