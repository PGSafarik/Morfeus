/***************************************************************************************************
* File:      MW_ContextBox                                                                         *
* Project:   Morfeus                                                                               *
* Copyright: Copyriright (C) 2019 - 2022 by D.A.Tiger GNU GPL v3                                   *
* Author(s): D.A.Tiger ( drakarax@seznam.cz )                                                      *
* Note:      The context manager widget                                                            *
***************************************************************************************************/
#ifndef CONTEXTBOX_H_INCLUDED
#define CONTEXTBOX_H_INCLUDED
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
#include<define.h>

class MW_ContextBox : public FXVerticalFrame {
FXDECLARE( MW_ContextBox )
  /*** BASE ***/
  FXComboBox *m_combo;
  FXObject   *m_target;
  FXSelector  m_selector;

  /*** XML Control segment ***/
  XMLElement *m_xmlactions;	// The XML Element of Actions list.
  XMLElement *m_xmlcurrent;	// The XML Element of curent context.

public :
  MW_ContextBox( FXComposite *p, FXObject *tgt = NULL, FXSelector sel = 0 );
  virtual ~MW_ContextBox( );

  /*** Operations ***/
  virtual void create( );

  /*** Access methods ***/
  FXint       getNumItems( ) { return m_combo->getNumItems( ); }
  FXString    checkAttr( XMLElement *e, const FXString &name );
  XMLElement* findAction( const FXString &name ) { return m_xmlactions->FirstChildElement( name.text( ) ); }

protected:
  MW_ContextBox( ) { }

  /*** Helpers operations ***/
  void Initialize( );
};



#endif // CONTEXTBOX_H_INCLUDED
