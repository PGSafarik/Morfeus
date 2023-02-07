/*************************************************************************
* Utils.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger                   *
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
#include<Utils.h>

//using namespace Mps;

FXint MArgumentsList::split( const FXString &src, const FXString &sep )
{
  FXint count = 0;
  FXint nstr, pos;
  FXString sub_str;

  if( !src.empty( ) ) {
    nstr = src.contains( sep );
    if( nstr > 0 ) {
      nstr++;
      pos = 0;
      while( pos < nstr ) {
        sub_str = src.section( sep, pos );
        if( !sub_str.empty( ) ) {
          this->append( recopy( sub_str ) );
          count++;
        }
        pos++;
      }
    }
    else {
      this->append( recopy( src ) );
      count = 1;
    }
  }
  return count;
}

void MArgumentsList::dump( /*const FXString &NECO*/ )
{
  FXint num = no( );

  cout << "\n" << __FILE__ << " " << "MArgumentsList::dump( ) \n";
  cout << "This parameter(s) setting of new process: " << at( 0 ) << "\n";
  for( FXint i = 1; i != num; i++  ) { cout << "\n" << i << ". '" << ( ( at( i ) != NULL) ? at( i ) : "--END--" ) << "' " ; }
  cout << endl;
  cout.flush( );
}


/*************************************************************************************************/
FXchar* /*Mps::*/recopy( const FXString &src )
{
  /*
   Pomocna fce pro metodu parseCommand. Prevede retezec ve formatu FXString na FXchar[] a
   alokuje pro nej pamet. Toto je nutne kvuli problemu vlastnictvi pametovych segmentu objekty.
   prms: src => Konvertovany retezec typu FXString
  */

  if( !src.empty( ) ) {
    FXchar *resh = new FXchar[ src.length( ) + 1 ];
    return strcpy( resh, src.text( ) );
  }
  return NULL;
}

FXint /*Mps::*/split( const FXString &src, FXStringList *buffer, const FXString &sep )
{
  FXint count = 0;
  FXint nstr, pos;
  FXString sub_str;

  if( !src.empty( ) && ( buffer != NULL ) ) {
    nstr = src.contains( sep );
    if( nstr > 0 ) {
      nstr++;
      pos = 0;
      while( pos < nstr ) {
        sub_str = src.section( sep, pos );
        if( !sub_str.empty( ) ) {
          buffer->append( sub_str );
          count++;
        }
        pos++;
      }
    }
  }
  return count;
}

FXString /*Mps::*/pack( FXStringList *src, const FXString &sep )
{
  FXint size   = src->no( );
  FXint ns     = size - 1;
  FXString str = "";

  for( FXint i = 0; i != size; i++ ) {
    str += src->at( i );
    if( i < ns ) { str += sep; }
  }

  return str;
}

FX::FXString& operator <<( FX::FXString &dest, const std::string &source ) {
  if( !source.empty( ) ) {
    int len = source.size( );
    dest.length( len );
    source.copy( dest.text( ), len ); 
  }   
  else { dest = FXString::null; }

  return dest;
}

std::string& operator <<( std::string &dest, const FX::FXString &source ) {
  if( !source.empty( ) ) { dest.assign( source.text( ) ); } 
  else { dest = ""; }
  
  return dest;
}

std::ostream& operator <<( std::ostream &store, const FX::FXString &str  ) {
  return store << str.text( );
}

std::istream& operator >>( std::istream &store, FX::FXString &str  ) {
  std::string s;

  store >> s;
  str << s;

  return store;
}

/*************************************************************************************************/

/*
void SetEnvironment( FXStringDict *dict )
{


}
*/
