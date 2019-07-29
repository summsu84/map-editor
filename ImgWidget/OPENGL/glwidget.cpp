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

#include <QtGui>
#include <QtOpenGL>
#include "const.h"
#include "gl2ps.h"

#include <cmath>

#include "glwidget.h"
//#include "sphereCanvas.h"

GLWidget::GLWidget(QWidget *parent)
     : QGLWidget(parent)
{

  psi=0;phi=0;
  mode=SPH_DRAW_MODE;
  snap=SPH_NO_SNAP;
  drawingOrientation=SPH_SHORT_EDGE;
  edgeStart=1;
  sphere.assignGraph(&graph);  
  setMouseTracking(1);
  glWidth=width();
  glHeight=height();

  setFocusPolicy(Qt::StrongFocus);
 // this->show();
  //  graph.addEdge(-1,1.1,2,2);
  //sphere.refreshArcs(1);
}

GLWidget::GLWidget(const QGLFormat & format, QWidget *parent)
     : QGLWidget(format, parent)
{

	qDebug()<<"[GLWidget] QGLFormat constructor is called..";
  psi=0;phi=0;
  mode=SPH_DRAW_MODE;
  snap=SPH_NO_SNAP;
  drawingOrientation=SPH_SHORT_EDGE;
  edgeStart=1;
  sphere.assignGraph(&graph);
  setMouseTracking(1);
  glWidth=width();
  glHeight=height();

  setFocusPolicy(Qt::StrongFocus);
  this->show();
  //  graph.addEdge(-1,1.1,2,2);
  //sphere.refreshArcs(1);
}

void GLWidget::exportFile()
{
  FILE *eps_out;
  int state = GL2PS_OVERFLOW, buffsize = 1024;


  
 QString saveFileName;
 saveFileName = QFileDialog::getSaveFileName(this,     tr("Export"), "", tr("Encapsulated Postscript (*.eps);;PDF (*.pdf)"));
 if (!saveFileName.isEmpty()) {
   eps_out= fopen(saveFileName.toLatin1(), "wb");
   GLint exportType=GL2PS_EPS;
   if (saveFileName.endsWith("pdf")) exportType=GL2PS_PDF;
   while(state == GL2PS_OVERFLOW){
     buffsize += 1024*1024;
     gl2psBeginPage(saveFileName.toLatin1(),"Spherical",0,exportType,
		    GL2PS_BSP_SORT,GL2PS_DRAW_BACKGROUND |GL2PS_USE_CURRENT_VIEWPORT,
		    GL_RGBA,0,NULL,0,0,0,buffsize,eps_out,saveFileName.toLatin1());
     gl2psPointSize(5);
     gl2psEnable(GL2PS_BLEND);
     gl2psLineWidth(1);
     
     // Export 
     glLoadIdentity();
     glPushMatrix();
     glRotatef(phi,1,0,0);
     glRotatef(psi,0,1,0); 
     // glBlendFunc(GL_ONE,GL_ZERO);  
     glEnable (GL_CLIP_PLANE0);	
     sphere.drawGraph();
     glDisable (GL_CLIP_PLANE0);
     glEnable (GL_CLIP_PLANE1);	
     gl2psEnable(GL2PS_LINE_STIPPLE);
     sphere.drawGraph();
     gl2psDisable(GL2PS_LINE_STIPPLE);     
     glDisable (GL_CLIP_PLANE1);
     glPopMatrix();

     GLUquadricObj *kreis;
     kreis= gluNewQuadric();
     gluQuadricDrawStyle(kreis,GLU_SILHOUETTE); 
     glColor3f(0,0,0);
     gl2psLineWidth(2);
     gluDisk(kreis,0,1,60,1);
     gl2psLineWidth(1);


     state=gl2psEndPage();
  }
  fclose(eps_out);
 }
}


void GLWidget::load()

