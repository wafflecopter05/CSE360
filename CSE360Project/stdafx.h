// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

#include <ctime>
#include <limits>
#include <fstream>
#include <string>

using namespace std;


namespace CSE360Project {

// TODO: reference additional headers your program requires here

//User Roles
typedef enum user_roles {
	student = 0,
	teacher = 1,
	admin = 999
} user_roles_t;

//Database Structures
//Users
struct db_users_data {
	int uid;
	string username;
	string password;
	string lastName;
	string firstName;
	string securityQuestion;
	string securityAnswer;
	user_roles_t userRole;
};

//Courses

//Enrolled

//Quizzes

//Quiz Questions

//Answered

//Scores

}