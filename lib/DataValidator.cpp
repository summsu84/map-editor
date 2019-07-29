/*
 * DataValidator.cpp
 *
 *  Created on: 2013. 6. 3.
 *      Author: jiwon
 */

#include "DataValidator.h"
DataValidator * DataValidator::pinstance = NULL;
DataValidator::DataValidator() {
	// TODO Auto-generated constructor stub

}

DataValidator::~DataValidator() {
	// TODO Auto-generated destructor stub
}



/**
 * Latitude 데이터가 올바른지 확인한다.
 * 빈문자열에 대해서는 검증하지 않고 true를 리턴한다.
 * 입력데이터 형식이 format으로 설정되어 있어 해당 데이터를 제거하고 올바른지 확인해야 한다.
 * format :=> A00:00:00.00
 */
bool DataValidator::IsLatitude(const QString data)
{
	bool found;
	QString d = data;
	d.replace(":", "");
	d.replace(".", "");

	if (d.trimmed().length() == 0) {
		return true;
	}else if(d.length() == 9) {
		return true;
	}else {
		return false;
	}
}
/**
 * Longitude 데이터가 올바른지 확인한다.
 * 빈문자열에 대해서는 검증하기 않고 true를 리턴한다.
 * 입력데이터 형식이 format으로 설정되어 있어 해당 데이터를 제거하고 올바른지 확인해야 한다.
 *  format :=> A000:00:00.00
 */
bool DataValidator::IsLongitude(const QString data)
{
	bool found;
	QString d = data;
	d.replace(":", "");
	d.replace(".", "");

	if (d.trimmed().length() == 0) {
		return true;
	}else if(d.length() == 10) {
		return true;
	}else {
		return false;
	}
}
