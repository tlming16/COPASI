// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfCallParametersHandler.h"

/**
 * Replace ListOfCallParameters with the name type of the handler and implement the
 * three methods below.
 */
ListOfCallParametersHandler::ListOfCallParametersHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfCallParameters)
{
  init();
}

// virtual
ListOfCallParametersHandler::~ListOfCallParametersHandler()
{}

// virtual
CXMLHandler * ListOfCallParametersHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfCallParametersHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfCallParameters:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfCallParametersHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfCallParameters", ListOfCallParameters, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfCallParameters, BEFORE}}
  };

  return Elements;
}
