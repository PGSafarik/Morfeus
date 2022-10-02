/***************************************************************************************************
* File:      MW_CoverFrame.h                                                                       *
* Project:   Morfeus                                                                               *
* Copyright: Copyriright (C) 2019 - 2022 by D.A.Tiger GNU GPL v3                                   *
* Author(s): D.A.Tiger ( drakarax@seznam.cz )                                                      *
* Note:      The image frame for show vertical cover image                                         *
***************************************************************************************************/
#ifndef COVER_H_INCLUDED
#define COVER_H_INCLUDED
/*************************************************************************
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
