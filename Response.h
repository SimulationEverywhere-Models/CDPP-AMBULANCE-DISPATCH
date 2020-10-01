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

#ifndef __Response_H
#define __Response_H

#include "atomic.h"     // class Atomic

class Response : public Atomic
{
public:
	Response ( const string &name = "Response" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &priority_in;
	Port &time_in;
	Port &response_out;
	Time preparationTime;
	int Outcome;
	int Priority;
	int Response_Time;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

	Time timeLeft;
	Time arrival_time;
};	// class Receiver

// ** inline ** //
inline
string Response::className() const
{
	return "Response" ;
}

#endif   //__Response_H
