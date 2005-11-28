/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeLogical.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: nsimus $ 
   $Date: 2005/11/28 14:02:39 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeLogical::CEvaluationNodeLogical():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeLogical::CEvaluationNodeLogical(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::OPERATOR | subType), data),
    mpLeft(NULL),
    mpRight(NULL)
{
  switch (mType & 0x00FFFFFF)
    {
    case OR:
      mPrecedence = PRECEDENCE_LOGIG_OR;
      break;

    case XOR:
      mPrecedence = PRECEDENCE_LOGIG_XOR;
      break;

    case AND:
      mPrecedence = PRECEDENCE_LOGIG_AND;
      break;

    case EQ:
      mPrecedence = PRECEDENCE_LOGIG_EQ;
      break;

    case NE:
      mPrecedence = PRECEDENCE_LOGIG_NE;
      break;

    case GT:
      mPrecedence = PRECEDENCE_LOGIG_GT;
      break;

    case GE:
      mPrecedence = PRECEDENCE_LOGIG_GE;
      break;

    case LT:
      mPrecedence = PRECEDENCE_LOGIG_LT;
      break;

    case LE:
      mPrecedence = PRECEDENCE_LOGIG_LE;
      break;
    }
}

CEvaluationNodeLogical::CEvaluationNodeLogical(const CEvaluationNodeLogical & src):
    CEvaluationNode(src)
{}

CEvaluationNodeLogical::~CEvaluationNodeLogical() {}

bool CEvaluationNodeLogical::compile(const CEvaluationTree * /* pTree */)
{
  mpLeft = static_cast<CEvaluationNode *>(getChild());
  if (mpLeft == NULL) return false;

  mpRight = static_cast<CEvaluationNode *>(mpLeft->getSibling());
  if (mpRight == NULL) return false;

  return (mpRight->getSibling() == NULL); // We must have exactly two children
}

std::string CEvaluationNodeLogical::getInfix() const
  {
    if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
      {
        Data Infix;

        if (*mpLeft < *(CEvaluationNode *)this)
          Infix = "(" + mpLeft->getInfix() + ")";
        else
          Infix = mpLeft->getInfix() + " ";

        Infix += mData;

        if (!(*(CEvaluationNode *)this < *mpRight))
          Infix += "(" + mpRight->getInfix() + ")";
        else
          Infix += " " + mpRight->getInfix();

        return Infix;
      }
    else
      return "@";
  }

std::string CEvaluationNodeLogical::getDisplayString(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
      {
        Data DisplayString;

        if (*mpLeft < *(CEvaluationNode *)this)
          DisplayString = "(" + mpLeft->getDisplayString(pTree) + ")";
        else
          DisplayString = mpLeft->getDisplayString(pTree) + " ";

        DisplayString += mData;

        if (!(*(CEvaluationNode *)this < *mpRight))
          DisplayString += "(" + mpRight->getDisplayString(pTree) + ")";
        else
          DisplayString += " " + mpRight->getDisplayString(pTree);

        return DisplayString;
      }
    else
      return "@";
  }

std::string CEvaluationNodeLogical::getDisplay_C_String(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
      {
        Data DisplayString;

        if (*mpLeft < *(CEvaluationNode *)this)
          DisplayString = "(" + mpLeft->getDisplay_C_String(pTree) + ")";
        else
          DisplayString = mpLeft->getDisplay_C_String(pTree) + " ";

        DisplayString += mData;

        if (!(*(CEvaluationNode *)this < *mpRight))
          DisplayString += "(" + mpRight->getDisplay_C_String(pTree) + ")";
        else
          DisplayString += " " + mpRight->getDisplay_C_String(pTree);

        return DisplayString;
      }
    else
      return "@";
  }

CEvaluationNode* CEvaluationNodeLogical::createNodeFromASTTree(const ASTNode& node)
{
  SubType subType;
  std::string data = "";
  switch (node.getType())
    {
    case AST_LOGICAL_AND:
      subType = AND;
      data = "and";
      break;
    case AST_LOGICAL_OR:
      subType = OR;
      data = "or";
      break;
    case AST_LOGICAL_XOR:
      subType = XOR;
      data = "xor";
      break;
    case AST_RELATIONAL_EQ:
      subType = EQ;
      data = "eq";
      break;
    case AST_RELATIONAL_GEQ:
      subType = GE;
      data = "ge";
      break;
    case AST_RELATIONAL_GT:
      subType = GT;
      data = "gt";
      break;
    case AST_RELATIONAL_LEQ:
      subType = LE;
      data = "le";
      break;
    case AST_RELATIONAL_LT:
      subType = LT;
      data = "lt";
      break;
    case AST_RELATIONAL_NEQ:
      subType = NE;
      data = "ne";
      break;
    default:
      subType = INVALID;
      break;
    }
  CEvaluationNode* convertedNode = new CEvaluationNodeLogical(subType, data);
  // convert the two children
  if (subType != INVALID)
    {
      convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
      convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getRightChild()));
    }

  return convertedNode;
}

ASTNode* CEvaluationNodeLogical::toAST() const
  {
    SubType subType = (SubType)CEvaluationNode::subType(this->getType());
    ASTNode* node = new ASTNode();
    switch (subType)
      {
      case AND:
        node->setType(AST_LOGICAL_AND);
        break;
      case OR:
        node->setType(AST_LOGICAL_OR);
        break;
      case XOR:
        node->setType(AST_LOGICAL_XOR);
        break;
      case EQ:
        node->setType(AST_RELATIONAL_EQ);
        break;
      case NE:
        node->setType(AST_RELATIONAL_NEQ);
        break;
      case GT:
        node->setType(AST_RELATIONAL_GT);
        break;
      case GE:
        node->setType(AST_RELATIONAL_GEQ);
        break;
      case LT:
        node->setType(AST_RELATIONAL_LT);
        break;
      case LE:
        node->setType(AST_RELATIONAL_LEQ);
        break;
      case INVALID:
        break;
      default:
        subType = INVALID;
        break;
      }
    if (subType != INVALID)
      {
        const CEvaluationNode* child1 = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* child2 = dynamic_cast<const CEvaluationNode*>(child1->getSibling());
        node->addChild(child1->toAST());
        node->addChild(child2->toAST());
      }

    return node;
  }
