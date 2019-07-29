/*  

    This file is part of the program Spherical  
    Copyright (C) 2007-2008  André Schulz

    Spherical is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Spherical is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
    License for more details.

    You should have received a copy of the GNU General Public License
    along with Spherical; if not, you can find it at
    "http://www.gnu.org/copyleft/gpl.html", or write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "sphereCanvas.h"

class QString;

class GLWidget : public QGLWidget
 {
   Q_OBJECT

 public:
   GLWidget(QWidget *parent = 0);
   GLWidget(const QGLFormat & format, QWidget *parent = 0);
   int getSnap();
 public slots:
   void load();
   void save();
   void saveAs();
   void exportFile();
   void setPhi(int newPhi);
   void setPsi(int newPsi);
   void enableDrawMode();
   void enableOrbitMode();
   void enableMoveMode();
   void twist();
   void opposite();
   void measure();
   void deletePiece();
   void resetGraph();
   void createCircle(int k, int r, int h);
 signals:
     void phiChanged(int newPhi);
     void psiChanged(int newPhi);
     void newFileName(QString name);



 protected:
   void initializeGL();
   void resizeGL(int w, int h);
   void paintGL();
   void mouseReleaseEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);


 private:
   void screen2Sphere(int px, int py,GLfloat &xs,GLfloat &ys,GLfloat &zs);

   QString fileName;
   geomGraph graph;
   sphereCanvas sphere;
   GLfloat phi,psi;
   QPoint mouseClicked;
   int moveVertex,mode,snap,edgeStart,drawingOrientation;
   int glWidth,glHeight;
   edge snapEdge;
   set<edge> incident; 
   vertex movePos,mousePos,snapVertex,startVertex;

 };

 #endif
