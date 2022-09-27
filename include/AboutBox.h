#include<define.h>
#include<fxghi.h>

class AboutBox : public FXGDialogBox {
FXDECLARE( AboutBox )

public:
  AboutBox( FXApp *a, XMLElement *links );
  virtual ~AboutBox( );

  virtual void create( );

protected:
  AboutBox( ) { }

};
