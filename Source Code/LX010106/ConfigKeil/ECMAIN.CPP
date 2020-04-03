/*--------------------------------------------------------------------------
EC_START.CPP

Startup code for C166/EC++ Version 5.
Copyright (c) 1999-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

/* 
 * This module contains:
 *
 *   -  __abort_execution function that is called on fatal errors
 *
 *   -  _main function that is called by the EC++ main function.
 *
 *   -  new/delete functions for C++ operator new/delete
 *
 */

#include "error.h"
#include <stdlib.h>
#include "LH_ST10F276.h"
//#include <reg167.h>
//#include "InterfaceCppC.h"
#include "typedef.h"



// L166 generated functions to call constructors and destructors
EXTERN_C void __sti__init__ (void);  //    initializers (constructors)
EXTERN_C void __std__init__ (void);  // de-initializers (destructors)


//unsigned char mempool[0x0001];       // 64K-2 memory pool for new / delete


/*
 * __abort_execution:  called on fatal errors.
 *  -  code is set to the error code that allows problem tracking
 */

EXTERN_C void __abort_execution (an_error_code code)  {
  while (1);
}




/*
 * _main:  performs the following operations in order:
 *   -  initializes the serial interface for printf text output
 *   -  initializes the memory pool used for new/delete
 *   -  calls of static constructor functions.
 */

EXTERN_C void _main ()  {

#ifndef Monitor         /* no init of serial interface on Monitor target */
                        /* initialize the serial interface               */
  P3  |= 0x0400;        /* SET PORT 3.10 OUTPUT LATCH (TXD)              */
  DP3 |= 0x0400;        /* SET PORT 3.10 DIRECTION CONTROL (TXD OUTPUT)  */
  DP3 &= 0xF7FF;        /* RESET PORT 3.11 DIRECTION CONTROL (RXD INPUT) */
  S0TIC = 0x80;         /* SET TRANSMIT INTERRUPT FLAG                   */
  S0RIC = 0x00;         /* DELETE RECEIVE INTERRUPT FLAG                 */
  S0BG  = 0x40;         /* SET BAUDRATE TO 9600 BAUD                     */
  S0CON = 0x8011;       /* SET SERIAL MODE                               */
#endif

//  init_mempool (mempool, sizeof (mempool));  // create memory pool for new & delete
  __sti__init__ ();                          // call initializer functions
}




/*
 * new():  allocate the specified memory size from mempool.
 *  - if the allocation fails the abort function is called.
 *  - if the size passed by the caller is zero, it is set to 1.
 *
 *    Note: operator new is not in the std namespace.
 */

extern void *operator new(size_t size)  {
  void *ptr;

  if (size == 0) size = 1;
  ptr = (void *) malloc (size);
  if (ptr == NULL)  {
    __abort_execution (ec_outofmemory);
  }
  return (ptr);
}


/*
 * delete:  free allocated memory previously allocated via new()
 */

void operator delete(void *ptr)  {
  free (ptr);
}



#if 0
extern "C" void _exit (int nStatus)  {
  while (1);
}
#endif

