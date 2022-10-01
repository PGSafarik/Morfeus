/*******************************************************************************
* File:      FXIconsTheme                                                      *
* Project:   FXDesktop                                                         *
* Copyright: Copyriright (C) 2021 - 2022 by D.A.Tiger GNU GPL v3               *
* Author(s): D.A.Tiger ( drakarax@seznam.cz )                                  *
* Note:      Application icon manager (dictionary - pattern method )           *
*******************************************************************************/
#include<fox-1.7/fx.h>
#include<map>
#include<define.h>

#ifndef __FXICONTHEME_H
#define __FXICONTHEME_H

typedef FXDictionaryOf<FXint>     FXSizesMap;
typedef std::map<FXString, FXint> __SizeMap; 
typedef FXArray<FXString>         FXStringList;

class FXIconsTheme {
  FXString t_name;		// Jmeno tematu
  FXString t_prefix;	// Koncova pripona ikonovych souboru
  FXString t_path;		// Korenova cesta k ikonovemu tematu
  FXString t_pattern;	// Vzor pro skladani cesty k souborum ikon v tematu

  FXStringList        t_list;      // Seznam tematickych slovniku 
  FXStringDictionary  t_dict;	     // Slovnik
  FXIconCache        *t_cache;     // cache ikon
  FXSizesMap          t_sizes;     // sizes map

  __SizeMap _sizes;

public:
  FXIconsTheme( FXApp *app );
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
 
  FXIcon* get_icon( const FXString &name, FXint size = 16 ) { return t_cache->insert( this->get_path( ) + "/" + this->at( name, size ) ); }
  FXIcon* get_icon( const FXString &name, const FXString &size_alias );
 

  void load( const FXString &themefile );
  //void load( XMLElement *iconsel );
};


#endif /* __FXICONTHEME_H */
