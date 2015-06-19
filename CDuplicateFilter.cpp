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
#include "CDuplicateFilter.h"
#include <RingItemComparisons.h>


/**! \class CDuplicateFilter
    Here is a sample implementation of a filter to append a reversed copy of the
    data in physics event to its body. This is for illustration purposes.

    See the documentation for the CFilter base class for the virtually declared 
    methods available for dealing with non-physics events. The user has access 
    to all of the different ring item types. In fact, it is not necessary for 
    the user to return the same type of ring item from method as it received. 
*/
CDuplicateFilter::CDuplicateFilter() 
  : m_cachedItem(nullptr)
{
}

CDuplicateFilter::CDuplicateFilter(const CDuplicateFilter& rhs) 
  : m_cachedItem(nullptr)
{
  //  item is different than the last
  if (rhs.m_cachedItem) {
    CRingItem* citem = CRingItemFactory::createRingItem(*rhs.m_cachedItem);
    if (citem) {
      // successfully copied the new item...
      //
      // cache the new copy
      m_cachedItem = citem;
    }
  }

  delete m_cachedItem;
}
CDuplicateFilter::~CDuplicateFilter() 
{
  delete m_cachedItem;
}

    // handle the physics events 
CRingItem* CDuplicateFilter::handlePhysicsEventItem(CPhysicsEventItem* pItem) 
{
  return filterDuplicate(pItem);

}

    // handle the physics events 
CRingItem* CDuplicateFilter::handleStateChangeItem(CRingStateChangeItem* pItem) 
{
  return filterDuplicate(pItem);
}

    // handle the physics events 
CRingItem* CDuplicateFilter::handleScalerItem(CRingScalerItem* pItem) 
{
  return filterDuplicate(pItem);
}

CRingItem* CDuplicateFilter::handleTextItem(CRingTextItem* pItem) 
{
  return filterDuplicate(pItem);
}

CRingItem* CDuplicateFilter::handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem) 
{
   return filterDuplicate(pItem);
}

CRingItem* CDuplicateFilter::handleFragmentItem(CRingFragmentItem* pItem) 
{
  return filterDuplicate(pItem);
}

// The money method.
CRingItem* CDuplicateFilter::filterDuplicate(CRingItem* item) 
{
  if (item == nullptr) return item;

  CRingItem* pToReturn = item;

  if (m_cachedItem) {
    // only compare if there is a cached item to compare to.
    pRingItem pNewItem = reinterpret_cast<pRingItem>(item->getItemPointer());
    pRingItem pCachedItem = reinterpret_cast<pRingItem>(m_cachedItem->getItemPointer());
    if (*pNewItem == *pCachedItem) {
      // the item was a duplicate
      pToReturn = nullptr;
    } else {
      //  item is different than the last
      CRingItem* citem = CRingItemFactory::createRingItem(*item);
      if (citem) {
        // successfully copied the new item...
        //
        // delete the old copy
        delete m_cachedItem; 

        // cache the new copy
        m_cachedItem = citem;
      }
    }
  } else {
     // There is no cached item... copy the current
      CRingItem* citem = CRingItemFactory::createRingItem(*item);
      if (citem) {
        // successfully copied the new item... store it.
        m_cachedItem = citem;
      }
  }

  // should return nullptr for duplicates and the original item
  // for uniques
  return pToReturn;
}

