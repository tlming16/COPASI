/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ObjectBrowserDialog.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/10/07 07:41:00 $
   End CVS Header */

#include "ObjectBrowserDialog.h"
#include <qlayout.h>
#include <qpushbutton.h>
#include "copasi.h"
#include "copasiui3window.h"
#include "report/CCopasiObject.h"
#include "ObjectBrowserWidget.h"
#include "qtUtilities.h"

/*
 *  Constructs a ObjectBrowserDialog which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ObjectBrowserDialog::ObjectBrowserDialog(QWidget* parent, const char* name, bool modal)
    : QDialog(parent, name, modal)
{
  //  setWFlags(getWFlags() | Qt::WDestructiveClose);
  if (!name)
    setName("ObjectBrowser");
  resize(420, 460);
  setCaption(trUtf8("Object Browser"));
  ObjectBrowserDialogLayout = new QGridLayout(this, 3, 4, 11, 6, "ObjectBrowserDialogLayout");
  //  objectBrowserWidget = new ObjectBrowserWidget(this, NULL, 0, 1);
  objectBrowserWidget = new ObjectBrowserWidget(this);
  ObjectBrowserDialogLayout->addMultiCellWidget(objectBrowserWidget, 0, 0, 0, 3);
  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);
  ObjectBrowserDialogLayout->addMultiCellWidget(Line1, 1, 1, 0, 3);

  cancelButton = new QPushButton(this, "cancelButton");
  cancelButton->setText(trUtf8("Cancel"));
  ObjectBrowserDialogLayout->addWidget(cancelButton, 2, 2);

  okButton = new QPushButton(this, "okButton");
  okButton->setText(trUtf8("OK"));
  okButton->setDefault(true);
  okButton->setAutoDefault(true);
  ObjectBrowserDialogLayout->addWidget(okButton, 2, 3);

  spacer = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);
  ObjectBrowserDialogLayout->addItem(spacer, 2, 1);

  setTabOrder(okButton, cancelButton);
  setTabOrder(cancelButton, objectBrowserWidget);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
  connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));

  mparent = (CopasiUI3Window*)parent;
  if (mparent)
    mparent->disable_object_browser_menu();
}

/*
 *  Destroys the object and frees any allocated resources
 */
void ObjectBrowserDialog::closeEvent (QCloseEvent * e)
{
  QWidget::closeEvent(e);
  if (mparent)
    {
      //if not a model dialog, it shall incur this function, when close
      // it shall enable the browser menu
      mparent->enable_object_browser_menu();
      mparent = NULL;
      cleanup();
    }
}

ObjectBrowserDialog::~ObjectBrowserDialog()
{
  //  cleanup();
  //  destroy();
}

void ObjectBrowserDialog::cleanup()
{
  return;
}

void ObjectBrowserDialog::setOutputVector(std::vector<CCopasiObject*>* pObjectVector)
{
  if (objectBrowserWidget) objectBrowserWidget->setOutputVector(pObjectVector);
}

void ObjectBrowserDialog::cancelClicked()
{
  close();
  //  QDialog::done(QDialog::Accepted);
}

void ObjectBrowserDialog::okClicked()
{
  objectBrowserWidget->commitClicked();
  done(QDialog::Accepted);
  //  QDialog::done(QDialog::Accepted);
}

void ObjectBrowserDialog::selectObjects(std::vector<CCopasiObject*>* pObjectVector)
{
  if (objectBrowserWidget) objectBrowserWidget->selectObjects(pObjectVector);
}
