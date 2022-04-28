/*******************************************************************
*
*  DESCRIPTION: Atomic Model Sender

*
*******************************************************************/

#ifndef __FILTER_H
#define __FILTER_H


#include "atomic.h"     // class Atomic

class Filter : public Atomic
{
public:
	Filter( const string &name = "Filter" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &bit1_in;
	const Port &bit2_in;
	const Port &bit3_in;
	const Port &bit4_in;
	const Port &choice_in;
	Port &bit_out;

	Time preparationTime;
	int bit1,bit2,bit3,bit4;
	int choice;
    bool sending4;
    bool sending3;
    bool sending2;
    bool sending1;

    bool processing;
};	// class Filter

// ** inline ** //
inline
string Filter::className() const
{
	return "Filter" ;
}

#endif   //__FILTER_H
