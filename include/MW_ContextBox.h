#ifndef CONTEXTBOX_H_INCLUDED
#define CONTEXTBOX_H_INCLUDED

#include<define.h>

class MW_ContextBox : public FXVerticalFrame {
FXDECLARE( MW_ContextBox )
  /*** BASE ***/
  FXComboBox *m_combo;
  FXObject   *m_target;
  FXSelector  m_selector;

  /*** XML Control segment ***/
  XMLElement *m_xmlactions;	// The XML Element of Actions list.
  XMLElement *m_xmlcurrent;	// The XML Element of curent context.

public :
  MW_ContextBox( FXComposite *p, FXObject *tgt = NULL, FXSelector sel = 0 );
  virtual ~MW_ContextBox( );

  /*** Operations ***/
  virtual void create( );

  /*** Access methods ***/
  FXint       getNumItems( ) { return m_combo->getNumItems( ); }
  FXString    checkAttr( XMLElement *e, const FXString &name );
  XMLElement* findAction( const FXString &name ) { return m_xmlactions->FirstChildElement( name.text( ) ); }

protected:
  MW_ContextBox( ) { }

  /*** Helpers operations ***/
  void Initialize( );
};



#endif // CONTEXTBOX_H_INCLUDED
