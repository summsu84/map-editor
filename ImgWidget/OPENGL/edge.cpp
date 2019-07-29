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

#include "edge.h"
#include <math.h>

static double PI = 3.141592653589793238462643; 

GLfloat edge::pointDistance(vertex v) const
  // for approximation !!
{

  // clac Normal vector
  
  GLfloat nx= pointA.getSY()*pointB.getSZ()-pointA.getSZ()*pointB.getSY();
  GLfloat ny= pointA.getSZ()*pointB.getSX()-pointA.getSX()*pointB.getSZ();
  GLfloat nz= pointA.getSX()*pointB.getSY()-pointA.getSY()*pointB.getSX();

  GLfloat scalar=((pointA.getSX()-v.getSX())*(pointB.getSX()-v.getSX()))+
		  ((pointA.getSY()-v.getSY())*(pointB.getSY()-v.getSY()))+
		   ((pointA.getSZ()-v.getSZ())*(pointB.getSZ()-v.getSZ()));

  if (scalar>0 && getOrientation()==1) return 1;
  if (scalar<0 && getOrientation()==0) return 1;		    
  return (nx*v.getSX()+ny*v.getSY()+nz*v.getSZ())/sqrt(nx*nx+ny*ny+nz*nz);
}


int  edge::getOrientation() const

{
  if (pointA.larger(pointB)) return 1;
  return 0;
}

GLfloat edge::measure()
{

  GLfloat x1= pointA.getSX();
  GLfloat y1= pointA.getSY();
  GLfloat z1= pointA.getSZ();

  GLfloat x2= pointB.getSX();
  GLfloat y2= pointB.getSY();
  GLfloat z2= pointB.getSZ();


  GLfloat w=acos((x1*x2+y1*y2+z1*z2)/
    (sqrt(x1*x1+y1*y1+z1*z1)*sqrt(x2*x2+y2*y2+z2*z2)));

  w=(float)180/PI*w;
  if (getOrientation()==0) w=360-w;
  return w;
}
