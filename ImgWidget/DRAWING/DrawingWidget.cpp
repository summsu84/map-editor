/*
 * DrawingWidget.cpp
 *
 *  Created on: 2013. 6. 3.
 *      Author: jiwon
 */

#include "DrawingWidget.h"
#include "InputText.h"
#include <QMessageBox>
#include "CLineItem.h"
#include "CRectItem.h"
#include "CEllipseItem.h"
#include "../LATLON/LatLonConvert.h"

const int IdRole = Qt::UserRole;
using namespace::DS;

DrawingWidget::DrawingWidget(double mpp, QWidget * parent)
: QWidget(parent)
{
	this->mpp = mpp;
	initButton();

	//드로잉 버튼
	QGridLayout * btnLayout = new QGridLayout;

	QVBoxLayout * btnVBox = new QVBoxLayout;

	btnLayout->addWidget(btnSelect, 0, 1);
	btnLayout->addWidget(btnCircle, 0, 2);
	btnLayout->addWidget(btnRect, 0, 3);
	btnLayout->addWidget(btnEllipse, 0, 4);
	btnLayout->addWidget(btnArc, 0, 5);
	btnLayout->addWidget(btnText, 1, 1);
	btnLayout->addWidget(btnLine, 1, 2);
	btnLayout->addWidget(btnPolygon, 1, 3);
	btnLayout->addWidget(btnPolyline, 1,4);
	btnLayout->addWidget(btnSymbol, 1, 5);

	btnVBox->addLayout(btnLayout);
	btnVBox->addWidget(btnManual);

	QGroupBox * grpBtn = new QGroupBox(tr("Draw Object"));
	grpBtn->setLayout(btnVBox);


	QVBoxLayout * mainVBox = new QVBoxLayout;
	mainVBox->addWidget(grpBtn);

	mainVBox->addWidget(this->initLineProp());
	mainVBox->addWidget(this->initFillProp());
	mainVBox->addWidget(this->initFontProp());
	mainVBox->addWidget(this->initUserProp());
	mainVBox->addWidget(this->initZoomProp());

	setLayout(mainVBox);

	drawing.shape = Line;
	isDone = false;

	setWindowTitle(tr("Object Panel"));

}


