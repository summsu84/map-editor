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

#include "sphereCanvas.h"
#include <cmath>
#include <QtOpenGL>
#include <iostream>


double PI = 3.141592653589793238462643; 

GLfloat winkel(GLfloat x1,GLfloat y1,GLfloat z1,
	       GLfloat x2,GLfloat y2,GLfloat z2)

{
  GLfloat w=acos((x1*x2+y1*y2+z1*z2)/
    (sqrt(x1*x1+y1*y1+z1*z1)*sqrt(x2*x2+y2*y2+z2*z2)));
  
  if ((x1*y2-y1*x2)<0) w=w*-1;
  if (((x1*y2-y1*x2)==0) && (x1>x2)) w=w*-1;
  return w/(2*PI)*360;
}




void sphereCanvas::assignGraph(geomGraph* graph)

{
  g=graph;
  arcList = glGenLists(1);
}


//점 그리기
void sphereCanvas::drawGraph()

{
   

  //  glCallList(arcList);

  const vertex *aktVertex;
  const edge   *aktEdge;
  
  //test
  const vertex *aktCircle;

  //glNewList(arcList,GL_COMPILE);	

  //Edge는 점과 점사이의 선을 의미한다. 아래 소스는 마우스를 이동한뒤 릴리즈 했을 때 라인을 그린다.
  glColor3f(1,0,0);
  aktEdge=g->getFirstEdge();
  while (aktEdge)  {  
    drawEdge(*aktEdge);
    aktEdge=g->getNextEdge();
  }

  // to increase speed we draw all vertices without calling drawVertex()
  // in red color
   
  //마우스를 클릭했을 때 정점을 그린다.
  glColor3f(0,1,0);
  glBegin(GL_POINTS);				//GL_POINTS는 정점을 그린다는 의미
  aktVertex=g->getFirstVertex();
  while (aktVertex)  {
           glVertex3f(aktVertex->getSX(),aktVertex->getSY(),aktVertex->getSZ()); //점을 그린다.
           //qDebug()<<"X : "<<aktVertex->getSX()<<", Y : "<<aktVertex->getSY()<<", Z : "<<aktVertex->getSZ();
	   aktVertex=g->getNextVertex();
  }
  //glVertex3f(0,0,0);
  /*glVertex3f(1,0,0);	//x 1
  glVertex3f(0,1,0);  //y 1
  glVertex3f(0,0,1);  // z 1
  glVertex3f(0,-1,0);
*/


   glColor3f(0,1,1);
	glBegin(GL_POINTS);				//GL_POINTS는 정점을 그린다는 의미
	aktCircle=g->getFirstCircleVertex();


	while (aktCircle)  {
	glVertex3f(aktCircle->getSX(),aktCircle->getSY(),aktCircle->getSZ()); //점을 그린다.
	//qDebug()<<"X : "<<aktVertex->getSX()<<", Y : "<<aktVertex->getSY()<<", Z : "<<aktVertex->getSZ();
	aktCircle=g->getNextCircleVertex();
	}


  glEnd();
}


void sphereCanvas::refreshArcs(int style)

{
  const vertex *aktVertex;
  const edge   *aktEdge;
  
  glNewList(arcList,GL_COMPILE);	

  glColor3f(0,0,0);
  aktEdge=g->getFirstEdge();
  while (aktEdge)  {  
    drawEdge(*aktEdge);
    aktEdge=g->getNextEdge();
  }

  // to increase speed we draw all vertices without calling drawVertex()
  // in red color
   
  glColor3f(0,0,0);	 
  glBegin(GL_POINTS);
  aktVertex=g->getFirstVertex();
  while (aktVertex)  {
           glVertex3f(aktVertex->getSX(),aktVertex->getSY(),aktVertex->getSZ());
	   aktVertex=g->getNextVertex();
  }
  glEnd();
 
  glEndList();
   
  
}


//정점을 그린다.
void sphereCanvas::drawVertex(const vertex v)

