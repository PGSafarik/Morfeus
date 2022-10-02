/*************************************************************************
* main.cpp Copyright (c) 2019 - 2022 by  D.A.Tiger                       *
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
