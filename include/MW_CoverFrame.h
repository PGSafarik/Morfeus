#ifndef COVER_H_INCLUDED
#define COVER_H_INCLUDED

#include<define.h>

class MW_CoverFrame : public FXImageFrame {
FXDECLARE( MW_CoverFrame )
  /*** Base ***/
  FXbool       m_created;   // Indicate to call method CoverFrame::create( ) - for images creating
  FXIconCache *m_covers;    // Uloziste coveru v pameti

  /*** XML control segment ***/
  XMLElement *m_xmlCoversMap;  // The XML cover images list

public:
  MW_CoverFrame( FXComposite *p, FXuint opts = FRAME_SUNKEN | FRAME_THICK,
			     FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0, FXint pl = 0, FXint pr = 0,
			     FXint pt = 0, FXint pb = 0 );
  virtual ~MW_CoverFrame( );

  /*** Operations ***/
  void create( );
  void showImage( const FXString &name = FXString::null );

protected:
  MW_CoverFrame( ) { }

};

#endif /* COVER_H_INCLUDED */
