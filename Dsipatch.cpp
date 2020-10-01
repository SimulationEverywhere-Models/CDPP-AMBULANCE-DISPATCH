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
#include "Dispatch.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include <string>
const int max_length = 3;
int trucks[max_length][max_length];


/** public functions **/

/*******************************************************************
* Function Name: Dispatch
* Description: Returns Location and Priority
********************************************************************/
Dispatch::Dispatch( const string &name )
: Atomic( name )
, lin( addInputPort( "lin" ) )
, pin( addInputPort( "pin" ) )
, refresh_in( addInputPort( "refresh_in" ) )
, ambulance_out( addOutputPort( "ambulance_out" ) )
, time_out( addOutputPort( "time_out" ) )
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
Model &Dispatch::initFunction()
{
	int i = 0;
	int j = 0;
	for(i = 0; i <= max_length; i++){
		for(j =0; j <= max_length; j++){
			trucks[i][j] = 1;
	}
	}

	this-> passivate();
	Ambulance = 0;
	Response_Time = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Dispatch::externalFunction( const ExternalMessage &msg )
{


	if( msg.port() == lin )
	{
		Ambulance = (static_cast < int > (msg.value()));
		holdIn( active, preparationTime );
	}
	if( msg.port() == pin )
	{
		Response_Time = static_cast < int > (msg.value());
		holdIn( active, preparationTime );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Dispatch::internalFunction( const InternalMessage & )
{

		passivate();
		return *this ;

}
/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Dispatch::outputFunction( const InternalMessage &msg )
{
	double distance = 0;
	double min_distance = 9.99;
	int i;
	int j;
	int min_i = 9;
	int min_j = 9;
	int temp_i = 0;
	int temp_j = 0;

	if( Response_Time < 10 && Ambulance < 10){
	if(Ambulance != 0){

		if(Ambulance == 1){
			temp_i = 1;
			temp_j = 1;
		}
		if(Ambulance == 2){
			temp_i = 2;
			temp_j = 1;
		}
		if(Ambulance == 3){
			temp_i = 3;
			temp_j = 1;
		}
		if(Ambulance == 4){
			temp_i = 1;
			temp_j = 2;
		}
		if(Ambulance == 5){
			temp_i = 2;
			temp_j = 2;
		}
		if(Ambulance == 6){
			temp_i = 3;
			temp_j = 2;
		}
		if(Ambulance == 7){
			temp_i = 1;
			temp_j = 3;
		}
		if(Ambulance == 8){
			temp_i = 2;
			temp_j = 3;
		}
		if(Ambulance == 9){
			temp_i = 3;
			temp_j = 3;
		}
		for( i = 1; i <= max_length; i++){
			for( j = 1; j <= max_length; j++){
				if(trucks[i][j] != 0 ){
					distance =  sqrt( (temp_i - i)*(temp_i - i) + (temp_j - j)*(temp_j - j) );
					if(distance < min_distance){
						min_distance = distance;
						min_i = i;
						min_j = j;
					}


				}

			}
		}

		if(min_i == 1 && min_j == 1){
			Ambulance = 1;
		}
		if(min_i == 2 && min_j == 1){
			Ambulance = 2;
		}
		if(min_i == 3 && min_j == 1){
			Ambulance = 3;
		}
		if(min_i == 1 && min_j == 2){
			Ambulance = 4;
		}
		if(min_i == 2 && min_j == 2){
			Ambulance = 5;
		}
		if(min_i == 3 && min_j == 2){
			Ambulance = 6;
		}
		if(min_i == 1 && min_j == 3){
			Ambulance = 7;
		}
		if(min_i == 2 && min_j == 3){
			Ambulance = 8;
		}
		if(min_i == 3 && min_j == 3){
			Ambulance = 9;
		}
		}
	if(min_i == 9 && min_j == 9 && min_distance == 9.99){
		Ambulance = 0;
		Response_Time = 0;
	}else {

		trucks[min_i][min_j] = 0;
		Response_Time = (30*min_distance + 60)*(10/Response_Time + 1);

	}

	sendOutput( msg.time(), ambulance_out, Ambulance ) ;
	sendOutput( msg.time(), time_out, Response_Time ) ;

	if( Ambulance == 0 && Response_Time == 0){
		for(i = 0; i <= max_length; i++){
			for(j =0; j <= max_length; j++){
				trucks[i][j] = 1;
		}
		}
	}
	}

	return *this ;

	}
