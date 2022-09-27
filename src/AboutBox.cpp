#include<AboutBox.h>

FXIMPLEMENT( AboutBox, FXGDialogBox, NULL, 0 );

/*************************************************************************************************/
AboutBox::AboutBox( FXApp *a, XMLElement *links )
        : FXGDialogBox( a, "About Morfeus", WINDOW_STATIC, 0, 0, 400, 200 )
{
  FXString ver_str = "Version: ";
  //ver_str += FXString::value( Morfeus_VERSION_MAJOR ) + "." + FXString::value( Morfeus_VERSION_MINOR );

  FXVerticalFrame *content = new FXVerticalFrame( this, FRAME_GROOVE | LAYOUT_FILL );
  new FXLabel( content, "The universal GUI for (game) launchers", NULL, JUSTIFY_LEFT | LAYOUT_FILL_X );
  //new FXLabel( content, ver_str, NULL, JUSTIFY_LEFT | LAYOUT_FILL_X );
  new FXLabel( content, "Author: P.Safarik aka D.A.Tiger (C) 2019 - 2022", NULL, JUSTIFY_LEFT | LAYOUT_FILL_X );
  new FXLabel( content, "Licence: GNU GPL v.3", NULL, JUSTIFY_LEFT | LAYOUT_FILL_X );
  new FXHorizontalSeparator( content );
  new FXLabel( content, "Tools and Libraries:", NULL, JUSTIFY_LEFT | LAYOUT_FILL_X );
  new FXLabel( content, "Fox toolkit: www.fox-toolkit.org", NULL, JUSTIFY_LEFT | LAYOUT_FILL_X );
  new FXLabel( content, "Tiny XML: http://www.grinninglizard.com/tinyxml/", NULL, JUSTIFY_LEFT | LAYOUT_FILL_X );
}

AboutBox::~AboutBox( )
{

}

void AboutBox::create( )
{
  FXGDialogBox::create( );
  show( PLACEMENT_SCREEN );
}
