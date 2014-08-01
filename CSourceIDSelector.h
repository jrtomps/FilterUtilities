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
    std::vector<uint32_t> m_whiteList;  //!< the list of wanted source ids 

  public:
    /*! Constructor
    * 
    * The instantiation of the filter object takes a vector of source ids
    * that are to be cared about. By default, the argument is an empty 
    * vector, which translates to passing on ring items that don't have 
    * body headers. 
    *
    * \param sourceids the list of source ids to pass on
    */
    CSourceIDSelector(std::vector<uint32_t> sourceids=std::vector<uint32_t>());
    ~CSourceIDSelector();

    /*! Virtual copy constructor */
    virtual CSourceIDSelector* clone() const 
    { 
      return new CSourceIDSelector(*this);
    }

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    // 
    // handleScalerItem and handleStateChangeItem on the only methods that 
    // are intelligent.

    /*! Process scaler items 
    *
    * This ultimately calls processItem to determine whether or not to send the
    * item through the filter.
    *
    * \return CRingItem*
    * \retval pItem - item satisfies criteria to be passed on
    * \retval NULL  - otherwise
    */
    virtual CRingItem* handleScalerItem(CRingScalerItem* pItem);

    /*! Process state change items 
    *
    * This ultimately calls processItem to determine whether or not to send the
    * item through the filter.
    *
    * \return CRingItem*
    * \retval pItem - item satisfies criteria to be passed on
    * \retval NULL  - otherwise
    */
    virtual CRingItem* handleStateChangeItem(CRingStateChangeItem* pItem);

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    // Begin unintelligent handlers
    // 
 
    // The rest of these all return NULL unconditionally. We don't care about
    // these types of ring items.
    virtual CRingItem* handlePhysicsEventItem(CPhysicsEventItem* pItem);
    virtual CRingItem* handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem);
    virtual CRingItem* handleTextItem(CRingTextItem* pItem);
    virtual CRingItem* handleFragmentItem(CRingFragmentItem* pItem);
  
  private:
    /*! Select whether or not a ring item should be passed on
     *
     * This compares what is in the list of source ids that are 
     * white listed with the source id (or lack thereof) of
     * the ring item. If the source id is present, then the
     * ring item is passed on if the source id is found in the white list.
     * If instead the white list is empty, then the item is
     * only passed on if the ring item has no body header.
     *
     * \param item the ring item to analyze
     *
     * \returns CRingItem*
     * \retval  pItem - if it is a wanted ring item 
     * \retval  NULL  - if it is not wanted
    */
    CRingItem* processItem(CRingItem* item);

    /*! Checks to see if source id is in white list
    *
    * This simply tries to find whether a number is in the 
    * list of source ids.
    *
    * \param id the source id the check
    *
    * \return bool
    * \retval true  - id is found in m_whiteList
    * \retval false - otherwise
    */
    bool isGoodSourceId(uint32_t id);

    /*! Logic for processing item when white list is not empty
    *
    * If the white list contains a number of source ids, then
    * this method handles the processing of the ring items.
    * If the item passed in has a source id that is in the list
    * it is returned. Otherwise it is discarded.
    *
    * \param item the item to process
    *
    * \return CRingItem*
    * \retval item - if item's source id is in white list
    * \retval NULL - otherwise
    */
    CRingItem* selectSourceIds(CRingItem* item);
  
    /*! Logic for processing items when white list is empty
    *
    * When the m_whiteList is empty, the filter will select
    * to pass on only ring items with no body header. This 
    * function handles that logic.
    *
    * \param item ring item to analyze
    *
    * \return CRingItem*
    * \retval item - if item has no body header
    * \retval NULL - if item has a body header
    */
    CRingItem* selectNoBodyHeader(CRingItem* item);


};

#endif
