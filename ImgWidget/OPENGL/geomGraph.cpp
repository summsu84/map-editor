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

#include "geomGraph.h"
#include <iostream>
#include <fstream>


using namespace std;



geomGraph::geomGraph()
{

	init();

  itEdges=edges.begin();
  itVertices=vertices.begin();
  itCircle = circle_vertices.begin();
}

//test
void geomGraph::init()
{

	qDebug()<<"init called..";
  vertex center;
  vertex x1;
  vertex x2;
  x1.setName("X1");
  x2.setName("X2");

  vertex y1;
  vertex y2;
  y1.setName("Y1");
  y2.setName("Y2");

  vertex z1;
  vertex z2;

  z1.setName("Z1");
  z2.setName("Z2");

  center.set(0,0,-1);
//  a.set(1.5, 0, 1);
//  b.set(-1.5, 0, 1);

  z1.setS(0,0,-0.99);
  z2.setS(0,0,0.99);

  y1.setS(0, -0.99, 0.01);
  y2.setS(0, 0.99, 0.01);


  x1.setS(-0.99, 0, -0.01);
  x2.setS(0.99, 0, -0.01);

  //vertices.insert(center);
  vertices.insert(x1);
  vertices.insert(x2);
  vertices.insert(y1);
  vertices.insert(y2);
  vertices.insert(z1);
  vertices.insert(z2);

  //addEdge(a,b);
  addEdge(x1, x2);
  addEdge(y1, y2);


  //30
  GLfloat x = 0.99;
  GLfloat y = 0;

  rotate(x, y, 30);

  qDebug()<<"rx : "<<x<<", y : "<<y;

  vertex x1_30;
  vertex x2_30;
  vertex x3_30;
  vertex x4_30;

  x1_30.setS(x, y, -0.01);
  x2_30.setS(-x, y, -0.01);
  x3_30.setS(x, -y, -0.01);
  x4_30.setS(-x, -y, -0.01);

  //x2_30.setS(x-4  , y, 0.01);

  vertices.insert(x1_30);
  vertices.insert(x2_30);
  vertices.insert(x3_30);
  vertices.insert(x4_30);

  addEdge(x1_30, x4_30);
  addEdge(x2_30, x3_30);

  //60
  x = 0.99;
  y = 0;

  rotate(x, y, 60);

	qDebug()<<"rx : "<<x<<", y : "<<y;

	vertex x1_60;
	vertex x2_60;
	vertex x3_60;
	vertex x4_60;

	x1_60.setS(x, y, -0.01);
	x2_60.setS(-x, y, -0.01);
	x3_60.setS(x, -y, -0.01);
	x4_60.setS(-x, -y, -0.01);

	//x2_30.setS(x-4  , y, 0.01);

	vertices.insert(x1_60);
	vertices.insert(x2_60);
	vertices.insert(x3_60);
	vertices.insert(x4_60);

	addEdge(x1_60, x4_60);
	addEdge(x2_60, x3_60);

  /*vertices.insert(x2_30);
  addEdge(x1_30, x2_30);*/

	/*for(int i = 1 ; i < 10 ; i++){
		this->drawCircle(0,1+i,0, 1 - (0.1 * i));
	}*/

	this->drawCircle(0, 10, 0, 0.001);						//0도
	//qDebug()<<"Cos 30 : "<<cos(M_PI/180*30);
	this->drawCircle(0, 10*cos(M_PI/180*10),0,0.17);
	this->drawCircle(0, 10*cos(M_PI/180*20),0,0.27);
	this->drawCircle(0, 10*cos(M_PI/180*30),0,0.47);
	this->drawCircle(0, 10*cos(M_PI/180*40),0,0.57);
	this->drawCircle(0, 10*cos(M_PI/180*50),0,0.67);
	this->drawCircle(0, 10*cos(M_PI/180*60),0,0.82);
	this->drawCircle(0, 10*cos(M_PI/180*70),0,0.92);
	this->drawCircle(0, 10*cos(M_PI/180*80),0,0.92);
	this->drawCircle(0, 10*cos(M_PI/180*90),0,0.99);
}

void geomGraph::rotate(GLfloat &x, GLfloat &y, int angle)
{

	float u = 0;
	float v = 0;

	GLfloat nx = (((x - u) * cos(M_PI/180*angle) + (y - v)*sin(M_PI/180*angle)) + u );
	GLfloat ny = (((x - u) * -sin(M_PI/180*angle) + (y - v)*cos(M_PI/180*angle)) + v );

	x = nx;
	y = ny;

}


