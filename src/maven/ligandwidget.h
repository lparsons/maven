/***************************************************************************
 *   Copyright (C) 2008 by melamud,,,   *
 *   emelamud@princeton.edu   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef LIGANDWIDGET_H
#define LIGANDWIDGET_H

#include "globals.h"
#include "stable.h"
#include "mainwindow.h"
#include "numeric_treewidgetitem.h"
#include <QtNetwork>
#include <QNetworkReply>

class QAction;
class QMenu;
class QTextEdit;
class MainWindow;
class Database;


using namespace std;

extern Database DB; 

class LigandWidget: public QDockWidget {
      Q_OBJECT

public:
    LigandWidget(MainWindow* parent);

    void updateDatabaseList();
    QString getDatabaseName();
    void clear() { treeWidget->clear(); }
    void showNext();
    void showLast();
    void setDatabaseAltered(QString dbame,bool altered);

public slots: 
    void setCompoundFocus(Compound* c);
    void setDatabase(QString dbname);
    void setFilterString(QString s);
    void showGallery();
    void showMatches(QString needle);
    void saveCompoundList();
    void updateTable() { showTable(); }
    void updateCurrentItemData();


signals:
    void urlChanged(QString url);
    void compoundFocused(Compound* c);
    void databaseChanged(QString dbname);

private slots:
      void showLigand();
      void showTable();
      void databaseChanged(int index);


private:

    QTreeWidget *treeWidget;
    QComboBox *databaseSelect;
    QToolButton *galleryButton;
    QToolButton *saveButton;
    QToolButton *loadButton;
    QPoint dragStartPosition;

    QHash<QString,bool>alteredDatabases;

    MainWindow* _mw;
    QString filterString;
    QTreeWidgetItem* addItem(QTreeWidgetItem* parentItem, string key , float value);
    QTreeWidgetItem* addItem(QTreeWidgetItem* parentItem, string key , string value);

};

#endif
