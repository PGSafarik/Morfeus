#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include<fox-1.7/fx.h>
#include<fxghi.h>
#include<iostream>
#include<sys/wait.h>
#include<tinyxml2.h>
#include<Utils.h>

#define __DEBUG

//#define DEFAULT_THEME_PATH  "/usr/share/games/morfeus/data/"
#define DEFAULT_THEME_PATH "/home/gabriel/Projects/Fox/Morfeus/BETA_02.00/data/"
#define IC_FAENZA			"faenza.cfg"
//#define IC_OXYGEN			"oxygen.cfg"


#define MAIN_DECOR DECOR_BORDER | DECOR_TITLE
#define JUSTIFY_CENTER JUSTIFY_CENTER_X | JUSTIFY_CENTER_X
#define LAYOUT_CENTER LAYOUT_CENTER_X | LAYOUT_CENTER_X
#define FRAME_DOWN_2 FRAME_NONE /*SUNKEN | FRAME_THICK*/ | LAYOUT_SIDE_BOTTOM | LAYOUT_CENTER_X | LAYOUT_FILL_X
#define FRAME_SERVICE_L FRAME_GROOVE | LAYOUT_SIDE_BOTTOM | LAYOUT_LEFT | PACK_UNIFORM_WIDTH | PACK_UNIFORM_HEIGHT
#define FRAME_SERVICE_R FRAME_GROOVE | LAYOUT_SIDE_BOTTOM | LAYOUT_RIGHT | PACK_UNIFORM_WIDTH | PACK_UNIFORM_HEIGHT

#define SPACING_NONE 0, 0, 0, 0,  0, 0, 0, 0,  0, 0
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
