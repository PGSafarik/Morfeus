/*************************************************************************
* MW_App.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger                     *
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
#include<MW_App.h>
#include<iostream>
/*************************************************************************************************/
FXDEFMAP( MW_App ) AM[ ] = { };
FXIMPLEMENT( MW_App, FXApp, AM, ARRAYNUMBER( AM ) )

/*************************************************************************************************/
MW_App::MW_App( const FXString &name, const FXString &vendor )
      : FXApp( name, vendor )
{
  ConsoleHeader( );
  m_icons = new FXIconsTheme( this );

  m_xmldocument = NULL;
  m_xmlroot     = NULL;
  m_xmlstate    = XML_ERROR_FILE_NOT_FOUND;

  settings_load( );
}

MW_App::~MW_App( )
{
  reg( ).write( );
  std::cout << "\n=== Bye! ==============================" << std::endl;
}

void MW_App::create( )
{
  FXApp::create( );
}

void MW_App::init( int &argc, char **argv, FXbool connect )
{
  #ifdef __DEBUG
  cout << "[DEBUG] Application Morfeus initialize... " << endl;
  #endif // __DEBUG
  FXApp::init( argc, argv, connect );

  FXString filename = DecodeControlName( );
  #ifdef __DEBUG
  cout << "       * Parse XML File: " << filename.text( ) << endl;
  #endif // __DEBUG

  m_xmldocument = new XMLDocument;
  if( ( m_xmlstate = m_xmldocument->LoadFile( filename.text( ) ) ) == XML_SUCCESS  ) {    
   	m_xmlroot = m_xmldocument->RootElement( );
  }
}

FXString MW_App::ValidatePath( const FXString &path )
{
  /*
    Pokud se jedna o relativni cestu otestuje jeji existenci vuci adresari kontrolnich souboru.
    V pripade neuspechu vraci prazdny retezec, jinak absolutni cestu.
  */
  if( !path.empty( ) ) {
	  if( path[ 0 ] == '/' ) { return path; }
	  else if( m_cdir >= 0 ) {
	    FXString resh = m_dirlist[ m_cdir ] + "/" + path;
	    if( FXStat::exists( resh ) ) { return resh; }
	  }
  }
  std::cerr << "[WARNING] Validate path: " << path.text( ) << " not found!";
  return FXString::null;
}

const FXString MW_App::ReadConfig( const FXString &key, const FXString &def )
{
  FXString   head  = m_xmlroot->Attribute( "title" );
  FXSettings conf  = reg( );
  FXString   value = FXString::null;

  if( conf.existingSection( head ) && conf.existingEntry( head, key ) ) {
	  value = conf.readStringEntry( head, key, def.text( ) );
  }

  return value;
}

void MW_App::WriteConfig( const FXString &key, const FXString &value )
{
  reg( ).writeStringEntry( m_xmlroot->Attribute( "title" ), key, value.text( ) );
}

void MW_App::settings_load( ) 
{ 
  reg( ).read( );

  // GUI Icons theme
  FXString icons_name, icons_map; 
  icons_name = reg( ).readStringEntry( "Theme", "icons", DEFAULT_IC_THEME_NAME );
  icons_map  = reg( ).readStringEntry( "Theme", "imap",  DEFAULT_IC_THEME_PATH );
  m_icons->load( icons_map, icons_name );  

}

void MW_App::settings_save( )
{


}


/*************************************************************************************************/
FXString MW_App::DecodeControlName( )
{
  /*
    Definuje seznam adresaru umisteni kontrolniho souboru a zjisti jeho nazev a vrati jeho
    absolutni cestu ( z nazvu linku, nebo z parametru programu )
  */
  FXString filename = FXString::null;

  m_cdir = -1;
  m_dirlist.append( "/usr/share/morfeus/" );
  m_dirlist.append( "/usr/share/games/morfeus/" );
  m_dirlist.append( "/usr/local/share/morfeus/" );
  m_dirlist.append( "/usr/local/share/games/morfeus/" );
  m_dirlist.append(  FXSystem::getHomeDirectory( ) + "/.local/share/games/morfeus/" );

  FXString appname = FXPath::name( this->getArgv( )[ 0 ] );
  if( appname == "Morfeus" || appname == "morfeus" ) {
    FXString arg = this->getArgv( )[ 1 ];
    if(  arg == "-f" ) {
      FXString filename = this->getArgv( )[ 2 ];
      if( !filename.empty( ) && FXStat::exists( filename ) ) {
        m_dirlist.append( FXPath::directory( filename ) );
        m_cdir = m_dirlist.no( ) - 1;
        return filename;	                        /* Primo zadany kontrolni soubor                    */
      } else { return FXString::null; }             /* Neni z ceho odvodit nazev kontrolniho souboru    */
    } else { filename = FindControlFile( arg  ); }  /* Nazev souboru se odvodi z argumentu              */
  } else { filename = FindControlFile( appname ); } /* Nazev souboru se odvodi z nazvu odkazu na Morfea */

  return filename;
}

FXString MW_App::FindControlFile( const FXString &name )
{
  /*
  Funkce se pokusi najit kontrolni soubor  v seznamu prislusnych adresaru podle nazvu (muze byt
	bez pripony). V pripade uspechu vrati absolutni cestu ke kontrolnimu souboru, v opacnem pripade
	FXString::null.
  */

  // test na priponu
  FXString ext = name.right( 4 );
  FXString _n = ( ( ext == ".xml" ) ? name : name + ".xml" );

  #ifdef __DEBUG
   std::cout << "[DEBUG] " <<  __FILE__ << " " << "::FindControlFile( )" << std::endl;
   std::cout << "       * Find file name: " << _n.text( ) << std::endl;
  #endif // __DEBUG

  // Pruchod seznamem dostupnych adresaru
  FXint num = m_dirlist.no( );
  for( FXint i = 0; i != num; i++ ) {
    FXString pth = m_dirlist[ i ] + "/" + _n;
	  if( FXStat::exists( pth ) ) {
	    m_cdir = i;
	    return pth;
	  }
  }

  return FXString::null;
}

void MW_App::ConsoleHeader( )
{
  std::cout << "=== Morfeus =========================================================" << std::endl;
  std::cout << "Copyright (C) 2019 - " << Morfeus_Version::YEAR << " D.A.Tiger <drakarax@seznam.cz>, GNU GPL 3 " << std::endl; 
  std::cout << "Version       : " << Morfeus_Version::MAJOR << "." << Morfeus_Version::MINOR << "." << Morfeus_Version::BUILD 
            << " [" << Morfeus_Version::STATUS << "]" << std::endl;
  std::cout << "lib Fox       : " << FOX_MAJOR << "." << FOX_MINOR << "." << FOX_LEVEL << std::endl;
  std::cout << "lib FoxGHI    : " << 0 << "." << 2 << "." << 1 << std::endl;
  std::cout << "lib TinyXML-2 : " << TINYXML2_MAJOR_VERSION << "." << TINYXML2_MINOR_VERSION << "." << TINYXML2_PATCH_VERSION << std::endl;
  std::cout << "\n=== Messages ======================================================" << std::endl;
}

/*** END *****************************************************************************************/
