/*******************************************************************
*
*  DESCRIPTION: Atomic Model Display
*******************************************************************/

/** include files **/
#include "display.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Write
* Description:
********************************************************************/
Display::Display( const string &name )
: Atomic( name )
, filter_in( addInputPort( "filter_in" ) )
, write_in ( addInputPort ( "write_in" ) )
, display_out( addOutputPort( "display_out" ) )
, preparationTime( 0, 0, 10, 0 )
,timeout (0,0,5,0)
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;

	string time2( MainSimulator::Instance().getParameter( description(), "timeout" ) ) ;

		if( time2 != "" )
			timeout = time2 ;

}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Display ::initFunction()
{
	this-> passivate();
	get_filter=false;
	get_write=false;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Display::externalFunction( const ExternalMessage &msg )
{
	//if(( msg.port() == filter_in  )&&(this->state()==passive))
	if( msg.port() == filter_in  )
	{
		    bit1_display = static_cast < int > (msg.value());
		    get_filter=true;
			holdIn(active, Time::Zero);
	}
    //if (( msg.port() == write_in )&&(this->state()==active))
	 if ( msg.port() == write_in )
	{
    	 bit2_display = static_cast < int > (msg.value());
    	 get_write=true;
    	 holdIn(active, Time::Zero);
    }
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Display::internalFunction( const InternalMessage & )
{


	    passivate();
        get_filter=false;
        get_write=false;
	    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Display::outputFunction( const InternalMessage &msg )
{

	  if (get_filter)
	  { sendOutput(msg.time(),display_out,bit1_display); cout<<"news from account "<<bit1_display<<endl;}
	  if (get_write)
	  {  sendOutput(msg.time(),display_out,bit2_display); cout<<"news from accout "<<bit2_display<<endl;}

	return *this ;
}
