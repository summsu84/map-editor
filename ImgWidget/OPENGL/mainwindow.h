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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class GLWidget;
class QSpinBox;
class QAction;
class QString;
class QMenu;

class MainWindow : public QMainWindow
{
  Q_OBJECT
    
 public:
  MainWindow(int size);


 public slots:
  void updateFileName(QString name);
  void about();
  //  void setResizeMode(bool mode);

 private:
  void setUpActions();
  void setUpStatusBar();
  void setUpMenu();
  void contextMenuEvent(QContextMenuEvent *event);


  GLWidget *glWidget;
  QSpinBox *phiBox;
  QSpinBox *psiBox;
  QToolBar *fileToolBar;
  QToolBar *modeToolBar;
  QMenu    *fileMenu;
  QMenu    *modeMenu;
  //  QMenu    *viewMenu;

  QAction  *newAction;
  QAction  *saveAsAction;
  QAction  *saveAction;
  QAction  *openAction;  
  QAction  *exportAction;  
  QAction  *quitAction;
  QAction  *drawAction;
  QAction  *orbitAction;
  QAction  *moveAction;
  QAction  *aboutAction;
  QAction  *twistAction;
  QAction  *oppositeAction;
  QAction  *measureAction;
  //  QAction  *resizeAction;

  QAction  *deleteArcAction;
  QAction  *deleteVertexAction;
  QString  fileName;



};

#endif
