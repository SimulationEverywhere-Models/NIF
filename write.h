/*******************************************************************
*
*  DESCRIPTION: Atomic Model Write

*******************************************************************/

#ifndef __WRITE_H
#define __WRITE_H


#include "atomic.h"     // class Atomic

class Write : public Atomic
{
public:
	Write( const string &name = "Write" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &choice_in;
	Port &write_out;

	Time preparationTime;
	int bit;
	int choice;

};	// class Write

// ** inline ** //
inline
string Write::className() const
{
	return "Write" ;
}

#endif   //__WRITE_H
