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
//#include <QPushButton>

#include "glwidget.h"
#include "mainwindow.h"
#include "const.h"

MainWindow::MainWindow(int size)
{
  
  
  glWidget = new GLWidget();
  //emit resizeEvent();

  glWidget->setMinimumSize(size,size);
  glWidget->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);  
  //glWidget->setMinimumSize(200,200);



  // Constructing the Toolbars and Statusbar

  fileToolBar =   addToolBar(tr("&File"));
  fileToolBar->setToolButtonStyle (Qt::ToolButtonIconOnly);
  modeToolBar =   addToolBar(tr("&Mode"));
  modeToolBar->setToolButtonStyle (Qt::ToolButtonTextOnly);

  setUpActions();
  setUpStatusBar();
  setUpMenu();

  setCentralWidget(glWidget);

  setWindowTitle(tr("Spherical ")+fileName);
  setWindowIcon(QIcon(":res/sphere.png"));

  connect(glWidget,SIGNAL(psiChanged(int)),psiBox,SLOT(setValue(int)));
  connect(glWidget,SIGNAL(phiChanged(int)),phiBox,SLOT(setValue(int)));
  connect(glWidget,SIGNAL(newFileName(QString)),this,SLOT(updateFileName(QString)));


  //adjustSize();
  //setFixedSize(size());  
}



void MainWindow::updateFileName(QString name)
{
  fileName=name;
  setWindowTitle(tr("Spherical ")+fileName);
}


void MainWindow::setUpStatusBar()

{
  phiBox = new QSpinBox();
  phiBox->setRange(0,359);
  phiBox->setAccelerated(1);
  phiBox->setWrapping(true);
  phiBox->setPrefix(tr("phi= "));
  psiBox = new QSpinBox();
  psiBox->setRange(0,359);
  psiBox->setAccelerated(1);
  psiBox->setPrefix(tr("psi= "));
  psiBox->setWrapping(true);
  connect(phiBox,SIGNAL(valueChanged (int)),glWidget,SLOT(setPhi(int)));
  connect(psiBox,SIGNAL(valueChanged (int)),glWidget,SLOT(setPsi(int)));

  statusBar()->addWidget(phiBox);
  statusBar()->addWidget(psiBox);
}


