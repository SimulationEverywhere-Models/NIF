/* description  Atomic Model Account
 *
 */
/** include files **/
#include "account.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Account
* Description:
********************************************************************/
Account::Account( const string &name )
: Atomic( name )
, account_setting( addInputPort( "account_setting" ) )
, plus_in( addInputPort( "plus_in" ) )
, minus_in( addInputPort( "minus_in" ) )
, accountNO_out( addOutputPort( "accountNO_out" ) )
, preparationTime( 0, 0, 10, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;

}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Account::initFunction()
{
	this-> passivate();
    accountNO=0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Account::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == account_setting)
		{
			if (this->state() == passive)
		   {	set_account= static_cast < int > (msg.value());
			    if (set_account == 1)
			  {
				processing=true;
				holdIn(active, Time::Zero );
			  }
		   }
	       else if (this->state()== active)
		  {
			  	set_account = static_cast < int > (msg.value());
			 	if (set_account == 1)
			  	{
			  		processing=false;
			  		holdIn(active,Time::Zero);
			    }
		  }
		}

	if (( msg.port() == plus_in )&& this->state()== active)
		{
			   set_plus =static_cast < int > (msg.value());
			   if (set_plus == 1)
			   {
				   accountNO++;
				   holdIn(active, Time::Zero) ;
			   }
		}
    if (( msg.port() == minus_in)&& this->state()== active)
		{
		    	set_minus = static_cast < int > (msg.value());
		    	if (set_minus==1)
		    	{
		           accountNO--;
		           holdIn(active, Time::Zero) ;
		    	}
	    }

		 	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Account::internalFunction( const InternalMessage & )
{
	if(processing)
			holdIn (active, preparationTime);

	else { accountNO=0; this->passivate();}

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Account::outputFunction( const InternalMessage &msg )
{
	if (processing==false)
		sendOutput( msg.time(), accountNO_out, accountNO ) ;

		return *this ;
}
