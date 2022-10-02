/***************************************************************************************************
* File:      Morfeus                                                                               *
* Project:   Morfeus                                                                               *
* Copyright: Copyriright (C) 2019 - 2022 by D.A.Tiger GNU GPL v3                                   *
* Author(s): D.A.Tiger ( drakarax@seznam.cz )                                                      *
* Note:      The main window for Morfeus application                                               *
***************************************************************************************************/
#ifndef MORFEUS_H_INCLUDED
#define MORFEUS_H_INCLUDED
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
#include<MW_App.h>
#include<AboutBox.h>
#include<FXIconsTheme.h>
#include<ProcessManager.h>
#include<MW_CoverFrame.h>

class MW_ContextBox;

class MorfeusWindow : public FXGWindow {
FXDECLARE( MorfeusWindow )
  /*** GUI ***/
  FXButton          *m_launch; // GO!
  FXButton          *m_config; // Game configure
  FXMenuButton      *m_menu;   // Menu (aplication)

  MW_ContextBox     *m_context;
  MW_CoverFrame     *m_cover;      // Widget vykreslujici obrazek (tzv. cover) aplikace / hry
  FXVerticalFrame   *right_fr;     //
  FXHorizontalFrame *m_service_fr; // Ram servisnich tlacitek

  /*** XML Objects ***/
  XMLElement   *m_xmlservices;     // XML Services list
  XMLElement   *m_xmlmenu;         // XML Menu definition;
  XMLElement   *m_xmlui;           // XML User interface descriptions
  XMLElement   *m_xmlictheme;	   // XML Icons map list
  XMLElement   *m_xmlcurrent;      // XML Current action entry (context)

  /*** Morfeus base ***/
  FXbool       m_autostart;  // Povoleni automatickeho startu defaultni aplikace.
  FXbool       m_created;    // true - Indikuje, ze jiz probehla faze Morfeus::create( ) - nutne kvuli obrazkum a ikonam.

  /*** System ***/
  FXIconsTheme        *m_ict;      // Zprava tematu ikon
  //FXIconCache        *m_icons;    // Uloziste ikon v pameti
  FXStringDictionary  m_envdict;  // Seznam promenych prostredi
  ProcessManager     *m_procman;

public :
  MorfeusWindow( FXApp *a );
  virtual ~MorfeusWindow( );

/////////////////////////////////////////////////
// Procedure methods
//
  virtual void create( );

  FXint environment( );				// Nastavy pozadovane promene prostredi
  FXint autostart( );				// Spusti casovac a po jeho uplinuti implicitni akci
  FXint weblinks( );				// Vygeneruje a nastavy panel servisnich tlacitek
  FXint menu( FXMenuPane *pane, XMLElement *mel = NULL );	//
  FXint Launch( XMLElement *ch, const FXString name = FXString::null );

//////////////////////////////////////////////////
// Access methods
//
  const char* getContext( ) { return ( m_xmlcurrent ? m_xmlcurrent->Name( ) : NULL ); }

/////////////////////////////////////////////////
// GUI event messages
//
  enum {
    ID_LAUNCH = FXGWindow::ID_LAST,  // Spustit vybranou akci hry (applikace)
    ID_CONFIG,                             // Spustit configuracni script/appku
    ID_EXIT,                               // Ukoncit Morfea
    NOTIFY_PROCESS,
    SERVICE_MENU,                          // Udalost z menu
    SERVICE_WEBLIK,                        // Stisknuto tlacitko servisni akce
    ID_SELECT,                             // Vybrana akce ze seznamu
    ID_LIST,
    ID_ABOUT,                              // Informacni panel programu
    ID_LAST
  };

  long OnCmd_launch( FXObject *sender, FXSelector sel, void *data );
  long OnCld_List( FXObject *sender, FXSelector sel, void *data );
  long OnProc_Notify( FXObject *sender, FXSelector sel, void *data );
  long OnCmd_About( FXObject *sender, FXSelector sel, void *data ) {
    AboutBox *abbx = new AboutBox( getApp( ), NULL );
    abbx->create( );
    return 1;
  }

protected :
  MorfeusWindow( ) { }

  FXbool      Initialize( );
  FXbool      ShowMessage( XMLElement *e );
  void        SetCurrent( XMLElement *entry );
  FXIcon*     GetIcon( const FXString &name, FXint size = 16 );
  FXIcon*     GetIconCopy( const FXString &name, int size = 16 );
  void        ShowMenuIcon( FXIcon *ic = NULL );
  XMLElement* CheckContext( XMLElement *el );
};


#endif // MORFEUS_H_INCLUDED
/*** END *****************************************************************************************/