DrawingWidget::DrawingWidget(QWidget * parent)
: QWidget(parent)
{
	// TODO Auto-generated constructor stub
	initButton();
	/*shapeComboBox = new QComboBox;
	shapeComboBox->addItem(tr("Polygon"), Polygon);
	shapeComboBox->addItem(tr("Rectangle"), Rect);
	shapeComboBox->addItem(tr("Rounded Rectangle"), RoundedRect);
	shapeComboBox->addItem(tr("Ellipse"), Ellipse);
	shapeComboBox->addItem(tr("Pie"),  Pie);
	shapeComboBox->addItem(tr("Chord"),  Chord);
	shapeComboBox->addItem(tr("Path"),  Path);
	shapeComboBox->addItem(tr("Line"),  Line);
	shapeComboBox->addItem(tr("Polyline"),  Polyline);
	shapeComboBox->addItem(tr("Arc"),  Arc);
	shapeComboBox->addItem(tr("Points"),  Points);
	shapeComboBox->addItem(tr("Text"),  Text);
	shapeComboBox->addItem(tr("Pixmap"),  Pixmap);

	shapeLabel = new QLabel(tr("&Shape:"));
	shapeLabel->setBuddy(shapeComboBox);

	penWidthSPinBox = new QSpinBox;
	penWidthSPinBox->setRange(0, 20);
	penWidthSPinBox->setSpecialValueText(tr("0 (cosmetic pen)"));

	penWidthLabel = new QLabel(tr("&Pen &Width:"));
	penWidthLabel->setBuddy(penWidthSPinBox);

	penStyleComboBox = new QComboBox;
	penStyleComboBox->addItem(tr("Solid"), Qt::SolidLine);
	penStyleComboBox->addItem(tr("Dash"), Qt::DashLine);
	penStyleComboBox->addItem(tr("Dot"), Qt::DotLine);
	penStyleComboBox->addItem(tr("Dash Dot"), Qt::DashDotLine);
	penStyleComboBox->addItem(tr("Dash Dot Dot"), Qt::DashDotDotLine);
	penStyleComboBox->addItem(tr("None"), Qt::NoPen);

	penStyleLabel = new QLabel(tr("&Pen Style:"));
	penStyleLabel->setBuddy(penStyleComboBox);

	penCapCombobox = new QComboBox;
	penCapCombobox->addItem(tr("Flat"), Qt::FlatCap);
	penCapCombobox->addItem(tr("Square"), Qt::SquareCap);
	penCapCombobox->addItem(tr("Round"), Qt::RoundCap);

	penCapLabel = new QLabel(tr("Pen &Cap:"));
	penCapLabel->setBuddy(penCapCombobox);

	penJoinComboBox = new QComboBox;
	penJoinComboBox->addItem(tr("Miter"), Qt::MiterJoin);
	penJoinComboBox->addItem(tr("Bevel"), Qt::BevelJoin);
	penJoinComboBox->addItem(tr("Round"), Qt::RoundJoin);

	penJoinLabel = new QLabel(tr("Pen &Join:"));
	penJoinLabel->setBuddy(penJoinComboBox);

	brushStyleComboBox = new QComboBox;
	brushStyleComboBox->addItem(tr("Linear Gradient"),
		 Qt::LinearGradientPattern);
	brushStyleComboBox->addItem(tr("Radial Gradient"),
		 Qt::RadialGradientPattern);
	brushStyleComboBox->addItem(tr("Conical Gradient"),
		 Qt::ConicalGradientPattern);
	brushStyleComboBox->addItem(tr("Texture"), Qt::TexturePattern);
	brushStyleComboBox->addItem(tr("Solid"), Qt::SolidPattern);
	brushStyleComboBox->addItem(tr("Horizontal"), Qt::HorPattern);
	brushStyleComboBox->addItem(tr("Vertical"), Qt::VerPattern);
	brushStyleComboBox->addItem(tr("Cross"), Qt::CrossPattern);
	brushStyleComboBox->addItem(tr("Backward Diagonal"), Qt::BDiagPattern);
	brushStyleComboBox->addItem(tr("Forward Diagonal"), Qt::FDiagPattern);
	brushStyleComboBox->addItem(tr("Diagonal Cross"), Qt::DiagCrossPattern);
	brushStyleComboBox->addItem(tr("Dense 1"), Qt::Dense1Pattern);
	brushStyleComboBox->addItem(tr("Dense 2"), Qt::Dense2Pattern);
	brushStyleComboBox->addItem(tr("Dense 3"), Qt::Dense3Pattern);
	brushStyleComboBox->addItem(tr("Dense 4"), Qt::Dense4Pattern);
	brushStyleComboBox->addItem(tr("Dense 5"), Qt::Dense5Pattern);
	brushStyleComboBox->addItem(tr("Dense 6"), Qt::Dense6Pattern);
	brushStyleComboBox->addItem(tr("Dense 7"), Qt::Dense7Pattern);
	brushStyleComboBox->addItem(tr("None"), Qt::NoBrush);

	brushStyleLabel = new QLabel(tr("&Brush Style:"));
	brushStyleLabel->setBuddy(brushStyleComboBox);

	otherOptionsLabel = new QLabel(tr("Other Options:"));
	antialiasingCheckBox = new QCheckBox(tr("&Antialiasing"));
	transformationCheckBox = new QCheckBox(tr("&Transformations"));

	btnDraw = new QPushButton(tr("DRAW"));

	//PenColor

	QLabel * lblR = new QLabel("R");
	QLabel * lblG = new QLabel("G");
	QLabel * lblB = new QLabel("B");


	//signal and slot

	connect(shapeComboBox, SIGNAL(activated(int)), this, SLOT(shapeChanged()));
	connect(penWidthSPinBox, SIGNAL(valueChanged(int)), this, SLOT(penChanged()));
	connect(penStyleComboBox, SIGNAL(activated(int)), this, SLOT(penChanged()));
	connect(penCapCombobox, SIGNAL(activated(int)), this, SLOT(penChanged()));
	connect(penJoinComboBox, SIGNAL(activated(int)), this, SLOT(penChanged()));
	connect(brushStyleComboBox, SIGNAL(activated(int)), this, SLOT(brushChanged()));
//	connect(antialiasingCheckBox, SIGNAL(toggled(bool)), renderArea, SLOT(setAntialiased(bool)));
//	connect(transformationCheckBox, SIGNAL(toggled(bool)),renderArea, SLOT(setTransformed(bool)));
	connect(btnDraw, SIGNAL(clicked()), this, SLOT(runDraw()));*/

	//Layout
/*	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(shapeLabel, 0, 1, Qt::AlignRight);
	mainLayout->addWidget(shapeComboBox, 0, 2);
	mainLayout->addWidget(penWidthLabel, 0, 3, Qt::AlignRight);
	mainLayout->addWidget(penWidthSPinBox, 0, 4);
	mainLayout->addWidget(penStyleLabel, 0, 5, Qt::AlignRight);
	mainLayout->addWidget(penStyleComboBox, 0, 6);
	mainLayout->addWidget(penCapLabel, 0, 7, Qt::AlignRight);
	mainLayout->addWidget(penCapCombobox, 0, 8);
	mainLayout->addWidget(penJoinLabel, 0, 9, Qt::AlignRight);
	mainLayout->addWidget(penJoinComboBox, 0, 10);
	mainLayout->addWidget(brushStyleLabel, 0, 11, Qt::AlignRight);
	mainLayout->addWidget(brushStyleComboBox, 0, 12);
	mainLayout->addWidget(otherOptionsLabel, 2, 1, Qt::AlignRight);
	mainLayout->addWidget(antialiasingCheckBox, 2, 2);
	mainLayout->addWidget(transformationCheckBox, 2, 4);
	mainLayout->addWidget(btnDraw, 0, 13);
	mainLayout->addWidget(btnRect, 0, 14);
	setLayout(mainLayout);*/

	//드로잉 버튼
	QGridLayout * btnLayout = new QGridLayout;

	QVBoxLayout * btnVBox = new QVBoxLayout;

	btnLayout->addWidget(btnSelect, 0, 1);
	btnLayout->addWidget(btnCircle, 0, 2);
	btnLayout->addWidget(btnRect, 0, 3);
	btnLayout->addWidget(btnEllipse, 0, 4);
	btnLayout->addWidget(btnArc, 0, 5);
	btnLayout->addWidget(btnText, 1, 1);
	btnLayout->addWidget(btnLine, 1, 2);
	btnLayout->addWidget(btnPolygon, 1, 3);
	btnLayout->addWidget(btnPolyline, 1,4);
	btnLayout->addWidget(btnSymbol, 1, 5);

	btnVBox->addLayout(btnLayout);
	btnVBox->addWidget(btnManual);

	QGroupBox * grpBtn = new QGroupBox(tr("Draw Object"));
	grpBtn->setLayout(btnVBox);


	QVBoxLayout * mainVBox = new QVBoxLayout;
	mainVBox->addWidget(grpBtn);

	mainVBox->addWidget(this->initLineProp());
	mainVBox->addWidget(this->initFillProp());
	mainVBox->addWidget(this->initFontProp());
	mainVBox->addWidget(this->initZoomProp());

	setLayout(mainVBox);


	/*shapeChanged();
	penChanged();
	brushChanged();*/
	//antialiasingCheckBox->setChecked(true);

	drawing.shape = Line;
	isDone = false;
}

