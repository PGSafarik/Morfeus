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
  cout << "[DEBUG] Show image of name: " << name.text( ) << endl;
  #endif // __DEBUG
  if( m_xmlCoversMap ) {
	XMLElement *e = m_xmlCoversMap->FirstChildElement( name.text( ) );
	if( !e ) { e = m_xmlCoversMap->FirstChildElement( ); }

	if( e ) {
	  /// FIXME CF_01: Adding control path of the image file, immediately after move the method
	  ///              ValidatePath( ) from MorfeusWindow class to the FXApp class.
	  f = e->Attribute( "file" ); // getApp( )->ValidatePath( e->Attribute( 'file' ) );
	}

    if( !f.empty( ) ) {
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
	  if( !this->getImage( ) && this->shown( ) ) {
	    this->hide( );
	  }
    }
  }
}

/*************************************************************************************************/
