/*************************************************************************
* MW_CoverFrame.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger                   *
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
#include<MW_CoverFrame.h>
#include<MW_App.h>

/*************************************************************************************************/
FXDEFMAP( MW_CoverFrame ) CFM[ ] = { };
FXIMPLEMENT( MW_CoverFrame, FXImageFrame, CFM, ARRAYNUMBER( CFM ) )

/*************************************************************************************************/
MW_CoverFrame::MW_CoverFrame( FXComposite *p, FXuint opts, FXint x, FXint y, FXint w, FXint h,
							  FXint pl, FXint pr, FXint pt, FXint pb )
		  : FXImageFrame( p, NULL, opts, x, y, w, h, pl, pr, pt, pb )
{
  MW_App *a = dynamic_cast<MW_App*>( getApp( ) );

  if( a->getXMLstate( ) == XML_SUCCESS  ) {
	  XMLElement *root = a->getXMLRoot( );
	  m_xmlCoversMap   = root->FirstChildElement( "Theme:Covers" );
  }

  m_created = false;
  m_covers  = new FXIconCache( getApp( ) );

  this->hide( );
}

MW_CoverFrame::~MW_CoverFrame( )
{ }

void MW_CoverFrame::create( )
{
  FXImageFrame::create( );
  m_created = true;
}

/*************************************************************************************************/
void MW_CoverFrame::showImage( const FXString &name )
{
  FXImage *image = NULL;
  FXString f     = FXString::null;

  #ifdef __DEBUG
  cout << "[DEBUG MW_CoverFrame::showImage] Show image of entry name: " << name.text( ) << endl;
  #endif // __DEBUG

  if( m_xmlCoversMap ) {
	  XMLElement *e = m_xmlCoversMap->FirstChildElement( name.text( ) );
	  if( !e ) { e = m_xmlCoversMap->FirstChildElement( ); }

	  if( e ) {
	    /// FIXME CF_01: Adding control path of the image file, immediately after move the method
	    ///              ValidatePath( ) from MorfeusWindow class to the FXApp class.
	    f = e->Attribute( "file" ); // getApp( )->ValidatePath( e->Attribute( 'file' ) );
      #ifdef __DEBUG
      cout << "[DEBUG MW_CoverFrame::showImage] Cover image of entry name: " << name.text( ) << "its " << f.text( ) << endl;
      #endif // __DEBUG
   
	    if( f.empty( ) ) {
         std::cout << "[WARNING] Entry " << name.text( ) << "not have a cover image" << std::endl; 
         return; 
      }
      if( !FXStat::exists( f ) ) { 
         std::cout << "[WARNING] Cover image file " << f.text( ) << " not found" << std::endl; 
         return; 
      }

	    if( ( image = m_covers->insert( f ) ) != NULL ) {
	      if( !this->shown( ) ) {	this->show( ); }

	    /// FIXME CF_02 : Resizing / scaling a image not function - deformate the image. Repair it.
        /*
	    // Auto scaling for frame size.
	    FXint w, h;
	    FXbool r = false;

      FXint f_width  = this->getWidth( );
	    FXint f_height = this->getHeight( );
	    w = image->getWidth( );
	    h = image->getHeight( );
	    if( f_width  > w ) { w = f_width;  r = true; }
	    if( f_height > h ) { h = f_height; r = true; }
	    if( r ) { image->scale( w, h ); }
        */

        if( m_created ) { image->create( ); }
	      this->setImage( image );
      }    
    }
    else { 
      #ifdef __DEBUG
      cout << "[DEBUG MW_CoverFrame::showImage] Cover image of entry name: " << name.text( ) << " not set" << endl;
      #endif // __DEBUG
    } 
  }

  if( !this->getImage( ) && this->shown( ) ) {
    std::cout << "[WARNING] Not find a cover image for entry: " << name.text( ) << "std::endl" << std::endl; 
    this->hide( );
  }
}

/*************************************************************************************************/
