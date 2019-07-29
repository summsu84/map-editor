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

#include "vertex.h"
#include "math.h"

void vertex::set(vertex v)

{
  set(v.getX(),v.getY(),v.getHemi());
}

void vertex::setAsOpposite(vertex v)

{
  set(-v.getX(),-v.getY(),-v.getHemi());
}


int vertex::larger(vertex compare) const

{
 

  
  GLfloat x1=sx;
  GLfloat y1=sy;
  GLfloat z1=sz;

  
  GLfloat x2=compare.getSX();
  GLfloat y2=compare.getSY();
  GLfloat z2=compare.getSZ();

  GLfloat w=acos((x1*x2+y1*y2+z1*z2)/
    (sqrt(x1*x1+y1*y1+z1*z1)*sqrt(x2*x2+y2*y2+z2*z2)));
  if (w>0) w=1; else w=0;
  
  if (((x1*y2-y1*x2)<0) || (((x1*y2-y1*x2)==0) && (x1>x2))) return (int)1-w;
  return (int)(w);
}

GLfloat vertex::euklid(vertex compare) const

{
    
  
  GLfloat x2=compare.getSX();
  GLfloat y2=compare.getSY();
  GLfloat z2=compare.getSZ();

  return (sx-x2)*(sx-x2)+(sy-y2)*(sy-y2)+(sz-z2)*(sz-z2);

}


void vertex::set(GLfloat setx,GLfloat sety,GLbyte sethemi) 

{
  x=setx;
  y=sety;
  hemi=sethemi;
  
  GLfloat   lambda=sqrt(1/(x*x+y*y+1));  

  //3차원 좌표평면으로 변환
  sx=lambda *x;
  sy=lambda *y;
  sz=lambda*hemi;
 
}

void vertex::setS(GLfloat setx,GLfloat sety,GLfloat setz)

{
  sx=setx;
  sy=sety;
  sz=setz;


  if (setz<0)  {
    x=-setx/setz;
    y=-sety/setz;
    hemi=-1;
  } else {
    x=setx/setz;
    y=sety/setz;
    hemi=1; 
  } 
}

//added
void vertex::convertZ()
{
	sz = sz * -1;
}

void vertex::test()
{
	sz = 0.99;
}

void vertex::setName(char * name)
{
	//memset(0, this->name, sizeof(this->name));
	strcpy(this->name, name);
}
