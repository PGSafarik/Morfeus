
#ifndef PRCOCESSMANAGER_H_INCLUDED
#define PRCOCESSMANAGER_H_INCLUDED

#include<define.h>

enum {
  SEL_PROCESS_RUN = SEL_LAST,
  SEL_PROCESS_END,
  SEL_LAST
};

class ProcessManager : public FXObject {
FXDECLARE( ProcessManager )
  /*** System ***/
  FXApp      *m_app;		// Ukazatel na instanci aplikace
  FXObject   *m_tgt;		// Ukazatel na notifikacni objekt
  FXSelector  m_sel;		// Registrovana zprava notifikaci

  /*** Work Path ***/
  FXString m_wpath;         // Globalni nastaveni pracovni cesty
  FXbool   m_wpchange;      // TRUE - Pracovni cesta byla zmenena
  FXbool   m_wplock;        // TRUE - Prcovni cesta NEMUZE byt zmenena

  /*** Process ***/
  FXProcess *m_process;     // Instance procesu
  FXint      m_procstat;    // Stav spusteneho procesu
  FXbool     m_exit;        // TRUE - indikace poazadavku ukonceni Morfea, po skonceni hry
  FXbool     m_notify;      // TRUE - Budou odesilany notifikace

public:
  ProcessManager( FXApp *a, FXObject *tgt = NULL, FXSelector sel = 0 );
  virtual ~ProcessManager( );

  /*** Operations ***/
  FXbool start( const MArgumentsList &args, FXbool wait = false );
  FXbool setWorkDir( const FXString &path = FXString::null, FXbool change = false, FXbool lock = false );

  /*** Access methods ***/
  void   setNotify( FXbool value = true ) { m_notify = value; }
  FXbool getNotify( )                     { return m_notify; }

  /*** Events & handlers ***/
  enum {
   SIG_CHILD = 1,       // Proces potomka byl ukoncen
   ID_LAST
  };
  long OnSig_Child( FXObject *sender, FXSelector sel, void *data );

protected:
  ProcessManager( ) { }
  long notify( FXuint type, void *data = NULL );
};

#endif //PRCOCESSMANAGER_H_INCLUDED
