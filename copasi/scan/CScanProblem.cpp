// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CScanProblem class.
 */

#include <string>
#include <cmath>

#include "copasi.h"
#include "CScanProblem.h"
//#include "model/CModel.h"
//#include "model/CState.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CScanProblem::CScanProblem(const CDataContainer * pParent):
  CCopasiProblem(CTaskEnum::Task::scan, pParent),
  mpScanItems(NULL)
{
  initializeParameter();
}

/**
 *  Copy constructor.
 *  @param "const CScanProblem &" src
 */
CScanProblem::CScanProblem(const CScanProblem & src,
                           const CDataContainer * pParent):
  CCopasiProblem(src, pParent),
  mpScanItems(NULL)
{
  initializeParameter();
}

/**
 *  Destructor.
 */
CScanProblem::~CScanProblem()
{}

void CScanProblem::initializeParameter()
{
  addParameter("Subtask", CCopasiParameter::UINT, (unsigned C_INT32) CTaskEnum::Task::timeCourse);

  addGroup("ScanItems");
  mpScanItems = dynamic_cast<CCopasiParameterGroup*>(getParameter("ScanItems"));

  addParameter("Output in subtask", CCopasiParameter::BOOL, true);
  addParameter("Adjust initial conditions", CCopasiParameter::BOOL, false);
}

//***********************************

void CScanProblem::setSubtask(CTaskEnum::Task type)
{
  setValue("Subtask", (unsigned C_INT32)type);
}

CTaskEnum::Task CScanProblem::getSubtask() const
{return (CTaskEnum::Task) getValue< unsigned C_INT32 >("Subtask");}

//************************************

void CScanProblem::setOutputInSubtask(bool ois)
{
  setValue("Output in subtask", ois);
}

const bool & CScanProblem::getOutputInSubtask() const
{return getValue< bool >("Output in subtask");}

//************************************

void CScanProblem::setContinueFromCurrentState(bool aic)
{
  setValue("Adjust initial conditions", aic);
}

bool CScanProblem::getContinueFromCurrentState() const
{return getValue< bool >("Adjust initial conditions");}

//************************************

void CScanProblem::load(CReadConfig & C_UNUSED(configBuffer),
                        CReadConfig::Mode C_UNUSED(mode))
{}

size_t CScanProblem::getNumberOfScanItems() const
{
  return mpScanItems->size();
}

const CCopasiParameterGroup* CScanProblem::getScanItem(size_t index) const
{
  CCopasiParameter* tmp = mpScanItems->getParameter(index);

  if (tmp->getType() != CCopasiParameter::GROUP)
    {
      // ERROR: not a parameter group!!!
      return NULL;
    }

  return (CCopasiParameterGroup*)tmp;
}

CCopasiParameterGroup* CScanProblem::getScanItem(size_t index)
{
  CCopasiParameter* tmp = mpScanItems->getParameter(index);

  if (tmp->getType() != CCopasiParameter::GROUP)
    {
      // ERROR: not a parameter group!!!
      return NULL;
    }

  return static_cast<CCopasiParameterGroup *>(tmp);
}

//CScanProblem::Type CScanProblem::getScanItemType(size_t index);
CCopasiParameterGroup* CScanProblem::addScanItem(CScanProblem::Type type, size_t steps, const CDataObject* obj)
{
  CCopasiParameterGroup * pItem = createScanItem(type, steps, obj);
  mpScanItems->addParameter(pItem);

  return pItem;
}

bool CScanProblem::removeScanItem(const size_t & index)
{
  return mpScanItems->removeParameter(index);
}

// static
CCopasiParameterGroup* CScanProblem::createScanItem(CScanProblem::Type type, size_t steps, const CDataObject* obj)
{
  CCopasiParameterGroup * tmp = new CCopasiParameterGroup("ScanItem");

  //create common parameters
  tmp->addParameter("Number of steps", CCopasiParameter::UINT, (unsigned C_INT32) steps);
  tmp->addParameter("Type", CCopasiParameter::UINT, (unsigned C_INT32) type);

  if (obj)
    tmp->addParameter("Object", CCopasiParameter::CN, obj->getCN());
  else
    tmp->addParameter("Object", CCopasiParameter::CN, CCommonName(""));

  //create specific parameters
  if ((type == SCAN_LINEAR) || (type == SCAN_RANDOM))
    {
      tmp->addParameter("Minimum", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);
      tmp->addParameter("Maximum", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
      tmp->addParameter("log", CCopasiParameter::BOOL, false);
    }

  if (type == SCAN_RANDOM)
    {
      tmp->addParameter("Distribution type", CCopasiParameter::UINT, (unsigned C_INT32)0);
    }

  if (type == SCAN_BREAK)
    {
      tmp->addParameter("Report break", CCopasiParameter::UINT, (unsigned C_INT32)0);
      tmp->addParameter("Plot break", CCopasiParameter::UINT, (unsigned C_INT32)0);
    }

  return tmp;
}

void CScanProblem::clearScanItems()
{
  mpScanItems->clear();
}

void CScanProblem::fixBuild81()
{
  CCopasiParameterGroup::index_iterator it = mpScanItems->beginIndex();
  CCopasiParameterGroup::index_iterator end = mpScanItems->endIndex();

  for (; it != end; ++it)
    {
      if ((*it)->getType() != CCopasiParameter::GROUP)
        {
          continue;
        }

      CCopasiParameterGroup * pGroup = static_cast< CCopasiParameterGroup * >(*it);
      CCopasiParameter * pParam = pGroup->getParameter("Type");

      if (pParam == NULL || (Type) pParam->getValue< unsigned C_INT32 >() != SCAN_RANDOM)
        {
          continue;
        }

      // Check whether distribution type is set and not uniform
      pParam = pGroup->getParameter("Distribution type");

      if (pParam == NULL || (Type) pParam->getValue< unsigned C_INT32 >() == 0)
        {
          continue;
        }

      // Check whether log is set and true
      pParam = pGroup->getParameter("log");

      if (pParam == NULL || pParam->getValue< bool >() == false)
        {
          continue;
        }

      // We need to fix min and max
      pParam = pGroup->getParameter("Minimum");

      if (pParam != NULL)
        {
          pParam->setValue(log(pParam->getValue< C_FLOAT64 >()));
        }

      pParam = pGroup->getParameter("Maximum");

      if (pParam != NULL)
        {
          pParam->setValue(log(pParam->getValue< C_FLOAT64 >()));
        }
    }

  return;
}
