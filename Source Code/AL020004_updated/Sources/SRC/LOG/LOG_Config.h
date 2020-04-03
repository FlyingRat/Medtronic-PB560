/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : LOG_Config.h                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

#ifndef LOG_Config_h
#define LOG_Config_h

/* ---- Global configuration ---- */

/* Uncomment the following line to enable LOGGING functionality */
//#define CFG_LOG_ENABLE
/* Uncomment the following line to enable LOGGING functionality using the MPLAB SIM debugger */
//#define CFG_LOG_ON_SIM 
/* Uncomment the following line to enable LOGGING functionality using a real UART on hardware */
#define CFG_LOG_ON_HARDWARE 
		
/* ---- Modules ---- */

#define CFG_LOG_MOD_ALL     (0xFFFFFFFF) /* All modules */
#define CFG_LOG_MOD_MAIN    (0x00000001L) /* PUST */
#define CFG_LOG_MOD_PUST    (0x00000002L) /* PUST */
#define CFG_LOG_MOD_FAN     (0x00000004L) /* FAN */

/* Uncomment the following line to activate logging on all modules */
//#define CFG_LOG_ACTIVATED_MODS CFG_LOG_MOD_ALL

/* 
   Uncomment the following line to enable logging of some modules
   For example, to activate logging on PUST and FAN modules:
   #define CFG_LOG_ACTIVATED_MODS (CFG_LOG_MOD_PUST|CFG_LOG_MOD_FAN)  
*/
#define CFG_LOG_ACTIVATED_MODS (CFG_LOG_MOD_PUST)

/* ---- Levels ---- */

#define CFG_LOG_LVL_FORCE (0x01)
#define CFG_LOG_LVL_INFO  (0x02)
#define CFG_LOG_LVL_DEBUG (0x03)

/* Define here under the global logging level */
#define CFG_LOG_CURRENT_LEVEL (CFG_LOG_LVL_DEBUG)

#endif // #ifndef LOG_Config_h
