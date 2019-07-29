/*
 * ConvertPoint.cpp
 *
 *  Created on: 2009. 11. 2.
 *      Author: root
 */
#include <QtGui>
#include "ConvertPoint.h"

ConvertPoint::ConvertPoint() {
	// TODO Auto-generated constructor stub

}

ConvertPoint::~ConvertPoint() {
	// TODO Auto-generated destructor stub
}
/**
 * N00:00:00.00 data validation check
 */
void ConvertPoint::validatorLatitude(QWidget * obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit *> (obj);
	int current = edit->cursorPosition();
	QChar ch1;
	QChar ch2;
	QString chk;
	qDebug() << "text function call...cursor : " << current <<"text : "<<edit->text();
	switch(current) {
	case 1:
			if (edit->displayText().at(0).toUpper() != 'N' && edit->displayText().at(0).toUpper() != 'S') {
				edit->setText(edit->displayText().replace(0, 1, "_"));
				edit->setCursorPosition(0);
			}else {
				edit->setText(edit->displayText().toUpper());
				edit->setCursorPosition(1);
			}
		break;
	case 2:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		if (edit->displayText().at(1) == '9' && edit->displayText().at(2) != '0' && edit->displayText().at(2) != '_') {
			edit->setText(edit->displayText().replace(1, 1, "_"));
			edit->setCursorPosition(1);
		}
		break;
	}
	case 4:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
			break;
		}
		ch1 = edit->displayText().at(1);
		ch2 = edit->displayText().at(2);
		if (ch1 == '9' && ch2 != '0') {
			edit->setText(edit->displayText().replace(2, 1, "_"));
			edit->setCursorPosition(2);
		}
		break;
	}
	case 5:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
			break;
		}
		ch1 = edit->displayText().at(4);
		if (ch1 >='0' && ch1 <= '5') {
			// success..
		}else {
			edit->setText(edit->displayText().replace(4,1,"_"));
			edit->setCursorPosition(4);
		}
		break;
	}
	case 7:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		break;
	}
	case 8:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
			break;
		}
		ch1 = edit->displayText().at(7);
		if (ch1 >='0' && ch1 <= '5') {
			// success..
		}else {
			edit->setText(edit->displayText().replace(7,1,"_"));
			edit->setCursorPosition(7);
		}
		break;
	}
	case 10:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		break;
	}
	case 11:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		break;
	}
	case 12:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		break;
	}
	default:
		break;
	}
}

/**
 * 00:00:00.00 data validation check
 */
void ConvertPoint::validatorLatLon(QWidget * obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit *> (obj);
	int current = edit->cursorPosition();
	QChar ch1;
	QChar ch2;
	QString chk;
	qDebug() << "text function call...cursor : " << current;
	switch(current) {
	case 1:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		if (edit->displayText().at(1) == '9' && edit->displayText().at(1) != '0' && edit->displayText().at(0) != '_') {
			edit->setText(edit->displayText().replace(0, 1, "_"));
			edit->setCursorPosition(0);
		}
		break;
	}
	case 3:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
			break;
		}
		ch1 = edit->displayText().at(0);
		ch2 = edit->displayText().at(1);
		if (ch1 == '9' && ch2 != '0') {
			edit->setText(edit->displayText().replace(1, 1, "_"));
			edit->setCursorPosition(1);
		}
		break;
	}
	case 4:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
			break;
		}
		ch1 = edit->displayText().at(3);
		if (ch1 >='0' && ch1 <= '5') {
			// success..
		}else {
			edit->setText(edit->displayText().replace(3,1,"_"));
			edit->setCursorPosition(3);
		}
		break;
	}
	case 6:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		break;
	}
	case 7:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
			break;
		}
		ch1 = edit->displayText().at(6);
		if (ch1 >='0' && ch1 <= '5') {
			// success..
		}else {
			edit->setText(edit->displayText().replace(6,1,"_"));
			edit->setCursorPosition(6);
		}
		break;
	}
	case 9:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		break;
	}
	case 10:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		break;
	}
	case 11:
	{
		int idx = validatorLatitudeCheck(edit, current);
		if (idx != -1) {
			edit->setCursorPosition(idx);
		}
		break;
	}
	default:
		break;
	}
}
void ConvertPoint::validatorFacility(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit *> (obj);
	int current = edit->cursorPosition();

	QString data = edit->text();

	if (data.at(0) != '-')
	{
		if (data.length() == 5)
		{
			data = data.mid(0, 4);
			edit->setText(data);
		}
	}
}
/**
 * 00.00.00 data validation check
 */
