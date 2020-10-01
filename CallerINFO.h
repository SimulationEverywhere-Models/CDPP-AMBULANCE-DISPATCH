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

#ifndef __CallerINFO_H
#define __CallerINFO_H

#include "atomic.h"     // class Atomic

class CallerINFO : public Atomic
{
public:
	CallerINFO ( const string &name = "CallerINFO" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &callin;
	Port &lout;
	Port &pout;
	Time preparationTime;
	int Location;
	int Priority;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

//	Time timeLeft;

};	// class Receiver

// ** inline ** //
inline
string CallerINFO::className() const
{
	return "CallerINFO" ;
}

#endif   //__RECEIVER_H
