/*******************************************************************
*
*  DESCRIPTION: CallerINFO
*
*  AUTHOR: Mike
*
*  EMAIL: mvschybd@gmail.com
*
*  DATE: Nov 2, 2011
*
*******************************************************************/

/** include files **/
#include "CallerINFO.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: CallerINFO
* Description: Returns Location and Priority
********************************************************************/
CallerINFO::CallerINFO( const string &name )
: Atomic( name )
, callin( addInputPort( "callin" ) )
, lout( addOutputPort( "lout" ) )
, pout( addOutputPort( "pout" ) )
, preparationTime( 0, 0, 0, 0 )
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
Model &CallerINFO::initFunction()
{
	Location = 0;
	Priority = 0;
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &CallerINFO::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == callin )
	{
		Priority = (static_cast < int > (msg.value()))/10;
		Location = static_cast < int > (msg.value())%10;
		if(Location > 0 && Priority > 0 && Location < 10 && Priority < 10){

			}else{
				if(Location == 0 && Priority == 0){

				}else{
					Priority = 0;
					Location = 0;
			}
		}
		holdIn( active, preparationTime );
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &CallerINFO::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &CallerINFO::outputFunction( const InternalMessage &msg )
{
	if(Priority <= 9 && Location <= 9){
	sendOutput( msg.time(), lout, Location ) ;
	sendOutput( msg.time(), pout, Priority ) ;
	}
	return *this ;
}
