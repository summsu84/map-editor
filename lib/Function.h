/*
 * Function.h
 *
 *  Created on: 2013. 5. 21.
 *      Author: jiwon
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <QPen>
#include <QBrush>
#include <QFont>

#define XFACTOR 0
#define YFACTOR 30

#define WX 2500
#define WY 2500

namespace DS{
	enum Shape{Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc, ManualPolygon,ManualPolyline, Text, Symbol, Circle};
}
enum LineType {Blank = 0, Solid = 1, Dashed = 2, Dotted =3 };

enum BndryVia{NONE, GREATECIRCLE, RHUMBLINE, COUNTERCLOCKWISEARC, CLOCKWISEARC, BNCIRCLE, BNSYMBOL};

enum DrawingMode {Initial, ReDrawing, SMSMap, UserMap};

enum SaveMode {All, User};			//all : �꾩껜, UserObject : UserObject留���옣

enum FillPattern{
	BLANK					= 0,
	SOLID_F 				= 1,
	DOTTED_F				= 2,
	HORIZONTALLINE 		= 3,
	VERTICALLINE 		= 4,
	CROSSLINE 			= 5,
	SLASHED 				= 6,
	REVERSESLASHED 		= 7,
	CROSSSLASHED 		= 9,
};

enum MapType{
	POLYGON = 10,
	POLYLINE,
	CIRCLE,
	ELLIPSE,
	LINE,
	TEXT,
	POINTnSYMBOL
};


#define M_PI		3.14159265358979323846	// pi

typedef struct _LatLon
{
	float lat;
	float lon;
}LatLon;


typedef struct _LAYER_MAP
{
	QString layer_id;
	QStringList map_id_list;
	bool isEnable[255];
}LAYER_MAP;

typedef struct _DRAWING
{
	DS::Shape shape;
	QPen pen;
	QBrush brush;
	QFont font;
	QString strText;
}DRAWING;

/*
 * => ManualCoord�먯꽌 �ъ슜�섎뒗 援ъ“泥� */
typedef struct _CoorDinates
{
	int idx;
	DS::Shape shape;
	BndryVia Via;
	QString Lat;
	QString Lon;
	QString centerLat;
	QString centerLon;
	double dist;
	double bearing;
	QPixmap symbol;
}COORDINATE;

/*
 * �ъ슜���ㅻ툕�앺듃 �쒕줈��諛�Manual Coord瑜��듯빐���ㅻ툕�앺듃瑜��쒕줈���덉쓣 ���뺣낫瑜�愿�━ �섎뒗 援ъ“泥� */
typedef struct _UserObject
{
	bool chkObject;
	QString obj_name;
	DS::Shape shape;
	void * object;
	QPen pen;
	QBrush brush;
}UserObject;

//�뚯씪����옣�섍린 �꾪븳 援ъ“泥�
typedef struct _SaveUserObject
{
	QString layer;
	QString id;
	QStringList coord_list;
}USER_OBJECT_LAYERINFO;
//const double rad2deg  = (180.0 / M_PI);

//Radar item info
typedef struct _RADARITEMINFO
{
	QString acid;
	QString from;
	QString to;
	int cu_spd;
	int cl_spd;
	int cl_heading;
	QString cu_alt;
	QString cl_alt;
}RDITEM;


#endif /* FUNCTION_H_ */
