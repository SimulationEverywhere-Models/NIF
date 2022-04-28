/*******************************************************************
*
*  DESCRIPTION: Atomic Model Write
*******************************************************************/

/** include files **/
#include "write.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Write
* Description:
********************************************************************/
Write::Write( const string &name )
: Atomic( name )
, choice_in( addInputPort( "choice_in" ) )
, write_out( addOutputPort( "write_out" ) )
, preparationTime( 0, 0, 10, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;

}

/*******************************************************************
* Function Name: initFunction
* Description:
*  Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Write::initFunction()
{
	this-> passivate();
		bit=0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
******************************************************** ************/
Model &Write::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == choice_in  && this->state() == passive)
	{
		    choice = static_cast < int > (msg.value());  //choice<=4
			if (choice == 4)
				bit=4;
			else if ( choice == 3)
			   bit=3;
			else if(choice == 2)
			  bit=2;
			else if (choice ==1)
			 bit=1;  //several accounts could be chosen at a time to write
			holdIn(active, preparationTime);
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Write::internalFunction( const InternalMessage & )
{
		bit=0;
		passivate();

	    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Write::outputFunction( const InternalMessage &msg )
{
    sendOutput(msg.time(),write_out,bit);

	return *this ;
}
