#pragma once
#include <string>
#include <vector>
#include "ClassDialogo.h"

class questions : ClassDialogo
{
public:
	std::string question;
	int questionId;
	std::vector <questions> questionVector;
};