{

 QString openFileName;
 openFileName = QFileDialog::getOpenFileName(this,
     tr("Open Spherical File"), "", tr("Spherical Files (*.sph);;All Files (*.*)"));
 if (!openFileName.isEmpty()) {
   fileName=openFileName;
   for (int i=openFileName.length()-1;i>=0;i--) 
     if (openFileName.at(i)==QChar('/') || openFileName.at(i)==QChar('\\'))
       {
	 openFileName.remove(0,i+1);
	 i=0;
       }
   graph.clear();
   graph.load((const char *)fileName.toLatin1());
   sphere.refreshArcs(1);
   emit newFileName(openFileName);
   updateGL();
 }
}

void GLWidget::save()

{
 if (fileName.isEmpty()) saveAs();
 else graph.save((const char *)fileName.toLatin1());
}


void GLWidget::saveAs()

{

 QString saveFileName;
 saveFileName = QFileDialog::getSaveFileName(this,
     tr("Save Spherical File"), fileName, tr("Spherical Files (*.sph);;All Files (*.*)"));
 if (!saveFileName.isEmpty()) {
   graph.save((const char *)saveFileName.toLatin1());
   fileName=saveFileName;
   for (int i=saveFileName.length()-1;i>=0;i--) 
    if (saveFileName.at(i)==QChar('/') || saveFileName.at(i)==QChar('\\'))
      {
       saveFileName.remove(0,i+1);
       i=0;
      }
   emit newFileName(saveFileName);
 }
}


void GLWidget::setPhi(int newPhi)
{
  phi=newPhi;
  updateGL(); 
}

void GLWidget::setPsi(int newPsi)
{
  psi=newPsi;
  updateGL(); 
}




void GLWidget::enableDrawMode()
{
  mode=SPH_DRAW_MODE;
}

void GLWidget::enableOrbitMode()
{
  mode=SPH_ORBIT_MODE;
}

void GLWidget::enableMoveMode()
{
  mode=SPH_MOVE_MODE;
}


void GLWidget::twist()
{
  graph.flipEdge(snapEdge.getA(),snapEdge.getB());
  snap=SPH_NO_SNAP;
  sphere.refreshArcs(1);
  updateGL();
}

void GLWidget::opposite()
{
  graph.oppositeVertex(snapVertex);
  snap=SPH_NO_SNAP;
  sphere.refreshArcs(1);
  updateGL();
}

void GLWidget::measure()
{

  GLfloat arcLength=snapEdge.measure();
  QString text=QString("Arc Length is %1.").arg((double)arcLength,0,'f',2) ;
  
  QMessageBox::StandardButton info;
  info = QMessageBox::information(this, tr("ArcLength"),text);
 
}


void GLWidget::deletePiece()
{
  if (snap==SPH_SNAPPED_VERTEX) {     
    graph.removeVertex(snapVertex);
    sphere.refreshArcs(1); 
  }    
  if (snap==SPH_SNAPPED_ARC) {
    graph.deleteEdge(snapEdge.getA(),snapEdge.getB());
    sphere.refreshArcs(1);     
  }      
  snap=SPH_NO_SNAP;
  updateGL();
}



void GLWidget::resetGraph()
{
 graph.clear();
 fileName.clear();
 emit newFileName(fileName);

 sphere.refreshArcs(1); 
 updateGL();
}


int GLWidget::getSnap()
{
  return snap;
}