DrawingWidget::~DrawingWidget() {
	// TODO Auto-generated destructor stub
}


/*
 * 버튼 초기화 함수
 */
void DrawingWidget::initButton()
{
	btnSelect = new QPushButton(QIcon(":/res/object_select.png"), "");
	btnCircle = new QPushButton(QIcon(":/res/object_circle.png"), "");
	btnRect = new QPushButton(QIcon(":/res/object_rectangle.png"), "");
	btnEllipse = new QPushButton(QIcon(":/res/object_ellipse.png"), "");
	btnLine = new QPushButton(QIcon(":/res/object_line.png"), "");
	btnPolygon = new QPushButton(QIcon(":/res/object_polygon.png"), "");
	btnPolyline = new QPushButton(QIcon(":/res/object_polyline.png"), "");
	btnArc = new QPushButton(QIcon(":/res/object_arc.png"), "");
	btnText = new QPushButton(QIcon(":/res/object_text.png"), "");
	btnSymbol = new QPushButton(QIcon(":/res/object_symbol.png"), "");


	btnManual = new QPushButton("Manual Coord. Input");

	connect(btnSelect, SIGNAL(clicked()), this, SLOT(runRect()));
	connect(btnCircle, SIGNAL(clicked()), this, SLOT(runCircle()));

	connect(btnRect, SIGNAL(clicked()), this, SLOT(runRect()));
	connect(btnEllipse, SIGNAL(clicked()), this, SLOT(runEllipse()));
	connect(btnLine, SIGNAL(clicked()), this, SLOT(runLine()));
	connect(btnPolygon, SIGNAL(clicked()), this, SLOT(runPolygon()));
	connect(btnPolyline, SIGNAL(clicked()), this, SLOT(runPolyline()));
	connect(btnArc, SIGNAL(clicked()), this, SLOT(runArc()));
	connect(btnText, SIGNAL(clicked()), this, SLOT(runText()));
	connect(btnSymbol, SIGNAL(clicked()), this, SLOT(runSymbol()));
	connect(btnManual, SIGNAL(clicked()), this, SLOT(runManualCoord()));
}

/*
 * Line Properties
 *
 */

QWidget * DrawingWidget::initLineProp()
{

	qDebug()<<"initLineProp is called..";
	QHBoxLayout * hbox = new QHBoxLayout;
	QLabel * lblType = new QLabel(tr("Type"));
	penStyleComboBox = new QComboBox;
	penStyleComboBox->addItem(tr("Solid"), Qt::SolidLine);
	penStyleComboBox->addItem(tr("Dash"), Qt::DashLine);
	penStyleComboBox->addItem(tr("Dot"), Qt::DotLine);
	penStyleComboBox->addItem(tr("Dash Dot"), Qt::DashDotLine);
	penStyleComboBox->addItem(tr("Dash Dot Dot"), Qt::DashDotDotLine);
	penStyleComboBox->addItem(tr("None"), Qt::NoPen);

	hbox->addWidget(lblType);
	hbox->addWidget(penStyleComboBox);

	QHBoxLayout * hbox2 = new QHBoxLayout;
	QLabel * lblWidth = new QLabel(tr("Width"));

	penWidthSPinBox = new QSpinBox;
	penWidthSPinBox->setRange(0, 20);
	penWidthSPinBox->setSpecialValueText(tr("0 (cosmetic pen)"));

	hbox2->addWidget(lblWidth);
	hbox2->addWidget(penWidthSPinBox);

	//Pen Color
	spnPenR = new QSpinBox;
	spnPenR->setRange(0, 255);
	spnPenG = new QSpinBox;
	spnPenG->setRange(0, 255);
	spnPenB = new QSpinBox;
	spnPenB->setRange(0, 255);

	QHBoxLayout * hbox3 = new QHBoxLayout;

	QLabel * lblColor = new QLabel(tr("Color"));

	hbox3->addWidget(lblColor);
	hbox3->addWidget(spnPenR);
	hbox3->addWidget(spnPenG);
	hbox3->addWidget(spnPenB);

	QVBoxLayout * vbox = new QVBoxLayout;

	vbox->addLayout(hbox);
	vbox->addLayout(hbox2);
	vbox->addLayout(hbox3);


	//connect
	connect(penWidthSPinBox, SIGNAL(valueChanged(int)), this, SLOT(penChanged()));
	connect(penStyleComboBox, SIGNAL(activated(int)), this, SLOT(penChanged()));
	connect(spnPenR, SIGNAL(valueChanged(int)), this, SLOT(penChanged()));
	connect(spnPenG, SIGNAL(valueChanged(int)), this, SLOT(penChanged()));
	connect(spnPenB, SIGNAL(valueChanged(int)), this, SLOT(penChanged()));

	QGroupBox * grpBox = new QGroupBox(tr("Line Properites"));
	grpBox->setLayout(vbox);

	QWidget * widget = dynamic_cast<QWidget *>(grpBox);
	if(widget == 0){
		qDebug()<<"[DrawingWidget] casting is failed..";
	}

	qDebug()<<"initLineProp is closed..";
	return widget;
}


