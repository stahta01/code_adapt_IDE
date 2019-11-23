
// Interface Dependencies ---------------------------------------------
#ifndef HooverDrawlet_h
#define HooverDrawlet_h

class wxDC;

// END Interface Dependencies -----------------------------------------

class HooverDrawlet
{
  public:
		HooverDrawlet();
		virtual ~HooverDrawlet();


		virtual bool Draw(wxDC &dc);
        virtual void UnDraw(wxDC &dc) = 0;

	private:
};

#endif



