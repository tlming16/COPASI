// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeObject.cpp,v $
//   $Revision: 1.28.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/26 22:22:39 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CExpression.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#include "sbml/math/ASTNode.h"
#include "sbml/SBase.h"
#include "sbml/SBMLTypeCodes.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Reaction.h"

CEvaluationNodeObject::CEvaluationNodeObject():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mpValue(NULL),
    mRegisteredObjectCN("")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::OBJECT | subType), data),
    mpValue(NULL),
    mRegisteredObjectCN(data.substr(1, data.length() - 2))
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const CEvaluationNodeObject & src):
    CEvaluationNode(src),
    mpValue(src.mpValue),
    mRegisteredObjectCN(src.mRegisteredObjectCN)
{}

CEvaluationNodeObject::~CEvaluationNodeObject() {}

bool CEvaluationNodeObject::compile(const CEvaluationTree * pTree)
{
  const CExpression * pExpression = dynamic_cast< const CExpression * >(pTree);
  if (!pExpression) return false;

  const CCopasiObject * pObject =
    pExpression->getNodeObject(mRegisteredObjectCN);

  if (pObject)
    mpValue = (C_FLOAT64 *) pObject->getValuePointer();
  else
    mpValue = NULL;

  if (mpValue == NULL) return false;
  if (!pObject->isValueDbl()) return false;

  mData = "<" + mRegisteredObjectCN + ">";

  return (getChild() == NULL); // We must not have any children.
}

CEvaluationNode::Data CEvaluationNodeObject::getData() const
{return "<" + mRegisteredObjectCN + ">";}

bool CEvaluationNodeObject::setData(const Data & data)
{
  mData = data;
  mRegisteredObjectCN = data.substr(1, data.length() - 2);

  return true;
}

std::string CEvaluationNodeObject::getInfix() const
  {return "<" + mRegisteredObjectCN + ">";}

#if 0
std::string CEvaluationNodeObject::getDisplayString(const CEvaluationTree * pTree) const
  {
    const CExpression * pExpression = dynamic_cast< const CExpression * >(pTree);
    if (!pExpression) return false;

    const CCopasiObject * pObject =
      CCopasiContainer::ObjectFromName(mRegisteredObjectCN);

    if (pObject == NULL) return "<" + mRegisteredObjectCN + ">";

    return "<" + pObject->getObjectDisplayName() + ">";
  }
#endif

std::string CEvaluationNodeObject::getDisplayString(const CEvaluationTree * /* pTree */) const
{return mData;}

std::string CEvaluationNodeObject::getDisplay_C_String(const CEvaluationTree * /* pTree */) const
  {
    return "<" + mRegisteredObjectCN + ">";
  }

std::string CEvaluationNodeObject::getDisplay_MMD_String(const CEvaluationTree * /* pTree */) const
  {
    return "<" + mRegisteredObjectCN + ">";
  }

std::string CEvaluationNodeObject::getDisplay_XPP_String(const CEvaluationTree * /* pTree */) const
  {
    return "<" + mRegisteredObjectCN + ">";
  }

CEvaluationNode* CEvaluationNodeObject::createNodeFromASTTree(const ASTNode& node)
{
  CEvaluationNodeObject* pNode = NULL;
  ASTNodeType_t type = node.getType();
  switch (type)
    {
    case AST_NAME_TIME:
    case AST_NAME:
      pNode = new CEvaluationNodeObject(ANY, CCopasiObjectName(std::string("<") + node.getName() + std::string(">")));
      break;
    default:
      break;
    }
  return pNode;
}

ASTNode* CEvaluationNodeObject::toAST() const
  {
    ASTNode* node = new ASTNode();
    node->setType(AST_NAME);
    // since I can not get the model in which this node is located, I just
    // assume that it will always be the current global model.
    CCopasiObject* object = CCopasiContainer::ObjectFromName(mRegisteredObjectCN);
    assert(object);
    // if it is a reference, we get the parent of the reference
    if (object->isReference())
      {
        object = object->getObjectParent();
      }
    // actually we need to get the name from the key of the copasi object
    SBase* pSBase = CCopasiDataModel::Global->getCopasi2SBMLMap()[object];
    CModel* pModel = NULL;
    if (pSBase)
      {
        switch (pSBase->getTypeCode())
          {
          case SBML_COMPARTMENT:
            node->setName(dynamic_cast<Compartment*>(pSBase)->getId().c_str());
            break;
          case SBML_SPECIES:
            node->setName(dynamic_cast<Species*>(pSBase)->getId().c_str());
            break;
          case SBML_PARAMETER:
            node->setName(dynamic_cast<Parameter*>(pSBase)->getId().c_str());
            break;
          case SBML_REACTION:
            node->setName(dynamic_cast<Reaction*>(pSBase)->getId().c_str());
            break;
          case SBML_MODEL:
            node->setType(AST_NAME_TIME);
            node->setName("time");
            pModel = dynamic_cast<CModel*>(object);
            if (pModel == NULL)
              {
                fatalError();
              }
            if (pModel->getInitialTime() != 0.0)
              {
                CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 1);
              }
            break;
          default:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCEvaluationNodeObject + 1);
            break;
          }
      }
    else
      {
        // it must be a local parameter
        node->setName(object->getObjectName().c_str());
      }
    return node;
  }

const CRegisteredObjectName & CEvaluationNodeObject::getObjectCN() const
  {return mRegisteredObjectCN;}

#include "utilities/copasimathml.h"

void CEvaluationNodeObject::writeMathML(std::ostream & out,
                                        const std::vector<std::vector<std::string> > & /* env */,
                                        bool /* expand */,
                                        unsigned C_INT32 l) const
  {
    const CCopasiObject* obj = CCopasiContainer::ObjectFromName(mRegisteredObjectCN);
    out << SPC(l) << CMathMl::getMMLName(obj) << std::endl;
    //or use mValue instead?
  }