{
  glBegin(GL_POINTS);
  qDebug()<<" x : "<<v.getSX()<<", y : "<<v.getSY()<<", z : "<<v.getSZ();
  glVertex3f(v.getSX(),v.getSY(),v.getSZ());
  glEnd(); 
}


//Edge를 그린다.
void sphereCanvas::drawEdge(const edge e)

{

 
  const vertex pointA=e.getA();
  const vertex pointB=e.getB();

  
  GLfloat x1=pointA.getSX();
  GLfloat y1=pointA.getSY();
  GLfloat z1=pointA.getSZ();

  GLfloat x2=pointB.getSX();
  GLfloat y2=pointB.getSY();
  GLfloat z2=pointB.getSZ();
  /*qDebug()<<"===============================================================================";
  qDebug()<<"ex1 :"<<x1<<", ey1 : "<<y1<<", ez1 : "<<z1<<", ex2 :"<<x2<<", ey2 : "<<y2<<", ez2 : "<<z2;
  qDebug()<<"===============================================================================";*/
  //  glColor3f(1,1,1);


  //degeneriert?

  if (x1==-x2 && y1==-y2 && z1==-z2) x2=x2+0.001;


  // Test Kreis durch punkte 

  GLUquadricObj *kreis;


  // Schnittgerade berechen 
  GLfloat xs=x1*z2-x2*z1;
  GLfloat ys=z2*y1-y2*z1;
  GLfloat zs=0;

 
  // Schnittwinkel berechnen
  GLbyte orientation=1;
  if (winkel(x1,y1,z1,x2,y2,z2)<0) orientation=-1;

  GLfloat angle;
  angle=winkel(0,0,1,xs,ys,-(x1*y2-y1*x2));
  if (angle>0) {
    xs=-xs,ys=-ys;};

  
  kreis= gluNewQuadric();
  gluQuadricDrawStyle(kreis,GLU_SILHOUETTE); 

  glPushMatrix();
  
  glRotatef(angle,xs,ys,zs);
  GLfloat winkelA2=(winkel(xs,ys,zs,x1,y1,z1));
  GLfloat winkel1=(winkel(0,1,0,xs,ys,zs));
  GLfloat winkelB2=(winkel(xs,ys,zs,x2,y2,z2));
  GLfloat winkelA=-winkel1+orientation*winkelA2;
  GLfloat winkelB=-winkel1+orientation*winkelB2;
  if (winkelB<0) winkelB=winkelB+360;
  GLfloat arcLength=(int)(winkelB-winkelA) % 360;
  if (orientation==-1)  arcLength=(int)(-360+arcLength) %360;
  if (abs(arcLength)<30)  gluPartialDisk(kreis,1,1,4,2,winkelA,arcLength);
  else  gluPartialDisk(kreis,1,1,abs(arcLength/6),2,winkelA,arcLength);

  gluDeleteQuadric(kreis);
  
  glPopMatrix();
  

}

//test added
void sphereCanvas::drawCircle(int k, int r, int h)
{
	qDebug()<<"drawCircle is called..";
	CIRCLE_TEST circle;
    //glBegin(GL_LINES);
     for (int i = 0; i < 180; i++)
     {
     circle.x = r * cos(i) - h;
     circle.y = r * sin(i) + k;
     glVertex3f((circle.x + k) / 10 ,(circle.y - h) / 10,0.01);

      vertex tmp;
      //qDebug()<<"x : "<<(circle.x + k) / 10 <<", y : "<<(circle.y - h) / 10;
      tmp.setS((circle.x + k) / 10, (circle.y - h) / 10, 0.1);
      drawVertex(tmp);

    /* circle.x = r * cos(i + 0.1) - h;
     circle.y = r * sin(i + 0.1) + k;
     glVertex3f(circle.x + k,circle.y - h,0.01);*/
     }
     //glEnd();
}

void sphereCanvas::drawEdgeOriented(const edge e,int o)

{
  if (e.getOrientation()==o) drawEdge(e);
  else
    {
      vertex v1=e.getA();
      vertex v2=e.getB();
      edge e2;
      e2.set(v2,v1);
      drawEdge(e2);
    }

}
