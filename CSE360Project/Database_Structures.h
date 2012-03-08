#pragma once
#include <string.h>

#define DATA_COL_DELIM '\t'
#define DATA_ROW_TERMINATE '\n'

//User Roles
enum user_roles_t {
	student = 0,
	teacher = 1,
	admin = 99
} ;

//Users
/*
username password lastName firstName securityQuestion securityAnswer userRole
*/
struct db_users_data {
	int uid; //User ID - Autogenerated in this class.
	std::string username;
	std::string password;
	std::string lastName;
	std::string firstName;
	std::string securityQuestion;
	std::string securityAnswer;
	user_roles_t userRole;
};

//Courses
struct db_courses_data {
	int cid; //Course ID - Autogenerated in this class.
	int uid;
	std::string courseName;
};

//Enrolled
struct db_enrolled_data {
	int eid; //Enrolled ID - Autogenerated in this class.
	int uid;
	int cid;
}; 

//Quizzes
struct db_quizzes_data {
	int qid; //Quiz ID - Autogenerated in this class.
	int cid;

};

//Quiz Questions
struct db_questions_data {
};

//Answered
struct db_answered_data {
};

//Scores
struct db_scores_data {
};