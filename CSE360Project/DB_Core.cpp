/*
 * DBCore.cpp
 *
 *  Created on: Mar 1, 2012
 *      Author: Ian
 */
#include "stdafx.h"
#include "DB_Core.h"

namespace CSE360Project {

DB_Core::DB_Core() {
	record_count = 0;
	lastID = 0;
}

int DB_Core::getLastID() {
	return lastID;
}

int DB_Core::getRecordCount() {
	return record_count;
}

DB_Core::~DB_Core() {
}

} /* namespace CSE360Project */