/*
 * Fill Properties
 *
 */

QWidget * DrawingWidget::initFillProp()
{

	qDebug()<<"initLineProp is called..";
	QHBoxLayout * hbox = new QHBoxLayout;
	QLabel * lblColor = new QLabel(tr("Color"));

	//Pen Color
	spnFillR = new QSpinBox;
	spnFillR->setRange(0, 255);
	spnFillG = new QSpinBox;
	spnFillG->setRange(0, 255);
	spnFillB = new QSpinBox;
	spnFillB->setRange(0, 255);


	hbox->addWidget(lblColor);
	hbox->addWidget(spnFillR);
	hbox->addWidget(spnFillG);
	hbox->addWidget(spnFillB);

	QHBoxLayout * hbox2 = new QHBoxLayout;
	QLabel * lblType = new QLabel(tr("Type"));

	brushStyleComboBox = new QComboBox;
	brushStyleComboBox->addItem(tr("Linear Gradient"),
		 Qt::LinearGradientPattern);
	brushStyleComboBox->addItem(tr("Radial Gradient"),
		 Qt::RadialGradientPattern);
	brushStyleComboBox->addItem(tr("Conical Gradient"),
		 Qt::ConicalGradientPattern);
	brushStyleComboBox->addItem(tr("Texture"), Qt::TexturePattern);
	brushStyleComboBox->addItem(tr("Solid"), Qt::SolidPattern);
	brushStyleComboBox->addItem(tr("Horizontal"), Qt::HorPattern);
	brushStyleComboBox->addItem(tr("Vertical"), Qt::VerPattern);
	brushStyleComboBox->addItem(tr("Cross"), Qt::CrossPattern);
	brushStyleComboBox->addItem(tr("Backward Diagonal"), Qt::BDiagPattern);
	brushStyleComboBox->addItem(tr("Forward Diagonal"), Qt::FDiagPattern);
	brushStyleComboBox->addItem(tr("Diagonal Cross"), Qt::DiagCrossPattern);
	brushStyleComboBox->addItem(tr("Dense 1"), Qt::Dense1Pattern);
	brushStyleComboBox->addItem(tr("Dense 2"), Qt::Dense2Pattern);
	brushStyleComboBox->addItem(tr("Dense 3"), Qt::Dense3Pattern);
	brushStyleComboBox->addItem(tr("Dense 4"), Qt::Dense4Pattern);
	brushStyleComboBox->addItem(tr("Dense 5"), Qt::Dense5Pattern);
	brushStyleComboBox->addItem(tr("Dense 6"), Qt::Dense6Pattern);
	brushStyleComboBox->addItem(tr("Dense 7"), Qt::Dense7Pattern);
	brushStyleComboBox->addItem(tr("None"), Qt::NoBrush);

	hbox2->addWidget(lblType);
	hbox2->addWidget(brushStyleComboBox);

	QVBoxLayout * vbox = new QVBoxLayout;

	vbox->addLayout(hbox);
	vbox->addLayout(hbox2);


	// connect

	connect(brushStyleComboBox, SIGNAL(activated(int)), this, SLOT(brushChanged()));
	connect(spnFillR, SIGNAL(valueChanged(int)), this, SLOT(brushChanged()));
	connect(spnFillG, SIGNAL(valueChanged(int)), this, SLOT(brushChanged()));
	connect(spnFillB, SIGNAL(valueChanged(int)), this, SLOT(brushChanged()));

	QGroupBox * grpBox = new QGroupBox(tr("Fill Properties"));
	grpBox->setLayout(vbox);

	QWidget * widget = dynamic_cast<QWidget *>(grpBox);
	if(widget == 0){
		qDebug()<<"[DrawingWidget] casting is failed..";
	}

	qDebug()<<"initLineProp is closed..";
	return widget;
}



/*
 * Font Properties
 *
 */

