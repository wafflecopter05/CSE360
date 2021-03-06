// Created by David Newton

// Quiz.h is the header file for the Quiz.cpp file, which will is used to hold information on a specific quiz

// File created on 4 April 2012.

#pragma once
#include "stdafx.h"
#include "core_header.h"


using namespace std;

namespace CSE360Project {

	class Quiz {
	public:
		
		Quiz(int cid);
		Quiz(int quizID,int uid, int cid);
		void setOpenDate(time_t openDate);
		time_t getOpenDate();
		void setCloseDate(time_t closeDate);
		time_t getCloseDate();
		void setTimeLimit(int timeLimit);
		int getTimeLimit();
		void setQuestions(vector<string> questions); 
		vector<db_question_data> getQuestions();
		void setAnswers(vector<string> answers);
		vector<db_answered_data> getAnswers();
		bool submitAnswers(int answerData []);
		void addQuestion(string question);
		bool saveQuiz();

	public:
		int quizID, uid, cid;
		vector<db_question_data> questionData;
		int timeLimit;
		time_t openDate;
		time_t closeDate;

		db_score_data* gradeQuiz(vector<db_answered_data> answered_data);

			}; //  end User class
}