
#ifndef CSOURCECOUNTERFILTER_H
#define CSOURCECOUNTERFILTER_H

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
#include <CRingPhysicsEventCountItem.h>
#include <CRingFragmentItem.h>

class CSourceCounterFilter : public CFilter
{
  private:
    std::map<uint32_t, std::map<uint32_t, uint32_t> > m_counters;
    uint32_t m_defaultId;

  public:

    CSourceCounterFilter(uint32_t defaultId);
    virtual ~CSourceCounterFilter();

    CSourceCounterFilter* clone() const { return new CSourceCounterFilter(*this);}

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

    virtual void finalize();

  private:
    bool counterExists(uint32_t type);
    void setupCounters(uint32_t id);
    void incrementCounter(CRingItem* pItem);

    void printCounters() const;
    std::string translate(uint32_t type) const;
  

};

#endif


