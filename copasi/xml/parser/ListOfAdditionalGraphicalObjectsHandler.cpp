// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfAdditionalGraphicalObjectsHandler.h"

/**
 * Replace ListOfAdditionalGraphicalObjects with the name type of the handler and implement the
 * three methods below.
 */
ListOfAdditionalGraphicalObjectsHandler::ListOfAdditionalGraphicalObjectsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfAdditionalGraphicalObjects)
{
  init();
}

// virtual
ListOfAdditionalGraphicalObjectsHandler::~ListOfAdditionalGraphicalObjectsHandler()
{}

// virtual
CXMLHandler * ListOfAdditionalGraphicalObjectsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfAdditionalGraphicalObjectsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfAdditionalGraphicalObjects:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfAdditionalGraphicalObjectsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfAdditionalGraphicalObjects", ListOfAdditionalGraphicalObjects, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfAdditionalGraphicalObjects, BEFORE}}
  };

  return Elements;
}
