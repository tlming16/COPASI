// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQUPDATESWIDGET_H
#define CQUPDATESWIDGET_H

//Added by qt3to4:
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>

#include <map>
#include <vector>

#include "copasi/UI/copasiWidget.h"

class QLabel;
class QTabWidget;
class QTableWidget;

class CModel;

/**
 * This widget displays tables representing the refresh lists. It will probably only
 * be activated in debug builds
 */
class CQUpdatesWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CQUpdatesWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQUpdatesWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:

protected:
  virtual bool enterProtected();
  void loadWidget();
  void clearArrays();

  void loadOneTable(QTableWidget * pTable, const std::vector< Refresh * > & list);
  void loadObjectsTable(CModel* pModel);

  std::map<const Refresh*, const CCopasiObject*> mRefreshsMap;

  void fillRefreshsMapRecursively(const CCopasiObject* obj);

  QGridLayout* mWidgetLayout;

  QLabel* mLabelTitle;

  QTabWidget* mpMainTab;
  QTabWidget* mpTab;
  QTabWidget* mpTab2;

  QTableWidget * mpTable0;
  QTableWidget * mpTable1;
  QTableWidget * mpTable2;
  QTableWidget * mpTable3;

  QTableWidget * mpTableObj;
  QTableWidget * mpTableState;
};

#endif
