// XA port of the Memory Test Library

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/




#include "PUST_ramtestlib.h"

#include "locate_boot_code.h"

/* START DON'T MOVE THIS... unless you exactly know why... */

/* NOINIT , otherwise they would be cleared by the startup code ! */
/* Keep it declared here to be at a fixed address ! */

#pragma NOINIT
UWORD16 _error_code;
#pragma INIT

/* END DON'T MOVE THIS */


/* statics */
static datum memTestDataBus(volatile datum xhuge * address);
static datum xhuge *memTestAddressBus(volatile datum xhuge * baseAddress, UWORD32 nBytes);
#if 0
static datum xhuge *memTestDevice(volatile datum xhuge * baseAddress, UWORD32 nBytes);
#endif

/*******************************************************************
 *
 * Function:    memTestDataBus()
 *
 * Description: Test the data bus wiring in a memory region by
 *              performing a walking 1's test at a fixed address
 *              within that region. The address (and hence the
 *              memory region) is selected by the caller.
 *
 * Notes:
 *
 * Returns:     0 if the test succeeds.
 *              A non-zero result is the first pattern that failed.
 *
 *******************************************************************/
datum memTestDataBus(volatile datum xhuge * address)
{
  datum pattern;
  
  /*
   * Perform a walking 1's test at the given address
   */
  for (pattern = 1; pattern != 0; pattern <<= 1)
  {
  	_srvwdt_();

    /*
     * Write the test pattern
     */
    *address = pattern;
    
    /*
     * Read it back (immediately is okay for this test).
     */
    if (*address != pattern)
    {
      return (pattern);
    }
  }
  
  return (0);
  
} /* memTestDataBus() */


/**********************************************************************
 *
 * Function:    memTestAddressBus()
 *
 * Description: Test the address bus wiring in a memory region by
 *              performing a walking 1's test on the relevant bits
 *              of the address and checking for aliasing.  The test
 *              will find single-bit address failures such as stuck
 *              -high, stuck-low, and shorted pins.  The base address
 *              and size of the region are selected by the caller.
 *
 * Notes:       For best results, the selected base address should
 *              have enough LSB 0's to guarantee single address bit
 *              changes.  For example, to test a 64-Kbyte region, 
 *              select a base address on a 64-Kbyte boundary.  Also, 
 *              select the region size as a power-of-two--if at all 
 *              possible.
 *
 * Returns:     NULL if the test succeeds.  
 *              A non-zero result is the first address at which an
 *              aliasing problem was uncovered.  By examining the
 *              contents of memory, it may be possible to gather
 *              additional information about the problem.
 *
 **********************************************************************/
datum xhuge *memTestAddressBus(volatile datum xhuge * baseAddress, UWORD32 nBytes)
{
  UWORD32 addressMask = (nBytes - 1);
  UWORD32 offset;
  UWORD32 testOffset;
  
  datum pattern     = (datum) 0xAAAAAAAA;
  datum antipattern = (datum) 0x55555555;
  
  /*
   * Write the default pattern at each of the power-of-two offsets.
   */
  for (offset = sizeof(datum); (offset & addressMask) != 0; offset <<= 1)
  {
    _srvwdt_();
    baseAddress[offset] = pattern;
  }
  
  /*
   * Check for address bits stuck high
   */
  testOffset = 0;
  baseAddress[testOffset] = antipattern;
  
  for (offset = sizeof(datum); (offset & addressMask) != 0; offset <<= 1)
  {
    if (baseAddress[offset] != pattern)
    {
      return ((datum xhuge *) &baseAddress[offset]);
    }
	_srvwdt_();
  }
  
  baseAddress[testOffset] = pattern;
  
  /*
   * Check for address bits stuck low or shorted
   */
  for (testOffset = sizeof(datum); (testOffset & addressMask) != 0;
       testOffset <<= 1)
  {
    baseAddress[testOffset] = antipattern;
	_srvwdt_();
    
    for (offset = sizeof(datum); (offset & addressMask) != 0; offset <<= 1)
    {
	  _srvwdt_();
      if ((baseAddress[offset] != pattern) && (offset != testOffset))
      {
        return ((datum xhuge *) &baseAddress[testOffset]);
      }
    }
    
    baseAddress[testOffset] = pattern;
  }
  
  return (NULL);
  
} /* memTestAddressBus() */