void ConvertPoint::validatorDate(QWidget * obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit *> (obj);
	int current = edit->cursorPosition();
	QChar ch1;
	QChar ch2;
	QString chk;
	qDebug() << "text function call...cursor : " << current;
	switch(current) {
	case 4:
	{
		ch1 = edit->displayText().at(current-1);
		if (ch1 == '0' || ch1 == '1') {
			// success
		}else {
			edit->setText(edit->displayText().replace(current-1, 1, "_"));
			edit->setCursorPosition(current-1);
		}
		break;
	}
	case 6:
	{
		ch1 = edit->displayText().at(3);
		ch2 = edit->displayText().at(4);
		if (ch1 =='0') {
			// success..
		}else {
			if (ch2 == '1' || ch2 == '2') {
				// success
			}else {
				edit->setText(edit->displayText().replace(4,1,"_"));
				edit->setCursorPosition(4);
			}
		}
		break;
	}
	case 7:
	{
		ch1 = edit->displayText().at(6);
		if (ch1 == '0' || ch1 == '1' || ch1 == '2' || ch1 == '3') {
			// success
		}else {
			edit->setText(edit->displayText().replace(6,1,"_"));
			edit->setCursorPosition(6);
		}
		break;
	}
	case 8:
	{
		ch1 = edit->displayText().at(6);
		ch2 = edit->displayText().at(7);
		if (ch1 == '0' || ch1 == '1' || ch1 == '2') {
			// success..
		}else {
			if (ch2 == '0' || ch2 == '1') {
				// success
			}else {
				edit->setText(edit->displayText().replace(7,1,"_"));
				edit->setCursorPosition(7);
			}
		}
		break;
	}
	default:
		break;
	}
}
/**
 * Bearing format validation : 000.0 [ max : 359.9 ]
 */
void ConvertPoint::validatorBearing(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);

	int current = edit->cursorPosition();
	QChar ch1;
	QChar ch2;
	qDebug() << "validatorBearing functioni call.. cursor : " << current;
	switch(current) {
		case 1:
		{
			setBearingFormat(edit, current, '0');
			if (edit->displayText().at(0) >= '0' && edit->displayText().at(0) <= '3') {
				edit->setCursorPosition(1);
			}else {
				edit->setText(edit->displayText().replace(0, 1, "_"));
				edit->setCursorPosition(0);
			}
			break;
		}
		case 2:
		{
			setBearingFormat(edit, current, '0');

			if (edit->displayText().at(0) == '3' && edit->displayText().at(1) >= '0' && edit->displayText().at(1) <= '5') {
				edit->setCursorPosition(2);
			}else if(edit->displayText().at(0) != '3' && edit->displayText().at(1) >= '0' && edit->displayText().at(1) <= '9') {
				edit->setCursorPosition(2);
			}else {
				edit->setText(edit->displayText().replace(1, 1, "_"));
				edit->setCursorPosition(1);
			}
			break;
		}
		case 3:
		{
			setBearingFormat(edit, current, '0');
			if (edit->displayText().at(2) >= '0' && edit->displayText().at(2) <= '9') {
				edit->setCursorPosition(3);
			}else {
				edit->setText(edit->displayText().replace(2, 1, "_"));
				edit->setCursorPosition(2);
			}
			break;
		}
		case 5:
		{
			setBearingFormat(edit, current, '0');
			break;
		}
		default:
			break;
	}
}
/**
 * Ellipsoid Height data validator
 * format : (+,-)0000.0
 */
void ConvertPoint::validatorEllipsoid(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	QChar ch1;
	QChar ch2;
	int current = edit->cursorPosition();
	switch(current) {
		case 1:
		{
			if (edit->displayText().at(0) == '+' || edit->displayText().at(0) == '-') {
				edit->setCursorPosition(1);
			}else {
				edit->setText(edit->displayText().replace(0, 1, "_"));
				edit->setCursorPosition(0);
			}
			break;
		}
		default: break;
	}
}
/**
 * Ellipsoid Height 입력 필드를 벗어 났을 때 데이터를 검증해서 채워 넣는다.
 */
void ConvertPoint::validatorEllipsoidEnd(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);

	if (edit->text().length() > 2) {
		int len = edit->displayText().length();
		QString str = "";
		for (int i=0; i<len; i++) {
			QChar ch = edit->displayText().at(i);

			if (i == 0) {
				if (ch == '+' || ch == '-') {
					str += ch;
				}else {
					str += "+";
				}
			}else {
				if (ch == '_') {
					str += "0";
				}else {
					str += ch;
				}
			}
		}
		edit->setText(str);
	}
}
void ConvertPoint::validatorDotEnd(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	qDebug()<<"Validator Dot End is called.. Text : "<<edit->text();
	QString str = "";
	if (edit->text().length() > 1) {
		QString data = edit->displayText();
		for (int i=0; i<data.length(); i++) {
			if (data.at(i) == '_') {
				str += '0';
			}else {
				str += data.at(i);
			}
		}
		edit->setText(str);
	}
}
/**
 * Gradient 데이터 검증
 * 첫번째 문자에 대해서는 +, -만 입력하게 한다.
 * format : (+)(-)9.000
 */
