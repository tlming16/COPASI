// Copyright (C) 2011 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTaskMethodWidget
#define COPASI_CQTaskMethodWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTaskMethodWidget.h"
#include "copasi/utilities/CCopasiMethod.h"

class CCopasiTask;
class CQTaskMethodParametersDM;
class CQComboDelegate;

class CQTaskMethodWidget: public QWidget, public Ui::CQTaskMethodWidget
{
  Q_OBJECT

public:
  CQTaskMethodWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

  virtual ~CQTaskMethodWidget();

  void setTask(CCopasiTask * pTask);

  void setValidMethods(const CTaskEnum::Method * validMethods);

  void showMethodParameters(const bool & show);

  bool loadMethod();

  bool saveMethod();

  void clearHistory();

  void pushMethod(CCopasiMethod * pMethod);

  void popMethod(CCopasiMethod * pMethod);

protected slots:

protected slots:
  void slotOpenEditor(const QModelIndex & index);
  void slotCloseEditor(const QModelIndex & index);
  void changeMethod(int);

protected:
  void addToHistory(CCopasiMethod * pMethod);
  void removeFromHistory(CCopasiMethod * pMethod);
  CCopasiMethod * getFromHistory(const CTaskEnum::Method & Type) const;
  void setActiveMethod(const CTaskEnum::Method & Type);

protected:
  CCopasiTask * mpTask;
  CCopasiMethod * mpMethod;
  CCopasiMethod * mpActiveMethod;
  std::map< CTaskEnum::Method, CCopasiMethod * > mMethodHistory;
  bool mShowMethods;
  bool mShowMethodParameters;
  CQTaskMethodParametersDM * mpMethodParameterDM;
  CQComboDelegate* mpValueDelegate;
};

#endif // COPASI_CQTaskMethodWidget
