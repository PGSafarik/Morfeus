/***************************************************************************************************
* File:      Utils                                                                                 *
* Project:   Morfeus                                                                               *
* Copyright: Copyriright (C) 2019 - 2022 by D.A.Tiger GNU GPL v3                                   *
* Author(s): D.A.Tiger ( drakarax@seznam.cz )                                                      *
* Note:      The internal simle utils for Morfeus application                                      *
***************************************************************************************************/
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
/*************************************************************************
* This program is free software: you can redistribute it and/or modify   *
* it under the terms of the GNU General Public License as published by   *
* the Free Software Foundation, either version 3 of the License, or      *
* (at your option) any later version.                                    *
*                                                                        *
* This program is distributed in the hope that it will be useful,        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of         *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
* GNU General Public License for more details.                           *
*                                                                        *
* You should have received a copy of the GNU General Public License      *
* along with this program.  If not, see <https://www.gnu.org/licenses/>. *
*************************************************************************/
#include<fox-1.7/fx.h>
#include<define.h>

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
