/*************************************************************************
* AboutBox.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger                   *
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
#include<AboutBox.h>

FXIMPLEMENT( AboutBox, FXSecondaryWindow, NULL, 0 );

/*************************************************************************************************/
AboutBox::AboutBox( FXApp *a, XMLElement *links )
        : FXSecondaryWindow( a, "About Morfeus", WINDOW_STATIC, 0, 0, 400, 200 )
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
  FXSecondaryWindow::create( );
  show( PLACEMENT_SCREEN );
}
