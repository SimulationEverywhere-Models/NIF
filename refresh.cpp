/* description  Atomic Model Refresh
 *
 */
/** include files **/
#include "refresh.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

using namespace std;
/** public functions **/

/*******************************************************************
* Function Name: Refresh
* Description:
********************************************************************/
Refresh::Refresh( const string &name )
: Atomic( name )
, refresh_setting( addInputPort( "refresh_setting" ) )
, plus_in ( addInputPort ( "plus_in" ) )
, minus_in ( addInputPort ( "minus_in") )
, refresh_out( addOutputPort( "refresh_out" ) )
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
Model &Refresh::initFunction()
{
	this-> passivate();
	refreshtime=5;  //initialize to 5
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Refresh::externalFunction( const ExternalMessage &msg )
{

	if( msg.port() == refresh_setting)
	{
		if (this->state() == passive)
	   {	set_refresh= static_cast < int > (msg.value());
		  if (set_refresh == 1)
		{
			processing=true;
			holdIn(active, Time::Zero );
		}
	   }
        else if (this->state()== active)
	   {
		  	set_refresh = static_cast < int > (msg.value());
		 	if (set_refresh == 1)
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
					refreshtime++;
					holdIn(active, Time::Zero) ;
				}
	    }
	 if (( msg.port() == minus_in)&& this->state()== active)
	    {
	    	set_minus = static_cast < int > (msg.value());
	    	if (set_minus==1)
	    	{
	           refreshtime--;
	           holdIn(active, Time::Zero) ;
	    	}
        }

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Refresh::internalFunction( const InternalMessage & )
{
	if(processing)
	{holdIn (active, preparationTime);}
	else { refreshtime=5; this->passivate();}

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Refresh::outputFunction( const InternalMessage &msg )
{
	if (processing==false)
	sendOutput( msg.time(), refresh_out, refreshtime ) ;

	return *this ;
}
