/*******************************************************************
*
*  DESCRIPTION: Atomic Model Data Generation
*
*******************************************************************/

#ifndef __DATAGENERATION_H
#define __DATAGENERATION_H


#include "atomic.h"     // class Atomic

class Datageneration : public Atomic
{
public:
	Datageneration( const string &name = "Datageneration" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &accountNO_in;
	const Port &LT_in;
	Port &data1_out;
	Port &data2_out;
	Port &data3_out;
	Port &data4_out;

	Time preparationTime;
	Time periodtime;
	int N4;
	int N3;
	int N2;
	int N1;
	int accountNO;
    int LT;
    bool sending;

};	// class Datageneration

// ** inline ** //
inline
string Datageneration::className() const
{
	return "Datageneration" ;
}

#endif   //__DATAGENERATION_H
