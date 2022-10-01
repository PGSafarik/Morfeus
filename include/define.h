#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include<fox-1.7/fx.h>
#include<fxghi.h>
#include<iostream>
#include<sys/wait.h>
#include<tinyxml2.h>

#include<Utils.h>

//#define __DEBUG

namespace Morfeus_Version {
	
	//Date Version Types
	static const char DATE[] = "30";
	static const char MONTH[] = "10";
	static const char YEAR[] = "2022";
	static const char UBUNTU_VERSION_STYLE[] =  "22.10";
	
	//Software Status
	static const char STATUS[] =  "ALPHA";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 3;
	static const long BUILD  = 1;
	static const long REVISION  = 1;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 1;
	#define RC_FILEVERSION 0,3,1,1
	#define RC_FILEVERSION_STRING "0, 3, 1, 1\0"
	static const char FULLVERSION_STRING [] = "0.3.1.1";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 0;
}


#define DEFAULT_IC_THEME_PATH "/usr/share/games/morfeus/data/icons.map"
#define DEFAULT_IC_THEME_NAME	"Faenza"

#define MAIN_DECOR DECOR_BORDER | DECOR_TITLE
#define JUSTIFY_CENTER JUSTIFY_CENTER_X | JUSTIFY_CENTER_X
#define LAYOUT_CENTER LAYOUT_CENTER_X | LAYOUT_CENTER_X
#define FRAME_DOWN_2 FRAME_NONE /*SUNKEN | FRAME_THICK*/ | LAYOUT_SIDE_BOTTOM | LAYOUT_CENTER_X | LAYOUT_FILL_X
#define FRAME_SERVICE_L FRAME_GROOVE | LAYOUT_SIDE_BOTTOM | LAYOUT_LEFT | PACK_UNIFORM_WIDTH | PACK_UNIFORM_HEIGHT
#define FRAME_SERVICE_R FRAME_GROOVE | LAYOUT_SIDE_BOTTOM | LAYOUT_RIGHT | PACK_UNIFORM_WIDTH | PACK_UNIFORM_HEIGHT

#define SPACING_NONE    0, 0, 0, 0,  0, 0, 0, 0,  0, 0
#define SPACING_ONE     0, 0, 0, 0,  1, 1, 1, 1,  1, 1
#define SPACING_LINKS   0, 0, 0, 0,  0, 0, 0, 0,  1, 0
#define SPACING_CONTENT 0, 0, 0, 0,  2, 2, 2, 2,  3, 3

#define MODE_CONTENT  FRAME_NONE | LAYOUT_FILL, SPACING_CONTENT
#define MODE_SELECTOR FRAME_LINE | LAYOUT_SIDE_TOP | LAYOUT_FILL_X, SPACING_NONE
#define MODE_ACTOR    FRAME_NONE | LAYOUT_SIDE_BOTTOM | LAYOUT_CENTER_X | LAYOUT_FILL_X, SPACING_NONE
#define MODE_SERVICE  FRAME_NONE /*| PACK_UNIFORM_WIDTH | PACK_UNIFORM_HEIGHT*/



using namespace tinyxml2;
using namespace std;
using namespace FX;
using namespace FXGHI;

#endif // DEFINE_H_INCLUDED

/*** END *****************************************************************************************/
