//@author   Alim Ozdemir 150140807
//@date     23.04.2017
//@desc
#include <string>
#include "rules.h"

class word {
public:
	word()
	{
	}

	word(std::string _text, RULES rule)
	{
		if(rule >= 0 && rule <= 4) //first rules
			text = RS[rule] + "("+_text + ")";
		else
			text = RS[rule] + "[" + _text + "]";

		type = rule;
	}
	
	std::string text;
	RULES type;
};