/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/13 18:02:22 $
   End CVS Header */

// Copyright � 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Thu Jul 13 13:58:22 2006
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.cpp,v 1.7 2006/07/13 18:02:22 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQOptimizationWidget.h"

#include <qvariant.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "TaskWidget.h"
#include "CQExpressionWidget.h"
#include "CQOptimizationWidget.ui.h"
static const unsigned char image0_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x5c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x93, 0x4d, 0x4f, 0x13,
    0x71, 0x10, 0x87, 0x9f, 0xff, 0xee, 0xd6, 0xd6, 0xb6, 0xdb, 0x52, 0x5a,
    0x40, 0x81, 0x16, 0x85, 0x5a, 0x5e, 0x04, 0xa2, 0xa9, 0x26, 0x26, 0x98,
    0x88, 0x89, 0x07, 0xaf, 0xc6, 0x0f, 0xe8, 0x47, 0xc0, 0x98, 0x78, 0x30,
    0x6a, 0x0c, 0x97, 0x62, 0xc4, 0x82, 0xc8, 0x6b, 0x63, 0x43, 0xaa, 0xa0,
    0xad, 0x5d, 0xe8, 0xf2, 0x62, 0x29, 0xdd, 0x6d, 0x3b, 0x1e, 0x10, 0x22,
    0x41, 0xf4, 0xe0, 0x9c, 0x26, 0x33, 0xf3, 0xfc, 0x0e, 0xbf, 0x99, 0x51,
    0x99, 0x4c, 0x86, 0xff, 0x09, 0xe3, 0x6f, 0x4d, 0x9f, 0xaf, 0x2c, 0xae,
    0xab, 0x61, 0xdb, 0x65, 0xb6, 0xb6, 0x2a, 0x78, 0xbd, 0x06, 0x3d, 0x3d,
    0x77, 0xd4, 0x3f, 0x05, 0x4c, 0xd3, 0x96, 0x4a, 0xe5, 0x80, 0x6c, 0xb6,
    0x40, 0xa1, 0x50, 0xc7, 0xeb, 0x15, 0x62, 0x31, 0x61, 0x60, 0x20, 0x4a,
    0x38, 0x5c, 0x91, 0xdd, 0xdd, 0x76, 0x75, 0xae, 0x80, 0xcf, 0x57, 0x97,
    0xf9, 0xf9, 0x0d, 0xe6, 0xe6, 0x2c, 0x82, 0x41, 0xc5, 0xc4, 0x44, 0x37,
    0x89, 0x44, 0x02, 0x91, 0x1f, 0x18, 0x86, 0xf0, 0x3b, 0x7c, 0x46, 0xc0,
    0xb6, 0xbf, 0xca, 0xcc, 0xcc, 0x67, 0x2c, 0xeb, 0x80, 0x64, 0xd2, 0xc3,
    0xe8, 0x68, 0x2f, 0xe1, 0xf0, 0x80, 0x72, 0x1c, 0x00, 0x3f, 0xae, 0xfb,
    0x17, 0x0f, 0xf2, 0xf9, 0x9c, 0x64, 0xe7, 0x4a, 0x04, 0xfc, 0x1a, 0x93,
    0x93, 0x7d, 0xf4, 0xf5, 0x5d, 0x53, 0x67, 0xc7, 0xcf, 0x11, 0xc8, 0xe7,
    0xd7, 0x64, 0x61, 0xe1, 0x3b, 0x83, 0xa9, 0x20, 0xe9, 0xf4, 0x75, 0x9a,
    0x4d, 0xdf, 0x29, 0x38, 0xac, 0xd6, 0x44, 0x73, 0x04, 0x6b, 0x7d, 0x95,
    0xda, 0x4e, 0x85, 0x50, 0x7b, 0x94, 0xee, 0xe1, 0x34, 0x5f, 0x1b, 0x09,
    0x65, 0x94, 0x4a, 0x39, 0xc9, 0x66, 0xbf, 0x91, 0x4c, 0x06, 0x19, 0x1b,
    0xeb, 0x3a, 0x05, 0x07, 0xdc, 0x05, 0xd9, 0x2f, 0x16, 0x59, 0x5a, 0x5a,
    0xa2, 0xb4, 0xd1, 0xc4, 0xda, 0x0f, 0x50, 0x6f, 0x18, 0xb4, 0x7b, 0x3e,
    0x71, 0x75, 0x3e, 0xc7, 0xed, 0xc7, 0x0f, 0xc4, 0x98, 0x9d, 0x9d, 0xc7,
    0x34, 0x03, 0xa4, 0x52, 0x09, 0x74, 0xbd, 0xf7, 0x04, 0xbe, 0xb0, 0xf1,
    0x42, 0x16, 0x3f, 0xac, 0x91, 0x2b, 0x18, 0x78, 0xc2, 0x31, 0xe2, 0x63,
    0x6d, 0xdc, 0x1c, 0xe9, 0xc7, 0x17, 0x08, 0x52, 0xdb, 0xb6, 0xc9, 0x3e,
    0x7f, 0x49, 0x7e, 0xe6, 0x15, 0x86, 0x65, 0xd9, 0x8c, 0x8f, 0xb7, 0x61,
    0x9a, 0xc9, 0x13, 0x58, 0xcf, 0x3f, 0x93, 0x77, 0xaf, 0x57, 0xd8, 0xb9,
    0x18, 0x65, 0xf0, 0x5e, 0x92, 0xc1, 0xf1, 0x1b, 0xb8, 0x44, 0x14, 0x40,
    0x03, 0xd0, 0xcd, 0x4d, 0xb1, 0x1b, 0x21, 0x76, 0xec, 0x6f, 0x67, 0xd7,
    0x98, 0x08, 0x94, 0xe5, 0xcd, 0xdb, 0x45, 0x0e, 0x82, 0x31, 0x26, 0x1f,
    0x3d, 0x04, 0x7f, 0x5c, 0xfd, 0x6e, 0xbe, 0x6e, 0xbd, 0x97, 0xcc, 0xf4,
    0x3a, 0x5e, 0xd1, 0xb8, 0x9c, 0x7e, 0x88, 0xd1, 0xd1, 0x11, 0xa1, 0x54,
    0x72, 0xb0, 0xac, 0x15, 0xe9, 0xe8, 0x18, 0x51, 0xf5, 0xba, 0xcd, 0x8f,
    0xea, 0x01, 0xa1, 0x78, 0x83, 0x20, 0x45, 0xcc, 0xe6, 0xb6, 0xb4, 0x9a,
    0x0d, 0xaa, 0xd5, 0x2a, 0x85, 0x8f, 0xab, 0x7c, 0x59, 0x2c, 0x72, 0xa8,
    0x5d, 0x62, 0xfc, 0xfe, 0x18, 0x46, 0xf7, 0x5d, 0xa5, 0xa6, 0xa6, 0x9e,
    0xc8, 0xf4, 0xf4, 0x17, 0xa2, 0x51, 0x97, 0x91, 0xe1, 0x5e, 0xa2, 0xa1,
    0x06, 0x9b, 0xb3, 0x4f, 0x29, 0xe7, 0xca, 0x38, 0xc5, 0x0b, 0x38, 0x7b,
    0xa0, 0xeb, 0x1a, 0x8e, 0x3f, 0x42, 0x35, 0x10, 0xa3, 0x2b, 0xd5, 0xc6,
    0xc8, 0xad, 0x21, 0x22, 0xf1, 0xb4, 0x02, 0x50, 0x99, 0x4c, 0x86, 0x5a,
    0xad, 0x20, 0xcb, 0xcb, 0x6b, 0x2c, 0x2f, 0x7b, 0xa8, 0x1f, 0x2a, 0xdc,
    0x9a, 0x8d, 0xb3, 0x5f, 0xa7, 0xbe, 0x27, 0xe8, 0x2d, 0xa1, 0x27, 0x2e,
    0xa4, 0x46, 0x4d, 0xae, 0x0c, 0xc5, 0x69, 0xef, 0x8a, 0xa0, 0x79, 0xfa,
    0x4f, 0xfc, 0x52, 0xc7, 0xdf, 0xe8, 0xf1, 0x6c, 0x8a, 0xeb, 0x7a, 0x68,
    0xb5, 0xe4, 0xa8, 0xd3, 0x82, 0x96, 0x80, 0xae, 0x0c, 0xfc, 0xc1, 0x10,
    0xd2, 0xda, 0xe1, 0xd0, 0xe9, 0x3c, 0x73, 0x5c, 0x27, 0x26, 0xba, 0xee,
    0xd1, 0x0a, 0x35, 0xed, 0x57, 0x41, 0x83, 0xe3, 0xb4, 0x76, 0x08, 0xd0,
    0xf9, 0xc7, 0x4b, 0xfc, 0x09, 0x52, 0xcb, 0x07, 0x62, 0x36, 0x43, 0x92,
    0xc6, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
    0x82
  };

