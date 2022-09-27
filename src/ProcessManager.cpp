#include<ProcessManager.h>

/*** Messages Definition Map **********************************************************************/
FXDEFMAP( ProcessManager ) PMM[ ] = {
  FXMAPFUNC( SEL_SIGNAL, ProcessManager::SIG_CHILD, ProcessManager::OnSig_Child )
};
FXIMPLEMENT( ProcessManager, FXObject, PMM, ARRAYNUMBER( PMM ) )

/*** Constructor, destructor *********************************************************************/
ProcessManager::ProcessManager( FXApp *a, FXObject *tgt, FXSelector sel )
{
  m_app      = a;
  m_tgt      = tgt;
  m_sel      = sel;
  m_process  = NULL;
  m_procstat = 0;
  m_exit     = false;
  m_wpchange = false;
  m_wplock   = false;
  m_notify   = true;

  setWorkDir( );
}

ProcessManager::~ProcessManager( )
{
  if( m_process ) { delete m_process; } // trochu nasilnicke;
}

/*** Operations **********************************************************************************/
FXbool ProcessManager::start( const MArgumentsList &args, FXbool wait )
{
 /*
  Vytvoreni a spusteni noveho procesu

  Cesta k spoustenemu souboru (args[0]) nesmi zacinat a koncit mezerou (" "), musi byt absolutni
  (tedy od korenoveho adresare). Navratovy kod spousteneho procesu lze ziskat pri waiting = true,
  to vsak zablokuje celou aplikaci!

  Funkce provadi explicitni kontrolu existence instance m_process. Takto je zabraneno vicenasobnemu s
  pousteni dane akce
  */
  if( m_process ) { return false; }
  else { m_process = new FXProcess; }

  #ifdef __DEBUG
    cout << "\n" << __FILE__ << " " << "MorfeusWindow::runProcess( )\n";
    cout << "Morfeus running process:\n";
    FXint _d_num = args.no( );
    for( FXint _d_i = 0; _d_i < _d_num; _d_i++ ) { cout << " " << ( ( args[ _d_i ] != NULL ) ? args[ _d_i ] : "\n" ); }
    cout << "\n";
  #endif // __DEBUG

  FXbool _resh = false;
  if( FXStat::exists( args[ 0 ] ) ) {
    _resh = m_process->start( args[ 0 ], args.data( ) );

    #ifdef __DEBUG
      if( _resh == true ) { cout << "This process running of " << m_process->id( ) << "\n"; }
      else { cout << "This process NOT running!\n"; }
    #endif // __DEBUG

    if( _resh && wait ) {
      m_process->wait( m_procstat );

      #ifdef __DEBUG
        cout << "Process on waiting exited with " << m_procstat << " exit status\n";
      #endif // __DEBUG
    }

    notify( SEL_PROCESS_RUN );
  }
  else { FXMessageBox::error( m_app, MBOX_OK, "Spusteni procesu", "Spustilny soubor \'%s\' nenalezen ", args[ 0 ] ); }

  #ifdef __DEBUG
  cout.flush( );
  #endif // __DEBUG

  return _resh;

}

FXbool ProcessManager::setWorkDir( const FXString &path, FXbool change, FXbool lock )
{
 /* FCE nastasvi pracovni adresar
  *
  */
  FXbool   reshult = false;
  FXString new_path  = FXString::null;

  if( !m_wplock ) {
	new_path = ( !path.empty( ) ? path : FXSystem::getHomeDirectory( ) );
    FXSystem::setCurrentDirectory( new_path );

    m_wplock   = lock;
    m_wpchange = change;

    #ifdef __DEBUG
    cout << "[DEBUG] Setting current work path: " << FXSystem::getCurrentDirectory( ).text( ) << endl;
    if( lock == true ) { cout << "[DEBUG] Work path is locked! " << endl;}
    #endif // __DEBUG

    reshult = true;
  }

  #ifdef __DEBUG
  std::cout << "[DEBUG] Current work path: " << FXSystem::getCurrentDirectory( ).text( ) << std::endl;
  #endif // __DEBUG

  return reshult;
}

/*** Handlers ************************************************************************************/
long ProcessManager::OnSig_Child( FXObject *sender, FXSelector sel, void *data )
{
  #ifdef __DEBUG
    FXint _chid = m_process->id( );
  #endif // __DEBUG

  m_process->wait( m_procstat );

  #ifdef __DEBUG
    cout << "\n" <<__FILE__ << " " << "MorfeusWindow::OnSig_Child( ) \n";
    cout << "Quiting the child process " << _chid << " at " << m_process->current( ) << "\n";
    cout << "Exit code is: " << m_procstat << "\n";
    cout.flush( );
  #endif // __DEBUG

  delete m_process;
  m_process = NULL;

  if( m_wpchange ) {
	setWorkDir( );
	m_wpchange = false;
  }

  notify( SEL_PROCESS_END );
  if( m_exit ) { m_app->handle( this, FXSEL( SEL_COMMAND, FXApp::ID_QUIT ), NULL ); }
  return 1;

}

/*** Helpers methods *****************************************************************************/
long ProcessManager::notify( FXuint type, void *data )
{
  if( m_notify && m_tgt && m_sel > 0 ) {
  	#ifdef __DEBUG
	cout << "[DEBUG]ProcessManager: Process notify" << endl;
    #endif // __DEBUG
    return m_tgt->handle( this, FXSEL( type, m_sel ), data );
  }
   return 1;
}

