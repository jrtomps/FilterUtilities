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
#include "CSizeAnalyzer.h"


/**! \class CSizeAnalyzer
*/
CSizeAnalyzer::CSizeAnalyzer() 
  : m_nBytes(0)
{
}

CSizeAnalyzer::~CSizeAnalyzer() 
{
}

CSizeAnalyzer::finalize() 
{
  std::cout << "\nSize Summary" << std::endl;
  std::cout << "Read " << m_nBytes << " bytes" << std::endl;
}

    // handle the physics events 
CRingItem* CSizeAnalyzer::handlePhysicsEventItem(CPhysicsEventItem* pItem) 
{
  m_nBytes += getSize(pItem->getItemPointer());

  // return the original item
  return pItem; 
}

    // handle the physics events 
CRingItem* CSizeAnalyzer::handleStateChangeItem(CRingStateChangeItem* pItem) 
{
  m_nBytes += getSize(pItem->getItemPointer());

  // return the original item
  return pItem; 
}

    // handle the physics events 
CRingItem* CSizeAnalyzer::handleScalerItem(CRingScalerItem* pItem) 
{
  m_nBytes += getSize(pItem->getItemPointer());

  // return the original item
  return pItem; 
}

CRingItem* CSizeAnalyzer::handleTextItem(CRingTextItem* pItem) 
{
  m_nBytes += getSize(pItem->getItemPointer());

  // return the original item
  return pItem; 
}

CRingItem* CSizeAnalyzer::handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem) 
{
  m_nBytes += getSize(pItem->getItemPointer());

  // return the original item
  return pItem; 
}

CRingItem* CSizeAnalyzer::handleFragmentItem(CRingFragmentItem* pItem) 
{
  m_nBytes += getSize(pItem->getItemPointer());

  // return the original item
  return pItem; 
}

size_t CSizeAnalyzer::getSize(pRingItem item) 
{
  return item->s_header.s_size;
}

