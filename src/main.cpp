// %Filename%.cpp Copyright (c) %date%;  D.A.Tiger; GNU GPL 3
#include<MW_App.h>
#include<Morfeus.h>

int main( int argc, char **argv ) {

  #ifdef __DEBUG
   std::cout << "[DEBUG] " << __FILE__ << " " << "::main( )" << std::endl;
   std::cout << "       * Debug log enabled" << std::endl;
  #endif // __DEBUG

  MW_App app( "Morfeus", "fox-desktop" );
  app.init( argc, argv );

  new MorfeusWindow( &app );

  app.create( );
  return app.run( );
}

/*** END *****************************************************************************************/
