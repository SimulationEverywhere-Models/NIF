/* description  Atomic Model Account
 *
 */

#ifndef __ACCOUNT_H
#define __ACCOUNT_H


#include "atomic.h"     // class Atomic

class Account : public Atomic
{
public:
	Account( const string &name = "Account" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &account_setting;
	const Port &plus_in;
	const Port &minus_in;
	Port &accountNO_out;

	Time preparationTime;

    int set_account;
    int set_plus;
    int set_minus;
    int accountNO;
    bool processing;

};	// class Account

// ** inline ** //
inline
string Account::className() const
{
	return "Account" ;
}

#endif   //__ACCOUNT_H
