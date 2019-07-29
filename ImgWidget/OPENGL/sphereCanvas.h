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

#include "geomGraph.h"


class sphereCanvas {
  geomGraph *g;
  GLuint arcList;
 public:
 // umschreiben assign zum Konstruktor
  void assignGraph(geomGraph* graph);
  void refreshArcs(int style);
  void drawGraph();

  void drawVertex(const vertex v);
  void drawEdge(const edge e);
  void drawEdgeOriented(const edge e,int o);

  void drawCircle(int k, int r, int h);

};