void GLWidget::initializeGL()
 {    

  qDebug()<<"[GLWidget] initializeGL is called..";

  glShadeModel(GL_FLAT);
  glMatrixMode(GL_PROJECTION);
  glEnable (GL_DEPTH_TEST);
  glLoadIdentity();
  glOrtho(-1.1, 1.1, -1.1, 1.1, -1.1,1.1);
  glMatrixMode(GL_MODELVIEW);


  glClearColor(0.95,0.95,0.95,0);
  glPointSize(5);
  glEnable (GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glLineStipple(1,0x00FF);
  glDisable(GL_LINE_STIPPLE);

  GLdouble eqnfront[4]={0,0,-1,0};
  GLdouble eqnback[4]={0,0,1,0};
  glClipPlane (GL_CLIP_PLANE0, eqnfront);
  glClipPlane (GL_CLIP_PLANE1, eqnback);

  //glEnable(GL_LINE_SMOOTH);
  //glEnable(GL_POINT_SMOOTH);

  qDebug()<<"[GLWidget] initializeGL close..";
 }



void GLWidget::resizeGL(int w, int h)
{
  //  if (w<=h)  h=w; else w=h;
  glViewport(0, 0, (GLint)w, (GLint)h);
  glWidth=w;
  glHeight=h;
  //         glFrustum(...);
}


 void GLWidget::paintGL()
{

	 //qDebug()<<"[GLWidget] paintGL is called..";
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  
  // Drawing the graph
  glLoadIdentity();				//현재의 행렬을 단위 행렬로 만든다.
  glPushMatrix();					//원형태로 만든다.
  //glColor3f(1,0,0);
  glRotatef(phi,1,0,0);			//방향 설정
  glRotatef(psi,0,1,0); 			//방향 설정
  glBlendFunc(GL_ONE,GL_ZERO);  
  glEnable (GL_CLIP_PLANE0);		//클리핑 평면 사용
  sphere.drawGraph();
  glDisable (GL_CLIP_PLANE0);	//클리핑 평면 사용 해
  glEnable (GL_CLIP_PLANE1);		//클리핑 평면1 사용
  //gl2psEnable(GL2PS_LINE_STIPPLE);
  glEnable(GL_LINE_STIPPLE);	
  sphere.drawGraph();				//z 축 그리기??
  //gl2psEnable(GL2PS_LINE_STIPPLE);

  //createCircle(0,10,0);
  glDisable(GL_LINE_STIPPLE);
  glDisable (GL_CLIP_PLANE1);




  // drawing incident arcs of moved vertex
  if (moveVertex) {
    set<edge>::iterator ii;
    edge drawEdge;
   for (ii=incident.begin();ii!=incident.end();ii++){
     if ((*ii).getA()==movePos) drawEdge.set(mousePos,(*ii).getB());
     if ((*ii).getB()==movePos) drawEdge.set((*ii).getA(),mousePos);
     glColor3f(0.7,0.7,0.7);   
     sphere.drawEdgeOriented(drawEdge,ii->getOrientation());
     glColor3f(0,0,0);
     sphere.drawVertex(drawEdge.getA());
     sphere.drawVertex(drawEdge.getB());
   }
 }

  // Noch nicht fertig angegebenen Bogen zeichen
  if (edgeStart==0 && !(mousePos==startVertex))    {
    edge e;
	if (drawingOrientation==SPH_LONG_EDGE){
		qDebug()<<"Long..";
		e.set(startVertex,mousePos);
	}else {
		qDebug()<<"SHRT..";
		e.set(mousePos,startVertex);

	}
    glColor3f(0,0,0);
	glEnable (GL_CLIP_PLANE0);	
	sphere.drawEdgeOriented(e,drawingOrientation);
	glDisable (GL_CLIP_PLANE0);	
	glEnable (GL_CLIP_PLANE1);	
    glEnable(GL_LINE_STIPPLE);	
	sphere.drawEdgeOriented(e,drawingOrientation);
	glDisable(GL_LINE_STIPPLE);
	glDisable (GL_CLIP_PLANE1);
  }

  // Snapped Point
  if (snap==SPH_SNAPPED_VERTEX) {
    glPointSize(9);
    glColor3f(0.6,0.6,0.6);
    sphere.drawVertex(snapVertex);
    glPointSize(5);
  }
  // Snapped Arc
  if (snap==SPH_SNAPPED_ARC) {
    glLineWidth(5);
    glColor3f(1,0.6,0.6);
    sphere.drawEdge(snapEdge);
    glLineWidth(1);
  }


  glPopMatrix();
 
  // Kugel
  GLUquadricObj *kreis;
  kreis= gluNewQuadric();
  gluQuadricDrawStyle(kreis,GLU_SILHOUETTE); 
  glColor3f(0,0,0);
  glLineWidth(2);
  gluDisk(kreis,0,1,60,1);
  glLineWidth(1);

 
 
 

 glFlush();

 //qDebug()<<"[GLWidget] paintGL close..";
}

void GLWidget::mouseReleaseEvent( QMouseEvent * event ) 
{
  if (edgeStart==0 && event->button()==Qt::LeftButton ) {
    edgeStart=1;
    GLfloat xm, ym, zm;
    screen2Sphere(event->x(),event->y(),xm,ym,zm);
    graph.snap(xm,ym,zm,0.003);
    if (zm<0)  {
      graph.addEdgeOriented(startVertex.getX(),startVertex.getY(),
			    startVertex.getHemi(),-xm/zm,-ym/zm,-1,drawingOrientation);
    } 
    else {	  
      graph.addEdgeOriented(startVertex.getX(),startVertex.getY(),
			    startVertex.getHemi(),xm/zm,ym/zm,1,drawingOrientation);
    }  
    updateGL();
  }
  if (moveVertex) {
    moveVertex=0;
    set<edge>::iterator ii;
    edge drawEdge;
    // GLfloat xm, ym, zm;
    //screen2Sphere(event->x(),event->y(),xm,ym,zm);
    //graph.snap(xm,ym,zm,0.003);    
    //mousePos.setS(xm,ym,zm);
    for (ii=incident.begin();ii!=incident.end();ii++){
      if ((*ii).getA()==movePos) drawEdge.set(mousePos,(*ii).getB());
      if ((*ii).getB()==movePos) drawEdge.set((*ii).getA(),mousePos);
      if (ii->getOrientation()==drawEdge.getOrientation()) 
	graph.addEdge(drawEdge.getA(),drawEdge.getB());
      else graph.addEdge(drawEdge.getB(),drawEdge.getA());
    }
    snapVertex.set(mousePos);
    snap=SPH_SNAPPED_VERTEX;
    updateGL();
  }
}



void GLWidget::mousePressEvent(QMouseEvent *event)
{
  mouseClicked = event->pos();

  GLfloat xm, ym, zm;
  screen2Sphere(event->x(),event->y(),xm,ym,zm);
  if (event->button()==Qt::LeftButton && mode==SPH_DRAW_MODE) {
    graph.snap(xm,ym,zm,0.003);
    if (edgeStart==1) { //1st Vertex
      edgeStart=0;
      if (zm<0) {
	startVertex.set(-xm/zm,-ym/zm,-1);
	graph.addVertex(-xm/zm,-ym/zm,-1);
      } 
      else {
	startVertex.set(xm/zm,ym/zm,1);
	graph.addVertex(xm/zm,ym/zm,1);
      }
    }			
    // Setzen der Koordinate zum Zeichnen des aktuellen Bogens vorm loslassen der Mouse
    mousePos.set(startVertex.getX(),startVertex.getY(),
		 startVertex.getHemi());    
  }  

  if (event->button()==Qt::LeftButton && mode==SPH_MOVE_MODE) {
    moveVertex=1;
    graph.snap(xm,ym,zm,0.003);
    movePos.setS(xm,ym,zm);
    mousePos.setS(xm,ym,zm);
    incident.clear();
    const edge *akt;
    edge *copy;
    for (akt=graph.getFirstEdge();akt;akt=graph.getNextEdge()) 
      if (akt->getA()==movePos || akt->getB()==movePos) {
	copy = new edge;
	copy->set(akt->getA(),akt->getB());
	incident.insert(*copy);
      }  
    set<edge>::iterator ii;
    for (ii=incident.begin();ii!=incident.end();ii++)
      graph.deleteEdge((*ii).getA(),(*ii).getB());   
  }


}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

  // Snapping

  if (event->button()== Qt::NoButton) {
    GLfloat xm, ym, zm;
    screen2Sphere(event->x(),event->y(),xm,ym,zm);
    if (graph.snap(xm,ym,zm,0.003)) { 
      snap=SPH_SNAPPED_VERTEX;
      snapVertex.setS(xm,ym,zm);
      updateGL();
    } 
    else {
      snap=SPH_NO_SNAP;      
      const edge *akt;
      vertex temp;
      temp.setS(xm,ym,zm);
      for (akt=graph.getFirstEdge();akt && snap!=SPH_SNAPPED_ARC;akt=graph.getNextEdge()) 
	if (abs(akt->pointDistance(temp))<0.02){
	  snap=SPH_SNAPPED_ARC;
	  snapEdge.set(akt->getA(),akt->getB());
	}
      updateGL();
    }   
  }

  // Orbit rotate
  
  if ((event->buttons() & Qt::MidButton) || 
      (mode==SPH_ORBIT_MODE && (event->buttons() & Qt::LeftButton))) {
    int dx = event->x() - mouseClicked.x();
    int dy = event->y() - mouseClicked.y();

    phi=(int)(phi - ( dy)) % 360;
    psi=(int)(psi - ( dx)) % 360;
    emit phiChanged((int)phi);
    emit psiChanged((int)psi);
    snap=SPH_NO_SNAP;
    updateGL();
  } 

  // Arc drawing

  if (edgeStart==0) {
	  //qDebug()<<"arc drawing..";
    GLfloat xm, ym, zm;
    screen2Sphere(event->x(),event->y(),xm,ym,zm);
    graph.snap(xm,ym,zm,0.003);    
    mousePos.setS(xm,ym,zm);
    updateGL();
  }

  // Vertex movement

  if (moveVertex) {
    GLfloat xm, ym, zm;
    screen2Sphere(event->x(),event->y(),xm,ym,zm);
    graph.snap(xm,ym,zm,0.003);    
    mousePos.setS(xm,ym,zm);
    updateGL();
  }
  
  mouseClicked = event->pos();

}

