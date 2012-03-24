#pragma once
#include "stdafx.h"
#include "DB_Core.h"


namespace CSE360Project {
	class DB_Scores: public CSE360Project::DB_Core {
	public:
		DB_Scores();

		///BEGIN PUBLIC METHODS THAT MODIFY DATA - "this->Write()" must be added before each method exits."
		void DeleteScore(int sid);
		void DeleteQuiz(int qid);
		void DeleteUser(int uid);
		void DeleteCourse(int cid);
		int Insert(vector<db_score_data> score_data);
		///END PUBLIC METHODS THAT MODIFY DATA

		vector<db_score_data> getQuizScores(int qid);
		vector<db_score_data> getUserScores(int uid);
		vector<db_score_data> getClassScores(int cid);
		double getUserQuizScore(int uid, int qid);

		//Debug functions
		void outputAllData();

		virtual ~DB_Scores();

	private:
		std::vector<db_score_data> score_data;

		int getVectorIndex(int sid);

		void Write();
		void ClearData();
	};

} /* namespace CSE360Project */