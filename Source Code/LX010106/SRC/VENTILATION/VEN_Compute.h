/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_Compute.h                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for VEN_Compute                                       */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef VEN_COMPUTE_H
#define VEN_COMPUTE_H

/* Rinse flow close loop compute */
extern void CMP_CalculFlowLeak(void);

/* Inspiratory rise pressure close loop compute */
extern void CMP_CalculAutoAdaptInsp(void);

/* Exhalation computed values  */
extern void CMP_ExhalationComputings(void);

/* Exhalation plateau computed values  */
extern void CMP_ExhPlatComputings(void);

/* Compute sequence during inspiration    */
extern void CMP_InspirationComputings(void);

/* Compute sequence during inspiration rise   */
extern void CMP_InspRiseComputings(void);

/* Compute sequence during inspiration plateau   */
extern void CMP_InspPlatComputings(void);

/* Time measure function   */
extern void CMP_TimeComputing(void);

/* Pi set point computing in PSIMV mode  function   */
extern void CMP_PiSetPointPsimvMode(void);

/* Control read function access  */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
/* Compute write function access  */
extern void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value);

/* Average Pressure computing on one cycle   */
extern void CMP_AveragePressureComputing(void);

extern void CMP_VentilationReport(void);

extern UWORD16 DB_RTCRead(e_DB_RTC);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern UWORD16 DB_TrendWrite(e_DB_Trend Id, UWORD16 Value);

extern UWORD16 DB_TrendRead(e_DB_Trend Id);

extern void CMP_LeakComputing(void);

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);

#endif