void MainWindow::setUpActions()
{

 newAction  = new QAction(tr("&New"),this);
 newAction->setShortcut(tr("Ctrl+N"));
 newAction->setIcon(QIcon(":/res/new.png"));
 newAction->setIconText(tr("New"));
 fileToolBar->addAction(newAction);
 connect(newAction,SIGNAL(triggered()),glWidget,SLOT(resetGraph()));

 openAction  = new QAction(tr("&Open ..."),this);
 openAction->setShortcut(tr("Ctrl+O"));
 // openAction->setStatusTip(tr("Open a Sphere File"));
 openAction->setIconText(tr("Open"));
 openAction->setIcon(QIcon(":/res/open.png"));
 fileToolBar->addAction(openAction);
 connect(openAction,SIGNAL(triggered()),glWidget,SLOT(load()));

 saveAction  = new QAction(tr("&Save"),this);
 saveAction->setShortcut(tr("Ctrl+S"));
 saveAction->setIcon(QIcon(":/res/save.png"));
 // openAction->setStatusTip(tr("Open a Sphere File"));
 saveAction->setIconText(tr("Save"));
 fileToolBar->addAction(saveAction);
 connect(saveAction,SIGNAL(triggered()),glWidget,SLOT(save()));


 saveAsAction  = new QAction(tr("Save as ..."),this);
 saveAsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
 // openAction->setStatusTip(tr("Open a Sphere File"));
 saveAsAction->setIcon(QIcon(":/res/saveas.png"));
 saveAsAction->setIconText(tr("Save as"));
 fileToolBar->addAction(saveAsAction);
 connect(saveAsAction,SIGNAL(triggered()),glWidget,SLOT(saveAs()));

 exportAction =  new QAction(tr("Export to ..."),this);
 exportAction->setShortcut(tr("Ctrl+E"));
 connect(exportAction,SIGNAL(triggered()),glWidget,SLOT(exportFile()));


 quitAction  = new QAction(tr("&Quit"),this);
 quitAction->setShortcut(tr("Ctrl+Q"));
 quitAction->setIcon(QIcon(":/res/exit.png"));
 //quitAction->setStatusTip(tr("Exit to OS"));
 quitAction->setIconText(tr("Quit"));
 fileToolBar->addAction(quitAction);
 connect(quitAction,SIGNAL(triggered()),this,SLOT(close()));



 drawAction  = new QAction(tr("Draw"),this);
 drawAction->setShortcut(Qt::Key_F1);
 //drawAction->setStatusTip(tr("Enable Drawing Mode"));
 drawAction->setIconText(tr("Draw"));
 drawAction->setCheckable(true);
 modeToolBar->addAction(drawAction);
 connect(drawAction,SIGNAL(triggered()),glWidget,SLOT(enableDrawMode()));

 orbitAction  = new QAction(tr("Orbit"),this);
 orbitAction->setShortcut(Qt::Key_F2);
 // orbitAction->setStatusTip(tr("Enable Orbit Mode"));
 orbitAction->setIconText(tr("Orbit"));
 orbitAction->setCheckable(true);
 modeToolBar->addAction(orbitAction);
 connect(orbitAction,SIGNAL(triggered()),glWidget,SLOT(enableOrbitMode()));

 moveAction  = new QAction(tr("Move"),this);
 moveAction->setShortcut(Qt::Key_F3);
 //moveAction->setStatusTip(tr("Enable Vertex Move Mode"));
 moveAction->setIconText(tr("Move"));
 moveAction->setCheckable(true);
 modeToolBar->addAction(moveAction);
 connect(moveAction,SIGNAL(triggered()),glWidget,SLOT(enableMoveMode()));

 aboutAction  = new QAction(tr("About Spherical"),this);
 aboutAction->setShortcut(tr("Ctrl+?"));
 connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));
 


 QActionGroup *modeGroup = new QActionGroup(this);
 modeGroup->addAction(drawAction);
 modeGroup->addAction(orbitAction);
 modeGroup->addAction(moveAction);
 drawAction->setChecked(true);

 twistAction  = new QAction(tr("Twist Arc"),this);
 twistAction->setShortcut(tr("Ctrl+T"));
 connect(twistAction,SIGNAL(triggered()),glWidget,SLOT(twist()));

 oppositeAction  = new QAction(tr("Opposite Vertex"),this);
 oppositeAction->setShortcut(tr("Ctrl+P"));
 connect(oppositeAction,SIGNAL(triggered()),glWidget,SLOT(opposite()));


 measureAction  = new QAction(tr("Measure Arc Length"),this);
 connect(measureAction,SIGNAL(triggered()),glWidget,SLOT(measure()));

 

 deleteArcAction  = new QAction(tr("Delete Arc"),this);
 deleteArcAction->setShortcut(Qt::CTRL + Qt::Key_D);
 connect(deleteArcAction,SIGNAL(triggered()),glWidget,SLOT(deletePiece()));

 deleteVertexAction  = new QAction(tr("Delete Vertex"),this);
 deleteVertexAction->setShortcut(Qt::CTRL + Qt::Key_D);
 connect(deleteVertexAction,SIGNAL(triggered()),glWidget,SLOT(deletePiece()));

 

 /* resizeAction = new QAction(tr("Fixed Size"),this);
 resizeAction->setCheckable(true);
 resizeAction->setChecked(false);
 connect(resizeAction,SIGNAL(triggered(bool)),this,SLOT(setResizeMode(bool)));
 */



 new QShortcut(Qt::CTRL+ Qt::Key_D, glWidget, SLOT(deletePiece()),SLOT(deletePiece()));
 new QShortcut(Qt::CTRL+ Qt::Key_T, glWidget, SLOT(twist()));
 new QShortcut(Qt::CTRL+ Qt::Key_P, glWidget, SLOT(opposite()));

}

void MainWindow::setUpMenu()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newAction);
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(saveAsAction);
  fileMenu->addAction(exportAction);
  fileMenu->addSeparator();
  fileMenu->addAction(aboutAction);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAction);


  modeMenu = menuBar()->addMenu(tr("&Mode"));
  modeMenu->addAction(drawAction);
  modeMenu->addAction(orbitAction);
  modeMenu->addAction(moveAction);

  //viewMenu = menuBar()->addMenu(tr("&View"));
  //viewMenu->addAction(resizeAction);


}


void MainWindow::about()
{
   QMessageBox::about(this, tr("About Spherical"),
            tr("<br><b><big>Spherical</big></b> <br><br> Version 0.6<br><br> "
               "A simple Editor for spherical drawings,<br> "
               "written by Andr&eacute; Schulz,<br>"
               "July 2008. <br><br>"
	       "This software is released under the GNU Public License."
));
}




void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu(this);
  if (glWidget->getSnap()==SPH_SNAPPED_ARC)  menu.addAction(twistAction);
  if (glWidget->getSnap()==SPH_SNAPPED_VERTEX)  menu.addAction(oppositeAction);
  if (glWidget->getSnap()==SPH_SNAPPED_ARC)  menu.addAction(measureAction);
  if (glWidget->getSnap()==SPH_SNAPPED_VERTEX)  menu.addAction(deleteVertexAction);
  if (glWidget->getSnap()==SPH_SNAPPED_ARC)  menu.addAction(deleteArcAction);
  if (glWidget->getSnap()!=SPH_NO_SNAP)  menu.addSeparator();
  menu.addAction(quitAction);
					   
  menu.exec(event->globalPos());
}

/*void MainWindow::setResizeMode(bool mode)
{
  if (mode) {
    glWidget->setFixedSize(500,500); 
    adjustSize();
    setFixedSize(size());
  }
  else {
    glWidget->setMinimumSize(200,200);
    glWidget->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
  }
}
*/
