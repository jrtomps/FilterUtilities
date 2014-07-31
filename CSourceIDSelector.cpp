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
#include <DataFormat.h>
#include <CRingItemFactory.h>
#include "CSourceIDSelector.h"


/**! \class CSourceIDSelector
    Here is a sample implementation of a filter to append a reversed copy of the
    data in physics event to its body. This is for illustration purposes.

    See the documentation for the CFilter base class for the virtually declared 
    methods available for dealing with non-physics events. The user has access 
    to all of the different ring item types. In fact, it is not necessary for 
    the user to return the same type of ring item from method as it received. 
*/
CSourceIDSelector::CSourceIDSelector(std::vector<uint32_t> sourceIds) 
  : m_whiteList(sourceIds)
{
}

CSourceIDSelector::~CSourceIDSelector() 
{
}

    // handle the physics events 
CRingItem* CSourceIDSelector::handlePhysicsEventItem(CPhysicsEventItem* pItem) 
{
  // return the original item
  return 0; 
}

    // handle the physics events 
CRingItem* CSourceIDSelector::handleStateChangeItem(CRingStateChangeItem* pItem) 
{
  return 0;
}

// handle the physics events 
CRingItem* CSourceIDSelector::handleScalerItem(CRingScalerItem* pItem) 
{
  // We will only deal with the toplevel ring item source id.
  
  bool targetNoBodyHeader = m_whiteList.size();

  CRingItem* pItemToReturn = 0;
  if (targetNoBodyHeader) {
    pItemToReturn = selectNoBodyHeader(pItem); 
  } else {
    pItemToReturn = selectSourceIds(pItem);
  }

  // return the original item
  return pItemToReturn; 
}

CRingItem* CSourceIDSelector::handleTextItem(CRingTextItem* pItem) 
{
  return 0; 
}

CRingItem* CSourceIDSelector::handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem) 
{
  // return the original item
  return 0; 
}

CRingItem* CSourceIDSelector::handleFragmentItem(CRingFragmentItem* pItem) 
{
  // return the original item
  return 0; 
}

/*!
* Sets the 
*/
bool CSourceIDSelector::isGoodSourceId(uint32_t id) 
{
    vector<uint32_t>::iterator result;
    result = find(m_whiteList.begin(), m_whiteList.end(), id);

    return (result != m_whiteList.end());
}


CRingItem* CSourceIDSelector::selectSourceIds(CRingItem* pItem) 
{
  CRingItem* pItemToReturn=pItem;

  if (pItem->hasBodyHeader()) {

    uint32_t id = pItem->getSourceId();
    if (isGoodSourceId(id)) {
      pItemToReturn = pItem;
    } else {
      pItemToReturn = 0;
    }
     

  } else {
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

