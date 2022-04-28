/*******************************************************************
*
*  DESCRIPTION: Atomic Model Datageneration
*
*******************************************************************/

/** include files **/
#include "datageneration.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Datageneration
* Description:
********************************************************************/
Datageneration::Datageneration( const string &name )
: Atomic( name )
, accountNO_in( addInputPort( "accountNO_in" ) )
, LT_in ( addInputPort( "LT_in" ) )
, data1_out( addOutputPort( "data1_out" ) )
, data2_out( addOutputPort( "data2_out" ) )
, data3_out( addOutputPort( "data3_out" ) )
, data4_out( addOutputPort( "data4_out" ) )
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
Model &Datageneration::initFunction()
{
	N4=4;
	N3=3;
	N2=2;
	N1=1;
	LT=0;
	accountNO=0;
	this-> passivate();

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Datageneration::externalFunction( const ExternalMessage &msg )
{
    if ( msg.port() == LT_in )
    {
    	LT=static_cast <int> (msg.value());
    	periodtime=Time (0,0,LT,0);
        sending=true;
        holdIn (active,Time::Zero);
    }
    if ((msg.port() == accountNO_in )&&(sending))
	{
		accountNO = static_cast < int > (msg.value());
		sending=false;
		holdIn(active, Time::Zero );
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Datageneration::internalFunction( const InternalMessage & )
{
	if (sending)
		holdIn(active, periodtime);
	else
	{  //std::cout<<"i am here"<<endl;
	  accountNO=0;
	  passivate();
	  }

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Datageneration::outputFunction( const InternalMessage &msg )
{
 if (sending==false)
 {   //std::cout<<"sending==false"<<endl;
	if (accountNO==4)
	 	{sendOutput(msg.time(),data4_out,N4);
	     sendOutput(msg.time(),data3_out,N3);
	     sendOutput(msg.time(),data2_out,N2);
	     sendOutput(msg.time(),data1_out,N1);}
	else if (accountNO==3)
	{    sendOutput(msg.time(),data3_out,N3);
	     sendOutput(msg.time(),data2_out,N2);
	     sendOutput(msg.time(),data1_out,N1);}
	else if (accountNO==2)
	{    sendOutput(msg.time(),data2_out,N2);
	     sendOutput(msg.time(),data1_out,N1);}
	else if (accountNO==1)
	 	{sendOutput(msg.time(),data1_out,N1);}
 }
		return *this ;
}


