/*******************************************************************
*
*  DESCRIPTION: Atomic Model Refresh
*
*******************************************************************/

#ifndef __REFRESH_H
#define __REFRESH_H


#include "atomic.h"     // class Atomic

class Refresh : public Atomic
{
public:
	Refresh( const string &name = "Refresh" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &refresh_setting;
	const Port &plus_in;
	const Port &minus_in;
	Port &refresh_out;

	int set_refresh;
	int set_plus;
	int set_minus;
	Time preparationTime;
    int refreshtime;
    bool processing;

};	// class Refresh

// ** inline ** //
inline
string Refresh ::className() const
{
	return "Refresh" ;
}

#endif   //__REFRESH_H
