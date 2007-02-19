// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLReactionGlyph.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/19 14:08:26 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include<iostream>

#define USE_LAYOUT 1

#include "sbml/layout/ReactionGlyph.h"
#include "sbml/layout/SpeciesReferenceGlyph.h"

#include "CLReactionGlyph.h"
#include "report/CKeyFactory.h"

const std::string CLMetabReferenceGlyph::RoleName[] =
  {
    "undefined role",
    "substrate",
    "product",
    "side substrade",
    "side product",
    "modifier",
    "activator",
    "inhibitor"
    ""
  };

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const std::string & name,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent),
    mMetabGlyphKey(),
    mCurve(),
    mRole(UNDEFINED)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent),
    mMetabGlyphKey(src.mMetabGlyphKey),
    mCurve(src.mCurve),
    mRole(src.mRole)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const SpeciesReferenceGlyph & sbml,
    const std::map<std::string, std::string> & /*modelmap*/,
    std::map<std::string, std::string> & layoutmap,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent),
    mMetabGlyphKey(), //initialized in the body below
    mCurve(), //initialized in the body below
    mRole((Role)sbml.getRole())
{
  //TODO problem: how to translate the sbml species reference id to a copasi key

  //get the copasi key corresponding to the sbml id for the species glyph
  if (sbml.getSpeciesGlyphId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getSpeciesGlyphId());
      if (it != layoutmap.end())
        mMetabGlyphKey = it->second;
    }

  //curve
  if (sbml.getCurve())
    mCurve = CLCurve(*sbml.getCurve());
}

CLMetabGlyph* CLMetabReferenceGlyph::getMetabGlyph() const
  {
    CCopasiObject* tmp = GlobalKeys.get(mMetabGlyphKey);
    return dynamic_cast<CLMetabGlyph*>(tmp);
  }

std::ostream & operator<<(std::ostream &os, const CLMetabReferenceGlyph & g)
{
  os << "    MetabReferenceGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);

  os << "      Role: " << CLMetabReferenceGlyph::RoleName[g.getRole()] << "\n";

  const CLMetabGlyph* tmp = g.getMetabGlyph();
  if (tmp)
    os << "      refers to a MetabGlyph that refers to "
    << tmp->getModelObjectDisplayName() << std::endl;
  os << g.mCurve;

  return os;
}

//*********** CLReactionGlyph ****************************************

CLReactionGlyph::CLReactionGlyph(const std::string & name,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent),
    mCurve()
{}

CLReactionGlyph::CLReactionGlyph(const CLReactionGlyph & src,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent),
    mCurve(src.mCurve)
{}

CLReactionGlyph::CLReactionGlyph(const ReactionGlyph & sbml,
                                 const std::map<std::string, std::string> & modelmap,
                                 std::map<std::string, std::string> & layoutmap,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent),
    mCurve()
{
  //get the copasi key corresponding to the sbml id for the reaction
  if (sbml.getReactionId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getReactionId());
      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }

  //species reference glyphs
  C_INT32 i, imax = sbml.getListOfSpeciesReferenceGlyphs().getNumItems();
  for (i = 0; i < imax; ++i)
    {
      const SpeciesReferenceGlyph* tmp
      = dynamic_cast<const SpeciesReferenceGlyph*>(sbml.getListOfSpeciesReferenceGlyphs().get(i));
      if (tmp)
        addMetabReferenceGlyph(new CLMetabReferenceGlyph(*tmp, modelmap, layoutmap));
    }

  //curve
  if (sbml.getCurve())
    mCurve = CLCurve(*sbml.getCurve());
}

void CLReactionGlyph::addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph)
{
  if (glyph)
    mvMetabReferences.add(glyph, true); //true means vector takes ownership
}

std::ostream & operator<<(std::ostream &os, const CLReactionGlyph & g)
{
  os << "ReactionGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  os << g.mCurve;

  C_INT32 i, imax = g.mvMetabReferences.size();
  if (imax)
    {
      os << "  List of metab reference glyphs: \n";
      for (i = 0; i < imax; ++i)
        os << *g.mvMetabReferences[i];
    }

  return os;
}
