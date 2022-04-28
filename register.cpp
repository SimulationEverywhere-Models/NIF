/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()

*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "filter.h"
#include "write.h"
#include "display.h"
#include "account.h"
#include "refresh.h"
#include "datageneration.h"


void MainSimulator::registerNewAtomics()
{

	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Filter>(), "Filter" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Write>(), "Write" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Display>(), "Display" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Datageneration>(), "Datageneration" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Account>(), "Account" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Refresh>(), "Refresh" ) ;


}
