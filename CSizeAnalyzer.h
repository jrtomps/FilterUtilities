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




#ifndef CSIZEANALYZER_CPP
#define CSIZEANALYZER_CPP

#include <CFilter.h>
#include <stdint.h>


/**! \class CSizeAnalyzer
*/
class CSizeAnalyzer : public CFilter
{
  private:
    size_t m_nBytes;

  public:
    CSizeAnalyzer();
    ~CSizeAnalyzer();

    virtual CSizeAnalyzer* clone() const { return new CSizeAnalyzer(*this);}

    // handle the  physics events
    virtual CRingItem* handlePhysicsEventItem(CPhysicsEventItem* pItem);
    virtual CRingItem* handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem);
    virtual CRingItem* handleScalerItem(CRingScalerItem* pItem);
    virtual CRingItem* handleStateChangeItem(CRingStateChangeItem* pItem);
    virtual CRingItem* handleTextItem(CRingTextItem* pItem);
    virtual CRingItem* handleFragmentItem(CRingFragmentItem* pItem);
  
    void finalize();

  private:
    size_t getSize(pRingItem item);
  
};

#endif
