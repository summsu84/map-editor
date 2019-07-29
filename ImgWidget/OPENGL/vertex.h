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

#include <QtOpenGL>


class vertex {
	char name[20];	//added
  int num;
  GLfloat x;
  GLfloat y;
  GLbyte  hemi;   
  GLfloat sx;
  GLfloat sy;
  GLfloat sz; 
  //  vertexstyle style;
  friend bool operator<(vertex lhs,vertex rhs)
  {if (lhs.x==rhs.x && lhs.y==rhs.y) return (lhs.hemi<rhs.hemi); 
   if (lhs.x==rhs.x && lhs.y!=rhs.y) return (lhs.y<rhs.y); 
   return (lhs.x<rhs.x);}
  friend bool operator==(vertex lhs,vertex rhs)
  {return (((lhs.x==rhs.x) && (lhs.y==rhs.y) && (lhs.hemi==rhs.hemi)) ||
	   ((lhs.sx==rhs.sx) && (lhs.sy==rhs.sy) && (lhs.sz==rhs.sz)));}
public:
  void setName(char * name);
  char * getName() {return name;}
  void set(vertex v);
  void setAsOpposite(vertex v);
  int larger(vertex compare) const;
  GLfloat euklid(vertex compare) const;
  void set(GLfloat setx,GLfloat sety,GLbyte sethemi);
  void setS(GLfloat setx,GLfloat sety,GLfloat setz);
  GLfloat getX() const {return x;};
  GLfloat getY() const {return y;};
  GLbyte getHemi() const {return hemi;};
  GLfloat getSX() const {return sx;}; 
  GLfloat getSY() const {return sy;}; 
  GLfloat getSZ() const {return sz;}; 
  void convertZ();			//added.. z 값의 부호를 변경한다..
  void test();
  };





  
