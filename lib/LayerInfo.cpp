/*
 * LayerInfo.cpp
 *
 *  Created on: 2013. 5. 15.
 *      Author: jiwon
 */

#include "LayerInfo.h"
#include <QDebug>

LayerInfo::LayerInfo() {
	// TODO Auto-generated constructor stub

}


LayerInfo::~LayerInfo() {
	// TODO Auto-generated destructor stub
}

Qt::BrushStyle LayerInfo::getBrushStyle()
{
	Qt::BrushStyle brushStyle;

	switch(layer_fille_pattern){

		case SOLID_F :
			brushStyle = Qt::SolidPattern;
			break;
		case DOTTED_F :
			brushStyle = Qt::Dense1Pattern;
			break;
		case HORIZONTALLINE:
			brushStyle = Qt::HorPattern;
			break;
		case VERTICALLINE:
			brushStyle = Qt::VerPattern;
			break;
		case CROSSLINE :
			brushStyle = Qt::CrossPattern;
			break;
		case SLASHED :
			brushStyle = Qt::BDiagPattern;
			break;
		case REVERSESLASHED:
			brushStyle = Qt::FDiagPattern;
			break;
		case CROSSSLASHED :
			brushStyle = Qt::DiagCrossPattern;
			break;
		default:
			brushStyle = Qt::NoBrush;
			break;
	}

	return brushStyle;
}

/*
 * 펜 스타일을 반환한다..
 */

Qt::PenStyle LayerInfo::getPenStyle()
{

	Qt::PenStyle penStyle;

	switch(layer_line_type){

		case Blank :
			penStyle = Qt::NoPen;
			break;
		case Solid :
			penStyle = Qt::SolidLine;
			break;
		case Dashed :
			penStyle = Qt::DashLine;
			break;
		case Dotted :
			penStyle = Qt::DotLine;
			break;
		default :
			penStyle = Qt::NoPen;
			break;
	}

	//qDebug()<<"Pen Style : "<<penStyle;
	return penStyle;
}