void ConvertPoint::validatorGradient(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	QChar ch1;
	QChar ch2;
	int current = edit->cursorPosition();
	switch(current) {
		case 1:
		{
			if (edit->displayText().at(0) == '+' || edit->displayText().at(0) == '-') {
				edit->setCursorPosition(1);
			}else {
				edit->setText(edit->displayText().replace(0, 1, "_"));
				edit->setCursorPosition(0);
			}
			break;
		}
		case 2:   // .
		{
			break;
		}
		case 3:
		{
			setGradientFormat(edit, current, '0');
			ch1 = edit->displayText().at(1);
			if (ch1 == '9') {
				edit->setText(edit->displayText().mid(0,1)+"9000");
				edit->setCursorPosition(3);
			}
			break;
		}
		case 4:
		{
			setGradientFormat(edit, current, '0');
			ch1 = edit->displayText().at(1);
			ch2 = edit->displayText().at(3);
			if (ch1 == '9' && ch2 != '0') {
				edit->setText(edit->displayText().replace(3, 1, "_"));
				edit->setCursorPosition(3);
			}else {
				edit->setCursorPosition(4);
			}
			break;
		}
		case 5:
		{
			setGradientFormat(edit, current, '0');
			ch1 = edit->displayText().at(1);
			ch2 = edit->displayText().at(4);
			if (ch1 == '9' && ch2 != '0') {
				edit->setText(edit->displayText().replace(4, 1, "_"));
				edit->setCursorPosition(4);
			}else {
				edit->setCursorPosition(5);
			}
			break;
		}
		case 6:
		{
			setGradientFormat(edit, current, '0');
			ch1 = edit->displayText().at(1);
			ch2 = edit->displayText().at(5);
			if (ch1 == '9' && ch2 != '0') {
				edit->setText(edit->displayText().replace(5, 1, "_"));
				edit->setCursorPosition(5);
			}else {
				edit->setCursorPosition(6);
			}
		}
		default: break;
	}
}
/**
 * Bearing 데이터 검증 체크
 * format : 0~359
 */
void ConvertPoint::validatorBearingTrue(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);

	int current = edit->cursorPosition();
	QChar ch1;
	QChar ch2;
	qDebug() << "validatorBearingTrue functioni call.. cursor : " << current;
	switch(current) {
		case 1:
		{
			setBearingFormat(edit, current, '0');
			if (edit->displayText().at(0) >= '0' && edit->displayText().at(0) <= '3') {
				edit->setCursorPosition(1);
			}else {
				edit->setText(edit->displayText().replace(0, 1, "_"));
				edit->setCursorPosition(0);
			}
			break;
		}
		case 2:
		{
			setBearingFormat(edit, current, '0');
			if (edit->displayText().at(1) >= '0' && edit->displayText().at(1) <= '5') {
				edit->setCursorPosition(2);
			}else {
				edit->setText(edit->displayText().replace(1, 1, "_"));
				edit->setCursorPosition(1);
			}
			break;
		}
		case 3:
		{
			setBearingFormat(edit, current, '0');
			if (edit->displayText().at(2) >= '0' && edit->displayText().at(2) <= '9') {
				edit->setCursorPosition(3);
			}else {
				edit->setText(edit->displayText().replace(2, 1, "_"));
				edit->setCursorPosition(2);
			}
			break;
		}
		default:
			break;
	}
}
/**
 * N000:00:00.00 data validation check
 */