void geomGraph::addVertex(GLfloat ax,GLfloat ay,GLbyte ah)
{

 vertex a;


 a.set(ax,ay,ah);
 vertices.insert(a);
}



void geomGraph::deleteVertex(vertex v)
{
  set<vertex>::iterator old=vertices.find(v);
  if (old!=vertices.end()) vertices.erase(old);
}


// remove Vertex takes also the adjacent edges out

void geomGraph::removeVertex(vertex v)
{
  set<edge> adj;

  const edge *akt;
  for (akt=getFirstEdge();akt;akt=getNextEdge())   
    if (akt->getA()==v || akt->getB()==v) adj.insert(*akt);

  set<edge>::iterator ii;

  for(ii=adj.begin();ii!=adj.end();ii++) {
    edges.erase(edges.find(*ii));
    deleteVertex(ii->getA());
    deleteVertex(ii->getB());
  }
  // any edges with missing vertex edges

  for (akt=getFirstEdge();akt;akt=getNextEdge())
    {
      set<vertex>::iterator knoten1=vertices.find(akt->getA());
      if (knoten1==vertices.end()) vertices.insert(akt->getA());
      set<vertex>::iterator knoten2=vertices.find(akt->getB());
      if (knoten2==vertices.end()) vertices.insert(akt->getB());
    }
}




// add the edge and the vertices if new

void geomGraph::addEdge(vertex v1,vertex v2)
{
  addEdge(v1.getX(),v1.getY(),v1.getHemi(),
	  v2.getX(),v2.getY(),v2.getHemi());
}


void geomGraph::addEdge(GLfloat ax,GLfloat ay,GLfloat bx, GLfloat by)

{
  addEdge(ax,ay,1,bx,by,1);
}  


void geomGraph::addEdge(GLfloat ax,GLfloat ay,GLbyte ah,GLfloat bx, GLfloat by,GLbyte bh)

{
  vertex a,b;
  edge     e;

 

  a.set(ax,ay,ah);
  vertices.insert(a);

  b.set(bx,by,bh);
  vertices.insert(b);

  e.set(a,b);

  edges.insert(e);
}  

void geomGraph::addEdgeOriented(GLfloat ax,GLfloat ay,GLbyte ah,GLfloat bx, GLfloat by,GLbyte bh,int o)
{
  vertex a,b;
  edge     e;

  a.set(ax,ay,ah);
  vertices.insert(a);

  b.set(bx,by,bh);
  vertices.insert(b);

  if (a.larger(b) && o) e.set(a,b); 
  else if (a.larger(b) && !o) e.set(b,a); 
  else if (!a.larger(b) && o) e.set(b,a); 
  else e.set(a,b);

  edges.insert(e);

}

void geomGraph::deleteEdge(vertex v1,vertex v2)
{
	edge e;
	e.set(v1,v2);

	set<edge>::iterator eold=edges.find(e);
	if (eold!=edges.end()) edges.erase(eold);
	// vertexupdate !
	deleteVertex(v1);
	deleteVertex(v2);

	const edge *akt;
	for (akt=getFirstEdge();akt;akt=getNextEdge())
	  {
	    set<vertex>::iterator knoten1=vertices.find(akt->getA());
	    if (knoten1==vertices.end()) vertices.insert(akt->getA());
	    set<vertex>::iterator knoten2=vertices.find(akt->getB());
	    if (knoten2==vertices.end()) vertices.insert(akt->getB());
	  }

}



int geomGraph::flipEdge(vertex v1,vertex v2)

{
	edge e,e1,e2;
	e1.set(v1,v2);
	e2.set(v2,v1);


	set<edge>::iterator eold1=edges.find(e1);
	if (eold1!=edges.end()) 
	  {
	    edges.erase(eold1);
	    e.set(v2,v1);
	    edges.insert(e);
	    return 1;
	  }

	set<edge>::iterator eold2=edges.find(e2);
	if (eold2!=edges.end()) 
	  {
	    edges.erase(eold2);
	    e.set(v1,v2);
	    edges.insert(e);
	    return 1;
	  }
	return 0;
}


const edge* geomGraph::getFirstEdge()

{
  itEdges=edges.begin();
  if (itEdges==edges.end()) return NULL;
  return  &(*itEdges);

}

const edge* geomGraph::getNextEdge()

{
  //  set<edge>::const_iterator   tempedge=itEdges++;
  if (++itEdges==edges.end()) return NULL;
  //  itEdges++;
  return &(*itEdges);
}

const vertex* geomGraph::getFirstVertex()

{
  itVertices=vertices.begin();
  if (itVertices==vertices.end()) return NULL;
  return &(*itVertices);
}

