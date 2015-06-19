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
#include "CCopyFilter.h"


/**! \class CCopyFilter
    Here is a sample implementation of a filter to append a reversed copy of the
    data in physics event to its body. This is for illustration purposes.

    See the documentation for the CFilter base class for the virtually declared 
    methods available for dealing with non-physics events. The user has access 
    to all of the different ring item types. In fact, it is not necessary for 
    the user to return the same type of ring item from method as it received. 
*/
CCopyFilter::CCopyFilter() 
  : m_cachedItem(0)
{
}

CCopyFilter::~CCopyFilter() 
{
  if (m_cachedItem) {
    std::cout << "\nLast item body " << std::endl;
    std::cout << m_cachedItem->toString() << std::endl;
  }
}

    // handle the physics events 
CRingItem* CCopyFilter::handlePhysicsEventItem(CPhysicsEventItem* pItem) 
{
   updateCache(pItem);

  // return the original item
  return pItem; 
}

    // handle the physics events 
CRingItem* CCopyFilter::handleStateChangeItem(CRingStateChangeItem* pItem) 
{
   updateCache(pItem);

  // return the original item
  return pItem; 
}

    // handle the physics events 
CRingItem* CCopyFilter::handleScalerItem(CRingScalerItem* pItem) 
{
   updateCache(pItem);

  // return the original item
  return pItem; 
}

CRingItem* CCopyFilter::handleTextItem(CRingTextItem* pItem) 
{
   updateCache(pItem);

  // return the original item
  return pItem; 
}

CRingItem* CCopyFilter::handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem) 
{
   updateCache(pItem);

  // return the original item
  return pItem; 
}

CRingItem* CCopyFilter::handleFragmentItem(CRingFragmentItem* pItem) 
{
   updateCache(pItem);

  // return the original item
  return pItem; 
}

void CCopyFilter::updateCache(CRingItem* item) 
{
  CRingItem* citem = CRingItemFactory::createRingItem(*item);
  if (citem) {
    if (m_cachedItem) {
      delete m_cachedItem; 
    }
    m_cachedItem = citem;
  }
}