void ConvertPoint::validatorLongitude(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);

	int current = edit->cursorPosition();
	QChar ch1;
	QChar ch2;
	qDebug() << "text function call...cursor : " << current;
	switch(current) {
		case 1:
		{
			if (edit->displayText().at(0).toUpper() != 'E' && edit->displayText().at(0).toUpper() != 'W') {
				edit->setText(edit->displayText().replace(0, 1, "_"));
				edit->setCursorPosition(0);
			}else {
				edit->setText(edit->displayText().toUpper());
				edit->setCursorPosition(1);
			}
			break;
		}
		case 2:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
				break;
			}
			ch1 = edit->displayText().at(1);
			if (ch1 == '0' || ch1 == '1') {
				// success
			}else {
				edit->setText(edit->displayText().replace(1,1,"_"));
				edit->setCursorPosition(1);
			}
			break;
		}
		case 3:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
				break;
			}
			ch1 = edit->displayText().at(1);
			ch2 = edit->displayText().at(2);
			if (ch1 == '1' && ch2 > '7') {
				edit->setText(edit->displayText().replace(2,1,"_"));
				edit->setCursorPosition(2);
			}
			break;
		}
		case 5:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
			}
			break;
		}
		case 6:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
				break;
			}
			ch1 = edit->displayText().at(5);
			if (ch1 >='0' && ch1 <= '5') {
				// success..
			}else {
				edit->setText(edit->displayText().replace(5,1,"_"));
				edit->setCursorPosition(5);
			}
			break;
		}
		case 8:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
			}
			break;
		}
		case 9:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
				break;
			}
			ch1 = edit->displayText().at(8);
			if (ch1 >='0' && ch1 <= '5') {
				// success..
			}else {
				edit->setText(edit->displayText().replace(8,1,"_"));
				edit->setCursorPosition(8);
			}
			break;
		}
		case 10:
			break;
		case 11:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
			}
			break;
		}
		case 12:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
			}
			break;
		}
		case 13:
		{
			int idx = validatorLatitudeCheck(edit, current);
			if (idx != -1) {
				edit->setCursorPosition(idx);
			}
			break;
		}
		default:
			break;
	}
}

int ConvertPoint::validatorLatitudeCheck(QWidget *obj, int currentIndex)
{
	// 형식 : A000:00:00.00
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	QString data = edit->displayText();
	int index = -1;
	for (int i=0; i<currentIndex; i++) {
		if (data.at(i) == '_') {
			index = i;
			break;
		}
	}
	if (index != -1) {
		for (int i=currentIndex-1; i>=index; i--) {
			edit->setText(edit->displayText().replace(i, 1, "_"));
		}
	}
	return index;
}

void ConvertPoint::setBearingFormat(QWidget *obj, int index, QChar format)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	QString data = edit->displayText();
	for (int i=0; i<index; i++) {
		if (data.at(i) == '_') {
			edit->setText(edit->displayText().replace(i, 1, format));
		}
	}

}
void ConvertPoint::setBearingTrueFormat(QWidget *obj, int index, QChar format)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	QString data = edit->displayText();
	for (int i=0; i<index; i++) {
		if (data.at(i) == '_') {
			edit->setText(edit->displayText().replace(i, 1, format));
		}
	}

}
/**
 * Edit Box 가 편집을 끝냈을 때 입력 데이터 외의 데이터에 대해서
 * 0으로 세팅한다.
 * InpubMask 가 있을 때 : 빈칸에 0을 넣는다.
 */
void ConvertPoint::validatorBearingEnd(QWidget *obj)
{
	qDebug()<<"ConverPoint is called..";
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	QString data = edit->text().replace(".", "");
	if (data.length() > 0) {
		for (int i=0; i<edit->displayText().length(); i++) {
			if (edit->displayText().at(i) == '_') {
				edit->setText(edit->displayText().replace(i, 1, '0'));
			}
		}
	}
}
/**
 * Edit Box 가 편집을 끝냈을 때 입력 데이터 외의 데이터에 대해서
 * 0으로 세팅한다.때
 * InputMask 가 없을 때 : 뒤에 0을 붙인다.
 */
void ConvertPoint::validatorBearingTrueEnd(QWidget *obj)
{
	qDebug() << "validatorBearingTrueEnd call...";
	//test
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	qDebug()<<"Text : "<<edit->text();
	int max = 3;
	QString data = edit->text();
	if (data.length() > 0) {
		QString format = "";
		for (int i=0; i<max-data.length(); i++) {
			format += "0";
		}
		edit->setText(data+format);
	}
}
/**
 * Gradient 데이터 format에 대해서 입력되지 않은 값은 0으로 세팅한다.
 */
void ConvertPoint::setGradientFormat(QWidget *obj, int index, QChar format)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	QString data = edit->displayText();
	for (int i=1; i<index; i++) {
		if (data.at(i) == '_') {
			edit->setText(edit->displayText().replace(i, 1, format));
		}else {
			break;
		}
	}
}
/**
 * Gradient 입력 한 데이터에 대해서 빈값은 0으로 채운다.
 */
void ConvertPoint::validatorGradientEnd(QWidget *obj)
{
	QLineEdit *edit = qobject_cast<QLineEdit*>(obj);
	if (edit->text().length() > 2) {
		int len = edit->displayText().length();
		QString str = "";
		for (int i=0; i<len; i++) {
			QChar ch = edit->displayText().at(i);

			if (i == 0) {
				if (ch == '+' || ch == '-') {
					str += ch;
				}else {
					str += "+";
				}
			}else {
				if (ch == '_') {
					str += "0";
				}else {
					str += ch;
				}
			}
		}
		edit->setText(str);
	}
}
