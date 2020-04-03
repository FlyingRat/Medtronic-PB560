/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MonitoringObjectTwoValueh.hpp  		 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_MonitoringObjectTwoValue.cpp 		         	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef MonitoringObjectTwoValueH
#define MonitoringObjectTwoValueH
								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_ValueTextField.hpp"
#include "HMI_TextField.hpp"
#include "HMI_MonitoringObject.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class MonitoringObjectTwoValue: public MonitoringObject
{

private:

	/* Parametres */

	ValueTextField VTFValue2;

	TextField TFSep;

	UWORD16 IdParam2;

	UWORD16 Value2;

	e_TYPE_OF_DB_TARGET DbTarget2;

	e_BOOL FloatDisplayOn2;

   e_BOOL MaxDisplayValue2Configured;
   
   UWORD16 MaxDisplayValue2;

	/* Méthodes */


protected:
	
	/* Parametres */

	/* Méthodes */
   void SetMaxDisplayValue2Configured(e_BOOL _MaxDisplayValue2Configured);
   
   e_BOOL IsMaxDisplayValue2Configured();

   void SaturateValue2(UWORD16* _Value);

public:

	/* Parametres */

   /* Méthodes */

	MonitoringObjectTwoValue();

	void Init(	e_SYMBOL _Icon,
               UWORD16 _Line,
					UWORD16 _Col,
					UBYTE **_Name,
					UWORD16 _Value,
					e_BOOL _ValueFloat,
					UWORD16 _Value2,
					e_BOOL _Value2Float,
					UBYTE ** _Text,
					e_BOOL _TextHeadOn,
					e_BOOL _Centered);

	void InitDbAccess2(	UWORD16 _IdParam2,
								e_TYPE_OF_DB_TARGET _DbTarget2);

	void SetIdParam2(UWORD16 IdParam2);
   	UWORD16 GetIdParam2();

	void SetDbTarget2(e_TYPE_OF_DB_TARGET DbTarget2);
	e_TYPE_OF_DB_TARGET GetDbTarget2();

   	void SetMaxDisplayValue2(UWORD16 _MaxDisplayValue2);
   	UWORD16 GetMaxDisplayValue2();

	virtual void Refresh();
	virtual void RefreshObject(e_BOOL Forced);

	virtual void DisplayNoValue();

	virtual void RefreshValueColumn();

   	void StartMonitoringMode();   
	virtual void StopMonitoringMode();
    virtual void StopMonitoringMode(e_BOOL _DisplayFlag);   

	virtual void SetInvertVideo(e_BOOL InvertVideo);
	virtual void Show();
	virtual void Hide();

    virtual void ShowTrigger();
};

#endif
