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




#ifndef CSOURCEIDSELECTOR_H
#define CSOURCEIDSELECTOR_H

#include <CFilter.h>
#include <stdint.h>
#include <vector>

/**! \class CSourceIDSelector

  This class simply understands how to filter out all scaler
  items that have a source id that it doesn't understand. It 
  keeps a list of source ids that it will pass on. That list is 
  the so-called white list. All source ids that do not lie in
  that list will not pass through the filter. However, if no
  source ids are provided, the filter will only output data
  that has no body header because there is no source id in that
  case.

*/
class CSourceIDSelector : public CFilter
{
  private:
    std::vector<uint32_t> m_whiteList;

  public:
    CSourceIDSelector(std::vector<uint32_t> sourceids=std::vector<uint32_t>());
    ~CSourceIDSelector();

    virtual CSourceIDSelector* clone() const { return new CSourceIDSelector(*this);}

    // handle the  physics events
    virtual CRingItem* handlePhysicsEventItem(CPhysicsEventItem* pItem);

    // handle the  physics events
    virtual CRingItem* handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem);
    virtual CRingItem* handleScalerItem(CRingScalerItem* pItem);
    virtual CRingItem* handleStateChangeItem(CRingStateChangeItem* pItem);
    virtual CRingItem* handleTextItem(CRingTextItem* pItem);
    virtual CRingItem* handleFragmentItem(CRingFragmentItem* pItem);
  
  private:
    bool isGoodSourceId(uint32_t id);
    CRingItem* selectSourceIds(CRingItem* item);
    CRingItem* selectNoBodyHeader(CRingItem* item);


};

#endif
