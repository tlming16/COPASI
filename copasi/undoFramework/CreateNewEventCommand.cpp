// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewEventCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "UI/CQEventWidget1.h"
#include "UndoEventData.h"

#include "CreateNewEventCommand.h"

CreateNewEventCommand::CreateNewEventCommand(CQEventWidget1 *pEventWidget)
  : CCopasiUndoCommand("Event", EVENT_CREATE)
  , mpEventData(NULL)
  , mpEventWidget(pEventWidget)
{
  this->setText(createNewEventText());
}
void CreateNewEventCommand::redo()
{
  if (mpEventData == NULL)
    {
      mpEventWidget->createNewEvent();

      std::string sName = mpEventWidget->mpEvent->getObjectName();
      mpEventData->setKey(mpEventWidget->mpEvent->getKey());
      mpEventData->setName(sName);
      mpEventData->setDelayExpression(mpEventWidget->mpEvent->getDelayExpression());
      mpEventData->setTriggerExpression(mpEventWidget->mpEvent->getTriggerExpression());
      mpEventData->setPriorityExpression(mpEventWidget->mpEvent->getPriorityExpression());
      setName(sName);
    }
  else
    {
      mpEventWidget->addEvent(mpEventData);
    }

  setUndoState(true);
  setAction("Create");
}

void CreateNewEventCommand::undo()
{
  mpEventWidget->deleteEvent(mpEventData);
  setUndoState(false);
  setAction("Delete");
}

QString CreateNewEventCommand::createNewEventText() const
{
  return QObject::tr(": Created new event ");
}

CreateNewEventCommand::~CreateNewEventCommand()
{
  pdelete(mpEventData);
}

UndoData *CreateNewEventCommand::getUndoData() const
{
  return mpEventData;
}
