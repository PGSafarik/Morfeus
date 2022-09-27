#include<fox-1.7/fx.h>
#include<define.h>

#ifndef __UTILS_H
#define __UTILS_H

/*** Types utils *****************************/
  class MArgumentsList : public FXArray<const FXchar*> {
  public:
  	FXint split( const FXString &src, const FXString &sep = " " );
  	void dump( );
  };

  typedef FXArray<FXString> FXStringList;

/*** Strings utils *******************************************************************************/
  extern FXchar*  recopy( const FXString &src );
  extern FXint    split( const FXString &src, FXStringList *buffer, const FXString &sep = ";" );
  extern FXString pack( FXStringList *src, const FXString &sep = ";" );

/*** System tools ********************************************************************************/
  extern void SetEnvironment( FXStringDictionary *dict );

/*** END *****************************************************************************************/

#endif /* __UTILS_H */
