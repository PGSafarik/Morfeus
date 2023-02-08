/***************************************************************************************************
* File:      MW_App                                                                                *
* Project:   Morfeus                                                                               *
* Copyright: Copyriright (C) 2019 - 2022 by D.A.Tiger GNU GPL v3                                   *
* Author(s): D.A.Tiger ( drakarax@seznam.cz )                                                      *
* Note:      The Morfeus application class                                                         *
***************************************************************************************************/
#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
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
#include<FXIconsTheme.h>
#include<define.h>

class MW_App : public FXApp {
FXDECLARE( MW_App )
  /*** Base ***/
  FXbool       m_created;     // TRUE - Application is craated (i.e. the create function has been successfully executed)   
  FXbool       m_initialized; // TRUE - Application is initialized (i.e. the init function has been successfully executed )   

  FXint              m_cdir;      // Index adresar s kontrolnim souborem
  FXStringList       m_dirlist;   // Seznam cest, v nichz se budou hledat kontrolni soubory
  FXStringDictionary m_envdict;   // Seznam promenych prostredi

  FXIconsTheme *m_icons;    // The icons theme manager    

  /*** XML Document ***/
  XMLError     m_xmlstate;
  XMLDocument *m_xmldocument;
  XMLElement  *m_xmlroot;
  XMLElement  *m_xml_icons;

public:
  MW_App( const FXString &name= "Application", const FXString &vendor = FXString::null );
  virtual ~MW_App( );

  /*** Operations ***/
  virtual void create( ); 
  virtual void init( int &argc, char **argv, FXbool connect = true );
  FXString     ValidatePath( const FXString &path );

  const FXString ReadConfig( const FXString &key, const FXString &def = "" );
  void           WriteConfig( const FXString &key, const FXString &value );

  /*** Access methods ***/
  XMLError      getXMLstate( ) { return m_xmlstate; }
  XMLElement*   getXMLRoot( )  { return m_xmlroot;  }

  FXString      getControlDir( ) { return ( ( m_cdir >= 0 ) ? m_dirlist[ m_cdir ] : FXString::null ); }
  FXIconsTheme* getIconsTheme( ) { return m_icons; }
  FXIcon*       getIcon( const FXString &name, FXint size = 16 );
  FXIcon*       getIconCopy( const FXString &name, int size = 16 );

protected :
  /*** Helpers methods ***/
  FXString    DecodeControlName( );                     //
  FXString    FindControlFile( const FXString &name );  //
  void        ConsoleHeader( );                         //
  FXint       environment( );                           // Nastavy pozadovane promene prostredi
};

#endif // APPLICATION_H_INCLUDED
