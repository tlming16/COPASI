// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMIRIAMModelWidget.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/10 21:15:53 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CMIRIAMMODELWIDGET
#define COPASI_CMIRIAMMODELWIDGET

#include "copasiWidget.h"
#include "listviews.h"

class CAuthorsWidget;
class QPushButton;

class CMIRIAMModelWidget : public CopasiWidget
  {
    Q_OBJECT
  public:
    CMIRIAMModelWidget(QWidget *parent, const char * name = 0, WFlags f = 0);

  private:
    CAuthorsWidget *mAuthorsWidget;
    CAuthorsWidget *mPublicationsWidget;

    QPushButton* btnOK;
    QPushButton* btnCancel;
    QPushButton* btnDelete;
    QPushButton* btnNew;
    QPushButton* btnClear;

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnDeleteClicked();
    virtual void slotBtnNewClicked();
    virtual void slotBtnClearClicked();

    virtual void slotEnableOKAndCancel(bool e);

  public:
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
  };

#endif // COPASI_CMIRIAMMODELWIDGET
