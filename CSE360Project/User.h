// Created by Stevie Robinson

// User.h is the header file for the User.cpp file, which will is used to hold a user's information locally during program use.
// It will also be integrated into the Teacher and Administrator classes, which inherit from User.

// File created on 3 April 2012.

#pragma once
#include "stdafx.h"
#include "Course.h"

using namespace std;

namespace CSE360Project {

	class User {
	public:
		User();
		User(int uID); // Used to initialize a user object from a retrieved uid on login.

		// Methods are straight from the Visio diagram.
		void setUserID(int uID);
		int getUserID();
		void setUsername(string username);
		string getUsername();
		void setPassword(string password);
		string getPassword();
		void setLastName(string lastName);
		string getLastName();
		void setFirstName(string firstName);
		string getFirstName();
		void setSecurityQ(string securityQ);
		string getSecurityQ();
		void setSecurityA(string securityA);
		string getSecurityA();
		void setUserRole(user_role_t userRole);
		user_role_t getUserRole();
		vector<db_enrolled_data> getEnrolledCourses(); // We need to check out this method; were we going to get rid of it?//I think we keep it so we can access the list of courses
		vector<db_course_data> getTaughtCourses();
		Course* getCourse(int courseID);
		//void addCourseID(int courseID);
		bool saveUser();
		//bool login(string username, string password);
		//void logout();

		//added teacher methods
		void deleteCourse(int cid);
		Course* createCourse(string courseName);

		virtual ~User();
	
	public:

		int userID;
		string username;
		string password;
		string lastName;
		string firstName;
		string securityQ;
		string securityA;
		user_role_t userRole; 
		vector<db_enrolled_data> enrolledCourses; 
		vector<db_course_data> taughtCourses;//for simplicity I'm combining the teacher and user objects for now
	}; // end User class

}