void GLWidget::keyPressEvent(QKeyEvent *event)
 {
	switch (event->key()) {
	case Qt::Key_Shift:
         drawingOrientation=SPH_LONG_EDGE;
		  updateGL();
		 break;
     default:
         QGLWidget::keyPressEvent(event);
     }
 }

void GLWidget::keyReleaseEvent(QKeyEvent *event)
 {
	switch (event->key()) {
	case Qt::Key_Shift:
         drawingOrientation=SPH_SHORT_EDGE;
		  updateGL();
		 break;
     default:
         QGLWidget::keyReleaseEvent(event);
     }
 }



void GLWidget::screen2Sphere(int px, int py,GLfloat &xs,GLfloat &ys,GLfloat &zs)
{
 GLfloat  xk=2*(float)px/glWidth-1;
 GLfloat  yk=2*(float)py/glHeight-1;
 xk=xk*1.1;
 yk=yk*1.1;
  
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glRotatef(psi,0,1,0);
 glRotatef(-phi,1,0,0);

 // arrays to hold matrix information
 GLdouble m[16];
 glGetDoublev(GL_MODELVIEW_MATRIX, m);	

 // get 3D coordinates based on window coordinates
 ys=-1*( m[1]*xk +m[5]*yk+ m[9]*sqrt((double)(1-xk*xk-yk*yk)));
 zs=-1*( m[2]*xk +m[6]*yk+ m[10]*sqrt((double)(1-xk*xk-yk*yk)));
 xs= m[0]*xk +m[4]*yk+ m[8]*sqrt((double)(1-xk*xk-yk*yk));
}



void GLWidget::createCircle(int k, int r, int h)
{

	qDebug()<<"[GLWidget] createCircle is called..";
	CIRCLE_TEST circle;


	glBegin(GL_POINT);

	glColor3f(0,0,0);
/*	for (int i = 0; i < 180; i++)
	{
		circle.x = r * cos(i) - h;
		circle.y = r * sin(i) + k;
		glVertex3f(circle.x + k,circle.y - h,0);

		circle.x = r * cos(i + 0.1) - h;
		circle.y = r * sin(i + 0.1) + k;
		glVertex3f(circle.x + k,circle.y - h,0);
	}*/
	glVertex3f(1,1,1);
	glEnd();

}
