// Created by David Newton

// Quiz.h is the header file for the Quiz.cpp file, which will is used to hold information on a specific quiz

// File created on 4 April 2012.


#include "stdafx.h"
#include "core_header.h"
#include "Quiz.h"


using namespace std;

namespace CSE360Project{

		Quiz::Quiz(){
			this->quizID = -1;
			timeLimit = -1;//initialize variables
			openDate  = -1;
			closeDate = -1;
		}
		//overloaded constructor #1 for taking a quiz sequence - pass it a quID and it will initialize its variables with all the data on a specific quiz 
		Quiz::Quiz(int quizID){
			this->quizID = quizID;
			db_quiz_data quizData = db->quizzes->getQuizData(quizID);//get info on quiz from quiz DB
			timeLimit = quizData.timeLimit;//initialize variables
			openDate  = quizData.openDate;
			closeDate = quizData.closeDate;
		}

		void Quiz::setOpenDate(time_t openDate){
			this->openDate = openDate;
		}

		time_t Quiz::getOpenDate(){		
			return openDate;
		}

		void Quiz::setCloseDate(time_t closeDate){
			this->closeDate = closeDate;
		}

		time_t Quiz::getCloseDate(){
			return closeDate;
		}

		void Quiz::setTimeLimit(int timeLimit){
			this->timeLimit = timeLimit;
		}

		int Quiz::getTimeLimit(){
			return timeLimit;
		}

		void Quiz::setQuestions(vector<string> questions){

			for(int i = 0; i<questions.size(); i++){

				db_question_data newQuestion; 
				WriteStructValue(newQuestion.question,questions[i],true);//add question to new db_question struct
				newQuestion.order = i;//set question order / #
				questionData.push_back(newQuestion);//add question struct to vector of questions
			}

		}

		vector<db_question_data> Quiz::getQuestions(){
			questionData = db->quizquestions->getQuestions(quizID);
			return questionData;
		}

		void Quiz::setAnswers(vector<string> answers){
			
			int count=0;

			for(int i = 0; i<questionData.size(); i++){
					
				for(int j = 0; j<5; j++){
					if(j==0)
					WriteStructValue(questionData[i].answer1,answers[count],false);	
					if(j==1)
					WriteStructValue(questionData[i].answer2,answers[count],false);
					if(j==2)
					WriteStructValue(questionData[i].answer3,answers[count],false);
					if(j==3)
					WriteStructValue(questionData[i].answer4,answers[count],false);
					if(j==4)
					questionData[i].correct_answer=atoi(answers[count].c_str());//save the correct answer, convert it to an int from a string and save 
					count++;
				}
			}
		}

		string* Quiz::getAnswers(){

			string placeholder = "test";
			string* test = &placeholder;
			return test;
		}

		bool Quiz::submitAnswers(int quizID, int answerData [], int uid){

			vector<db_answered_data> answered_data;
			for(int i = 0; i<questionData.size(); i++){//use size of question vector to step through answer array
				db_answered_data newAnswer;
				newAnswer.uid = uid;
				newAnswer.qid = quizID;
				newAnswer.question_id = questionData[i].question_id;
				newAnswer.answer = answerData[i];
				answered_data.push_back(newAnswer);//add question struct to vector of questions
			}
			db->answered->Insert(answered_data);
			return 1;
		}

		void Quiz::addQuestion(string question){
		}
		
		bool Quiz::saveQuiz(int cid){

			db_quiz_data* quizDataPtr;
			db_quiz_data quizData;
			quizDataPtr = &quizData;
			quizData.cid = cid;//initialize quiData struct
			quizData.openDate = openDate;//initialize quiData struct
			quizData.closeDate = closeDate;//initialize quiData struct
			quizData.timeLimit = timeLimit;//initialize quiData struct
			quizID = db->quizzes->Insert(quizDataPtr);//send to quizzes database and return the generated qid

			for(int i = 0; i<questionData.size(); i++)//initialize quiz ID for each question data struct in the vector array
				questionData[i].qid = quizID;

			db->quizquestions->Insert(questionData);//send vector of quizquestion structs to quizquestions db for storage.


			return 1;
		}

		void Quiz::gradeQuiz(){
		}
}