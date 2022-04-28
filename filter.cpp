/*******************************************************************
*
*  DESCRIPTION: Atomic Model Filter

*
*******************************************************************/

/** include files **/
#include "filter.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Filter
* Description:
********************************************************************/
Filter::Filter( const string &name )
: Atomic( name )
, bit1_in( addInputPort( "bit1_in" ) )
, bit2_in( addInputPort( "bit2_in" ) )
, bit3_in( addInputPort( "bit3_in" ) )
, bit4_in( addInputPort( "bit4_in" ) )
, choice_in( addInputPort( "choice_in" ) )
, bit_out( addOutputPort( "bit_out" ) )
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
Model &Filter::initFunction()
{
	this-> passivate();
	processing=false;
	sending1=false;
	sending2=false;
	sending3=false;
	sending4=false;
	bit1=bit2=bit3=bit4=0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Filter::externalFunction( const ExternalMessage &msg )
{
		if (msg.port() == bit1_in)
			{
                processing=true;
				bit1 = static_cast < int > (msg.value());
				holdIn(active, Time::Zero );
			}
		if (msg.port() == bit2_in)
			{
                processing=true;
				bit2 = static_cast < int > (msg.value());
			    holdIn(active, Time::Zero );
			}
		if (msg.port() == bit3_in)
			{
              processing=true;
			  bit3 = static_cast < int > (msg.value());
			  holdIn(active, Time::Zero );
			}
		if (msg.port() == bit4_in)
		{
			processing=true;
			bit4 = static_cast < int > (msg.value());
			holdIn(active, Time::Zero );
		}

	if ((msg.port()==choice_in)&&( this->state() == active))
				{
					choice=static_cast < int > (msg.value()); //choice<=4
					if (choice==4)
						sending4=true;    //account 4 is chosen
					else if (choice==3)
						sending3=true;    //account 3 is chosen
					else if(choice==2)
						sending2=true;     //account 2 is chosen
					else if (choice==1)
						sending1=true;     //account 1 is chosen
					processing=false;
					holdIn (active,Time::Zero);
				}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Filter::internalFunction( const InternalMessage & )
{
	if (processing)
		holdIn(active, preparationTime);
	else
	{
		sending1=false;
	    sending2=false;
        sending3=false;
        sending4=false;
        bit1=bit2=bit3=bit4=0;
        passivate();
	}
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Filter::outputFunction( const InternalMessage &msg )
{
	if (processing==false)
	{
if (sending4)
 	sendOutput(msg.time(),bit_out,bit4); //sending out 0 means no information received in this account

if (sending3)
    sendOutput(msg.time(),bit_out,bit3);

if (sending2)
    sendOutput(msg.time(),bit_out,bit2);

if (sending1)
 	sendOutput(msg.time(),bit_out,bit1);
	}
	return *this ;
}
