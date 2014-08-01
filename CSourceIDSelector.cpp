/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2014.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Jeromy Tompkins
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/





#include <CFilter.h>
#include <iostream>
#include <algorithm>
#include <DataFormat.h>
#include <CRingItemFactory.h>
#include "CSourceIDSelector.h"

using namespace std;

CSourceIDSelector::CSourceIDSelector(std::vector<uint32_t> sourceIds) 
  : m_whiteList(sourceIds)
{
}

CSourceIDSelector::~CSourceIDSelector() 
{
}

///////////////////////////////////////////////////////////////////////////////
///
//  Begin intelligent handlers

CRingItem* CSourceIDSelector::handleStateChangeItem(CRingStateChangeItem* pItem) 
{
  return processItem(pItem);
}

CRingItem* CSourceIDSelector::handleScalerItem(CRingScalerItem* pItem) 
{
  return processItem(pItem);
}

//////////////////////////////////////////////////////////////////////////////
//
// BEGIN UTILITY METHODS


CRingItem* CSourceIDSelector::processItem(CRingItem* pItem) 
{
  // We will only deal with the toplevel ring item source id.
  
  bool targetNoBodyHeader = (m_whiteList.size()==0);

  CRingItem* pItemToReturn = 0;
  if (targetNoBodyHeader) {
    pItemToReturn = selectNoBodyHeader(pItem); 
  } else {
    pItemToReturn = selectSourceIds(pItem);
  }

  // return the original item
  return pItemToReturn; 

}

// Determine whether or not the id is one that we care about
bool CSourceIDSelector::isGoodSourceId(uint32_t id) 
{
    vector<uint32_t>::iterator result;
    result = find(m_whiteList.begin(), m_whiteList.end(), id);

    // Return whether the item was in the list
    return (result != m_whiteList.end());
}

// figure out what to do when the list of source ids is non-empty
CRingItem* CSourceIDSelector::selectSourceIds(CRingItem* pItem) 
{
  CRingItem* pItemToReturn=pItem;

  
  if (pItem->hasBodyHeader()) {
    uint32_t id = pItem->getSourceId();

    // we care now to see if it is a good id
    if (isGoodSourceId(id)) {
      pItemToReturn = pItem;
    } else {
      pItemToReturn = 0;
    }
     

  } else { // no body header is automatically bad
    pItemToReturn=0;
  }

  return pItemToReturn;

}

/*! Only send on ring items that have no body header
*
* \param pItem the ring item to process
* 
* \return CRingItem*
* \retval NULL - when ring item has body header
* \retval the pointer passed in as the argument
*
*/
CRingItem* CSourceIDSelector::selectNoBodyHeader(CRingItem* pItem) 
{
  CRingItem* pItemToReturn=pItem;

  if (pItem->hasBodyHeader()) {
    pItemToReturn=0;
  }

  return pItemToReturn;

}

///////////////////////////////////////////////////////////////////
//
// BEGIN UNINTELLIGENT HANDLERS THAT RETURN NULL


// handle the physics events 
CRingItem* CSourceIDSelector::handlePhysicsEventItem(CPhysicsEventItem* pItem) 
{
  // return the original item
  return 0; 
}

CRingItem* CSourceIDSelector::handleTextItem(CRingTextItem* pItem) 
{
  return 0; 
}

CRingItem* 
CSourceIDSelector::handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem) 
{
  // return the original item
  return 0; 
}

CRingItem* CSourceIDSelector::handleFragmentItem(CRingFragmentItem* pItem) 
{
  // return the original item
  return 0; 
}