QWidget * DrawingWidget::initFontProp()
{

	qDebug()<<"initFontProp is called..";
	QHBoxLayout * hbox = new QHBoxLayout;
	QLabel * lblType = new QLabel(tr("Type"));

	cboFont = new QComboBox;

	hbox->addWidget(lblType);
	hbox->addWidget(cboFont);

	QHBoxLayout * hbox2 = new QHBoxLayout;
	QLabel * lblSize = new QLabel(tr("Size"));
	spnFontSize = new QSpinBox;
	spnFontSize->setRange(0, 20);

	hbox2->addWidget(lblSize);
	hbox2->addWidget(spnFontSize);

	//Pen Color
	spnFontR = new QSpinBox;
	spnFontR->setRange(0, 255);
	spnFontG = new QSpinBox;
	spnFontG->setRange(0, 255);
	spnFontB = new QSpinBox;
	spnFontB->setRange(0, 255);

	QHBoxLayout * hbox3 = new QHBoxLayout;

	QLabel * lblColor = new QLabel(tr("Color"));

	hbox3->addWidget(lblColor);
	hbox3->addWidget(spnFontR);
	hbox3->addWidget(spnFontG);
	hbox3->addWidget(spnFontB);

	QVBoxLayout * vbox = new QVBoxLayout;

	vbox->addLayout(hbox);
	vbox->addLayout(hbox2);
	vbox->addLayout(hbox3);


	connect(spnFontSize, SIGNAL(valueChanged(int)), this, SLOT(fontChanged()));
	connect(spnFontR, SIGNAL(valueChanged(int)), this, SLOT(fontChanged()));
	connect(spnFontG, SIGNAL(valueChanged(int)), this, SLOT(fontChanged()));
	connect(spnFontB, SIGNAL(valueChanged(int)), this, SLOT(fontChanged()));


	QGroupBox * grpBox = new QGroupBox(tr("Font Properties"));
	grpBox->setLayout(vbox);

	QWidget * widget = dynamic_cast<QWidget *>(grpBox);
	if(widget == 0){
		qDebug()<<"[DrawingWidget] casting is failed..";
	}

	qDebug()<<"initFontProp is closed..";
	return widget;
}




/*
 * Zoom Properties
 *
 */

QWidget * DrawingWidget::initZoomProp()
{

	qDebug()<<"initZoomProp is called..";
	QHBoxLayout * hbox = new QHBoxLayout;

	sldScale = new QSlider(Qt::Horizontal);
	int value = (int)mpp;
	qDebug()<<"value : "<<value;
	sldScale->setMaximum(4600);
	sldScale->setMinimum(0);
	sldScale->setValue(value);

	txtScale = new QSpinBox;
	txtScale->setRange(0, 4600);
	txtScale->setValue(value);
	//txtScale->setText(QString::number(value, 10));
	txtScale->setMaximumWidth(80);

	connect(sldScale, SIGNAL(sliderReleased()), this, SLOT(runSliderReleased()));
	connect(sldScale, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged_2(int )));
	connect(txtScale, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int )));

	hbox->addWidget(sldScale);
	hbox->addWidget(txtScale);


	QGroupBox * grpBox = new QGroupBox(tr("Zoom"));
	grpBox->setLayout(hbox);

	QWidget * widget = dynamic_cast<QWidget *>(grpBox);
	if(widget == 0){
		qDebug()<<"[DrawingWidget] casting is failed..";
	}

	return widget;
}

QWidget * DrawingWidget::initUserProp()
{
	qDebug()<<"initUserProp is called..";
	QHBoxLayout * hbox = new QHBoxLayout;

	tblWidget = new QTableWidget;

	btnDelete = new QPushButton(tr("Delete"));
	btnModify = new QPushButton(tr("Modify"));
	btnChange = new QPushButton(tr("Change Id"));

	hbox->addWidget(btnDelete);
	hbox->addWidget(btnModify);
	hbox->addWidget(btnChange);

	connect(btnDelete, SIGNAL(clicked()), this, SLOT(runDelete()));
	connect(btnModify, SIGNAL(clicked()), this, SLOT(runModify()));
	connect(btnChange, SIGNAL(clicked()), this, SLOT(runChange()));

	QVBoxLayout * vbox = new QVBoxLayout;

	vbox->addWidget(tblWidget);
	vbox->addLayout(hbox);


	QGroupBox * grpBox = new QGroupBox(tr("User Map Id"));
	grpBox->setLayout(vbox);

	QWidget * widget = dynamic_cast<QWidget *>(grpBox);
	if(widget == 0){
		qDebug()<<"[DrawingWidget] casting is failed..";
	}

	return widget;
}


void DrawingWidget::shapeChanged()
{
     /*Shape shape =  Shape(shapeComboBox->itemData(shapeComboBox->currentIndex(), IdRole).toInt());
     drawing.shape = shape;
     qDebug()<<"Shape : "<<shape;*/
    //renderArea->setShape(shape);
   // renderArea->setShape(shape);

}

void DrawingWidget::penChanged()
{
    int width = penWidthSPinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
            penStyleComboBox->currentIndex(), IdRole).toInt());
    /*Qt::PenCapStyle cap = Qt::PenCapStyle(penCapCombobox->itemData(
            penCapCombobox->currentIndex(), IdRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(
            penJoinComboBox->currentIndex(), IdRole).toInt());*/

  //  renderArea->setPen(QPen(Qt::blue, width, style, cap, join));

    int r = spnPenR->value();
    int g = spnPenG->value();
    int b = spnPenB->value();

    QPen tmpPen(QColor(r,g,b), width, style);
    drawing.pen = tmpPen;




}

