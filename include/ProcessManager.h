/***************************************************************************************************
* File:      ProcessManager                                                                        *
* Project:   Morfeus                                                                               *
* Copyright: Copyriright (C) 2019 - 2022 by D.A.Tiger GNU GPL v3                                   *
* Author(s): D.A.Tiger ( drakarax@seznam.cz )                                                      *
* Note:      Class for run and managment an childrens process                                      *
***************************************************************************************************/
#ifndef PRCOCESSMANAGER_H_INCLUDED
#define PRCOCESSMANAGER_H_INCLUDED
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

enum {
  SEL_PROCESS_RUN = SEL_LAST,
  SEL_PROCESS_END,
  SEL_LAST
};

class ProcessManager : public FXObject {
FXDECLARE( ProcessManager )
  /*** System ***/
  FXApp      *m_app;		// Ukazatel na instanci aplikace
  FXObject   *m_tgt;		// Ukazatel na notifikacni objekt
  FXSelector  m_sel;		// Registrovana zprava notifikaci

  /*** Work Path ***/
  FXString m_wpath;         // Globalni nastaveni pracovni cesty
  FXbool   m_wpchange;      // TRUE - Pracovni cesta byla zmenena
  FXbool   m_wplock;        // TRUE - Prcovni cesta NEMUZE byt zmenena

  /*** Process ***/
  FXProcess *m_process;     // Instance procesu
  FXint      m_procstat;    // Stav spusteneho procesu
  FXbool     m_exit;        // TRUE - indikace poazadavku ukonceni Morfea, po skonceni hry
  FXbool     m_notify;      // TRUE - Budou odesilany notifikace

public:
  ProcessManager( FXApp *a, FXObject *tgt = NULL, FXSelector sel = 0 );
  virtual ~ProcessManager( );

  /*** Operations ***/
  FXbool start( const MArgumentsList &args, FXbool wait = false );
  FXbool setWorkDir( const FXString &path = FXString::null, FXbool change = false, FXbool lock = false );

  /*** Access methods ***/
  void   setNotify( FXbool value = true ) { m_notify = value; }
  FXbool getNotify( )                     { return m_notify; }

  /*** Events & handlers ***/
  enum {
   SIG_CHILD = 1,       // Proces potomka byl ukoncen
   ID_LAST
  };
  long OnSig_Child( FXObject *sender, FXSelector sel, void *data );

protected:
  ProcessManager( ) { }
  long notify( FXuint type, void *data = NULL );
};

#endif //PRCOCESSMANAGER_H_INCLUDED
