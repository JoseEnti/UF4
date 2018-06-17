#pragma once
#include "pugixml.hpp"
#include "questions.h"
#include "ClassDialogo.h"
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <future>

#define _MAX_SECONDS_TO_SKIP 5
typedef const pugi::char_t* pugiCharArray;

int input = 0;
bool shouldEnd = false;
bool gameShouldClose = false;
bool answer = false;

std::vector <ClassDialogo> LoadQuestionary(std::string path, questions &question1);
void time(int seconds);

void thread_function()
{
	while (!gameShouldClose)
	{
		if (answer)
		{
			std::cin >> input;
			shouldEnd = true;	
		}
	}
}

int main()
{
	int index = 0;
	int score = 0;
		
	questions questions;
	std::string dialogo = "questionario.xml";

	std::cout << "Bienvenido jugador, pulse cualquier tecla para comenzar el questionario." << std::endl << "Solo tendras 5 segundos por pregunta, piensa rapido!" << std::endl << std::endl;
	system("pause");
		
	std::vector <ClassDialogo> questionario = LoadQuestionary(dialogo, questions);
	
	for (int i = 0; i < (int)questions.questionVector.size(); i++)
	{
		std::cout << questions.questionVector[i].question << std::endl << "1.- " << questionario[index].answers << std::endl << "2.- " << questionario[index+1].answers << std::endl << "3.- " << questionario[index+2].answers << std::endl;
		std::thread t(thread_function);
		index += 3;

		answer = true;
		time(_MAX_SECONDS_TO_SKIP);
		answer = false;
		t.join();
	}
	return 0;
}

void time(int seconds)
{
	std::clock_t init;
	double time;

	init = std::clock();
	do 
	{
		time = (std::clock() - init) / (double)CLOCKS_PER_SEC;

	} while (time < seconds && !shouldEnd);
}

std::vector <ClassDialogo> LoadQuestionary(std::string path, questions &question1)
{
	ClassDialogo d;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path.c_str());

	pugi::xml_node nodoQuestionario = doc.child("questionario");
	pugi::xml_node nodoQuestion = nodoQuestionario.child("pregunta");

	for (nodoQuestion; nodoQuestion; nodoQuestion = nodoQuestion.next_sibling("pregunta"))
	{
		pugiCharArray question = nodoQuestion.attribute("frase").value();
		pugiCharArray idQuestion = nodoQuestion.attribute("grupo").value();

		question1.question = std::string(question);
		question1.questionId = stoi(std::string(idQuestion));
		question1.questionVector.push_back(question1);
		
		for (pugi::xml_node nodoAnswer = nodoQuestion.child("respuestas").child("respuesta"); nodoAnswer; nodoAnswer = nodoAnswer.next_sibling("respuesta"))
		{
			pugiCharArray playerAnswer = nodoAnswer.attribute("respuestaJugador").value();
			pugiCharArray answerId = nodoAnswer.attribute("id_pregunta").value();
			pugiCharArray scoreAnswer = nodoAnswer.attribute("puntos").value();

			d.answerId = stoi(std::string(answerId));
			d.score = stoi(std::string(scoreAnswer));
			d.answers = std::string(playerAnswer);

			d.dialogueVector.push_back(d);
		}
	}
	return d.dialogueVector;
}