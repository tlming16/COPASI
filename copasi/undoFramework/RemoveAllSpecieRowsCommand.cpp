/*
 * RemoveAllSpecieRowsCommand.cpp
 *
 *  Created on: 26 Aug 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "UI/CQSpecieDM.h"
#include "function/CFunctionDB.h"

#include "model/CReaction.h"
#include "model/CReactionInterface.h"

#include "RemoveAllSpecieRowsCommand.h"
#include "UndoSpecieData.h"
#include "UndoReactionData.h"

RemoveAllSpecieRowsCommand::RemoveAllSpecieRowsCommand(CQSpecieDM * pSpecieDM, const QModelIndex&) {
	mpSpecieDM = pSpecieDM;

	assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
	CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
	assert(pDataModel != NULL);
	CModel * pModel = pDataModel->getModel();

	assert(pModel != NULL);

	for (int i = 0; i != pSpecieDM->rowCount()-1; ++i)
	{
		UndoSpecieData *data = new UndoSpecieData();

		if (pModel->getMetabolites()[i]){
			data->setName(pModel->getMetabolites()[i]->getObjectName());
			data->setIConc(pModel->getMetabolites()[i]->getInitialConcentration());
			data->setCompartment(pModel->getMetabolites()[i]->getCompartment()->getObjectName());
			data->setStatus(pModel->getMetabolites()[i]->getStatus());

			setDependentObjects(pModel->getMetabolites()[i]->getDeletedObjects());
			data->setReactionDependencyObjects(getReactionData());

			mpSpecieData.append(data);
		}


	}

	this->setText(removeAllSpecieRowsText());
}

void RemoveAllSpecieRowsCommand::redo(){
	mpSpecieDM->removeAllSpecieRows();
}

void RemoveAllSpecieRowsCommand::undo(){
	mpSpecieDM->insertSpecieRows(mpSpecieData);
}

QString RemoveAllSpecieRowsCommand::removeAllSpecieRowsText() const {
	return QObject::tr(": Removed All Species");
}

RemoveAllSpecieRowsCommand::~RemoveAllSpecieRowsCommand() {
	// TODO Auto-generated destructor stub
}

