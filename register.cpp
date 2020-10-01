#include "modeladm.h"
#include "mainsimu.h"
#include "CallerINFO.h"        // class Receiver
#include "Dispatch.h"
#include "Response.h"
#include "Queue.h"
#include "Generat.h"
//#include "Refresh.h"
//#include "CallLength.h"
void MainSimulator::registerNewAtomics()
{

	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CallerINFO>(), "CallerINFO" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Dispatch>(), "Dispatch" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Response>(), "Response" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
//	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Refresh>() , "Refresh" ) ;
}
