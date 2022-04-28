/*******************************************************************
*
*  DESCRIPTION: Atomic Model DISPLAY

*******************************************************************/

#ifndef __DISPLAY_H
#define __DISPLAY_H


#include "atomic.h"     // class Display

class Display : public Atomic
{
public:
	Display( const string &name = "Display" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &filter_in;
	const Port &write_in;
	Port &display_out;

	Time preparationTime;
	Time timeout;
	int bit1_display;
	int bit2_display;
	bool get_filter;
	bool get_write;

};	// class Write

// ** inline ** //
inline
string Display::className() const
{
	return "Display" ;
}

#endif   //__DISPLAY_H
