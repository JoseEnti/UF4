#pragma once
#include "pugixml.hpp"
#include <string>

struct Question
{
	int order;
	int amountOfAnswers;
	std::string text;
};

struct Answer
{
	int order;
	//int relatedQuestion;
	int points;
	std::string text;
};

struct AnswerPoints
{
	int pointsGained;
	int relatedQuestion;
};

class Generator
{
private:
	int questionsAmount;
	Question *allQuestions;

	int globalAnswersAmount;
	Answer *allAnswers;

	int totalpoints;
	AnswerPoints *pointsForQuestion;
};

