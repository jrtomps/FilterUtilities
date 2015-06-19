
#ifndef CMONOTONICTSTAMP_H
#define CMONOTONICTSTAMP_H

#include <stdint.h>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <CFilter.h>
#include <DataFormat.h>
#include <CRingItem.h>
#include <CRingStateChangeItem.h>
#include <CPhysicsEventItem.h>
#include <CRingTextItem.h>
#include <CRingItemFactory.h>
#include "FragmentIndex.h"
#include <CRingPhysicsEventCountItem.h>
#include <CRingFragmentItem.h>

class CMonotonicTstamp : public CFilter
{
  private:
    uint64_t m_lastTstamp;
    uint64_t m_evtCount;

  public:

    CMonotonicTstamp();
    virtual ~CMonotonicTstamp();

    CMonotonicTstamp* clone() const { return new CMonotonicTstamp(*this);}

    // The default handlers
    virtual CRingItem* handleRingItem(CRingItem* pItem) 
    {
      incrementCounter(pItem);
      return pItem;
    }

    virtual CRingItem* handleStateChangeItem(CRingStateChangeItem* pItem) 
    {
      incrementCounter(pItem);
      return static_cast<CRingItem*>(pItem);
    }

    virtual CRingItem* handleScalerItem(CRingScalerItem* pItem) 
    {
      incrementCounter(pItem);
      if (pItem->hasBodyHeader()) {
        uint64_t tstamp = pItem->getEventTimestamp();
//        updateTstamp(tstamp);
      }
      return static_cast<CRingItem*>(pItem);
    }

    virtual CRingItem* handleTextItem(CRingTextItem* pItem) 
    {
      incrementCounter(pItem);
      return static_cast<CRingItem*>(pItem);
    }

    virtual CRingItem* handlePhysicsEventItem(CPhysicsEventItem* pItem) 
    {
      incrementCounter(pItem);
      FragmentIndex index(reinterpret_cast<uint16_t*>(pItem->getBodyPointer()));
      FragmentIndex::iterator it = index.begin();
      FragmentIndex::iterator itend = index.end();
      while (it != itend) {
        uint64_t tstamp = it->s_timestamp;
        updateTstamp(tstamp);
        ++it;
      }
      return static_cast<CRingItem*>(pItem);
    }

    virtual CRingItem* 
      handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem) 
      {
        incrementCounter(pItem);
        return static_cast<CRingItem*>(pItem);
      }

    virtual CRingItem* handleFragmentItem(CRingFragmentItem* pItem)
    {
      incrementCounter(pItem);
      return static_cast<CRingItem*>(pItem);
    }

  private:
    void incrementCounter(CRingItem* pItem);
    void updateTstamp(uint64_t tstamp);

};

#endif