void DrawingWidget::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(
            brushStyleComboBox->currentIndex(), IdRole).toInt());

    if (style == Qt::LinearGradientPattern) {
        QLinearGradient linearGradient(0, 0, 100, 100);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::black);
     //   renderArea->setBrush(linearGradient);

    } else if (style == Qt::RadialGradientPattern) {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::black);
       // renderArea->setBrush(radialGradient);
    } else if (style == Qt::ConicalGradientPattern) {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, Qt::green);
        conicalGradient.setColorAt(1.0, Qt::black);
        //renderArea->setBrush(conicalGradient);
    } else if (style == Qt::TexturePattern) {
        //renderArea->setBrush(QBrush(QPixmap(":/images/brick.png")));
    } else {
       // renderArea->setBrush(QBrush(Qt::green, style));
    }

   int r = spnFillR->value();
	int g = spnFillG->value();
	int b = spnFillB->value();

    drawing.brush = QBrush(QColor(r,g,b), style);
}

void DrawingWidget::fontChanged()
{
    int size = spnFontSize->value();

    int r = spnFontR->value();
    int g = spnFontG->value();
    int b = spnFontB->value();


    QFont font("Times", size);


    drawing.font = font;
    drawing.pen = QPen(QColor(r,g,b));



}



void DrawingWidget::runDraw()
{
	qDebug()<<"Run Draw is called..";


	emit emitDrawingProp(drawing);

}

void DrawingWidget::runManualCoord()
{
	ManualCoord * mc = new ManualCoord(this);
	connect(mc, SIGNAL(emitDone(QVector<COORDINATE>, DrawingMode, QGraphicsItem *)), this, SLOT(runDone(QVector<COORDINATE>, DrawingMode, QGraphicsItem *)));
	mc->show();
}


void DrawingWidget::runRect()
{
	drawing.shape = Rect;
	runDraw();
}

void DrawingWidget::runEllipse()
{
	drawing.shape = Ellipse;
	runDraw();
}

void DrawingWidget::runCircle()
{
	drawing.shape = Circle;
	runDraw();
}



void DrawingWidget::runLine()
{
	drawing.shape = Line;
	runDraw();
}

void DrawingWidget::runPolygon()
{
	drawing.shape = Polygon;
	runDraw();
}

void DrawingWidget::runPolyline()
{
	drawing.shape = Polyline;
	runDraw();
}

void DrawingWidget::runArc()
{
	drawing.shape = Arc;
	runDraw();
}

void DrawingWidget::runText()
{
	drawing.shape = Text;

	InputText * inputText = new InputText(this);
	inputText->setModal(true);
	if(inputText->exec()){
		delete inputText;
	}else{
		delete inputText;
	}

	qDebug()<<"text : "<<drawing.strText;
	runDraw();
}

void DrawingWidget::runSymbol()
{
	drawing.shape = Symbol;

	SymbolSelector * symbolSelector = new SymbolSelector(this);
	symbolSelector->setModal(true);
	if(symbolSelector->exec()){
		delete symbolSelector;
	}else{
		delete symbolSelector;
	}
	runDraw();
}


void DrawingWidget::closeEvent(QCloseEvent * event)
{
	qDebug()<<"Drawing Widget closing..";
	emit emitDrawingClose();
}

/**
 * Manual Drawing 화면에서 Done을 클릭한다.
 */
void DrawingWidget::runDone(QVector<COORDINATE> coord_list, DrawingMode dm, QGraphicsItem * item)
{
	emitManualDrawingIsDone(coord_list, dm, item);
}

/**
 * Spin Scale 값이 변경되었을때 슬롯
 */

void DrawingWidget::scaleChanged(int value)
{

	sldScale->setValue(value);
	emit emitSliderReleassed(value);
}
void DrawingWidget::scaleChanged_2(int value)
{

	qDebug()<<"chaged..value: "<<value;
	txtScale->setValue(value);
}

void DrawingWidget::runSliderReleased()
{

	int value = sldScale->value();

	qDebug()<<"runSliderReleased.. value : "<<value;

	emit emitSliderReleassed(value);
}

/*
 * 휠 이벤트 발생시 호출되는 함수
 */
void DrawingWidget::adjustMpp(double mpp)
{
	//qDebug()<<"=====================adjustMpp================mpp : "<<mpp;
	this->mpp = mpp;

	sldScale->setValue(mpp);
	txtScale->setValue(mpp);
}


/*
 * 오브젝트 판넬을 통해서 드로잉한 오브젝트들에 대해서 테이블을 생성한다.
 */
void DrawingWidget::genTable()
{
	//qDebug()<<"display Blanking Area Info called...test";

	tblWidget->disconnect();
	tblWidget->setRowCount(0);

	connect(tblWidget, SIGNAL(clicked(const QModelIndex &)), this,	SLOT(processTable(const QModelIndex &)));

	QColor color(255,0,0,100);
	QBrush brush(color);

	tblWidget->setColumnCount(2);

	tblWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	//tblView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tblWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	tblWidget->resizeColumnsToContents();
	tblWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//	tblWidget->setHorizontalHeaderLabels(QStringList()
//			<<tr("Symbol")<<tr("File Name"));

	for(int row = 0 ; row < object_list.size(); row++){
		addRows();
		if(object_list.at(row).chkObject == true){
			tblWidget->item(row,0)->setCheckState(Qt::Checked);
		}
		tblWidget->item(row,1)->setText(object_list.at(row).obj_name);
	}

	tblWidget->resizeColumnsToContents();
	tblWidget->setCurrentCell(0,0);
}

