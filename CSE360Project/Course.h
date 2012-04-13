
// Created by David Newton

// Quiz.h is the header file for the Quiz.cpp file, which will is used to hold information on a specific quiz

// File created on 5 April 2012.

#pragma once
#include "stdafx.h"
#include "core_header.h"

using namespace std;

namespace CSE360Project {
	class Course {
	public:
		Course();
		Course(int courseID); // Overloaded constructor for creating local object from DB_Courses
		void setName(string courseName);
		string getName();
		void setStudents(int studentIDList[]);
		string getStudents();
		vector<db_quiz_data> getQuizList();
		// Quiz getQuiz();
		vector<double> getGrades();
		//Quiz creatQuiz();
		void deleteQuiz();
		void deleteStudents();
		int addCourseData(int userID, string courseName);

	protected:
		int courseID;
		string courseName;
		vector<db_quiz_data> quizList;

	};
}