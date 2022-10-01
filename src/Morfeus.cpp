#include<Morfeus.h>
#include<MW_ContextBox.h>

/*************************************************************************************************/
FXDEFMAP( MorfeusWindow ) MWM[ ] = {
  FXMAPFUNCS( SEL_COMMAND,     MorfeusWindow::ID_LAUNCH,      MorfeusWindow::SERVICE_WEBLIK, MorfeusWindow::OnCmd_launch ),
  FXMAPFUNC(  SEL_PROCESS_RUN, MorfeusWindow::NOTIFY_PROCESS, MorfeusWindow::OnProc_Notify ),
  FXMAPFUNC(  SEL_PROCESS_END, MorfeusWindow::NOTIFY_PROCESS, MorfeusWindow::OnProc_Notify ),
  FXMAPFUNC(  SEL_COMMAND,     MorfeusWindow::ID_LIST,        MorfeusWindow::OnCld_List ),
  FXMAPFUNC(  SEL_COMMAND,     MorfeusWindow::ID_ABOUT,       MorfeusWindow::OnCmd_About )
};
FXIMPLEMENT( MorfeusWindow, FXGWindow, MWM, ARRAYNUMBER( MWM ) )

#define MORFEUS_APP( ) ( dynamic_cast<MW_App*>( this->getApp( ) ) )

/*************************************************************************************************/
MorfeusWindow::MorfeusWindow( FXApp *a )
             : FXGWindow( a, "Morfeus", NULL, NULL, CONTROLS_STATIC | WINDOW_PRIMARY | WINDOW_STATIC | WINDOW_CLIENTSIZE, 0, 0, 500, 350 )
{
  /// initialize //////////////////////////////
  new FXToolTip( getApp( ) );

  FXString icthpth = DEFAULT_THEME_PATH;
  FXString th_name = IC_FAENZA;
  //m_ict.load( icthpth + th_name );

  //m_icons = new FXIconCache( getApp( ) );

  m_procman    = new ProcessManager( getApp( ), this, MorfeusWindow::NOTIFY_PROCESS );
  m_xmlcurrent = NULL;
  m_created    = false;

  if( Initialize( ) ) {
    /// Window  mask ////////////////////////////
    FXVerticalFrame   *base_fr    = new FXVerticalFrame( this, FRAME_NONE | LAYOUT_FILL );		   // Hlavni layout okna
    FXHorizontalFrame *content_fr = new FXHorizontalFrame( base_fr, MODE_CONTENT );                // Obsah okna
    m_cover  = new MW_CoverFrame( content_fr, FRAME_LINE | LAYOUT_SIDE_LEFT | LAYOUT_FILL_Y );     // Cover

    /// Panel spoustece ////////////////////
    right_fr = new FXVerticalFrame( content_fr, FRAME_NONE | LAYOUT_FILL, SPACING_CONTENT );       // Pravy panel pro obsah aplikace
	  m_context = new MW_ContextBox( right_fr, this, MorfeusWindow::ID_LIST );                       // Combobox pro vyber kontextu
	  new FXSpring( right_fr, LAYOUT_FILL_Y );													   // Pruzinka ... ;)
    FXVerticalFrame *action_fr = new FXVerticalFrame( right_fr, MODE_ACTOR );                      // Panel pro tlacitko(/a)
    m_launch = new FXButton( action_fr, "Start game", NULL, this, MorfeusWindow::ID_LAUNCH, BUTTON_NORMAL | LAYOUT_FILL_X );   // Tlacitko pro spusteni aplikace

    /// Window headerbar widgets - Application menu button
    FXMenuPane *mp = new FXMenuPane( this );
    m_menu = new FXMenuButton( getHeader( ), "\tMenu", getMenuIcon( ), mp, BUTTON_TOOLBAR |ICON_ABOVE_TEXT );

    this->menu( mp, m_xmlmenu );
    new FXMenuSeparator( mp );
    new FXMenuCommand( mp, "About", GetIcon( "#about", 16 ), this, MorfeusWindow::ID_ABOUT );

    /// Window headerbar widgets - Service weblinks button bar
    m_service_fr = new FXHorizontalFrame( getHeader( ), LAYOUT_RIGHT | MODE_SERVICE | LAYOUT_CENTER_Y, SPACING_NONE );

    this->getApp( )->addSignal( SIGCHLD, m_procman, ProcessManager::SIG_CHILD, false, 0 );
  }
  else { getHeader( )->setText( "( C ) 2019 - 2022 D.A.Tiger by GNU GPL v3" ); }
}

