/*************************************************************************
* FXIconTheme.cpp; Copyright (c) 2021 - 2022 by D.A.Tiger                *
*                                                                        *
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
#include "FXIconsTheme.h"
#include<iostream>

/*************************************************************************************************/
class FXSubsTextMacro : public FXStringDictionary {
public:
  FXSubsTextMacro( ) { }
  virtual ~FXSubsTextMacro( ) { }

  FXString operator ( )( const FXString &pattern )
  {
    FXString result = pattern;
    FXint    num    = used( );
    FXint    size   = no( );

    for( FXint i = 0; i != size; i++ ) {
	  FXString k = key( i );
	  if( !k.empty( ) ) {
		result.substitute( k, data( i ) );
		num--;
	  }
	  if( num <= 0 ) { break; }
    }

    return result;
  }
};


/*************************************************************************************************/
FXIconsTheme::FXIconsTheme( FXApp *app )
{
  t_cache = new FXIconCache( app, FXSystem::getHomeDirectory( ) );
}

FXIconsTheme::~FXIconsTheme( )
{

}

/*************************************************************************************************/
FXString FXIconsTheme::operator[ ]( const FXString &input )
{
  /*NOTHING*/
  return FXString::null;
}


FXString FXIconsTheme::at( const FXString &name, int size )
{
  FXString result = FXString::null;
  FXString tr = t_dict[ name ];
 
  if( !tr.empty( ) ) {
    #ifdef __DEBUG
    std::cout << "[DEBUG] FXIconsTheme::at: Find path icon file \'" << name.text( ) << "\' with size \'" << size << "\'" << std::endl;
    #endif // __DEBUG
    
    FXint pos = tr.find( "/" );
    FXString i_sect = tr.left( pos );
    FXString i_name = tr.mid( pos + 1, tr.length( ) );

    FXSubsTextMacro macro;
    macro.insert( "${SIZE}", FXString::value( size ) );
    macro.insert( "${TYPE}", i_sect );
    macro.insert( "${NAME}", i_name );
    macro.insert( "${EXP}",  t_prefix );

    // We have everything we need - We will start replacing the pattern with values
    result = t_path + "/" + macro( t_pattern );
  }

  #ifdef __DEBUG
  std::cout << "[DEBUG] FXIconsTheme::at: Value of \'" << name.text( ) << "\' is \'" << tr.text( ) << "\'" << std::endl;
  std::cout << "[DEBUG] FXIconsTheme::at: Path is " << result.text( ) << std::endl; 
  #endif // __DEBUG

  return result;
}

FXIcon* FXIconsTheme::get_icon( const FXString &name, FXint size ) 
{ 
  FXIcon   *icon = NULL;
  FXString  path = this->at( name, size ); 

  if( !path.empty( ) ) { icon = t_cache->insert( path ); }
  else { std::cerr << "[WARNING] FXIconsTheme::at: Nenalezena cesta k ikone jmenem: \'" << name.text( ) << "\'" << endl; }
  
  return icon;
}

FXIcon* FXIconsTheme::get_icon( XMLElement *thelem, const FXString &name, int size ) 
{ 
  FXIcon   *icon = NULL;
  FXString  path = this->at( thelem, name, size ); 

  if( !path.empty( ) ) { icon = t_cache->insert( path ); }
  else { std::cerr << "[WARNING] FXIconsTheme::at: Nenalezena cesta k ikone jmenem: \'" << name.text( ) << "\'" << endl; }
  
  return icon;
}

FXIcon* FXIconsTheme::get_icon( const FXString &name, const FXString &size_alias )
{
   FXint _size = 16;
   if( !_sizes.empty( ) ) { _size = _sizes.at( size_alias ); }
   return get_icon( name, _size );
}

FXString FXIconsTheme::at( XMLElement *thelem, const FXString &name, int size )
{
  FXString    result = FXString::null;
  XMLElement *child  = NULL;

  if( thelem ) {
    if( ( child = thelem->FirstChildElement( name.text( ) ) ) != NULL ) {
	   FXSubsTextMacro macro;

       FXString i_base = get_path( child );
       if( i_base.empty( )  ) { i_base = get_path( thelem ); }
       macro.insert( "${BASE}", ( !i_base.empty( ) ? i_base += "/" : "" ) );

	   FXString i_size = child->Attribute( "Size" );
	   if( i_size.empty( )  ) { i_size = thelem->Attribute( "size" ); }
       macro.insert( "${SIZE}", ( !i_size.empty( ) ? i_size += "/" : "" ) );

	   FXString i_colname = child->Attribute( "Sect" );
	   if( i_colname.empty( )  ) { i_colname = thelem->Attribute( "Sect" ); }
       macro.insert( "${SECT}", ( !i_colname.empty( ) ? i_colname += "/" : "" ) );

	   FXString i_exp = child->Attribute( "exp" );
	   if( i_exp.empty( ) ) { i_exp = thelem->Attribute( "exp" ); }
	   if( i_exp.empty( ) ) { i_exp = "png"; }
       macro.insert( "${EXP}", i_exp );

       FXString i_name = child->Attribute( "name" );
       if( i_name.empty( ) ) { i_name = child->GetText( ); }
       macro.insert( "${NAME}", i_name );

       // We have everything we need - We will start replacing the pattern with values
   	   FXString i_pattern = child->Attribute( "pattern" );
       if( i_pattern.empty( ) ) { i_pattern = thelem->Attribute( "pattern" ); }
       result = macro( i_pattern );
    }
    else { std::cerr << "[WARNING] FXIconsTheme::at: Nenalezena icona jmenem: \'" << name.text( ) << "\'" << endl; }
  }
  else { std::cerr << "[WARRNING] FXIconsTheme::at: Nepredan element seznamu \'<Theme:Icon>\'!" << std::endl;	}

  return result;
}

void FXIconsTheme::load( const FXString &themefile, const FXString &name )
{
  FXSettings data;
  FXString   head;

  t_dict.clear( );
  t_sizes.clear( );
  t_cache->clear( );
  t_list.clear( );

  #ifdef __DEBUG
  std::cout << "Load icons theme \'" << name.text( ) << "\' from \'" << themefile.text( ) << "\' mapfile" << std::endl;
  #endif // __DEBUG

  if( FXStat::exists( themefile ) && data.parseFile( themefile ) ) {
    if ( data.existingSection( "Sizes" ) ) {
      FXStringDictionary sm = data.at( "Sizes" );
      for( FXint i = 0; i != sm.no( ); i++ ) {
        FXString k = sm.key( i );
        if( !k.empty( ) ) {
          FXint value =  sm.data( i ).toInt( );
          _sizes.insert( std::pair<FXString, int>( k, value ) );
        }
      }
    } 
    else { std::cout << "[WARNING] FXIconsTheme::load: The size definitions section not found!" << std::endl;}


    // Read base informations about icon theme    
    t_prefix  = data.readStringEntry( name, "map.type", "png" );
    t_path    = data.readStringEntry( name, "map.path" );
    t_pattern = data.readStringEntry( name, "map.pattern" );
    t_dict    = data.at( name );
  } 
  else { std::cout << "[WARNING] FXIconsTheme::load: Select icons theme is NOT LOADED!" << std::endl;}

  std::cout.flush( );
}

/*
void FXIconsTheme::load( XMLElement *icelem )
{

}
*/