const vertex* geomGraph::getNextVertex()

{
  //  set<vertex>::const_iterator   tempVertex=itVertices++;
  if (++itVertices==vertices.end()) return NULL;
  //  itVertices++;
  return  &(*itVertices);

}



void geomGraph::moveVertex(vertex from,vertex to)

{

  const edge *akt;


  for (akt=getFirstEdge();akt;akt=getNextEdge())  {
    if (akt->getA()==from) 	
      const_cast<edge*>(akt)->set(to,akt->getB());
    if (akt->getB()==from) 
      const_cast<edge*>(akt)->set(akt->getA(),to);
  }

  const vertex *aktVertex;

  for (aktVertex=getFirstVertex();aktVertex;aktVertex=getNextVertex())  
    if (*aktVertex==from) const_cast<vertex*>(aktVertex)->set(to);

}


void geomGraph::oppositeVertex(vertex v)
{
  const edge *akt;
  vertex w;
  w.setAsOpposite(v); 

  for (akt=getFirstEdge();akt;akt=getNextEdge())  {
    if (akt->getA()==v) 	
      const_cast<edge*>(akt)->set(akt->getB(),w);
    if (akt->getB()==v) 
      const_cast<edge*>(akt)->set(w,akt->getA());
  }

  const vertex *aktVertex;

  for (aktVertex=getFirstVertex();aktVertex;aktVertex=getNextVertex())  
    if (*aktVertex==v) const_cast<vertex*>(aktVertex)->set(w);



}


int geomGraph::snap(GLfloat &xm,GLfloat &ym, GLfloat &zm,GLfloat threshold)
{

  vertex a;

  a.setS(xm,ym,zm);
  const vertex *akt;

  for (akt=getFirstVertex();akt;akt=getNextVertex())
  {
   if (a.euklid(*akt)<threshold)
	{
	  xm= akt->getSX();
	  ym= akt->getSY();
	  zm= akt->getSZ();
	  return 1;
	}
  };

  return 0;
}


void geomGraph::save(const char *s)

{
  ofstream fp_out;
  fp_out.open(s, ios::out);
  fp_out << "SphereFile" << endl;
  const edge *akt;
    for (akt=getFirstEdge();akt;akt=getNextEdge())
      {
	fp_out << akt->getA().getX() << endl;
	fp_out << akt->getA().getY() << endl;
	fp_out << (GLfloat)akt->getA().getHemi() << endl;
	fp_out << akt->getB().getX() << endl;
	fp_out << akt->getB().getY() << endl;
	fp_out << (GLfloat)akt->getB().getHemi() << endl;
      }
fp_out.close(); 


}


void geomGraph::load(const char *s)

{
  
  char signature[8]; 

  GLfloat x1,x2,y1,y2;
  GLfloat  h1,h2;

  ifstream fp_in;

  fp_in.open(s, ios::in);
  fp_in >> signature;
  if (!strcmp(signature,"SphereFile")) 
    {
      while( fp_in >> x1) 
		{
	   // fp_in >> x1;
	    fp_in >> y1;
	    fp_in >> h1;
	    fp_in >> x2;
	    fp_in >> y2;
	    fp_in >> h2;
	    
		addEdge(x1,y1,h1,x2,y2,h2);
	    		}
	}
  fp_in.close(); 
}

void geomGraph::clear()
{
  vertices.clear();
  edges.clear();
}


void geomGraph::drawCircle(int k, double r, int h, float z)
{
	qDebug()<<"drawCircle is called.."<<z;
	CIRCLE_TEST circle;
    //glBegin(GL_LINES);
	for (int i = 0; i < 180; i++)
	{
		circle.x = r * cos(i) - h;
		circle.y = r * sin(i) + k;
		glVertex3f((circle.x + k) / 10 ,(circle.y - h) / 10, z);

		vertex tmp;
		tmp.setS((circle.x + k) / 10, (circle.y - h) / 10, z);
		addCircleVertex(tmp);
	}

}


//test
void geomGraph::addCircleVertex(vertex a)
{
  circle_vertices.insert(a);
}


const vertex* geomGraph::getFirstCircleVertex()

{
  itCircle=circle_vertices.begin();
  if (itCircle==circle_vertices.end()) return NULL;
  return &(*itCircle);
}


const vertex* geomGraph::getNextCircleVertex()

{
  //  set<vertex>::const_iterator   tempVertex=itVertices++;
  if (++itCircle==circle_vertices.end()) return NULL;
  //  itVertices++;
  return  &(*itCircle);

}
