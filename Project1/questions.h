#pragma once
#include <string>
#include <vector>
#include "ClassDialogo.h"

class questions : ClassDialogo
{
public:
	questions();
	~questions();
	std::string question;
	int questionId;
	std::vector <questions> questionVector;
};