MorfeusWindow::~MorfeusWindow( )
{

}

void MorfeusWindow::create( )
{
   MW_App *a = MORFEUS_APP( );

   FXGWindow::create( );
   this->show( PLACEMENT_SCREEN );
   m_created = true; /// :'(

   if( a->getXMLstate( ) == XML_SUCCESS ) {
	   ShowMenuIcon( );
     weblinks( );
     //actions( );
   }
   else {
	   FXString msg = "Nenalezen nebo chybny kontrolni XML soubor:\n";
     //msg += m_xmldoc->ErrorStr( );
	   cerr << "[FATAL RRROR] Morfeus xml control file not found! Exiting...\n" << msg.text( ) << endl;
	   FXMessageBox::error( getApp( ), MBOX_OK, "Nelze pokracovat!", msg.text( ) );
	   exit( 1 );
   }
}

/*** Control file ********************************************************************************/
FXbool MorfeusWindow::Initialize( )
{
  /* Necteni sekci z kontrolniho XML souboru a nastaveni titulku okna */
  XMLElement *xml_root = NULL;
  FXbool resh   = false;
  MW_App *a     = MORFEUS_APP( );
  m_xmlservices = NULL;
  m_xmlui       = NULL;
  m_xmlictheme  = NULL;

  if( a->getXMLstate( ) == XML_SUCCESS ) {
    FXWindowHeader *wh = getHeader( );

    xml_root      = a->getXMLRoot( );
    m_xmlservices = xml_root->FirstChildElement( "Services" );
    m_xmlmenu     = xml_root->FirstChildElement( "Menu" );
    m_xmlui       = xml_root->FirstChildElement( "Ui" );
    m_xmlictheme  = xml_root->FirstChildElement( "Theme:Icons" );

    // Titulek okna
    wh->setTitle( xml_root->Attribute( "title" ) );
    wh->setText( xml_root->Attribute( "subtitle" ) );

    // Rozmery okna
    FXString w_size = xml_root->Attribute( "width" );
    FXString h_size = xml_root->Attribute ( "height" );
    
    #ifdef __DEBUG
    cout << "[DEBUG] Set size: " << w_size.text( ) << " x " << h_size.text( ) << endl;
    #endif // __DEBUG

    if( !w_size.empty( ) ) { this->setWidth( w_size.toInt( ) ); }
    if( !h_size.empty( ) ) { this->setHeight( h_size.toInt( ) ); }

    if( m_xmlictheme ) {
      FXIcon *icon = GetIcon( xml_root->Attribute( "icon" ) );
      if( icon ) { setIcon( icon ); }
    }
    else { cerr << "[WARNING] Nenalezeny seznam ikon!" << endl; }

    // Pocatecni nastaveni pracovniho adresar Morfea
    FXString wp = xml_root->Attribute( "workdir" );
    if( !wp.empty( ) ) { m_procman->setWorkDir( wp, false, true ); } else { m_procman->setWorkDir( ); }

    resh = true;
  }

  return resh;
}

/*************************************************************************************************/
FXint MorfeusWindow::environment( )
{
 /* FCE nastasvi promene prostredi
  * prms -
  */

  FXint _resh = 0;
  FXint _num  = m_envdict.no( );
  FXString _k, _d;

  for( FXint i = 0; i < _num; i++ ) {
    _k = m_envdict.key( i );
    _d = m_envdict.data( i );

    if( !_k.empty( ) && !_d.empty( ) ) {
      FXSystem::setEnvironment( _k, _d );
      _resh++;
    }
  }

  return _resh;
}

FXint MorfeusWindow::autostart( )
{
 /* realizuje automaticky start vybrane akce
  * prms -
  */

  FXint _resh = 0;
  //if( m_autostart ) { _resh = runAction( ); }
  return _resh;
}

