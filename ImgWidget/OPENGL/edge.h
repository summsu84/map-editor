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


#include <QtOpenGL>
#include "vertex.h"

class edge {
  int num;
  vertex pointA,pointB;
  //  style: edgestyle;
  friend bool operator<(edge lhs,edge rhs)
  {if ((lhs.pointA==rhs.pointA)) 
    return (lhs.pointB<rhs.pointB); 
    else return (lhs.pointA<rhs.pointA);}
  public:
  void  set(vertex a, vertex b) 
  {pointA.set(a.getX(),a.getY(),a.getHemi());
   pointB.set(b.getX(),b.getY(),b.getHemi());};
  vertex getA() const {return pointA;};
  vertex getB() const {return pointB;};
  GLfloat pointDistance(vertex v) const;
  int getOrientation() const;
  GLfloat measure();
};


  
