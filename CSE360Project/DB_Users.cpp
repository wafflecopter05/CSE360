/*
* DBUsers.cpp
*
*  Created on: Mar 1, 2012
*      Author: Ian
*/
#include "stdafx.h"
#include "DB_Users.h"
#include "timingClass.h"

namespace CSE360Project {

	DB_Users::DB_Users() {
		database_file = "Users.db";
		database_info_file = database_file+".info";

		//Load Data
		this->LoadData<db_users_data>(user_data);
	}

	void DB_Users::ClearData() {
		user_data.clear();
	}

	void DB_Users::Write() {
		this->WriteData<db_users_data>(user_data);
	}

	void DB_Users::Delete(int uid) {
		int vector_index = getVectorIndex(uid);

		if (vector_index >= 0)
			user_data.erase(user_data.begin()+vector_index);

		this->Write();
	}

	int DB_Users::Insert(db_users_data *user_data) {
		//Auto-assign UID
		user_data->uid = ++lastID;

		//We need to error check, if they are already a user, do nothing.
		this->user_data.push_back(*user_data);

		this->Write();

		return 0;
	}

	bool DB_Users::validateUser(string username, string password) {
		int vector_index = getVectorIndex(username);

		return (vector_index >= 0 && password.compare(user_data[vector_index].password) == 0);
	}

	bool DB_Users::checkSecurityAnswer(string username, string answer) {
		int vector_index = getVectorIndex(username);

		return (vector_index >= 0 && answer.compare(user_data[vector_index].securityAnswer) == 0);
	}

	user_roles_t DB_Users::getUserRole(int uid) {
		return user_data[getVectorIndex(uid)].userRole;
	}

	string DB_Users::getUsername(int uid) {
		return user_data[ getVectorIndex(uid) ].username;
	}

	string DB_Users::getFirstname(int uid) {
		return user_data[ getVectorIndex(uid) ].firstName;
	}

	string DB_Users::getLastname(int uid) {
		return user_data[ getVectorIndex(uid) ].lastName;
	}

	string DB_Users::getSecurityQuestion(string username) {
		int vector_index = getVectorIndex(username);

		return (vector_index >= 0 ? user_data[ vector_index ].securityQuestion : "invalid");
	}

	int DB_Users::getUID(string username) {
		int vector_index = getVectorIndex(username);

		return (vector_index >= 0 ? user_data[vector_index].uid : 0);
	}

	int DB_Users::getVectorIndex(string username) {
		for (int i = 0; i < (int) user_data.size(); i++) {
			if (username.compare(user_data[i].username) == 0) {
				return i;
			}
		}

		return -1;
	}

	int DB_Users::getVectorIndex(int uid) {
		for (int i = 0; i < (int) user_data.size(); i++) {
			if (uid == user_data[i].uid) {
				return i;
			}
		}

		return -1;
	}

	void DB_Users::outputAllUsers() {
		if (!user_data.empty()) {
			for (int i = 0; i < (int) user_data.size(); i++) {
				cout << i+1 << ") ";
				cout << "uid: " << user_data[i].uid << endl; //User ID - Autogenerated in this class.
				cout << "username: " << user_data[i].username << endl;
				cout << "password: " << user_data[i].password << endl;
				cout << "lname: " << user_data[i].lastName << endl;
				cout << "fname: " << user_data[i].firstName << endl;
				cout << "question: " << user_data[i].securityQuestion << endl;
				cout << "answer: " << user_data[i].securityAnswer << endl;
				cout << "role: ";
				switch (user_data[i].userRole) {
				case admin:
					cout << "Admin";
					break;
				case teacher:
					cout << "Teacher";
					break;
				default:
					cout << "Student";
					break;
				}
				cout << endl << endl;
			}
		} else {
			cout << "User Data is empty." << endl;
		}
	}

	DB_Users::~DB_Users() {
		this->Write();

		this->ClearData();
	}

} /* namespace CSE360Project */