FXint MorfeusWindow::weblinks( )
{
  FXint num = 0;
  FXString label;

  if( m_xmlservices ) {
	  for( XMLElement *service = m_xmlservices->FirstChildElement( "weblink" ); service; service = service->NextSiblingElement( "weblink" ) ){
	    FXIcon *icon = GetIcon( service->Attribute( "icon" ) );
      label = ( icon == NULL ? "" : "\t" );
	    label += service->Attribute( "label" );
	    FXButton *b = new FXButton( m_service_fr, label, icon, this, MorfeusWindow::SERVICE_WEBLIK, BUTTON_TOOLBAR );
	    b->create( );
	    b->setUserData( service );
	    b->setBackColor( getHeader( )->getBackColor( ) );
	    num++;
	  }
  }

  return num;
}

FXint MorfeusWindow::menu( FXMenuPane *pane, XMLElement *mel )
{
  FXint num = 0;

  if( mel ) {
	  for( XMLElement *e = mel->FirstChildElement( ); e; e = e->NextSiblingElement( ) ) {
	    FXString type = e->Name( );
	    if( type == "Separator" 	) { new FXMenuSeparator( pane ); }
	    else if( type == "Entry" ) {
        FXString icon_name = e->Attribute( "icon" );
	      FXIcon   *icon = GetIconCopy( icon_name );
	      FXMenuCommand *mc = new FXMenuCommand( pane, e->Attribute( "label" ), icon, this, MorfeusWindow::SERVICE_MENU );
	      mc->setUserData( e );
	      num++;
	    }
	  }
  }

  if( m_xmlservices ) {
    for( XMLElement *entry = m_xmlservices->FirstChildElement( "menu" ); entry; entry = entry->NextSiblingElement( "menu" ) ) {
 	    FXString icon_name = entry->Attribute( "icon" );
	    FXIcon   *icon = GetIconCopy( icon_name );
	    FXMenuCommand *mc = new FXMenuCommand( pane, entry->Attribute( "label" ), icon, this, MorfeusWindow::SERVICE_MENU );
	    XMLElement *mc_service = entry;
	    mc->setUserData( mc_service );
	    num++;
    }
  }

  return num;
}

void MorfeusWindow::SetCurrent( XMLElement *entry )
{
  if( m_xmlcurrent != entry ) {
	  m_xmlcurrent = entry;

	  // Set button text, if-any
    FXString start_label = entry->Attribute( "start" );
    if( !start_label.empty( ) ) { m_launch->setText( start_label ); }
    else{ m_launch->setText( "Start game" ); }

    // Set cover image, if-any
    m_cover->showImage( entry->Name( ) );

    // Set icon, if-any
    FXString icon_str = entry->Attribute( "icon" );
    if( !icon_str.empty( ) ) { ShowMenuIcon( GetIcon( icon_str ) ); }
  }
}

/*** Run a process *******************************************************************************/
FXint MorfeusWindow::Launch( XMLElement *actel, const FXString name )
{
  MArgumentsList _args;
  FXString        cmd;
  FXString        url;
  FXint           resh = -1;

  if( !actel ) { return -2; }
  actel = CheckContext( actel );

  url = actel->Attribute( "xlink:href" );
  if( url.empty( ) ) {
    cmd = m_context->checkAttr( actel, "cmd" );
    if( !cmd.empty( ) ) {
      if( !ShowMessage( actel ) ) { return -3; }
      m_procman->setWorkDir( m_context->checkAttr( actel, "workdir" ), true );

      _args.insert( 0, cmd.text( ) ); /// FIXME 01 : Add program exists control
      _args.split( actel->Attribute( "args" ) );
      _args.append( NULL );
    }
  }
  else {
	  _args.insert( 0, "/usr/bin/xdg-open" );
	  _args.insert( 1, url.text( ) );
	  _args.append( NULL );
  }

  if( m_procman->start( _args ) ) { resh = 0; }

  return resh;
}