/*
 *  Constructs a CQOptimizationWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQOptimizationWidget::CQOptimizationWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  QImage img;
  img.loadFromData(image0_data, sizeof(image0_data), "PNG");
  image0 = img;
  if (!name)
    setName("CQOptimizationWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  setMinimumSize(QSize(0, 0));
  CQOptimizationWidgetLayout = new QVBoxLayout(this, 11, 6, "CQOptimizationWidgetLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpEditExpression = new CQExpressionWidget(this, "mpEditExpression");

  mpGridLayout->addMultiCellWidget(mpEditExpression, 0, 1, 1, 2);

  mpBtnObject = new QToolButton(this, "mpBtnObject");
  mpBtnObject->setMaximumSize(QSize(20, 20));
  mpBtnObject->setIconSet(QIconSet(image0));

  mpGridLayout->addWidget(mpBtnObject, 0, 3);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblType, 2, 0);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblExpression, 0, 0);
  mpSpacer2 = new QSpacerItem(233, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpGridLayout->addMultiCell(mpSpacer2, 2, 2, 2, 3);
  mpSpacer = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Preferred);
  mpGridLayout->addItem(mpSpacer, 1, 3);

  mpBtnGroup = new QButtonGroup(this, "mpBtnGroup");
  mpBtnGroup->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)4, 0, 0, mpBtnGroup->sizePolicy().hasHeightForWidth()));
  mpBtnGroup->setFrameShape(QButtonGroup::NoFrame);
  mpBtnGroup->setAlignment(int(QButtonGroup::WordBreak | QButtonGroup::AlignVCenter | QButtonGroup::AlignBottom | QButtonGroup::AlignTop));
  mpBtnGroup->setColumnLayout(0, Qt::Vertical);
  mpBtnGroup->layout()->setSpacing(6);
  mpBtnGroup->layout()->setMargin(0);
  mpBtnGroupLayout = new QHBoxLayout(mpBtnGroup->layout());
  mpBtnGroupLayout->setAlignment(Qt::AlignTop);

  mpBtnSteadystate = new QRadioButton(mpBtnGroup, "mpBtnSteadystate");
  mpBtnSteadystate->setChecked(TRUE);
  mpBtnGroupLayout->addWidget(mpBtnSteadystate);

  mpBtnTimeCourse = new QRadioButton(mpBtnGroup, "mpBtnTimeCourse");
  mpBtnGroupLayout->addWidget(mpBtnTimeCourse);

  mpGridLayout->addWidget(mpBtnGroup, 2, 1);
  CQOptimizationWidgetLayout->addLayout(mpGridLayout);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");
  mpTabWidget->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, mpTabWidget->sizePolicy().hasHeightForWidth()));

  mpParametersPage = new QWidget(mpTabWidget, "mpParametersPage");
  mpTabWidget->insertTab(mpParametersPage, QString::fromLatin1(""));

  mpConstraintsPage = new QWidget(mpTabWidget, "mpConstraintsPage");
  mpTabWidget->insertTab(mpConstraintsPage, QString::fromLatin1(""));
  CQOptimizationWidgetLayout->addWidget(mpTabWidget);
  languageChange();
  resize(QSize(627, 412).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpTabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(slotPageChange(QWidget*)));
  connect(mpEditExpression, SIGNAL(valid(bool)), this, SLOT(slotExpressionValid(bool)));
  connect(mpBtnObject, SIGNAL(clicked()), mpEditExpression, SLOT(slotSelectObject()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQOptimizationWidget::~CQOptimizationWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQOptimizationWidget::languageChange()
{
  setCaption(tr("Optimization"));
  mpBtnObject->setText(QString::null);
  mpBtnObject->setTextLabel(tr("select"));
  mpLblType->setText(tr("Experiment Type"));
  mpLblExpression->setText(tr("Expression"));
  mpBtnGroup->setTitle(QString::null);
  mpBtnSteadystate->setText(tr("Steady State"));
  mpBtnTimeCourse->setText(tr("Time Course"));
  mpTabWidget->changeTab(mpParametersPage, tr("Parameters (0)"));
  mpTabWidget->changeTab(mpConstraintsPage, tr("Constraints (0)"));
}