void DrawingWidget::addRows()
{
	int row = tblWidget->rowCount();
	tblWidget->insertRow(row);

		QTableWidgetItem * item[2];
		for(int i = 0 ; i < 2; i++){
			item[i] = new QTableWidgetItem;
			if(i == 0){
				item[i]->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
				item[i]->setCheckState(Qt::Unchecked);
			}
			item[i]->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
			item[i]->setFlags(item[i]->flags() ^ Qt::ItemIsEditable);

			tblWidget->setItem(row,i,item[i]);
		}
	//위의 소스코드에서 체크 박스 및 하나의 셀을 만드는 과정이다..

		tblWidget->setCurrentItem(item[0]);
}

/*
 * DrawingObject를 완료 했을 때, 호출되는 함수
 */
void DrawingWidget::runUserObject(QVector<UserObject> object_list)
{
	qDebug()<<"[DrawingWidget-runUserObject] called..";

	this->object_list = object_list;
	this->genTable();
}

void DrawingWidget::processTable(const QModelIndex & index)
{
	qDebug()<<"========================[DrawingWidget-ProcessTable] called.. rows : "<<index.row();

	int row = index.row();

	UserObject object = object_list.at(row);

	QTableWidgetItem * item = tblWidget->item(row, 0);

	QGraphicsItem * grpItem = static_cast<QGraphicsItem *>(object.object);
	//CLineItem * grpItem = static_cast<CLineItem *>(object.object);
	if(item->checkState() == Qt::Unchecked)
	{
		grpItem->setVisible(false);
	}else
	{
		grpItem->setVisible(true);
	}

	qDebug()<<"Selected Text : "<<item->text();

	//selectedName = item->text();
}

void DrawingWidget::runDelete()
{

	QMessageBox::StandardButtons reply;

	reply = QMessageBox::question(this, tr("Delete"), tr("Do you want delete?"), QMessageBox::Ok | QMessageBox::Cancel);

	if(reply != QMessageBox::Ok){
		return;
	}

	int row = tblWidget->currentRow();

	UserObject object = object_list.at(row);

	//QTableWidgetItem * item = tblWidget->item(row, 0);

	QGraphicsItem * grpItem = static_cast<QGraphicsItem *>(object.object);
	//CLineItem * grpItem = static_cast<CLineItem *>(object.object);

	emitRemoveItem(grpItem, row);

	object_list.remove(row);

	genTable();

}

/*
 * Modfiy 버튼을 클릭했을 때, 현재 오브젝트 테이블의 정보를 Manual Coord 정보로 변환한다.
 */
