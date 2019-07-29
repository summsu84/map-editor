/*
 * DataValidator.h
 *
 *  Created on: 2013. 6. 3.
 *      Author: jiwon
 */

#ifndef DATAVALIDATOR_H_
#define DATAVALIDATOR_H_

#include <QString>

class DataValidator {
public:
	static DataValidator & getInstance()
	{
		if(pinstance == NULL){
			pinstance = new DataValidator;
		}

		return * pinstance;
	}
	DataValidator();
	virtual ~DataValidator();
	bool IsLatitude(const QString data);
	bool IsLongitude(const QString data);

private:
	static DataValidator * pinstance;
};

#endif /* DATAVALIDATOR_H_ */
