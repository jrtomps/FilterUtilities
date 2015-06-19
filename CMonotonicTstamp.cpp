
#include "CMonotonicTstamp.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <FragmentIndex.h>

using namespace std;

CMonotonicTstamp::CMonotonicTstamp()
  : m_lastTstamp(0), m_evtCount(0) 
{
}

CMonotonicTstamp::~CMonotonicTstamp() 
{
}


void CMonotonicTstamp::incrementCounter(CRingItem* pItem) 
{
  ++m_evtCount;
}

void CMonotonicTstamp::updateTstamp(uint64_t currentTstamp) 
{
    if (currentTstamp < m_lastTstamp) {
      std::cout << "Timestamp jumped backwards from " << m_lastTstamp << " to " << currentTstamp;
      std::cout << " @ evt # " << m_evtCount << std::endl;
    }

    m_lastTstamp = currentTstamp;

}