void DrawingWidget::runModify()
{
	qDebug()<<"[DrawingWidget - runModify] called..";

	QMessageBox::StandardButtons reply;

	reply = QMessageBox::question(this, tr("Modify"), tr("Do you want modify?"), QMessageBox::Ok | QMessageBox::Cancel);

	if(reply != QMessageBox::Ok){
		return;
	}

	QVector<COORDINATE> cn_list;

	int row = tblWidget->currentRow();
	if(row < 0){
		QString err = "Error";
		QString text = "Select Item";
		QMessageBox::warning(this, err, text);
		return;
	}

	UserObject object = object_list.at(row);

	QGraphicsItem * grpItem = static_cast<QGraphicsItem * >(object.object);		//QGraphicsItem 으로 변환
	//qDebug()<<"GrpItem : "<<grpItem;

	Shape shape;			//ManualCoord에서 사용될 Shape (Line, Polyline, => Polyline) (Rect, Ellipse => Polygon)
	BndryVia via;
	QString lat;
	QString lon;


	//Line Object
	if(object.shape == Line)
	{
		//qDebug()<<"Line";
		shape = Line;
		via = GREATECIRCLE;

		//CLineItem * line = static_cast<CLineItem *>(object.object);
		CLineItem * line = static_cast<CLineItem *>(grpItem);

		qDebug()<<"line : "<<line->getId();
		//line->setVisible(false);
		QLineF lineF = line->line();

		QPointF p1 = lineF.p1();

		QPointF p1_latlon = LatLonConvert::getInstance().screenToDecimal(p1.toPoint());

		QString p1_lat = LatLonConvert::getInstance().decimalLatToString(p1_latlon.x());
		QString p1_lon = LatLonConvert::getInstance().decimalLonToString(p1_latlon.y());


		QPointF p2 = lineF.p2();

		QPointF p2_latlon = LatLonConvert::getInstance().screenToDecimal(p2.toPoint());

		QString p2_lat = LatLonConvert::getInstance().decimalLatToString(p2_latlon.x());
		QString p2_lon = LatLonConvert::getInstance().decimalLonToString(p2_latlon.y());

		qDebug()<<"P1 Lat : "<<p1_lat<<", P1 Lon : "<<p1_lon<<", P2 Lat : "<<p2_lat<<", P2_Lon : "<<p2_lon;

		COORDINATE cn[2];

		cn[0].shape = shape;
		cn[0].Via = via;
		cn[0].Lat = p1_lat;
		cn[0].Lon = p1_lon;

		cn[1].shape = shape;
		cn[1].Via = via;
		cn[1].Lat = p2_lat;
		cn[1].Lon = p2_lon;

		cn_list.append(cn[0]);
		cn_list.append(cn[1]);



	}
	//Rectangle Object
	else if(object.shape == Rect)
	{
		//Rect의 경우 네개의 지점으로 구성되어 있으므로 네개의 점을 생성한다..
		shape = Polygon;
		via = GREATECIRCLE;

		CRectItem * rect = static_cast<CRectItem *>(grpItem);

		//qDebug()<<"line : "<<line->getId();
		//line->setVisible(false);
		QPointF point[4];
		point[0] = rect->rect().topLeft();
		point[1] = rect->rect().topRight();
		point[2] = rect->rect().bottomRight();
		point[3] = rect->rect().bottomLeft();

		QString lat[4];
		QString lon[4];

		for(int i = 0 ; i < 4 ; i++){
			QPointF tmp = LatLonConvert::getInstance().screenToDecimal(point[i].toPoint());
			lat[i] = LatLonConvert::getInstance().decimalLatToString(tmp.x());
			lon[i] = LatLonConvert::getInstance().decimalLonToString(tmp.y());

			COORDINATE cn;

			cn.shape = Polygon;
			cn.Via = via;
			cn.Lat = lat[i];
			cn.Lon = lon[i];

			cn_list.append(cn);
		}

	}else if(object.shape == Ellipse)
	{
		//Ellipse의 경우 원이므로, 센터 값을 구해야한다.
		//1. topLeft값과 toRight 값을 구한 다음 해당 거리에서 2를 나누면 반지름이 된다.
		//2. topLeft에서 해당 반지름 길이만큼, x축과 y축으로 이동한 곳이 원의 중심점이 된다.
		shape = Circle;
		via = BNCIRCLE;

		CEllipseItem * rect = static_cast<CEllipseItem *>(grpItem);

		QPointF leftTop = rect->rect().topLeft();
		QPointF rightTop = rect->rect().topLeft();

		double dist = LatLonConvert::getInstance().distance(leftTop.toPoint(), rightTop.toPoint());

		QPointF center = QPointF(leftTop.x() + dist, leftTop.y() + dist);

		QPointF decimalCenter = LatLonConvert::getInstance().screenToDecimal(center.toPoint());

		QString lat = LatLonConvert::getInstance().decimalLatToString(decimalCenter.x());
		QString lon = LatLonConvert::getInstance().decimalLonToString(decimalCenter.y());

		COORDINATE cn;

		cn.shape = Circle;
		cn.Via = via;
		cn.centerLat = lat;
		cn.centerLon = lon;

		cn_list.append(cn);

	}
	//Manual Coord를통해서 생성된 오브젝트
	else if(object.shape == ManualPolygon || object.shape == ManualPolyline)
	{
		//Path에 대한 값을 구한다.

		shape = Polygon;
		via = GREATECIRCLE;

		QGraphicsPathItem * pathItem = static_cast<QGraphicsPathItem *>(grpItem);

		QPainterPath path = pathItem->path();

		QVector<QPointF> point_list;			//위경도로 변환된 좌표 리스트 목록들.

		for(int i = 0 ; i < path.elementCount(); i++)
		{
			QPainterPath::Element pt = path.elementAt(i);
			QPointF point = LatLonConvert::getInstance().screenToDecimal(QPointF(pt.x, pt.y).toPoint());
			point_list.append(point);
		}

		for(int i = 0 ; i < point_list.size() ; i++){
			QPointF point = point_list.at(i);
			COORDINATE cn;

			QString lat = LatLonConvert::getInstance().decimalLatToString(point.x());
			QString lon = LatLonConvert::getInstance().decimalLonToString(point.y());
			cn.shape = shape;
			cn.Via = via;
			cn.Lat = lat;
			cn.Lon = lon;

			cn_list.append(cn);
		}

	}
	//Circle Object
	else if(object.shape == Circle)
	{
		qDebug()<<"Circle..";
		//Path에 대한 값을 구한다.

		shape = Circle;
		via = BNCIRCLE;

		QGraphicsEllipseItem * rect = static_cast<QGraphicsEllipseItem *>(grpItem);

		QPointF leftTop = rect->rect().topLeft();
		QPointF rightTop = rect->rect().topLeft();

		double dist = LatLonConvert::getInstance().distance(leftTop.toPoint(), rightTop.toPoint());

		QPointF center = QPointF(leftTop.x() + dist, leftTop.y() + dist);

		QPointF decimalCenter = LatLonConvert::getInstance().screenToDecimal(center.toPoint());

		QString lat = LatLonConvert::getInstance().decimalLatToString(decimalCenter.x());
		QString lon = LatLonConvert::getInstance().decimalLonToString(decimalCenter.y());

		COORDINATE cn;

		cn.shape = Circle;
		cn.Via = via;
		cn.centerLat = lat;
		cn.centerLon = lon;
		cn.dist = dist/2;

		cn_list.append(cn);
	}

	ManualCoord * mc = new ManualCoord(this, cn_list, grpItem);
	connect(mc, SIGNAL(emitDone(QVector<COORDINATE>, DrawingMode, QGraphicsItem *)), this, SLOT(runDone(QVector<COORDINATE>, DrawingMode, QGraphicsItem *)));
	mc->show();

}

void DrawingWidget::runChange()
{

}
