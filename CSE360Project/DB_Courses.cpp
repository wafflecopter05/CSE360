/*
* DBCourses.cpp
*
*  Created on: Mar 1, 2012
*      Author: Ian
*/
#include "stdafx.h"
#include "DB_Courses.h"
#include "timingClass.h"

namespace CSE360Project {

	DB_Courses::DB_Courses() {
		database_file = "Courses.db";

		//Open File
		this->Open(ios_base::in);

		//Load Data
		this->LoadData();

		//Close Data
		this->Close();
	}

	void DB_Courses::LoadData() {
		//variable declarations
		char input_char; //Will hold the character just read and being processed.
		int struct_position = 0; //Current struct position, will iterate upon reading DATA_COL_DELIM and reset to 0 on DATA_ROW_TERMINATE
		string in_int; //for reading in arbitrary lengthed numeric fields.
		bool new_row = true; //Flag new row to create new struct

		//Clear data in preparation for loading data.  If it's empty, will have no effect
		course_data.clear();

		//Open if not already open
		this->Open(ios_base::in);

		//Load last inserted id
		string lastID = "";
		while (in.good()) {
			input_char = in.get();

			//If terminate character is read we are done reading lastID
			if (input_char == DATA_ROW_TERMINATE)
				break;

			//If terminate character not read, we're still in last id.
			lastID += input_char;
		}

		if (!lastID.empty()) {
			//If last id is not empty, cast it to interger and save it!
			this->lastID = atoi(lastID.c_str());

			//Load Data
			//cid    uid	courseName
			//	0		1		2

			//cout << "Begin Courses Read" << endl; //removed, debug only.
			while (in.good()) {
				//if new row is flagged, create it.
				if (new_row) {
					//Create data row
					course_data.push_back(*(new db_course_data));

					//un flag it.
					new_row = false;

					//set struct_position to 0 to begin data entry into new data row
					struct_position = 0;

					//clear id strings for new row.
					in_int.erase();
				}

				input_char = in.get();
				if (in.good()) {
					if (input_char == DATA_COL_DELIM) {
						//Col delim found, move to next struct location.
						struct_position++;
					} else if (input_char == DATA_ROW_TERMINATE) {
						//set flag to true, the next line
						new_row = true;
					} else {
						switch (struct_position) {
						case 0:
							//add input_char to uid, cast to int to store.  if uid is partial it will replace itself until it's complete.
							in_int += input_char;
							course_data.back().cid = atoi(in_int.c_str());
							break;
						case 1:
							//add input_char to uid, cast to int to store.  if uid is partial it will replace itself until it's complete.
							in_int += input_char;
							course_data.back().uid = atoi(in_int.c_str());
							break;
						case 2:
							course_data.back().courseName += input_char;
							break;
						}
					}
				}
			}
		}

		//Close
		this->Close();
	}

	void DB_Courses::Write() {
		//Open file
		this->Open(ios_base::out);

		//Create timing class, and tic value.  Tic = start temporary timer variable.
		timingClass timing;
		timing.tic();

		//Write Data
		int data_array_size = (int) course_data.size();

		//Write last ID
		out << course_data.back().cid << DATA_ROW_TERMINATE;

		for (int i = 0; i < data_array_size; i++) {
			//This adds a termination to the end of the last data row.  This prevents 'ghost records' at the end of the file.
			if (i > 0)
				out << DATA_ROW_TERMINATE;

			out << course_data[i].cid << DATA_COL_DELIM; //Class ID - Autogenerated in this class.
			out << course_data[i].uid << DATA_COL_DELIM;
			out << course_data[i].courseName;
		}

		out.close();
		this->writeBenchmark(data_array_size,timing.toc());
	}

	void DB_Courses::Delete(int cid) {
		int vector_index = getVectorIndex(cid);

		if (vector_index >= 0)
			course_data.erase(course_data.begin()+vector_index);
	}
	

	void DB_Courses::DeleteUser(int uid) {
		for (int i = 0; i < (int) course_data.size(); i++) {
			if (course_data[i].uid == uid) {
				course_data.erase(course_data.begin()+i);
				i++;
			}
		}
	}

	int DB_Courses::Insert(db_course_data *course_data) {
		//Auto-assign UID
		course_data->cid = ++lastID;

		//We need to error check, if they are already a user, do nothing.
		this->course_data.push_back(*course_data);

		return 0;
	}

	int DB_Courses::getVectorIndex(int cid) {
		for (int i = 0; i < (int) course_data.size(); i++) {
			if (cid == course_data[i].cid) {
				return i;
			}
		}

		return -1;
	}

	void DB_Courses::outputAllCourses() {

		if (!course_data.empty()) {
			for (int i = 0; i < (int) course_data.size(); i++) {
				cout << i+1 << ") ";
				cout << "cid: " << course_data[i].cid << endl; //Course ID - Autogenerated in this class.
				cout << "uid: " << course_data[i].uid << endl;
				cout << "course name: " << course_data[i].courseName << endl;
				cout << endl << endl;
			}
		} else {
			cout << "Course Data is empty." << endl;
		}
	}

	DB_Courses::~DB_Courses() {
		course_data.clear();
	}

} /* namespace CSE360Project */