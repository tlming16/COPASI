// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModelParameterHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "model/CModelParameter.h"

/**
 * Replace ModelParameter with the name type of the handler and implement the
 * three methods below.
 */
ModelParameterHandler::ModelParameterHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelParameter)
{
  init();
}

// virtual
ModelParameterHandler::~ModelParameterHandler()
{}

// virtual
CXMLHandler * ModelParameterHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * CN;
  const char * pValue;
  C_FLOAT64 Value = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  const char * pType;
  CModelParameter::Type Type;
  const char * pSimulationType;
  CModelEntity::Status SimulationType;

  switch (mCurrentElement.first)
    {
      case ModelParameter:
        // Element specific code.
        CN = mpParser->getAttributeValue("cn", papszAttrs);
        pValue = mpParser->getAttributeValue("value", papszAttrs);
        pType = mpParser->getAttributeValue("type", papszAttrs);
        pSimulationType = mpParser->getAttributeValue("simulationType", papszAttrs);

        if (pValue != NULL)
          {
            Value = CCopasiXMLInterface::DBL(pValue);
          }

        Type = toEnum(pType, CModelParameter::TypeNames, CModelParameter::unknown);

        switch (Type)
          {
            case CModelParameter::Species:
              mpData->pCurrentModelParameter = new CModelParameterSpecies(mpData->ModelParameterGroupStack.top());
              break;

            case CModelParameter::Compartment:
              mpData->pCurrentModelParameter = new CModelParameterCompartment(mpData->ModelParameterGroupStack.top());
              break;

            case CModelParameter::ReactionParameter:
              mpData->pCurrentModelParameter = new CModelParameterReactionParameter(mpData->ModelParameterGroupStack.top());
              break;

            default:
              mpData->pCurrentModelParameter = new CModelParameter(mpData->ModelParameterGroupStack.top(), Type);
              break;
          }

        mpData->pCurrentModelParameter->setCN(std::string(CN));

        SimulationType = toEnum(pSimulationType, CModelEntity::XMLStatus, CModelEntity::FIXED);
        mpData->pCurrentModelParameter->setSimulationType(SimulationType);

        mpData->pCurrentModelParameter->setValue(Value, CCore::Framework::ParticleNumbers);
        break;

      case InitialExpression:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ModelParameterHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ModelParameter:
        finished = true;
        break;

      case InitialExpression:
      {
        size_t Size = CCopasiMessage::size();

        mpData->pCurrentModelParameter->setInitialExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ModelParameterHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ModelParameter, HANDLER_COUNT}},
    {"ModelParameter", ModelParameter, ModelParameter, {InitialExpression, AFTER, HANDLER_COUNT}},
    {"InitialExpression", InitialExpression, CharacterData, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
