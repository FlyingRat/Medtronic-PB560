/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MonitoringObjectWithRecall.hpp 	 	 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_MonitoringObjectWithRecall.cpp 		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef MonitoringObjectWithRecallH
#define MonitoringObjectWithRecallH
								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_MonitoringObject.hpp"
#include "HMI_BlinkTable.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define RECALL_NB		2

class MonitoringObjectWithRecall: public MonitoringObject
{

private:

   /* Parametres */

	ValueTextField VTFLimit[RECALL_NB];
   
   e_BOOL LimitDisplay[RECALL_NB];
   
   UWORD16 BlinkTarget;

	e_BOOL DefaultFlag[RECALL_NB];
   
   UBYTE** NameDefaultValue[RECALL_NB];
   
   UWORD16 IdDefaultFlag[RECALL_NB];
   
   e_TYPE_OF_DB_TARGET DbIdFlag[RECALL_NB];
   
   e_BOOL FlagForDefault[RECALL_NB];
	
	/* Méthodes */

protected:
	
	/* Parametres */

	/* Méthodes */

public:

	/* Parametres */
	
	/* Méthodes */

	MonitoringObjectWithRecall();

	void Init(  UWORD16 Line,
               UWORD16 Col,
               UBYTE **Name,
               UWORD16 Value,
               e_BOOL ValueFloat,
               UBYTE ** Text,
               e_BOOL TextHeadOn,
               e_BOOL Centered);

	void InitDbAccess1(  UWORD16 IdParamRefresh,
                        e_TYPE_OF_DB_TARGET DbTargetRefresh,
                        UWORD16 IdParamLimit,
                        e_TYPE_OF_DB_TARGET DbTargetLimit,
                       	e_BOOL FirstLimitDisplay);

	void InitDbAccess2(  UWORD16 IdParamRefresh,
                        e_TYPE_OF_DB_TARGET DbTargetRefresh,
    				   	   UWORD16 IdParamLimit1,
                        e_TYPE_OF_DB_TARGET DbTargetLimit1,
    				   	   UWORD16 IdParamLimit2,
                        e_TYPE_OF_DB_TARGET DbTargetLimit2);

	void InitDefaultFlag(UBYTE FieldNb,
                        UBYTE** NameDfltValue,
                        UWORD16 IdDfltFlag,
                        e_TYPE_OF_DB_TARGET DbIdFlag,
                        e_BOOL FlagForDflt);

   UWORD16 GetBlinkTarget(void);
   void SetBlinkTarget(UWORD16 BlinkTarget);

	virtual void SetInvertVideo(e_BOOL InvertVideo);

	virtual void Show();
	virtual void Hide();
	virtual void Blink(e_BOOL Actif);

};

#endif