/*** Event handlers ******************************************************************************/
long MorfeusWindow::OnCmd_launch( FXObject *sender, FXSelector sel, void *data )
{
  /* Handler obsluhy udalosti - obecny */
  long resh = 0;

  switch( FXSELID( sel ) ) {
    case MorfeusWindow::ID_LAUNCH : {
      Launch( m_xmlcurrent );
      if( m_context->getNumItems( ) > 1 ) { MORFEUS_APP( )->WriteConfig( "context", m_xmlcurrent->Name( ) ); }

      break;
    }

    case MorfeusWindow::ID_CONFIG : {
      break;
    }

    case MorfeusWindow::ID_EXIT : {
      	/*
      	if( !m_process ) { getApp( )->handle( this, FXSEL( SEL_COMMAND, FXApp::ID_QUIT ), NULL ); }
      	else {
		  // Ochranna pojistka. Nektere procesy (nebo spis system) oznamuji sve ukonceni driv, nez skutecne skonci. Toto by melo zabranit nasilnemu preruseni procesu.
		  FXuint answer = FXMessageBox::error( getApp( ), MBOX_YES_NO, "Nelze skoncit",
						  "posledni spusteny proces jeste bezi, nemohu skoncit, protoze hrozi ztrata dat!\n Ma Morfeus skoncit ihned po ukonceni spustene ulohy?" );
		  if( answer == MBOX_CLICKED_YES ) {
			if( !m_process ) { getApp( )->handle( this, FXSEL( SEL_COMMAND, FXApp::ID_QUIT ), NULL ); }
			else { m_exit = true; }
		  }
      	}
      	*/
      break;
    }

    case MorfeusWindow::SERVICE_WEBLIK : {
      FXId       *entry  = dynamic_cast<FXId*>( sender );
      XMLElement *data   = static_cast<XMLElement*>( entry->getUserData( ) );
      if( Launch( data ) != 0 ) {
        FXMessageBox::error( getApp( ), MBOX_OK, "Menu error", "Pozadovanou akci Menu ->'%s' nelze provest ", data->Attribute( "label" ) );
      }

      break;
    }

    case MorfeusWindow::SERVICE_MENU : {
      FXId       *entry = dynamic_cast<FXId*>( sender );
      XMLElement *data  = static_cast<XMLElement*>( entry->getUserData( ) );
      if( Launch( m_context->findAction( data->Attribute( "action" ) ) ) != 0 ) {
        FXMessageBox::error( getApp( ), MBOX_OK, "Menu error", "Pozadovanou akci Menu ->'%s' nelze provest ", data->Attribute( "label" ) );
      }
      break;
    }
  }

  return resh;
}

long MorfeusWindow::OnProc_Notify( FXObject *sender, FXSelector sel, void *data )
{
  switch( FXSELTYPE( sel ) ) {
    case SEL_PROCESS_RUN : hide( ); break;
    case SEL_PROCESS_END : show( ); break;
  }

  return 0;
}

long MorfeusWindow::OnCld_List( FXObject *sender, FXSelector sel, void *data )
{
  FXComboBox *combobox = dynamic_cast<FXComboBox*>( sender );
  FXint index = combobox->getCurrentItem( );
  SetCurrent( static_cast<XMLElement*>( combobox->getItemData( index ) ) );
  return 1;
}

