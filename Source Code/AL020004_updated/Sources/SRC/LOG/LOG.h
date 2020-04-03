/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : LOG.h                                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

#include "LOG_Config.h"
#include "LOG_Print.h"

#ifndef LOG_h
#define LOG_h


#ifdef CFG_LOG_ENABLE
	#ifdef CFG_LOG_ON_SIM 
		#define LOG(module, level, formatted_string) LOG_Print(_H_USART, module, level, formatted_string) 
		#define LOG_INIT() LOG_Print_Init()
	#elif defined CFG_LOG_ON_HARDWARE
		#define LOG(module, level, formatted_string) LOG_Print(_H_USER, module, level, formatted_string) 
        #define LOG_INIT() LOG_Print_Init()
	#else
		#error /* if CFG_LOG_ENABLE is defined, must select CFG_LOG_ON_SIM or CFG_LOG_ON_HARDWARE */
	#endif

    #define LOG_DEBUG(module, formatted_string) LOG(module, CFG_LOG_LVL_DEBUG, formatted_string)
    #define LOG_INFO(module, formatted_string) LOG(module, CFG_LOG_LVL_INFO, formatted_string)
    #define LOG_FORCE(module, formatted_string) LOG(module, CFG_LOG_LVL_FORCE, formatted_string)
#else
	#define LOG(module, level, formatted_string) 1
	#define LOG_INIT() 1
    #define LOG_DEBUG(module, formatted_string) 1
    #define LOG_INFO(module, formatted_string) 1
    #define LOG_FORCE(module, formatted_string) 1
#endif // #ifdef CFG_LOG_ENABLE

#endif // #ifndef LOG_h