/*
 * LayerInfo.h
 *
 *  Created on: 2013. 5. 15.
 *      Author: jiwon
 */

#ifndef LAYERINFO_H_
#define LAYERINFO_H_

#include <QString>
#include <QColor>
#include "Function.h"

class LayerInfo {
public:
	LayerInfo();
	virtual ~LayerInfo();
	Qt::BrushStyle getBrushStyle();
	Qt::PenStyle getPenStyle();

	LineType 		layer_line_type;
	FillPattern 		layer_fille_pattern;
	int 				layer_line_width;
	QString 			layer_name;
	QColor  			layer_line_color;
	QColor  			layer_fill_color;
	QString 			layer_font_name;
	int  				layer_font_size;
	QColor  			layer_font_color;
	QString 			layer_symbol;
};

#endif /* LAYERINFO_H_ */
