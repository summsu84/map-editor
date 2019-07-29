/*  

    This file is part of the program Spherical  
    Copyright (C) 2007-2008  Andr� Schulz

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

#include <set>
#include <QtOpenGL>
//#include "vertex.h"
#include "edge.h"

using namespace std;

typedef struct
{
	float x;
	float y;
}CIRCLE_TEST;

#define M_PI 3.14

class geomGraph {
  
  // The sets of Vertices and Edges
  set<edge> edges;
  set<vertex> vertices;

  //test
  set<vertex> circle_vertices;
  //test
  set<vertex>::const_iterator itCircle;
  // Iterators for Vertices an Edges
  set<edge>::const_iterator itEdges;
  set<vertex>::const_iterator itVertices;



  // Id's for Vertices an Edges
  //int numEdge; 
  //int numVertex; 


 public:

  geomGraph();
  void init();
  void rotate(GLfloat &x, GLfloat &y, int angle);

  void addVertex(GLfloat ax,GLfloat ay,GLbyte ah);
  void deleteVertex(vertex v);
  void removeVertex(vertex v);
  void addEdge(vertex v1,vertex v2);
  void addEdge(GLfloat ax,GLfloat ay,GLfloat bx, GLfloat by);
  void addEdge(GLfloat ax,GLfloat ay,GLbyte ah,GLfloat bx, GLfloat by,GLbyte bh);
  void addEdgeOriented(GLfloat ax,GLfloat ay,GLbyte ah,GLfloat bx, GLfloat by,GLbyte bh,int o);
  void deleteEdge(vertex v1,vertex v2);
  int flipEdge(vertex v1,vertex v2);
  const edge* getFirstEdge();
  const edge* getNextEdge();
  const vertex* getFirstVertex();
  const vertex* getNextVertex();
  void moveVertex(vertex from,vertex to);
  void oppositeVertex(vertex v);
  int snap(GLfloat &xm,GLfloat &ym, GLfloat &zm,GLfloat threshold);

  void save(const char *s);
  void load(const char *s);
  void clear();


  void drawCircle(int k, double r, int h, float z);
  void addCircleVertex(vertex a);
  const vertex* getFirstCircleVertex();
  const vertex* getNextCircleVertex();


};
