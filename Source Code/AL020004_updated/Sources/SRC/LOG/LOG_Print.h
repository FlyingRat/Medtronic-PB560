/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : LOG_Print.h                                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
#include "stdio.h"

#ifndef LOG_Print_h
#define LOG_Print_h

/* LOGGING PUBLIC API */
extern int LOG_Print(auto FILE *f, unsigned long module, unsigned int level, auto const MEM_MODEL rom char *fmt, ...);
extern int LOG_Print_Init(void);
extern int LOG_Print_Set_Activated_Modules(unsigned long modules);
extern int LOG_Print_Set_level(unsigned int level);

#endif // #ifndef LOG_Print_h