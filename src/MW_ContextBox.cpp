/*************************************************************************
* MW_ContextBox.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger                   *
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
#include<MW_ContextBox.h>
#include<MW_App.h>

/*************************************************************************************************/
FXDEFMAP( MW_ContextBox ) CBM[ ] = { };
FXIMPLEMENT( MW_ContextBox, FXVerticalFrame, CBM, ARRAYNUMBER( CBM ) )

#define MORFEUS_APP ( dynamic_cast<MW_App*>( this->getApp( ) ) )
/*************************************************************************************************/
MW_ContextBox::MW_ContextBox( FXComposite *p, FXObject *tgt, FXSelector sel )
          : FXVerticalFrame( p, MODE_SELECTOR )
{
  m_combo = new FXComboBox( this, 10, tgt, sel, COMBOBOX_NORMAL | LAYOUT_FILL_X );

  m_xmlactions = NULL;
  m_xmlcurrent = NULL;

  m_target   = tgt;
  m_selector = sel;
}

MW_ContextBox::~MW_ContextBox( )
{
  m_xmlcurrent = NULL;
}

void MW_ContextBox::create( )
{
  FXVerticalFrame::create( );
  m_combo->create( );

  Initialize( );
}

/*************************************************************************************************/
FXString MW_ContextBox::checkAttr( XMLElement *e, const FXString &name )
{
  // Pokud nektery z elementu ma nastaveny atribut 'workdir' jeho hodnota se pouzije k nastaveni
  // pracovniho adresare Morfea, za podminky ze je to povoleno. Prednost ma element ch
  FXString res = e->Attribute( name.text( ) );
  if( res.empty( ) ) { res = m_xmlactions->Attribute( name.text( ) ); }

  return res;
}

/**************************************************************************************************/
void MW_ContextBox::Initialize( )
{
 FXint num  = 0;
 FXint defid = 0;

  if( MORFEUS_APP->getXMLstate( ) == XML_SUCCESS ) {
    XMLElement *xmlroot = MORFEUS_APP->getXMLRoot( );
    m_xmlactions = xmlroot->FirstChildElement( "Actions" );
    m_xmlcurrent = NULL;

	FXString def = MORFEUS_APP->ReadConfig( "context" );
    if( def.empty( ) ) { m_xmlactions->Attribute( "default" ); }

	for( XMLElement *action = m_xmlactions->FirstChildElement( ); action; action = action->NextSiblingElement( ) ) {
	  FXString name  = action->Name( );
	  FXString label = action->Attribute( "label" );
      FXString hide  = action->Attribute( "hide" );

      if( hide != "1" ) { // :( Ne, ne, proste NE!!!
        if( !def.empty( ) && ( name == def ) ) { defid = num; }

	    m_combo->appendItem( ( label.empty( ) ? name : label ), action );
	    num++;
      }
	}
    m_combo->setNumVisible( num );

	if( defid >= 0 ) {
	  m_combo->setCurrentItem( defid );
	  m_xmlcurrent = static_cast<XMLElement*>( m_combo->getItemData( defid ) );
	}
	m_target->handle( m_combo, FXSEL( SEL_COMMAND, m_selector ), NULL );

  }
}
