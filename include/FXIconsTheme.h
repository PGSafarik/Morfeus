/*******************************************************************************
* File:      FXIconsTheme                                                      *
* Project:   FXDesktop                                                         *
* Copyright: Copyriright (C) 2021 by D.A.Tiger GNU GPL v3                      *
* Author(s): D.A.Tiger ( drakarax@seznam.cz )                                  *
* Note:      Application icon manager (dictionary - pattern method )           *
*******************************************************************************/
#include<fox-1.7/fx.h>
#include<define.h>

#ifndef __FXICONTHEME_H
#define __FXICONTHEME_H


class FXIconsTheme {
  FXString t_name;		// Jmeno tematu
  FXString t_prefix;	// Koncova pripona ikonovych souboru
  FXString t_path;		// Korenova cesta k ikonovemu tematu
  FXString t_pattern;	// Vzor pro skladani cesty k souborum ikon v tematu

  FXStringDictionary t_dict;	// Icons paths dictionary

public:
  FXIconsTheme( );
  ~FXIconsTheme( );

  ///////////////////////////////////////////////
  // Access methods
  //
  FXString get_path( )   { return t_path; }
  FXString get_path( XMLElement *elem ) { return elem->Attribute( "base" ); }
  FXString get_prefix( ) { return t_prefix; }

  ///////////////////////////////////////////////
  // Operators
  //
  FXString operator[ ]( const FXString &input );       // FXString iOpen_str = ic_theme[ "Open:16" ];

  ///////////////////////////////////////////////
  // Actions method
  //
  FXString at( const FXString &name, int size );
  FXString at( XMLElement *thelem, const FXString &name, int size = 0 );
  void load( const FXString &themefile );
  //void load( XMLElement *iconsel );
};


#endif /* __FXICONTHEME_H */
