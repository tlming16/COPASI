// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ReactionDataChangeCommand.cpp
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */
#include <QDebug>

#include "copasi/copasi.h"
#include "copasi/UI/qtUtilities.h"

#include "copasi/core/CRootContainer.h"

#include "ReactionDataChangeCommand.h"
#include "copasi/UI/CQReactionDM.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"

ReactionDataChangeCommand::ReactionDataChangeCommand(
  const QModelIndex& index,
  const QVariant& value,
  CQReactionDM *pReactionDM)
  : CCopasiUndoCommand("Reaction", REACTION_DATA_CHANGE, "Change")
  , mNew(value)
  , mOld(index.data(Qt::DisplayRole))
  , mpReactionDM(pReactionDM)
  , mColumn(index.column())
  , mOldFunctionName()
  , mNewFunctionName("")
  , mCreatedObjects()
{
  // stores the data

  assert(pReactionDM->getDataModel() != NULL);
  CModel * pModel = pReactionDM->getDataModel()->getModel();
  assert(pModel != NULL);

  CDataVectorNS < CReaction > &reactions = pModel->getReactions();

  if ((int)reactions.size() <= index.row())
    {
      return;
    }

  CReaction *pRea = &reactions[index.row()];
  mOldFunctionName = FROM_UTF8(pRea->getFunction()->getObjectName());

  //set the data for UNDO history
  setName(pRea->getObjectName());
  setKey(pRea->getKey());
  setOldValue(TO_UTF8(mOld.toString()));
  setNewValue(TO_UTF8(mNew.toString()));

  switch (mColumn)
    {
      case 0:
        setProperty("");
        break;

      case 1:
        setProperty("Name");
        break;

      case 2:
        setProperty("Reaction");
        break;
    }

  setText(QString(": Changed reaction %1").arg(getProperty().c_str()));
}

ReactionDataChangeCommand::~ReactionDataChangeCommand()
{
}

void ReactionDataChangeCommand::redo()
{
  mpReactionDM->reactionDataChange(getKey(), mNew, mColumn, mNewFunctionName, mCreatedObjects);
  setAction("Change");
}

void ReactionDataChangeCommand::undo()
{
  mpReactionDM->reactionDataChange(getKey(), mOld, mColumn, mOldFunctionName, mCreatedObjects);
  setAction("Undone change");
}
