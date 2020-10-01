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

#ifndef __Dispatch_H
#define __Dispatch_H

#include "atomic.h"     // class Atomic
#include <string>
class Dispatch : public Atomic
{
public:
	Dispatch ( const string &name = "Dispatch" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &lin;
	Port &pin;
	Port &refresh_in;
	Port &ambulance_out;
	Port &time_out;
	Time preparationTime;
	int Ambulance;
	int Response_Time;
	int Refresh;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

//	Time timeLeft;

};	// class Receiver

// ** inline ** //
inline
string Dispatch::className() const
{
	return "Dispatch" ;
}

#endif   //__RECEIVER_H
