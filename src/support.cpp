/*************************************************************************
 *
 * Copyright (C) 1997-2014 by Dimitri van Heesch.
 * Copyright (C) 2014-2015 Barbara Geller & Ansel Sermersheim
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License version 2
 * is hereby granted. No representations are made about the suitability of
 * this software for any purpose. It is provided "as is" without express or
 * implied warranty. See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
*************************************************************************/

#include "mainwindow.h"

void MainWindow::closeEvent(QCloseEvent *event)
{ 
   bool exit = querySave();

   if (exit) {
      saveSettings();
      event->accept();

   } else {
      event->ignore();
   }
}

QString MainWindow::pathName(QString fileName) const
{
   return QFileInfo(fileName).path();
}

bool MainWindow::querySave()
{
   if (m_modified) {

      QMessageBox quest;
      quest.setWindowTitle(tr("CS Doxygen"));
      quest.setText( tr("Configuration file has been modified. Save changes?"));
      quest.setStandardButtons(QMessageBox::Save | QMessageBox::Discard  | QMessageBox::Cancel );
      quest.setDefaultButton(QMessageBox::Cancel);

      int retval = quest.exec();

      if (retval == QMessageBox::Save) {
         // saveDoxCfgFile();
         csMsg("Do the save now");

         return true;

      } else if (retval == QMessageBox::Cancel) {
         return false;

      }
   }

   return true;
}

void MainWindow::setDoxygenTitle(bool isModified)
{
   m_modified = isModified;

   // displays as: CS Doxygen --  ConfigFileName[*]
   if (m_ConfigFile.isEmpty())   {

      setWindowTitle(tr("CS Doxygen ") );

   } else {
      QString temp = QChar(0x02014);

      if (m_modified) {
         setWindowTitle(tr("CS Doxygen ") + temp + " " + m_ConfigFile + " [*]" );
      } else {
         setWindowTitle(tr("CS Doxygen ") + temp + " " + m_ConfigFile );
      }
   }
}

/*

void MainWindow::createStatusBar()
{
   m_statusLine = new QLabel("", this);
   m_statusName = new QLabel("", this);

   statusBar()->addPermanentWidget(m_statusLine, 0);
   statusBar()->addPermanentWidget(m_statusName, 0);
}

void MainWindow::setStatusBar(QString msg, int timeOut)
{
   statusBar()->showMessage(msg, timeOut);
}

*/
