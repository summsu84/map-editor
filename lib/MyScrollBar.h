/*
 * MyScrollBar.h
 *
 *  Created on: 2013. 7. 17.
 *      Author: jiwon
 */


#ifndef MYSCROLLBAR_H_
#define MYSCROLLBAR_H_

#include <QScrollBar>
//#include <SliderChange>

class MyScrollBar : public QScrollBar
{
public:
	MyScrollBar();
	virtual ~MyScrollBar();

protected :
	void sliderChange(SliderChange change);

};

#endif /* MYSCROLLBAR_H_ */
