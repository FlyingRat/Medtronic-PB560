/*--------------------------------------------------------------------------
ERROR.H
Declaration of EC++ runtime error codes for C166/EC++ Version 5.
Copyright (c) 2000-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef ERROR_H
#define ERROR_H 1

/*
 * EXTERN_C is used to declare an external function with C linkage.  When
 * compiling with a C compiler this is just set to ``extern'', but when
 * compiling with a C++ compiler it is set to ``extern "C"''.
 */

#ifdef __cplusplus
  #define EXTERN_C extern "C"
#else
  #define EXTERN_C extern
#endif                               /* __cplusplus */

typedef enum /* an_error_code */ {
  ec_none,
  ec_abort_header,
  ec_terminate_called,
  ec_terminate_returned,
  ec_already_marked_for_destruction,
  ec_main_called_more_than_once,
  ec_pure_virtual_called,
  ec_bad_cast,
  ec_bad_typeid,
  ec_array_not_from_vec_new,
  ec_outofmemory,                  // added, HP.
  ec_last
} an_error_code;

EXTERN_C void __abort_execution(an_error_code err_code);

#endif /* ERROR_H */

