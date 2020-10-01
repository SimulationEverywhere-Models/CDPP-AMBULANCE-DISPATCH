/*******************************************************************
*
*  DESCRIPTION: Response
*
*  AUTHOR: Mike
*
*  EMAIL: mvschybd@gmail.com
*
*  DATE: Nov 2, 2011
*
*******************************************************************/

/** include files **/
#include "Response.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Response
* Description: Returns Location and Priority
********************************************************************/
Response::Response( const string &name )
: Atomic( name )
, priority_in( addInputPort( "priority_in" ) )
, time_in( addInputPort( "time_in" ) )
, response_out( addOutputPort( "response_out" ) )
, preparationTime( 0, 0, 0, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
	arrival_time = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Response::initFunction()
{
	this-> passivate();
	Priority = 0;
	Outcome = 0;
	Response_Time = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Response::externalFunction( const ExternalMessage &msg )
{

	if( msg.port() == time_in )
	{
		Response_Time = static_cast < int > (msg.value());
		arrival_time = msg.time() +Time(0,0,Response_Time,0);
		holdIn( active, preparationTime );
	}
	if( msg.port() == priority_in )
	{
		Priority = (static_cast < int > (msg.value()));
		holdIn( active, preparationTime  );
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Response::internalFunction( const InternalMessage & )
{

	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Response::outputFunction( const InternalMessage &msg )
{
int max = 900;
if( Priority < 10 && Priority > 0  && Response_Time > 0){
if( Response_Time < max/(Priority * 0.5 ) ){
	Outcome = 1;
}else{
	Outcome = 0;
}

	sendOutput( arrival_time, response_out, Outcome ) ;
}
	return *this ;
}
