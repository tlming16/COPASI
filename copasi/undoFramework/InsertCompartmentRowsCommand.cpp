// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertCompartmentRowsCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

#include <utilities/CCopasiException.h>

#include "CQCompartmentDM.h"

#include "UndoCompartmentData.h"

#include "InsertCompartmentRowsCommand.h"

InsertCompartmentRowsCommand::InsertCompartmentRowsCommand(
  int position,
  int rows,
  CQCompartmentDM *pCompartmentDM)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_INSERT)
  , mpCompartmentDM(pCompartmentDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex()
  , mpCompartmentData(NULL)
  , mValue()
{
  setText(QObject::tr(": Inserted new compartment"));
}

InsertCompartmentRowsCommand::InsertCompartmentRowsCommand(
  int position,
  int rows,
  CQCompartmentDM *pCompartmentDM,
  const QModelIndex &index,
  const QVariant &value)
  : CCopasiUndoCommand("Compartment", COMPARTMENT_INSERT)
  , mpCompartmentDM(pCompartmentDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex(index)
  , mpCompartmentData(NULL)
  , mValue(value)
{
  setText(QObject::tr(": Inserted new compartment"));
}

void InsertCompartmentRowsCommand::redo()
{
  if (mpCompartmentData == NULL)
    {
      GET_MODEL_OR_RETURN(pModel);

      mpCompartmentDM->insertNewCompartmentRow(mPosition, mRows, mIndex, mValue);

      int Index = mIndex.isValid() ? mIndex.row() : mPosition;

      CCompartment *pCompartment = pModel->getCompartments()[Index];
      mpCompartmentData = new UndoCompartmentData(pCompartment);
    }
  else
    {
      mpCompartmentDM->addCompartmentRow(mpCompartmentData);
    }

  setUndoState(true);
  setAction("Add to list");
  setName(mpCompartmentData->getName());
}

void InsertCompartmentRowsCommand::undo()
{
  try
    {
      mpCompartmentDM->deleteCompartmentRow(mpCompartmentData);
      setUndoState(false);
      setAction("Remove from list");
    }
  catch (CCopasiException&)
    {
      // handle the case that the compartment does not
      // exist that is to be removed
    }
}

InsertCompartmentRowsCommand::~InsertCompartmentRowsCommand()
{
  pdelete(mpCompartmentData);
}