/*** Icons and images ****************************************************************************/
FXIcon* MorfeusWindow::GetIcon( const FXString &name, int size )
{
// Vrati instanci ikony uvedenou v ridicim souboru. Funkce si precte informace o pozadavane ikone
// z elemntu <Theme:Icons>. Dokaze rozlisit podle pocatacniho znaku '#' ze je pozadovana ikona z
// preddefinovaneho tematu (viz popis ridiciho XML souboru v dokumentaci)
//
// Vrati instanci ikony ze slovniku ikonoveho tematu. Pokud ikona jeste nebyla pred tim pouzite,
// bude zarazen do iconcahe a odtud bude nadale vracena kdykoliv o ni bude pozdeji pozadano. V
// pripade neuspechu vraci NULL

  if( name.empty( ) ) { return NULL; }
  #ifdef __DEBUG
  cout << "[DEBUG] Load icon: " << name.text( ) << endl;
  #endif // __DEBUG
  FXIcon   *icon = NULL;
  FXString  icon_path = FXString::null;

  if( name[ 0 ] != '#' ) {
    icon_path = m_ict.at( m_xmlictheme, name );
  }
  else {
	  FXString ic_name, ic_size;
	  FXint sep = name.find( ':' );

	  if( sep > 0 ) {
	    ic_name = name.mid( 1, sep - 1 );
	    ic_size = name.right( ( name.length( ) - sep ) - 1 );
	    icon_path = m_ict.at( ic_name, ic_size.toInt( ) );
	  }
	  else {
	    ic_name = name.mid( 1, name.length( ) );
	    icon_path = m_ict.at( ic_name, size );
	  }
  }

  if( !icon_path.empty( ) ) {
	  icon = m_icons->insert( icon_path );
	  #ifdef __DEBUG
    if( !icon ) { cout << "[DEBUG] Icon " << name.text( ) << "NOT CREATED!" << endl; }
    #endif // __DEBUG

	  if( m_created ) { icon->create( ); }
  }

  return icon;
}

FXIcon* MorfeusWindow::GetIconCopy( const FXString &name, int size )
{
  FXIcon *copy =NULL;
  FXColor *data = NULL;

  FXIcon *source = GetIcon( name, size );
  FXint w, h, csize;

  if( source != NULL ) {
    source->restore( );
    w = source->getWidth( );
    h = source->getHeight( );
    csize = w * h;
    callocElms( data, csize );
    copyElms( data, source->getData( ), csize );
    copy = new FXIcon( getApp( ), data, source->getTransparentColor( ), source->getOptions( ) | IMAGE_KEEP | IMAGE_SHMI, w, h );
  }

  return copy;
}

void MorfeusWindow::ShowMenuIcon( FXIcon *ic )
{
   FXIcon *menu_ic = NULL;
   if( !ic ) { cout << "[WARNING] Icon not set" << endl; }
   menu_ic = ( ic ? ic : this->getIcon( ) );													   // FXWindow::getIcon( )      -> Vrati ikonu ktera je aktualne oknu nastavena
   m_menu->setIcon( ( menu_ic ? menu_ic : getMenuIcon( ) ) );									   // FXGWindow::getMenuIcon( ) -> Vrati preddefinovanou ikonu urcenou pro hlavni menu
}

/*** Helpers methods *****************************************************************************/
XMLElement* MorfeusWindow::CheckContext( XMLElement *actionel )
{
// Actions
// Vrati kontextovy element dane akce, pokud takovy existuje. V pripade neuspechu vraci zadany
// element akce.
  FXString    contextid = getContext( );
  XMLElement *contextel = NULL;

  if( !actionel ) { return NULL; }
  #ifdef __DEBUG
  cout << "[DEBUG] Context: " << contextid.text( ) << " Action : " << ( actionel ? actionel->Name( ) : "Not enter!" ) <<  endl;
  #endif // __DEBUG
  if( contextid != actionel->Name( ) ) {
    for( contextel = actionel->FirstChildElement( "Context" ); contextel; contextel = contextel->NextSiblingElement( "Context" ) ) {
      if( contextel && contextel->Attribute( "id" ) == contextid ) { break; }
    }
  }
  #ifdef __DEBUG
  cout << "[DEBUG] Found context? " << ( contextel ? "Yes" : "No" ) << "\n";
  #endif // __DEBUG
  
  return ( contextel ? contextel : actionel );
}

FXbool MorfeusWindow::ShowMessage( XMLElement *e )
{
  FXbool   res     = true;

  FXString message = e->Attribute( "alert" );
  if( !message.empty( ) ) {
    FXuint answer = FXMessageBox::warning( getApp( ), MBOX_YES_NO, "VYSTRAHA", "%s \nPrejete si OPRAVDU pokracovat?", message.text( ) );
	  if( answer == MBOX_CLICKED_NO ) { res = false; }
  }

  message = e->Attribute( "info" );
  if( !message.empty( ) ) {
    FXMessageBox::information( getApp( ), MBOX_OK, "INFO", message.text( ) );
  }

  return res;
}

/*** END *****************************************************************************************/
