/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MessageList.hpp   	 		  			 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_MessageList.cpp 					  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef MessageListH
#define MessageListH


/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "typedef.h"
#include "HMI_Tools.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
#define HMI_MESSAGE_LIST_CFG_FAST

#define MESSAGE_LIST_SIZE 15
#define MESSAGE_LIST_NB_ITEMS (88)
#define MESSAGE_LIST_IN_LIST_TABLE_SIZE (MESSAGE_LIST_NB_ITEMS / 8)

class MessageList
{
private:

   typedef struct
   {
      UWORD16 Id;
      UBYTE Text[cMAX_LINE][cMAX_CHARACTER];
      e_BOOL Used;

	} TMessage;

   /* Parametres */
   TMessage Messages[MESSAGE_LIST_SIZE];

   UBYTE InListTable[MESSAGE_LIST_IN_LIST_TABLE_SIZE];   /* Permet de gérer les ids de 0 à
                                                               8 * MESSAGE_LIST_IN_LIST_TABLE_SIZE */

   /* Methodes */
   SWORD16  FindFreeIndex(UWORD16* _Index);

   SWORD16  GetIndexFromId(UWORD16 _Id, UWORD16* _Index);

   void ClearEntry(UWORD16 _Index);



protected:

   /* Parametres */

   /* Methodes */

public:

   #define E_OK            (0)
   #define E_NO            (-1)
   #define E_NOMEM         (-2)
   #define E_BAD_ID        (-3)
   #define E_OUT_OF_BOUNDS (-4)

   /* Parametres */

   /* Methodes */

   MessageList();

   void Init(UWORD16 _MaxId);

   SWORD16  AddToList(  UWORD16 _Id,
                        UWORD16 _Line,
                        UBYTE* _Message);

   SWORD16  GetTextLineFromId(   UWORD16 _Id,
                                 UWORD16 _Line,
                                 UBYTE** _Text);

   SWORD16  RemoveFromList(   UWORD16 _Id);

   SWORD16 EmptyList(void);

   SWORD16  InList( UWORD16 _Id);

   e_BOOL IsListFull(void);

   #ifndef HMI_MESSAGE_LIST_CFG_FAST
   e_BOOL FAST_IS_INLIST(UWORD16 X);
   void FAST_SET_INLIST(UWORD16 X);
   void FAST_UNSET_INLIST(UWORD16 X);
   #endif
};

#endif