#if 0
/**********************************************************************
 *
 * Function:    memTestDevice()
 *
 * Description: Test the integrity of a physical memory device by
 *              performing an increment/decrement test over the
 *              entire region.  In the process every storage bit 
 *              in the device is tested as a zero and a one.  The
 *              base address and the size of the region are
 *              selected by the caller.
 *
 * Notes:       
 *
 * Returns:     NULL if the test succeeds.  Also, in that case, the
 *              entire memory region will be filled with zeros.
 *
 *              A non-zero result is the first address at which an
 *              incorrect value was read back.  By examining the
 *              contents of memory, it may be possible to gather
 *              additional information about the problem.
 *
 **********************************************************************/
datum xhuge *memTestDevice(volatile datum xhuge * baseAddress,UWORD32 nBytes)	
{
  UWORD32 offset;
  UWORD32 nWords = nBytes / sizeof(datum);

  datum pattern;
  datum antipattern;

  /*
   * Fill memory with a known pattern.
   */
#ifdef _16BITDATABUS
  for (pattern = 0x0101, offset = 0; offset < nWords; pattern += 0x0101, offset += 2)
#else
  for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
#endif
  {
  	_srvwdt_();
    baseAddress[offset] = pattern;
  }

  /*
   * Check each location and invert it for the second pass.
   */
#ifdef _16BITDATABUS
  for (pattern = 0x0101, offset = 0; offset < nWords; pattern += 0x0101, offset += 2)
#else
  for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
#endif
  {
    if (baseAddress[offset] != pattern)
    {
      return ((datum xhuge *) &baseAddress[offset]);
    }
	_srvwdt_();

    antipattern = ~pattern;
    baseAddress[offset] = antipattern;
  }

  /*
   * Check each location for the inverted pattern and zero it.
   */
#ifdef _16BITDATABUS
  for (pattern = 0x0101, offset = 0; offset < nWords; pattern += 0x0101, offset += 2)
#else
  for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
#endif
  {
    antipattern = ~pattern;
    if (baseAddress[offset] != antipattern)
    {
      return ((datum xhuge *) &baseAddress[offset]);
    }

    baseAddress[offset] = 0;
  }

  return (NULL);

} /* memTestDevice() */

#endif

/**********************************************************************
 *
 * Function:    memTest()
 *
 * Description: Test of a RAM range !
 * 
 * Notes:       
 *
 * Returns:     0 on success.
 *              Otherwise -1 indicates failure.
 *
 **********************************************************************/
e_RAM_ERROR_CODE RamTest(T_RAM_MEM_RANGE* PtMem)
{
  UWORD32 _baseAddress;
  UWORD32 _nbOfBytes;
  UWORD16 rc = RAM_ERR_ADDRESS_BUS_KO;
 
  
  if(PtMem == NULL)
  {		
		return rc;
  }

  rc = RAM_ERR_OK;

  if(PtMem->ToBeCalc)
  {
   	  _baseAddress = PtMem->MinAddress;
	  _nbOfBytes = PtMem->MaxAddress - PtMem->MinAddress + 1;

	  if( (rc == RAM_ERR_OK) &&  (memTestAddressBus((volatile datum xhuge *)_baseAddress, _nbOfBytes) != NULL) )
	  {
	  		rc = RAM_ERR_ADDRESS_BUS_KO;
	  }

	  if( (rc == RAM_ERR_OK) &&  (memTestDataBus((volatile datum xhuge *)_baseAddress) != 0) )
	  {
	  		rc = RAM_ERR_DATABUS_BUS_KO;
	  }	  		
   }
   return(rc);
}
 
