/*
* DBCourses.cpp
*
*  Created on: Mar 1, 2012
*      Author: Ian
*/
#include "stdafx.h"
#include "DB_Scores.h"
#include "timingClass.h"

namespace CSE360Project {

	DB_Scores::DB_Scores() {
		database_file = "Scores.db";
		database_info_file = database_file+".info";

		//Load Data
		this->LoadData<db_score_data>(score_data);
	}

	void DB_Scores::DeleteScore(int sid) {
		int vector_index = getVectorIndex(sid);

		if (vector_index >= 0)
			score_data.erase(score_data.begin()+vector_index);

		this->Write();
	}

	void DB_Scores::DeleteQuiz(int qid) {
		for (int i = 0; i < (int) score_data.size(); i++) {
			if (score_data[i].qid == qid) {
				score_data.erase(score_data.begin()+i);
				i++;
			}
		}

		this->Write();
	}

	void DB_Scores::DeleteUser(int uid) {
		for (int i = 0; i < (int) score_data.size(); i++) {
			if (score_data[i].uid == uid) {
				score_data.erase(score_data.begin()+i);
				i++;
			}
		}

		this->Write();
	}

	void DB_Scores::DeleteCourse(int cid) {
		for (int i = 0; i < (int) score_data.size(); i++) {
			if (score_data[i].cid == cid) {
				score_data.erase(score_data.begin()+i);
				i++;
			}
		}

		this->Write();
	}


	int DB_Scores::Insert(vector<db_score_data> score_data) {
		for (int i = 0; i < score_data.size(); i++) {
			//Auto-assign UID
			score_data[i].sid = ++lastID;
			this->score_data.push_back(score_data[i]);
		}

		//Parameter lets the writ method know this is insertion.
		this->Write();
		
		return lastID;
	}

	vector<db_score_data> DB_Scores::getQuizScores(int sid) {
		vector<db_score_data> packaged_data;

		for (int i = 0; i < (int) score_data.size(); i++) {
			if (score_data[i].sid == sid) {
				packaged_data.push_back(score_data[i]);
			}
		}

		return packaged_data;
	}

	vector<db_score_data> DB_Scores::getUserScores(int uid) {
		vector<db_score_data> packaged_data;

		for (int i = 0; i < (int) score_data.size(); i++) {
			if (score_data[i].uid == uid) {
				packaged_data.push_back(score_data[i]);
			}
		}

		return packaged_data;
	}

	vector<db_score_data> DB_Scores::getClassScores(int cid) {
		vector<db_score_data> packaged_data;

		for (int i = 0; i < (int) score_data.size(); i++) {
			if (score_data[i].cid == cid) {
				packaged_data.push_back(score_data[i]);
			}
		}

		return packaged_data;
	}

	double DB_Scores::getUserQuizScore(int uid, int qid) {
		for (int i = 0; i < (int) score_data.size(); i++) {
			if (score_data[i].uid == uid && score_data[i].qid == qid) {
				return score_data[i].score;
			}
		}

		return 0.0;
	}

	void DB_Scores::outputAllData() {
		if (!score_data.empty()) {
			for (int i = 0; i < (int) score_data.size(); i++) {
				cout << i+1 << ") ";
				cout << "sid: " << score_data[i].sid << endl; //Course ID - Autogenerated in this class.
				cout << "uid: " << score_data[i].uid << endl;
				cout << "qid: " << score_data[i].qid << endl;
				cout << "cid: " << score_data[i].cid << endl;
				cout << "score: " << score_data[i].score << endl;
				cout << endl << endl;
			}
		} else {
			cout << "Scores Data is empty." << endl;
		}
	}

	int DB_Scores::getVectorIndex(int cid) {
		for (int i = 0; i < (int) score_data.size(); i++) {
			if (cid == score_data[i].cid) {
				return i;
			}
		}

		//Vector index of < 0 indicates failure to locate record.
		return -1;
	}

	void DB_Scores::Write() {
		this->WriteData<db_score_data>(score_data);	
	}

	void DB_Scores::ClearData() {
		score_data.clear();
	}

	DB_Scores::~DB_Scores() {
		this->ClearData();
	}
} /* namespace CSE360Project */